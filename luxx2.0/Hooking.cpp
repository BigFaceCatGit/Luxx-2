#include "stdafx.h"
#include "PolyHook.hpp"

HANDLE mainFiber;
DWORD wakeAt;

static CHooking::NativeRegistration** m_registrationTable;
static std::unordered_map<uint64_t, CHooking::NativeHandler> m_handlerCache;

eGameState* CHooking::m_gameState;
CBlipList* CHooking::m_blipList;
__int64** CHooking::m_globalBase;
CPlayers* CHooking::m_players;
void* CHooking::m_nativeTable;

/* store our native once we find it */
static LPVOID m_hookNative;

/* private declerations */
bool initHook();
void initPatterns();

void CHooking::init()
{
	CLog::Message("Hooks are being initialized");

	/* find patterns and what not */
	initPatterns();

	/* if hooking fails */
	if (!initHook()) {
		CLog::Error("Failed to hook native(s).");
	}

	/* if code reaches here, then everything is fine */
	CLog::Message("Hooks are done.");
}

void __stdcall script(LPVOID lpParameter)
{
	try {
		while (1) {
			CHack::mainLoop();
			SwitchToFiber(mainFiber);
		}
	}
	catch (...)
	{
		CLog::Fatal("script failed");
	}
}

/* For the love of god please change this */
void CHooking::onTick()
{
	if (mainFiber == nullptr) {
		mainFiber = ConvertThreadToFiber(nullptr);

		if (mainFiber == nullptr)
		{
			mainFiber = GetCurrentFiber();
		}
	}

	if (timeGetTime() < wakeAt)
		return;

	/* grabbed from sudo cause I got pissed */
	static HANDLE scriptFiber;
	if (scriptFiber)
		SwitchToFiber(scriptFiber);
	else
		scriptFiber = CreateFiber(NULL, script, nullptr);
}

typedef void(__cdecl* APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT)();
APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT HookedFunction = nullptr;

CHooking::NativeHandler ORIG_APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT = nullptr;
void* __cdecl HK_APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT(NativeContext* cxt)
{
	CHooking::onTick();
	return cxt;
}

PLH::X64Detour* nativeHook;

bool initHook()
{
	nativeHook = new PLH::X64Detour();
	nativeHook->SetupHook(
		reinterpret_cast<BYTE*>(m_hookNative),
		reinterpret_cast<BYTE*>(HK_APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT)
	);
	nativeHook->Hook();
	HookedFunction = nativeHook->GetOriginal<APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT>();

	CLog::Message("Native signature hooked.");

	return true;
}

void failPattern(const char* name)
{
	CLog::Error("Failed to find %s", name);

	/* do cleanup here if we want to */
}

/* get our globals lad */
__int64* CHooking::getGlobalPtr(int index)
{
	return &m_globalBase[index >> 0x12 & 0x3F][index & 0x3FFFF];
}

void WAIT(DWORD ms)
{
	wakeAt = timeGetTime() + ms;
	SwitchToFiber(mainFiber);
}

/*
Taken mostly from sub1to. Credits to him, regardless.
Change this when we got time.
*/
template <typename T>
void findPattern(
	const char* name,
	char* pat,
	char* mask,
	T** out,
	bool rel,
	int offset = 0,
	int deref = 0,
	int skip = 0
)
{
	T* ptr = nullptr;

	CPattern pattern(pat, mask);
	pattern.find(1 + skip);
	if (rel)
		ptr = pattern.get(skip).get_rel<T>(offset);
	else
		ptr = pattern.get(skip).get<T>(offset);

	while (true)
	{
		if (ptr == nullptr)
			failPattern(name);

		if (deref <= 0)
			break;
		ptr = *(T**)ptr;
		--deref;
	}

	*out = ptr;
	return;
}

void initPatterns() // 48 8B 05 00 00 00 00 4C 8B 68 08 4C 89 AD D8 03 00 00 4D 85 ED 0F 84 93 04 00 00 8D 4B 0F 48 8D
{
	/* find world */
	findPattern("world", "\x48\x8B\x05\x00\x00\x00\x00\x4C\x8B\x68\x08\x4C\x89\xAD\xD8\x03\x00\x00\x4D\x85\xED\x0F\x84\x93\x04\x00\x00\x8D\x4B\x0F\x48\x8D",
		"xxx????xxxxxxxxxxxxxxxxxxxxxxxxx",
		&CHack::m_pCWorld, true, 3, 1);

	/* find gamestate */
	findPattern("gamestate", "\x8B\x05\x00\x00\x00\x00\x33\xED\x8B\xF2",
		"xx????xxxx", &CHooking::m_gameState, true, 2);

	/* find blips */
	findPattern("blips", "\x4C\x8D\x05\x00\x00\x00\x00\x0F\xB7\xC1", "xxx????xxx", &CHooking::m_blipList, true, 3);

	/* find global */
	findPattern("global", "\x4C\x8D\x05\x00\x00\x00\x00\x4D\x8B\x08\x4D\x85\xC9\x74\x11", "xxx????xxxxxxxx", &CHooking::m_globalBase, true, 3);

	/* find the playerlist */
	findPattern("playerlist", "\x48\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xC8\xE8\x00\x00\x00\x00\x48\x8B\xCF",
		"xxx????x????xxxx????xxx", &CHooking::m_players, true, 3);

	char* c_ptr = nullptr;
	void* v_ptr = nullptr;

	/* find native table */
	CPattern pattern_native_table("\x76\x61\x49\x8B\x7A\x40\x48\x8D\x0D", "xxxxxxxxx");
	c_ptr = pattern_native_table.find(0).get(0).get<char>(9);
	c_ptr == nullptr ? CLog::Error("Could not find native table") : m_registrationTable = reinterpret_cast<decltype(m_registrationTable)>(c_ptr + *(int32_t*)c_ptr + 4);

	/* model bypass */
	CPattern pattern_modelCheck("\x48\x85\xC0\x0F\x84\x00\x00\x00\x00\x8B\x48\x50",
		"xxxxx????xxx");
	c_ptr = pattern_modelCheck.find(0).get(0).get<char>(0);
	c_ptr == nullptr ? CLog::Error("Failed to find model check") : mem_nop(c_ptr, 24);

	CPattern pattern_modelSpawn("\x48\x8B\xC8\xFF\x52\x30\x84\xC0\x74\x05\x48",
		"xxxxxxxxxxx");
	c_ptr = pattern_modelSpawn.find(0).get(0).get<char>(8);
	c_ptr == nullptr ? CLog::Error("Failed to find is player model allowed to spawn bypass pattern") : mem_nop(c_ptr, 2);

	/* game legals */
	CPattern pattern_gameLegals("\x72\x1F\xE8\x00\x00\x00\x00\x8B\x0D", "xxx????xx");
	v_ptr = pattern_gameLegals.find(0).get(0).get<void>(0);
	v_ptr == nullptr ? CLog::Error("Failed to nop game legals") : mem_nop(v_ptr, 2);

	/* game logos */
	CPattern  pattern_gameLogos("\x70\x6C\x61\x74\x66\x6F\x72\x6D\x3A", "xxxxxxxxx");
	v_ptr = pattern_gameLogos.find(0).get(0).get<void>(0);
	v_ptr == nullptr ? CLog::Error("Failed to nop game logos") : mem_nop(v_ptr, 2);

	/*
	Original sig to the function
	\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x20\x8B\x0D\x00\x00\x00\x00\xE8\x00\x00\x00\x00
	xxxx?xxxxxxx????x????

	Another useful sig
	\x50\x5C\x48\x89\x1C\x24\x48\x83\xEC\x20\x48\x89\x4C\x24\x00\x48\x8D\x64\x24\x00\x48\x8B\x1C\x24\x48\x8D\x64\x24\x00\xE9\x00\x00\x00\x00\x48\x8B\x04\x24
	xxxxxxxxxxxxxx?xxxx?xxxxxxxx?x????xxxx
	*/

	/* find our native to hook. IIRC it was APP_HAS_LINKED_SOCIAL_CLUB_ACCOUNT */
	CPattern pattern_app_has_linked_social_club_account("\x50\x5C\x48\x89\x1C\x24\x48\x83\xEC\x20\x48\x89\x4C\x24\x00\x48\x8D\x64\x24\x00\x48\x8B\x1C\x24\x48\x8D\x64\x24\x00\xE9\x00\x00\x00\x00\x48\x8B\x04\x24",
		"xxxxxxxxxxxxxx?xxxx?xxxxxxxx?x????xxxx");
	v_ptr = pattern_app_has_linked_social_club_account.find(0).get(0).get<void>(0);
	v_ptr == nullptr ? CLog::Error("Failed to find native signature") : m_hookNative = v_ptr;

	CLog::Message("Done finding pattern(s).");

	/* init our native native hash map */
	CrossMapping::initNativeMap();

	/* if code reaches here, then we're gucci */
	CLog::Message("Done.");
}

static CHooking::NativeHandler _Handler(uint64_t origHash) {

	uint64_t newHash = CrossMapping::MapNative(origHash);
	if (newHash == 0) {
		return nullptr;
	}

	CHooking::NativeRegistration * table = m_registrationTable[newHash & 0xFF];

	for (; table; table = table->nextRegistration)
	{
		for (uint32_t i = 0; i < table->numEntries; i++)
		{
			if (newHash == table->hashes[i])
			{
				return table->handlers[i];
			}

		}
	}

	return nullptr;
}

CHooking::NativeHandler CHooking::GetNativeHandler(uint64_t origHash)
{
	auto& handler = m_handlerCache[origHash];

	if (handler == nullptr)
	{
		handler = _Handler(origHash);
	}

	return handler;
}

typedef HRESULT(__stdcall *D3D11PresentHook) (IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
typedef void(__stdcall *D3D11DrawIndexedHook) (ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
typedef void(__stdcall *D3D11ClearRenderTargetViewHook) (ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4]);

ID3D11Device *pDevice = NULL;
ID3D11DeviceContext *pContext = NULL;

IDXGISwapChain* pSwapChain;
DWORD_PTR* pSwapChainVtable = NULL;
DWORD_PTR* pDeviceContextVTable = NULL;

IFW1Factory *pFW1Factory = NULL;
IFW1FontWrapper *pFontWrapper = NULL;

// for our trampline
D3D11PresentHook phookD3D11Present = NULL;
D3D11DrawIndexedHook phookD3D11DrawIndexed = NULL;
D3D11ClearRenderTargetViewHook phookD3D11ClearRenderTargetView = NULL;

bool firstTime = true;
bool drawBox = false;

// colours for our fontwrapper 
#pragma region hex colours
constexpr DWORD ORANGE{ 0xFF00BFFF };
constexpr DWORD BLACK{ 0xFF000000 };
constexpr DWORD WHITE{ 0xFFFFFFFF };
constexpr DWORD GREEN{ 0xFF00FF00 };
constexpr DWORD RED{ 0xFFFF0000 };
constexpr DWORD GRAY{ 0xFF2F4F4F };
constexpr DWORD PINK{ 0xffff00b6 };
constexpr DWORD LIGHTRED{ 0xffe27a7a };
constexpr DWORD LIGHTBLUE{ 0xff1caecc }; // ??? For some reason it aint lightblue
#pragma endregion;

HRESULT __stdcall hookD3D11Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{
	if (firstTime) {
		pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pContext);

		FW1CreateFactory(FW1_VERSION, &pFW1Factory);
		pFW1Factory->CreateFontWrapper(pDevice, L"Futura Md BT Medium", &pFontWrapper);

		pSwapChain->GetDevice(__uuidof(pDevice), (void**)&pDevice);

		pFW1Factory->Release();

		firstTime = false;
	}
	pFontWrapper->DrawString(pContext, L"POLYHOOK BIATCH", 12.0f, 14.0f, 16.0f, LIGHTRED, FW1_RESTORESTATE);

	return phookD3D11Present(pSwapChain, SyncInterval, Flags);
}

void __stdcall hookD3D11DrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
{
	return phookD3D11DrawIndexed(pContext, IndexCount, StartIndexLocation, BaseVertexLocation);
}

void __stdcall hookD3D11ClearRenderTargetView(ID3D11DeviceContext* pContext, ID3D11RenderTargetView *pRenderTargetView, const FLOAT ColorRGBA[4])
{
	return phookD3D11ClearRenderTargetView(pContext, pRenderTargetView, ColorRGBA);
}

PLH::X64Detour* presentHook;
PLH::X64Detour* drawIndexedHook;
PLH::X64Detour* clearRenderTargetHook;

DWORD __stdcall Init(LPVOID)
{
	HWND hwnd = GetForegroundWindow();

	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;//((GetWindowLong(hWnd, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, &featureLevel, 1
		, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext)))
	{
		MessageBox(hwnd, (LPCWSTR)"Failed to create directX device and swapchain!", (LPCWSTR)"uBoos?", MB_ICONERROR);
		return NULL;
	}

	pSwapChainVtable = (DWORD_PTR*)pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];

	pDeviceContextVTable = (DWORD_PTR*)pContext;
	pDeviceContextVTable = (DWORD_PTR*)pDeviceContextVTable[0];

	presentHook = new PLH::X64Detour();
	presentHook->SetupHook((BYTE*)pSwapChainVtable[8], (BYTE*)hookD3D11Present);
	presentHook->Hook();
	phookD3D11Present = presentHook->GetOriginal<D3D11PresentHook>();

	drawIndexedHook = new PLH::X64Detour();
	drawIndexedHook->SetupHook((BYTE*)pDeviceContextVTable[12], (BYTE*)hookD3D11DrawIndexed);
	drawIndexedHook->Hook();
	phookD3D11DrawIndexed = drawIndexedHook->GetOriginal<D3D11DrawIndexedHook>();

	clearRenderTargetHook = new PLH::X64Detour();
	clearRenderTargetHook->SetupHook((BYTE*)pDeviceContextVTable[50], (BYTE*)hookD3D11ClearRenderTargetView);
	clearRenderTargetHook->Hook();
	phookD3D11ClearRenderTargetView = clearRenderTargetHook->GetOriginal<D3D11ClearRenderTargetViewHook>();

	pDevice->Release();
	pContext->Release();
	pSwapChain->Release();

	return NULL;
}

void CHooking::unLoad()
{
	//unhook main game
	nativeHook->UnHook();

	//unload FW1FontWrapper
	if (pFontWrapper) {
		pFontWrapper->Release();
	}

	//unload d3d
	presentHook->UnHook();
	drawIndexedHook->UnHook();
	clearRenderTargetHook->UnHook();

	CLog::Message("Unhooking successful.");
	NativeMenu::CMenu::drawSubtitle("Unloading...");

	//not really needed, unless you want it for debugging
	//MessageBox(nullptr, "Unhooked sucessfully", "Success!", MB_OK);
}