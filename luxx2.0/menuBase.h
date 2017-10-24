#ifndef ALPHA_MENU_BASE_H
#define ALPHA_MENU_BASE_H

class CMenu;

namespace NativeMenu {
	/*
	string to char
	http://stackoverflow.com/questions/36789380/how-to-store-a-const-char-to-a-char
	*/
	class CharAdapter {
	public:
		explicit CharAdapter(const char* s) : m_s(::_strdup(s)) { }
		explicit CharAdapter(std::string str) : m_s(::_strdup(str.c_str())) { }

		CharAdapter(const CharAdapter& other) = delete; // non construction-copyable
		CharAdapter& operator=(const CharAdapter&) = delete; // non copyable

		~CharAdapter() /*free memory on destruction*/ {
			::free(m_s); /*use free to release strdup memory*/
		}
		operator char*() /*implicit cast to char* */ {
			return m_s;
		}

	private:
		char* m_s;
	};

	struct RGBA {
		int r, g, b, a;
	};

#define MenuFunc void __cdecl
	MenuFunc MAIN_MENU();

	typedef void(__cdecl* SubmenuHandler)();

	extern bool bspawninvehicle;
	extern bool bdeletevehicle;

	class CMenu
	{
	public:
		CMenu(bool unk);
		CMenu(Variables::CPlayer &m_player, Variables::CWeapon &m_weapon, Variables::CMisc &m_misc, Variables::CNetwork &m_network, Variables::CVehicle &m_vehicle);
		~CMenu();
		
		Variables::CPlayer* p_player;
		Variables::CWeapon* p_weapon;
		Variables::CMisc* p_misc;
		Variables::CNetwork* p_network;
		Variables::CVehicle* p_vehicle;

		void nextOption();
		void previousOption();
		static void drawSubtitle(char* text);

		bool currentMenu(void* current);
		void changeSubmenu(void* newSubmenu);

		void PrintText(std::string text, int font, float x, float y, float scaleX, float scaleY, RGBA rgba, int position, bool outline);
		void DrawRect(float x, float y, float width, float height, RGBA rbga);
		void DrawSprite(std::string textureDict, std::string textureName, float x, float y, float width, float height, float rotation, RGBA rgba);
		void DrawGlare(float pX, float pY, float sX, float sY, RGBA rgba);
		void menuBeep(std::string sound);

		void Title(std::string title, std::string textureDict = {}, std::string textureName = {});
		bool Submenu(std::string text, void* submenu, std::vector<std::string> details, void* sqaureMenu = {});
		bool HotKey(std::function<void()> function, DWORD hotKey);
		bool Option(std::string text, std::vector<std::string> details = {});
		bool OptionCallBack(std::string text, std::function<void()> function, std::vector<std::string> details = {});
		bool Toggle(std::string text, bool* boolean, std::vector<std::string> details = {});
		bool ToggleCallback(std::string text, bool* boolean, std::function<void()> trueFunc, std::function<void()> falseFunc, std::vector<std::string> details = {});
		bool Int(std::string text, int* var, int min, int max, int step = 1, std::vector<std::string> details = {});
		bool Float(std::string text, float* var, float min, float max, float step = 0.1f, std::vector<std::string> details = {});
		bool Teleport(std::string text, Vector3_t location);
		bool Weapon(std::string weapon);
		bool AddFavourite(Hash model, std::string name);
		bool aVehicle(std::string name, Hash model);
		bool VehicleModType(Vehicle vehicle, int modType, void* mRef);
		bool VehicleMod(int modValue);
		bool aPlayer(char * name, Player player, void* submenu);

		void DrawDetails(std::vector<std::string> details, float y);

		void OpenMenuMonitor();
		void ClosedMenuMonitor();
		void resetButtonState();
		void disableKeys();
		int getOption();
		std::string show_keyboard(char * title_id, char * prepopulated_text);

		void Main();
		void DrawMenu();

		std::vector<std::string> TextureNames = {
			"",
			"gradient_nav",
			"interaction_bgd",
			"gradient_bgd",
			"gradient_nav",
		};
		std::vector<std::string> TextureDicts = {
			"",
			"commonmenu",
			"commonmenu",
			"commonmenu",
			"commonmenu",
		};

		int TitleTextureIndex = 0;
		int BackgTextureIndex = 3; //3
		int HighlTextureIndex = 0; //4

		float footerOffset = 0.003f;

		RGBA titleText = { 200, 200, 200, 255 };
		RGBA optionCounterColour = { 240, 128, 128, 255 }; //{ 255, 255, 255, 255 }
		RGBA mainColour = { 30, 144, 255, 255 };
		RGBA scroller = { 255, 255, 255, 255 };
		RGBA secondTitleText = { 240, 128, 128, 255 }; // 200, 200, 200, 255
		RGBA thirdTitleText = { 240, 128, 128, 255 };
		RGBA titleRect = { 14, 14, 14, 230 };
		RGBA titleSpriteRect = { 190, 190, 190, 230 };
		RGBA secondRect = { 8, 8, 8, 230 };
		RGBA options = { 200, 200, 200, 255 };
		RGBA optionsBlack = { 0, 0, 0, 255 };
		RGBA indicators = { 240, 128, 128, 255 };
		RGBA white = { 255, 255, 255, 255 };

		/* REASSIGNABLE KEYBINDS */
		DWORD openKey = VK_MULTIPLY;
		DWORD backKey = VK_NUMPAD0;
		DWORD selectKey = VK_NUMPAD5;
		DWORD upKey = VK_NUMPAD8;
		DWORD downKey = VK_NUMPAD2;
		DWORD leftKey = VK_NUMPAD4;
		DWORD rightKey = VK_NUMPAD6;
		DWORD squareKey = VK_NUMPAD7;
		DWORD upgradeKey = VK_ADD;
		DWORD repairKey = VK_DIVIDE;
		DWORD unloadKey = VK_INSERT;
		DWORD teleKey = VK_SUBTRACT;
		DWORD ejectKey = 0x51; //Q
		DWORD ragdollKey = 0x52; //R

		/* speedo settings */
		int gauge = 1;
		bool loop_chr0m3Speedo = false;
		int speedoPos = 1;

		/* ESP Settings */
		bool flatEsp = true;

		/* Online Variables */
		bool trackPlayer[32];
		bool explodePlayer[32];
		bool freezePlayer[32];
		bool fuckCamera[32];
		bool forcefield[32];
		bool moneyDrop[32];
		bool annoyLoop[32];
		bool killPed[32];
		unsigned int ExplodeDelay, StealthDelay;

		bool gotoFav = true;

	private:
		/* dis is cheeky. This lets us organize where we want to draw what. */
		typedef std::vector<std::function<void(void)>> functionList;
		functionList backgroundDrawCalls;
		functionList highlightsDrawCalls;
		functionList foregroundDrawCalls;

		/* Vector of details. We can use this to size our infobox and make it size automatically. */
		std::vector<std::string> details;

		/* for our subswitcher handler whatever */
		SubmenuHandler currentSubmenu;
		int submenuLevel;
		int lastOption[20];
		SubmenuHandler lastSubmenu[20];

		int optionsrectAlpha = 0;
		RGBA optionsrect = { 14, 14, 14, 56 };

		float globex = 0.563f;
		float globey = 0.507f;
		float globeSzX = 0.981f;
		float globeSzY = 0.960f;
		RGBA globeColor = { 200, 200, 200, 255 };

		int titleFont = 1;
		float menux = 0.227f;
		float menuy = 0.125f;
		float secondTitleX = 0.110f;
		float secondTitleY = 0.0340f;
		float thirdTitleX = 0.110f;
		float thirdTitleY = 0.0340f;

		float barunderRect = 0.17650f;

		float optionHeight = 0.035f;
		float menuWidth = 0.23f;
		float titleHeight = 0.085f;
		float menuTextMargin = 0.0060f; //75
		float optionTextSize = 0.45f;
		float mainoptiony = 0.03250f;
		float optionRightMargin = 0.015f;
		float textureTextOffset = 0.05f;

		int optionCount = 0;
		int currentOption = 0;
		bool optionPress = false;
		bool sqaurePress = false;
		bool leftPress = false;
		bool rightPress = false;
		bool upPress = false;
		bool downPress = false;
	};
}

#endif