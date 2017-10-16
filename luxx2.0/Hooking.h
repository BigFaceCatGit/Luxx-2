#pragma once

class CHooking;

class CHooking {
public:
	/* Native function handler */
	typedef void(__cdecl * NativeHandler)(scrNativeCallContext * context);
	struct NativeRegistration
	{
		NativeRegistration * nextRegistration;
		CHooking::NativeHandler handlers[7];
		uint32_t numEntries;
		uint64_t hashes[7];
	};
	static NativeHandler GetNativeHandler(uint64_t origHash);

	/* where all the magic stats*/
	static void init();
	static void onTick();
	static void unLoad();

	/* our reclass structs */
	static eGameState* m_gameState;
	static CBlipList* m_blipList;
	static void* m_nativeTable;
	static __int64** m_globalBase;
	static CPlayers* m_players;

	/* our globals */
	static __int64*	getGlobalPtr(int index);
};

DWORD __stdcall Init(LPVOID);
void WAIT(DWORD ms);
