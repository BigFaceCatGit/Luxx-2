#include "stdafx.h"
#include "webFunctions.h"


namespace Features {

	NativeMenu::CMenu l_menu(1);
	/* Initiate Ini Stuff */
	Ini config("config");
	Ini fVeh("favourite", "LUXX\\Vehicles\\");
	Ini theme("theme");

	/* private declerations */
	void giveWeaponAddon(Ped ped, Hash weapon);

	Hash CUtil::$(std::string str) {
		std::string lowerNative = str;
		transform(lowerNative.begin(), lowerNative.end(), lowerNative.begin(), ::tolower);
		Hash num = 0;
		const char* bytes = lowerNative.c_str();;
		int length = strlen(bytes);
		for (int i = 0; i < length; i++)
		{
			num += bytes[i];
			num += num << 10;
			num ^= num >> 6;
		}
		num += num << 3;
		num ^= num >> 11;
		return (num + (num << 15));
	}

	void  CUtil::notifyMap(std::string msg, BOOL blink) {
		UI::SET_TEXT_OUTLINE();
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(&msg[0u]);
		UI::_DRAW_NOTIFICATION(blink, FALSE);
	}

	void  CUtil::notifyError(std::string msg) {
		CUtil::notifyMap("~r~Error: ~w~" + msg, 0);
	}

	void  CUtil::notifyBottom(char* msg)
	{
		//if (menuXCoord == 0.845f)
		{
			UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
			UI::_ADD_TEXT_COMPONENT_SCALEFORM(msg);
			UI::END_TEXT_COMMAND_PRINT(2000, 1);
		}
	}

	void  CUtil::notifyClan(char* msg)
	{
		UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(msg);
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("CHAR_SOCIAL_CLUB", "CHAR_SOCIAL_CLUB", 1, 7, "~b~LUXX Menu", "~c~Boi", 1, "___GTA*", 9, 0);
		UI::_DRAW_NOTIFICATION(3000, 1);
	}

	char str[69];
	char* CUtil::AddStrings(char* string1, char* string2)
	{
		memset(str, 0, sizeof(str));
		strcpy_s(str, "");
		strcpy_s(str, string1);
		strcat_s(str, string2);
		return str;
	}

	int CUtil::StringToInt(char* text)
	{
		int tempp;
		if (text == "") return NULL;
		if (GAMEPLAY::STRING_TO_INT(text, &tempp)) return NULL;

		return tempp;
	}

	std::string CUtil::IntToString(int integer) {
		std::ostringstream ss;
		ss << integer;
		std::string str(ss.str());
		return str;
	}

	std::string CUtil::FloatToString(float flt) {
		std::ostringstream ss;
		ss << flt;
		std::string str(ss.str());
		return str;
	}

	float CUtil::StringToFloat(std::string str) {
		return ::atof(str.c_str());
	}

	DWORD CUtil::StringToDWORD(std::string str) {
		DWORD doubleWord;
		std::string dwordHexString = str;
		std::stringstream dwordStream;
		dwordStream << dwordHexString;
		dwordStream >> std::hex >> doubleWord;
		return doubleWord;
	}

	std::string CUtil::DocumentsPath(bool trailing = 1) {
		wchar_t Folder[1024];
		HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
		if (SUCCEEDED(hr))
		{
			char str[1024];
			wcstombs(str, Folder, 1023);
			if (trailing)
				return CUtil::AddStrings(str, "\\");
			else return str;
		}
		else return "";
	}

	void CUtil::WriteINI(std::string section, std::string key, std::string value)
	{
		std::string iniPath = CUtil::DocumentsPath(1) + "LUXX\\config.ini";
		if (!std::ifstream(iniPath)) std::ofstream file(iniPath);
		WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), iniPath.c_str());
	}

	void CUtil::WriteINIRGBA(NativeMenu::RGBA rgba, std::string section, std::string key) {
		CUtil::WriteINI(section, key + "R", IntToString(rgba.r));
		CUtil::WriteINI(section, key + "G", IntToString(rgba.g));
		CUtil::WriteINI(section, key + "B", IntToString(rgba.b));
		CUtil::WriteINI(section, key + "A", IntToString(rgba.a));
	}

	void CUtil::WriteMenuColorDefault() {
		CUtil::WriteINI("Menu Title Box", "Red", "0");
		CUtil::WriteINI("Menu Title Box", "Green", "0");
		CUtil::WriteINI("Menu Title Box", "Blue", "0");
		CUtil::WriteINI("Menu Title Box", "Alpha", "210");
		//
		CUtil::WriteINI("Menu Background", "Red", "20");
		CUtil::WriteINI("Menu Background", "Green", "20");
		CUtil::WriteINI("Menu Background", "Blue", "20");
		CUtil::WriteINI("Menu Background", "Alpha", "190");
		//
		CUtil::WriteINI("Menu Title Text", "Red", "255");
		CUtil::WriteINI("Menu Title Text", "Green", "255");
		CUtil::WriteINI("Menu Title Text", "Blue", "255");
		CUtil::WriteINI("Menu Title Text", "Alpha", "255");
		//
		CUtil::WriteINI("Menu Options Text", "Red", "255");
		CUtil::WriteINI("Menu Options Text", "Green", "255");
		CUtil::WriteINI("Menu Options Text", "Blue", "255");
		CUtil::WriteINI("Menu Options Text", "Alpha", "255");
		////
		CUtil::WriteINI("Menu Selected Text", "Red", "255");
		CUtil::WriteINI("Menu Selected Text", "Green", "255");
		CUtil::WriteINI("Menu Selected Text", "Blue", "255");
		CUtil::WriteINI("Menu Selected Text", "Alpha", "255");
		//
		CUtil::WriteINI("Menu Option Break", "Red", "255");
		CUtil::WriteINI("Menu Option Break", "Green", "255");
		CUtil::WriteINI("Menu Option Break", "Blue", "255");
		CUtil::WriteINI("Menu Option Break", "Alpha", "240");
		//
		CUtil::WriteINI("Menu Options Count", "Red", "255");
		CUtil::WriteINI("Menu Options Count", "Green", "255");
		CUtil::WriteINI("Menu Options Count", "Blue", "255");
		CUtil::WriteINI("Menu Options Count", "Alpha", "255");
		//
		CUtil::WriteINI("Menu Selection Box", "Red", "255");
		CUtil::WriteINI("Menu Selection Box", "Green", "255");
		CUtil::WriteINI("Menu Selection Box", "Blue", "255");
		CUtil::WriteINI("Menu Selection Box", "Alpha", "140");
		//
		//Contro
	}

	void CUtil::CreateFolder(std::string path)
	{
		if (!CreateDirectoryA(path.c_str(), NULL))
		{
			return;
		}
	}

	void CUtil::WriteLocINI(std::string section, std::string key, std::string value)
	{
		//CreateFolder(DocumentsPath() + "LUXX\\Custom Locations"))
		std::string iniPath = CUtil::DocumentsPath(1) + "LUXX\\CustomLocations.ini";
		if (!std::ifstream(iniPath)) std::ofstream file(iniPath);
		WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), iniPath.c_str());
	}

	/*void saveCustom()
	{
	std::string inputLoc = show_keyboard("HUD_TITLE", "");
	WriteLocINI(inputLoc, "Custom Loc.x", FloatToString(CustomLoc1.x));
	WriteLocINI(inputLoc, "Custom Loc.y", FloatToString(CustomLoc1.y));
	WriteLocINI(inputLoc, "Custom Loc.z", FloatToString(CustomLoc1.z));
	}
	void checkDir() {
	std::vector<std::string> files;
	int items;
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(&DocumentsPath(1)[0u])) != NULL) {
	/* print all the files and directories within directory
	while ((ent = readdir(dir)) != NULL) {
	printf("%s\n", ent->d_name);
	}
	closedir(dir);
	}
	else {
	/* could not open directory
	perror("");
	}
	}*/

	void CUtil::saveTheme(bool notify, NativeMenu::CMenu &menu) {
		theme.write_rgba(menu.titleRect, "Head", "Banner");
		theme.write_rgba(menu.titleText, "Head", "BannerTextCol");
		theme.write_rgba(menu.options, "Body", "OptionCol");
		theme.write_rgba(menu.scroller, "Body", "Scroller");
		theme.write_rgba(menu.mainColour, "Body", "Highlight");
		theme.write_rgba(menu.indicators, "Footer", "Indicator");
		//theme.write_rgba(menu.bac, "Theme", "Background");
		//WriteINI("Theme", "BannerTextureName", static_cast<ostringstream*>(&(ostringstream() << BannertextureName))->str());
		//WriteINI("Theme", "FooterTextureName", static_cast<ostringstream*>(&(ostringstream() << FootertextureName))->str());
		//WriteINI("Theme", "MaxOptions", IntToString(maxOptions));
		//WriteINI("Theme", "BannerFont", IntToString(bannerTextFont));
		//WriteINI("Theme", "OptionFont", IntToString(optionsFont));
		//WriteINI("Theme", "MenuXCoord", FloatToString(menuXCoord));
		//WriteINI("Theme", "MenuYCoord", FloatToString(menuYCoord));
		//WriteINI("Theme", "CustomTextures", IntToString(customTextures));
		//WriteINI("Theme", "MenuTextures", IntToString(drawTextures));
		//WriteINI("Theme", "CenterOptions", IntToString(optionsTextCenter));
		//WriteINI("Theme", "CenterBanner", IntToString(bannerTextCenter));
		//WriteINI("Theme", "ApplyToVehicle", IntToString(vehThemeActive));
		if (notify)
			CUtil::notifyMap("Custom Theme Saved", 0);
	}

	void CUtil::saveKeyBinds(bool notify, NativeMenu::CMenu &menu) {
		CUtil::WriteINI("KeyBinds", "openKey", IntToString(menu.openKey));
		CUtil::WriteINI("KeyBinds", "backKey", IntToString(menu.backKey));
		CUtil::WriteINI("KeyBinds", "selectKey", IntToString(menu.selectKey));
		CUtil::WriteINI("KeyBinds", "upKey", IntToString(menu.upKey));
		CUtil::WriteINI("KeyBinds", "downKey", IntToString(menu.downKey));
		CUtil::WriteINI("KeyBinds", "leftKey", IntToString(menu.leftKey));
		CUtil::WriteINI("KeyBinds", "rightKey", IntToString(menu.rightKey));
		CUtil::WriteINI("KeyBinds", "squareKey", IntToString(menu.squareKey));
		CUtil::WriteINI("KeyBinds", "upgradeKey", IntToString(menu.upgradeKey));
		CUtil::WriteINI("KeyBinds", "ejectKey", IntToString(menu.ejectKey));
		CUtil::WriteINI("KeyBinds", "ragdollKey", IntToString(menu.ragdollKey));
		if (notify)
			CUtil::notifyMap("Custom Keybinds Saved", 0);
	}

	void CUtil::saveSpeedo(bool notify, NativeMenu::CMenu &menu) {
		CUtil::WriteINI("Speedo", "Guage", IntToString(menu.gauge));
		CUtil::WriteINI("Speedo", "SpeedoActive", IntToString(menu.loop_chr0m3Speedo));
		CUtil::WriteINI("Speedo", "SpeedoPosition", IntToString(menu.speedoPos));
		CUtil::WriteINI("Speedo", "SpeedoPosition", IntToString(menu.flatEsp));
		if (notify)
			CUtil::notifyMap("Speedo Settings Saved", 0);
	}

	void CUtil::saveConfig(bool notify, NativeMenu::CMenu &menu)
	{
		CUtil::saveKeyBinds(0, menu);
		CUtil::saveSpeedo(0, menu);
		CUtil::saveTheme(0, menu);
		if (notify)
			CUtil::notifyMap("~g~All Settings Saved", 0);
	}

	/*void Clock(bool notify) {
	WriteINI("Clock", "ClockEnabled", IntToString(realtimeMod));
	WriteINI("Clock", "TimeScaleMod", IntToString(timescaleMod));
	WriteINI("Clock", "hideClockInMission", IntToString(hideClockInMission));
	WriteINI("Clock", "hideClockInVehicle", IntToString(hideClockInVehicle));
	WriteINI("Clock", "hideClockWhileAiming", IntToString(hideClockWhileAiming));
	WriteINI("Clock", "clockMilitaryTime", IntToString(clockMilitaryTime));
	WriteINI("Clock", "clockTextFont", IntToString(clockTextFont));
	WriteINI("Clock", "clockScale", FloatToString(clockScale));
	WriteINI("Clock", "clockAlignCentre", IntToString(clockAlignCentre));
	WriteINI("Clock", "clockpositionX", FloatToString(clockpositionX));
	WriteINI("Clock", "clockpositionY", FloatToString(clockpositionY));
	WriteINI("Clock", "dateAlignCentre", IntToString(dateAlignCentre));
	WriteINI("Clock", "showDate", IntToString(showDate));
	WriteINI("Clock", "datepositionX", FloatToString(datepositionX * 100));
	WriteINI("Clock", "datepositionY", FloatToString(datepositionY * 100));
	WriteINI("Clock", "dateScale", FloatToString(dateScale));
	if (notify)
	CUtil::notifyMap("Clock Settings Saved", 0);
	}
	void Smoke(bool notify) {
	WriteINI("Smoke Trail", "planesmokeEnabled", IntToString(planesmokeEnabled));
	WriteINI("Smoke Trail", "smokeSize", FloatToString(smokeSize));
	WriteINI("Smoke Trail", "smokeR", FloatToString(sr));
	WriteINI("Smoke Trail", "smokeG", FloatToString(sg));
	WriteINI("Smoke Trail", "smokeB", FloatToString(sb));
	WriteINI("Smoke Trail", "smokeX", FloatToString(sx));
	WriteINI("Smoke Trail", "smokeY", FloatToString(sy));
	WriteINI("Smoke Trail", "smokeZ", FloatToString(sz));
	WriteINI("Smoke Trail", "smokeType", IntToString(smokeType));
	if (notify)
	CUtil::notifyMap("Smoke Trail Settings Saved", 0);
	}
	void Rainbow(bool notify) {
	WriteINI("Rainbow", "rainbowActive", IntToString(rainbowActive));
	WriteINI("Rainbow", "rainbowFade", IntToString(rainbowFade));
	WriteINI("Rainbow", "rainbowBody", IntToString(rainbowBody));
	WriteINI("Rainbow", "rainbowNeon", IntToString(rainbowNeon));
	WriteINI("Rainbow", "rainbowTyre", IntToString(rainbowTyre));
	WriteINI("Rainbow", "rainbowPrimary", IntToString(rainbowPrim));
	WriteINI("Rainbow", "rainbowSecondary", IntToString(rainbowSeco));
	WriteINI("Rainbow", "rainbowMenu", IntToString(miscMenuRainbow));
	if (notify)
	CUtil::notifyMap("Rainbow Settings Saved", 0);
	}*/

	void WriteINIDefaults() {
		CUtil::CreateFolder(CUtil::DocumentsPath(1) + "LUXX");
		//CUtil::saveConfig(0);
	}

	std::string CUtil::ReadIniKey(std::string section, std::string key) {
		std::string iniPath = CUtil::DocumentsPath(1) + "LUXX\\config.ini";
		if (!std::ifstream(iniPath)) { std::ofstream file(iniPath); WriteINIDefaults(); }
		char retVal[255];
		GetPrivateProfileStringA(section.c_str(), key.c_str(), "", retVal, 255, iniPath.c_str());
		return retVal;
	}

	std::string CUtil::ReadIniKey(std::string section, std::string key, std::string fileName) {
		std::string iniPath = CUtil::DocumentsPath(1) + "LUXX\\" + fileName + ".ini";
		if (!std::ifstream(iniPath)) { std::ofstream file(iniPath); WriteINIDefaults(); }
		char retVal[255];
		GetPrivateProfileStringA(section.c_str(), key.c_str(), "", retVal, 255, iniPath.c_str());
		return retVal;
	}

	bool CUtil::DoesKeyExist(std::string fileName, std::string section, std::string key) {
		return CUtil::ReadIniKey(section, key, fileName).length() > 0;
	}

	/*int CUtil::GetNumberOfObjectFromFile(std::string name) {
		std::string iniPath = DocumentsPath(1) + "LUXX\\Map Mods\\" + name + ".ini";
		int no = 0;
		for (int i = 0; i < 150; i++) {
			if (DoesPresetKeyExists(name, FloatToString(i), "X")) {
				no++;
			}
			else {
				return no;
			}
		}
		return no;
	}*/

	NativeMenu::RGBA CUtil::ReadINIRGBA(std::string section, std::string key) {
		NativeMenu::RGBA col = { 0,0,0, 255 };
		//Check key exists to avoid crashes.
		if (!CUtil::DoesKeyExist(section, key + "R")) { CUtil::notifyMap("~r~Error:~w~ Theme failed to load. Are you sure it exists?", 0); return col; }

		//build the RGBA struct and return
		col = { std::stoi(ReadIniKey(section, key + "R")), std::stoi(ReadIniKey(section, key + "G")), std::stoi(ReadIniKey(section, key + "B")), std::stoi(ReadIniKey(section, key + "A")) };
		return col;
	}

	std::string CUtil::ReadPresetKey(std::string name, std::string section, std::string key)
	{
		std::string iniPath = DocumentsPath(1) + "LUXX\\" + name + ".ini";
		if (!std::ifstream(iniPath)) {
			CreateFolder(DocumentsPath() + "LUXX");
			CreateFolder(DocumentsPath() + "LUXX\\Vehicles");
			std::ofstream file(iniPath);
			WriteINIDefaults();
		}
		char retVal[255];
		GetPrivateProfileStringA(section.c_str(), key.c_str(), "", retVal, 255, iniPath.c_str());
		return retVal;
	}

	bool CUtil::DoesPresetKeyExists(std::string name, std::string section, std::string key) {
		return ReadPresetKey(name, section, key).length() > 0;
	}

	int CUtil::GetNumberOfObjectFromFile(std::string name) {
		std::string iniPath = DocumentsPath(1) + "SUPER DANK\\Map Mods\\" + name + ".ini";
		int no = 0;
		for (int i = 0; i < 150; i++) {
			if (DoesPresetKeyExists(name, FloatToString(i), "X")) {
				no++;
			}
			else {
				return no;
			}
		}
		return no;
	}

	void CUtil::loadTheme(bool notify, NativeMenu::CMenu* menu) {
		menu->titleRect = theme.read_rgba("Head", "Banner");
		menu->titleText = theme.read_rgba("Head", "BannerTextCol");
		menu->options = theme.read_rgba("Body", "OptionCol");
		menu->scroller = theme.read_rgba("Body", "Scroller");
		menu->mainColour = theme.read_rgba("Body", "Highlight");
		menu->indicators = theme.read_rgba("Footer", "Indicator");
		//background = theme.read_rgba("Theme", "Background");
		//BannertextureName = &ReadIniKey("Theme", "BannerTextureName")[0u];
		//FootertextureName = &ReadIniKey("Theme", "FooterTextureName")[0u];
		//maxOptions = internals::StoI(&ReadIniKey("Theme", "MaxOptions")[0u]);
		//bannerTextFont = internals::StoI(&ReadIniKey("Theme", "BannerFont")[0u]);
		//optionsFont = internals::StoI(&ReadIniKey("Theme", "OptionFont")[0u]);
		//menuXCoord = StringToFloat(ReadIniKey("Theme", "MenuXCoord"));
		//menuYCoord = StringToFloat(ReadIniKey("Theme", "MenuYCoord"));
		//customTextures = internals::StoI(&ReadIniKey("Theme", "CustomTextures")[0u]);
		//drawTextures = internals::StoI(&ReadIniKey("Theme", "MenuTextures")[0u]);
		//optionsTextCenter = internals::StoI(&ReadIniKey("Theme", "CenterOptions")[0u]);
		//bannerTextCenter = internals::StoI(&ReadIniKey("Theme", "CenterBanner")[0u]);
		//vehThemeActive = internals::StoI(&ReadIniKey("Theme", "ApplyToVehicle")[0u]);
		if (notify)
			notifyMap("Custom Theme Loaded", 0);
	}

	fVehicle CUtil::receiveVeh(int ind) {
		return fVeh.read_fav(ind);
	}

	void CUtil::loadKeyBinds(bool notify, NativeMenu::CMenu &menu) {
		menu.openKey = std::stoi(ReadIniKey("KeyBinds", "openKey"));
		menu.backKey = std::stoi(ReadIniKey("KeyBinds", "backKey"));
		menu.selectKey = std::stoi(ReadIniKey("KeyBinds", "selectKey"));
		menu.upKey = std::stoi(ReadIniKey("KeyBinds", "upKey"));
		menu.downKey = std::stoi(ReadIniKey("KeyBinds", "downKey"));
		menu.leftKey = std::stoi(ReadIniKey("KeyBinds", "leftKey"));
		menu.rightKey = std::stoi(ReadIniKey("KeyBinds", "rightKey"));
		menu.squareKey = std::stoi(ReadIniKey("KeyBinds", "squareKey"));
		menu.upgradeKey = std::stoi(ReadIniKey("KeyBinds", "upgradeKey"));
		menu.ejectKey = std::stoi(ReadIniKey("KeyBinds", "ejectKey"));
		menu.ragdollKey = std::stoi(ReadIniKey("KeyBinds", "ragdollKey"));
		if (notify)
			notifyMap("Custom Keybinds Loaded", 0);
	}

	void CUtil::loadSpeedo(bool notify, NativeMenu::CMenu &menu) {
		menu.gauge = StringToInt(&ReadIniKey("Speedo", "Guage")[0u]);
		menu.loop_chr0m3Speedo = StringToInt(&ReadIniKey("Speedo", "SpeedoActive")[0u]);
		menu.speedoPos = StringToInt(&ReadIniKey("Speedo", "SpeedoPosition")[0u]);
		menu.flatEsp = StringToInt(&ReadIniKey("Speedo", "SpeedoPosition")[0u]);
		if (notify)
			notifyMap("Speedo Settings Loaded", 0);
	}

	/*void CUtil::loadClock(bool notify) {
	realtimeMod = internals::StoI(&ReadIniKey("Clock", "ClockEnabled")[0u]);
	timescaleMod = internals::StoI(&ReadIniKey("Clock", "TimeScaleMod")[0u]);
	hideClockInMission = internals::StoI(&ReadIniKey("Clock", "hideClockInMission")[0u]);
	hideClockInVehicle = internals::StoI(&ReadIniKey("Clock", "hideClockInVehicle")[0u]);
	hideClockWhileAiming = internals::StoI(&ReadIniKey("Clock", "hideClockWhileAiming")[0u]);
	clockMilitaryTime = internals::StoI(&ReadIniKey("Clock", "clockMilitaryTime")[0u]);
	clockTextFont = internals::StoI(&ReadIniKey("Clock", "clockTextFont")[0u]);
	clockScale = StringToFloat(ReadIniKey("Clock", "clockScale"));
	clockAlignCentre = internals::StoI(&ReadIniKey("Clock", "clockAlignCentre")[0u]);
	clockpositionX = StringToFloat(ReadIniKey("Clock", "clockpositionX"));
	clockpositionY = StringToFloat(ReadIniKey("Clock", "clockpositionY"));
	dateAlignCentre = internals::StoI(&ReadIniKey("Clock", "dateAlignCentre")[0u]);
	showDate = internals::StoI(&ReadIniKey("Clock", "showDate")[0u]);
	datepositionX = StringToFloat(ReadIniKey("Clock", "datepositionX")) / 100;
	datepositionY = StringToFloat(ReadIniKey("Clock", "datepositionY")) / 100;
	dateScale = StringToFloat(ReadIniKey("Clock", "dateScale"));
	if (notify)
	notifyMap("Clock Settings Loaded", 0);
	}
	void CUtil::loadSmoke(bool notify) {
	planesmokeEnabled = internals::StoI(&ReadIniKey("Smoke Trail", "planesmokeEnabled")[0u]);
	smokeSize = StringToFloat(ReadIniKey("Smoke Trail", "smokeSize"));
	sr = StringToFloat(ReadIniKey("Smoke Trail", "smokeR"));
	sg = StringToFloat(ReadIniKey("Smoke Trail", "smokeG"));
	sb = StringToFloat(ReadIniKey("Smoke Trail", "smokeB"));
	sx = StringToFloat(ReadIniKey("Smoke Trail", "smokeX"));
	sy = StringToFloat(ReadIniKey("Smoke Trail", "smokeY"));
	sz = StringToFloat(ReadIniKey("Smoke Trail", "smokeZ"));
	smokeType = internals::StoI(&ReadIniKey("Smoke Trail", "smokeType")[0u]);
	if (notify)
	notifyMap("Smoke Trail Settings Loaded", 0);
	}
	void CUtil::loadRainbow(bool notify) {
	rainbowActive = internals::StoI(&ReadIniKey("Rainbow", "rainbowActive")[0u]);
	rainbowFade = internals::StoI(&ReadIniKey("Rainbow", "rainbowFade")[0u]);
	rainbowBody = internals::StoI(&ReadIniKey("Rainbow", "rainbowBody")[0u]);
	rainbowNeon = internals::StoI(&ReadIniKey("Rainbow", "rainbowNeon")[0u]);
	rainbowTyre = internals::StoI(&ReadIniKey("Rainbow", "rainbowTyre")[0u]);
	rainbowPrim = internals::StoI(&ReadIniKey("Rainbow", "rainbowPrimary")[0u]);
	rainbowSeco = internals::StoI(&ReadIniKey("Rainbow", "rainbowSecondary")[0u]);
	miscMenuRainbow = internals::StoI(&ReadIniKey("Rainbow", "rainbowMenu")[0u]);
	if (notify)
	notifyMap("Rainbow Settings Loaded", 0);
	}*/

	void CUtil::loadConfig(bool notify, NativeMenu::CMenu *menu) {

		//ejectForce = StringToFloat(ReadIniKey("Ejector Seat", "ejectForce"));
		//LifelessRagdoll = internals::StoI(&ReadIniKey("Ragdoll", "LifelessRagdoll")[0u]);
		//ToggleMode = internals::StoI(&ReadIniKey("Ragdoll", "ToggleMode")[0u]);
		//CUtil::loadClock(0);
		//CUtil::loadKeyBinds(0, menu);
		//CUtil::loadRainbow(0);
		//CUtil::loadSmoke(0);
		//CUtil::loadSpeedo(0, menu);
		CUtil::loadTheme(0, menu);
		if (notify)
			notifyMap("~g~All Settings Loaded", 0);
	}

	void CUtil::addFavourite(Hash model, std::string name) {
		int index = fVeh.numSections("model");
		fVeh.write_fav({ model, name, "?" }, index);
	}

	std::vector<fVehicle> CUtil::REFRESH() {

		std::vector<fVehicle> tmp;

		tmp.clear();
		tmp.shrink_to_fit();

		for (int i = 0; i < fVeh.numSections("model"); i++) {
			tmp.push_back(fVeh.read_fav(i));
		}
	}

	static unsigned int lastSec = GetTickCount();
	static int framesThisSec = 0;
	static int framePerSec = 0;

	double CUtil::CalcAverageTick()
	{
		framesThisSec++;
		if (GetTickCount() - lastSec >= 1000) {
			framePerSec = framesThisSec;
			framesThisSec = 0;
			lastSec = GetTickCount();
		}
		return framePerSec;
	}

	float CUtil::CalcSpeed(bool mphOut, Vehicle veh)
	{
		float speed = ENTITY::GET_ENTITY_SPEED(veh);
		float MetersPerHour = (speed * 3600);
		if (mphOut) {
			float mph = (MetersPerHour / 1609.344f);
			return mph;
		}
		else if (!mphOut) {
			float kmh = MetersPerHour / 1000;
			return kmh;
		}
		else
			return speed;
	}

	void CUtil::printFPS()
	{
		int screen_res_x, screen_res_y;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_res_x, &screen_res_y);
		std::stringstream oss;
		oss << CalcAverageTick();
		l_menu.PrintText((char*)oss.str().c_str(), 0, (screen_res_x / 1000) - 0.100f, (screen_res_y / 1000) + 0.040f, 0.f, 0.35f, { 225, 150, 96, 255 }, 1, 0);
	}

	void CUtil::printSpeed() {
		/*SET_TEXT_FONT(0);
		SET_TEXT_SCALE(7.26f, 7.26f);
		SET_TEXT_CENTRE(1);speedometertypesize
		BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		_ADD_TEXT_COMPONENT_SCALEFORM(name);*/
		int screen_res_x, screen_res_y;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_res_x, &screen_res_y);

		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
		{
			UI::SET_TEXT_FONT(0);
			UI::SET_TEXT_PROPORTIONAL(1);
			//SET_TEXT_SCALE(0.0, 0.60);
			UI::SET_TEXT_SCALE(0.0, 0.92f);
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 255);
			UI::SET_TEXT_DROP_SHADOW();
			UI::SET_TEXT_OUTLINE();
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			std::stringstream oss;
			/*float speed = GET_ENTITY_SPEED(GET_VEHICLE_PED_IS_USING(PLAYER_PED_ID()));
			float MetersPerHour = (speed * 3600);
			float mph = (MetersPerHour / 1609.344f);
			float mps = GET_ENTITY_SPEED(GET_VEHICLE_PED_IS_IN(PLAYER_PED_ID(), 0));
			float kmh = mps * 3600 / 1000;
			float milesperhour = kmh * 0.6213711916666667f;
			if (SpeedMPH)
			speed = round(milesperhour);
			else if (!SpeedMPH)
			speed = round(kmh); */
			oss << round(CalcSpeed(true, VEHICLE::GET_LAST_DRIVEN_VEHICLE()));
			UI::_ADD_TEXT_COMPONENT_SCALEFORM((char*)oss.str().c_str());
			UI::END_TEXT_COMMAND_DISPLAY_TEXT((screen_res_x / 1000) - 0.096f, 1 - 0.074f);
			UI::SET_TEXT_FONT(0);
			UI::SET_TEXT_PROPORTIONAL(1);
			//SET_TEXT_SCALE(0.0, 0.60);
			UI::SET_TEXT_SCALE(0.0, 0.38f);
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 255);
			UI::SET_TEXT_DROP_SHADOW();
			UI::SET_TEXT_OUTLINE();
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			std::stringstream osss;
			osss << "~g~mph";
			UI::_ADD_TEXT_COMPONENT_SCALEFORM((char*)osss.str().c_str());
			UI::END_TEXT_COMMAND_DISPLAY_TEXT((screen_res_x / 1000) - 0.045f, 1 - 0.043f);
		}
		//END_TEXT_COMMAND_DISPLAY_TEXT(-0.015f + (screen_res_x / 100), -0.015f + (screen_res_y / 100));
	}

	bool CUtil::isPlayerFriend(Player player) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(player)) {
			int handle;
			NETWORK::NETWORK_HANDLE_FROM_PLAYER(player, &handle, 13);
			return NETWORK::NETWORK_IS_FRIEND(&handle);
		}
		return false;
	}

	Vector3 CUtil::getBlipMarker()
	{
		static Vector3 zero;
		Vector3 coords;

		bool blipFound = false;
		// search for marker blip
		int blipIterator = UI::_GET_BLIP_INFO_ID_ITERATOR();
		for (Blip i = UI::GET_FIRST_BLIP_INFO_ID(blipIterator); UI::DOES_BLIP_EXIST(i) != 0; i = UI::GET_NEXT_BLIP_INFO_ID(blipIterator))
		{
			if (UI::GET_BLIP_INFO_ID_TYPE(i) == 4)
			{
				coords = UI::GET_BLIP_INFO_ID_COORD(i);
				blipFound = true;
				break;
			}
		}
		if (blipFound)
		{
			return coords;
		}

		return zero;
	}

	void CUtil::tpToMarker()
	{
		Vector3 coords = getBlipMarker();

		if (coords.x == 0 && coords.y == 0)
		{
			notifyError("No Waypoint has been set!");
			return;
		}

		// get entity to teleport
		Entity e = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(e, 0))
		{
			e = PED::GET_VEHICLE_PED_IS_USING(e);
		}

		// load needed map region and check height levels for ground existence
		bool groundFound = false;
		static float groundCheckHeight[] =
		{ 100.0, 150.0, 50.0, 0.0, 200.0, 250.0, 300.0, 350.0, 400.0, 450.0, 500.0, 550.0, 600.0, 650.0, 700.0, 750.0, 800.0 };
		for (int i = 0; i < sizeof(groundCheckHeight) / sizeof(float); i++)
		{
			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(e, coords.x, coords.y, groundCheckHeight[i], 0, 0, 1);
			STREAMING::LOAD_ALL_OBJECTS_NOW();
			WAIT(100);
			if (GAMEPLAY::GET_GROUND_Z_FOR_3D_COORD(coords.x, coords.y, groundCheckHeight[i], &coords.z, 0))
			{
				groundFound = true;
				coords.z += 3.0;
				break;
			}
		}
		// if ground not found then set Z in air and give player a parachute
		if (!groundFound)
		{
			coords.z = 1000.0;
			WEAPON::GIVE_DELAYED_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), 0xFBAB5776, 1, 0);
		}
		//do it
		tpToCoords(e, coords);
	}

	void CUtil::tpToObjective()
	{
		Vector3 coords;
		Entity e;
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE))
			e = PED::GET_VEHICLE_PED_IS_USING(playerPed);
		else e = playerPed;

		bool blipFound = false;

		if (ENTITY::IS_ENTITY_A_VEHICLE(e)) CNetwork::controlEnt(e);
		for (int i = 0; i <= 1000; i++)
		{
			CBlipList bList;
			CBlip* blip = bList.m_Blips[i];
			if (blip)
			{
				if ((blip->dwColor == ColorYellowMission && blip->iIcon == SpriteStandard) || (blip->dwColor == ColorYellow && blip->iIcon == SpriteStandard) ||
					(blip->dwColor == ColorWhite && blip->iIcon == SpriteRaceFinish) || (blip->dwColor == ColorGreen && blip->iIcon == SpriteStandard) || (blip->iIcon == SpriteCrateDrop)) {
					coords = blip->v3Pos;
					blipFound = true;
					break; //During a race there's sometimes 2 yellow markers. We want the first one.
				}
			}
		}

		blipFound ? tpToCoords(e, coords) : notifyError("Objective not found!");

	}

	void CUtil::tpToCar()
	{
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();
		//	Vector3 getCoords(Ped ped); //{ return ENTITY::GET_ENTITY_COORDS(playerPed, 1) };
		Vector3 startLoc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);

		int veh = VEHICLE::GET_CLOSEST_VEHICLE(startLoc.x, startLoc.y, startLoc.z, 100.0, 0, 70);
		VEHICLE::SET_VEHICLE_NEEDS_TO_BE_HOTWIRED(veh, 0);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
	}

	void CUtil::tpToCoords(float x, float y, float z)
	{
		if (!(PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)))
		{
			ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), x, y, z, 1, 0, 0, 1);
		}
		else
		{
			Vehicle playerVeh = (PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()));
			CNetwork::controlEnt(playerVeh);
			ENTITY::SET_ENTITY_COORDS(playerVeh, x, y, z, 1, 0, 0, 1);
		}
		STREAMING::LOAD_ALL_OBJECTS_NOW();
	}

	void CUtil::tpToCoords(Entity ent, Vector3 coords)
	{
		ENTITY::SET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), coords.x, coords.y, coords.z, 1, 0, 0, 1);
		CNetwork::controlEnt(ent);
		STREAMING::LOAD_ALL_OBJECTS_NOW();
	}

	void CUtil::tpToPlayer(Ped playerPed)
	{
		Vector3 destloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0)) {
			Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), 0);
			CNetwork::controlEnt(veh);
			if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(veh)) {
				ENTITY::SET_ENTITY_COORDS_NO_OFFSET(veh, destloc.x, destloc.y, destloc.z, 0, 0, 0);
				STREAMING::LOAD_ALL_OBJECTS_NOW();
			}
		}
		else
		{
			tpToCoords(destloc.x, destloc.y, destloc.z);
			STREAMING::LOAD_ALL_OBJECTS_NOW();
			WAIT(1);
			if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 1))
				if (VEHICLE::ARE_ANY_VEHICLE_SEATS_FREE(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0)) && 1) {
					CNetwork::controlEnt(PED::GET_VEHICLE_PED_IS_IN(playerPed, 0));
					PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), PED::GET_VEHICLE_PED_IS_IN(playerPed, 0), -1);
				}
		}
	}

	bool CUtil::signIn() {
		if (auth::signIn(0)) { notifyMap("~g~Sign-In Successful", 1); return true; }
		else { notifyError("Sign-In Failed"); return false; }
	}

	void CPlayer::healArmor()
	{
		// set our health
		CHack::m_pCWorld->CPedLocalPlayer->fHealth = CHack::m_pCWorld->CPedLocalPlayer->fHealthMax;
		// set our armor
		CHack::m_pCWorld->CPedLocalPlayer->fArmor = 1337.f;
	}

	void CPlayer::cleanPlayer()
	{
		PED::CLEAR_PED_BLOOD_DAMAGE(PLAYER::PLAYER_PED_ID());
		PED::RESET_PED_VISIBLE_DAMAGE(PLAYER::PLAYER_PED_ID());
	}

	void CPlayer::superRun()
	{
		if (GetAsyncKeyState(VK_SHIFT)) {
			CGameplay::applyForceToEntity(PLAYER::PLAYER_PED_ID(), .0f, 1.5f, .0f);
		}
	}

	void CWeapon::giveAllGuns(Ped ped)
	{
		for each (Hash weaponlist in weaponlist) {
			if (!WEAPON::HAS_PED_GOT_WEAPON(ped, weaponlist, false)) {
				WEAPON::GIVE_WEAPON_TO_PED(ped, weaponlist, 9999, false, true);
				WEAPON::SET_PED_WEAPON_TINT_INDEX(ped, weaponlist, WeaponTintLSPD);
			}
		}
	}

	void CWeapon::replenishAllGuns(Ped ped)
	{
		for each (Hash weaponlist in weaponlist) {
			int ammo = 0;
			if (WEAPON::GET_MAX_AMMO(ped, weaponlist, &ammo)) {
				WEAPON::SET_PED_AMMO(ped, weaponlist, ammo);
			}
		}
	}

	void giveWeaponAddon(Ped ped, Hash weapon)
	{
		static Hash weaponAddons[] = { COMPONENT_AT_SCOPE_MACRO, COMPONENT_AT_SCOPE_MACRO_02, COMPONENT_AT_SCOPE_SMALL, COMPONENT_AT_SCOPE_SMALL_02, COMPONENT_AT_SCOPE_MEDIUM, COMPONENT_AT_SCOPE_LARGE, COMPONENT_AT_SCOPE_MAX, COMPONENT_AT_RAILCOVER_01, COMPONENT_AT_AR_AFGRIP, COMPONENT_AT_PI_FLSH, COMPONENT_AT_AR_FLSH, COMPONENT_PISTOL_CLIP_02, COMPONENT_COMBATPISTOL_CLIP_02, COMPONENT_APPISTOL_CLIP_02, COMPONENT_MICROSMG_CLIP_02, COMPONENT_SMG_CLIP_02, COMPONENT_ASSAULTRIFLE_CLIP_02, COMPONENT_CARBINERIFLE_CLIP_02, COMPONENT_ADVANCEDRIFLE_CLIP_02, COMPONENT_MG_CLIP_02, COMPONENT_COMBATMG_CLIP_02, COMPONENT_ASSAULTSHOTGUN_CLIP_02, COMPONENT_PISTOL50_CLIP_02, COMPONENT_ASSAULTSMG_CLIP_02, COMPONENT_SNSPISTOL_CLIP_02, COMPONENT_COMBATPDW_CLIP_02, COMPONENT_HEAVYPISTOL_CLIP_02, COMPONENT_SPECIALCARBINE_CLIP_02, COMPONENT_BULLPUPRIFLE_CLIP_02, COMPONENT_VINTAGEPISTOL_CLIP_02, COMPONENT_MARKSMANRIFLE_CLIP_02, COMPONENT_HEAVYSHOTGUN_CLIP_02, COMPONENT_GUSENBERG_CLIP_02 };

		for each (Hash weaponAddons in weaponAddons) {
			if (WEAPON::DOES_WEAPON_TAKE_WEAPON_COMPONENT(weapon, weaponAddons)) {
				WEAPON::GIVE_WEAPON_COMPONENT_TO_PED(ped, weapon, weaponAddons);
			}
		}
	}

	void CWeapon::upgradeAllGuns(Ped ped)
	{
		for each (Hash weaponlist in weaponlist) {
			giveWeaponAddon(ped, weaponlist);
		}
	}

	void CWeapon::removeAllWeapons(Ped ped)
	{
		WEAPON::REMOVE_ALL_PED_WEAPONS(ped, false);
	}

	void CWeapon::infiniteParachute()
	{
		if (PED::IS_PED_FALLING(PLAYER::PLAYER_PED_ID())) {
			WEAPON::GIVE_WEAPON_TO_PED(PLAYER::PLAYER_PED_ID(), -72657034, 1, false, true);
		}
	}

	void CWeapon::ammoModification(Hash type)
	{
		Entity weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
		Vector3 launchCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, +.2f, 0.0f, 0.0f);
		Vector3 endCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, +300.0f, 0.0f, 0.0f);
		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);

		if (GetAsyncKeyState((VK_LBUTTON) & 1)) {
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(launchCoords.x, launchCoords.y, launchCoords.z, endCoords.x, endCoords.y, endCoords.z,
				250, false, type, PLAYER::PLAYER_PED_ID(), true, false, 500.0f);
		}
		/* if code reaches here, restore our shite. */
		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
	}

	void CWeapon::rapidFire()
	{
		Entity weapon = WEAPON::GET_CURRENT_PED_WEAPON_ENTITY_INDEX(PLAYER::PLAYER_PED_ID());
		Vector3 launchCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, +0.2f, 0.0f, 0.0f);
		Vector3 endCoords = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(weapon, 0.0f, 0.0f, 0.0f);

		Hash weaponHash;
		WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &weaponHash, true);

		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), true);

		if (GetAsyncKeyState((VK_LBUTTON) & 1)) {
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(launchCoords.x, launchCoords.y, launchCoords.z, endCoords.x, endCoords.y, endCoords.z,
				250, false, weaponHash, PLAYER::PLAYER_PED_ID(), true, false, 500.0f);
		}

		PLAYER::DISABLE_PLAYER_FIRING(PLAYER::PLAYER_ID(), false);
	}

	void CWeapon::infiniteAmmo()
	{
		Hash currentWeapon;

		if (WEAPON::GET_CURRENT_PED_WEAPON(PLAYER::PLAYER_PED_ID(), &currentWeapon, true)) {
			if (WEAPON::IS_WEAPON_VALID(currentWeapon)) {
				int maxAmmo;

				if (WEAPON::GET_MAX_AMMO(PLAYER::PLAYER_PED_ID(), currentWeapon, &maxAmmo)) {
					WEAPON::SET_PED_AMMO(PLAYER::PLAYER_PED_ID(), currentWeapon, maxAmmo);
				}
			}
		}
	}

	void CTeleport::teleportToWaypoint()
	{
		//
	}

	void CTeleport::teleportToVehicle()
	{
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);

		int vehicle = VEHICLE::GET_CLOSEST_VEHICLE(pos.x, pos.y, pos.z, 500.0f, 0, 0);
		PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);
	}

	Ped CGameplay::clonePed(Ped ped)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped)) {
			return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), true, true);
		}

		return 0;
	}

	void CGameplay::applyForceToEntity(Entity e, float x, float y, float z)
	{
		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0.0f, 0.0f, 0.0f, 0, true, true, true, false, true);
	}

	void CVehicle::repair(Vehicle vehicle) {
		if (FIRE::IS_ENTITY_ON_FIRE(vehicle))
			FIRE::STOP_ENTITY_FIRE(vehicle);
		VEHICLE::SET_VEHICLE_FIXED(vehicle);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
		VEHICLE::SET_VEHICLE_PETROL_TANK_HEALTH(vehicle, 1000.0f);
		VEHICLE::SET_VEHICLE_BODY_HEALTH(vehicle, 1000.0f);
		VEHICLE::SET_VEHICLE_ENGINE_HEALTH(vehicle, 1000.0f);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
		VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.0f);
		VEHICLE::SET_VEHICLE_UNDRIVEABLE(vehicle, FALSE);
		VEHICLE::SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(vehicle, TRUE);
		VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, TRUE, TRUE, TRUE);
		VEHICLE::_SET_VEHICLE_JET_ENGINE_ON(vehicle, TRUE);
		VEHICLE::SET_DISABLE_VEHICLE_PETROL_TANK_FIRES(vehicle, FALSE);
	}

	void CVehicle::clean(Vehicle vehicle) {
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);
		VEHICLE::SET_VEHICLE_ENVEFF_SCALE(vehicle, 0.0f);
	}

	void CVehicle::paintRandom(Vehicle vehicle, bool primary, bool secondary, bool neon, bool wheels, bool tyresmoke)
		{
			if (tyresmoke)
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
			if (neon)
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
			if (wheels)
				VEHICLE::SET_VEHICLE_EXTRA_COLOURS(vehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUMBER_OF_VEHICLE_COLOURS(vehicle)), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 67));

			VEHICLE::SET_VEHICLE_COLOURS(vehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUMBER_OF_VEHICLE_COLOURS(vehicle)), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, VEHICLE::GET_NUMBER_OF_VEHICLE_COLOURS(vehicle)));

			if (primary)
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
			if (secondary)
				VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255), GAMEPLAY::GET_RANDOM_INT_IN_RANGE(0, 255));
		}

	void CVehicle::stockUpgrade(Vehicle vehicle)
		{
			for (int i = 0; i < 48; i++)
				VEHICLE::SET_VEHICLE_MOD(vehicle, i, -1, 0);
		}

	void CVehicle::baseUpgrade(Vehicle vehicle)
		{
			if (VEHICLE::GET_VEHICLE_MOD_KIT(vehicle) != 0)
				VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			VEHICLE::SET_VEHICLE_MOD(vehicle, 4, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 4) - 1, 1);
			VEHICLE::SET_VEHICLE_MOD(vehicle, 11, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 11) - 1, 1);
			VEHICLE::SET_VEHICLE_MOD(vehicle, 12, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 12) - 1, 1);
			VEHICLE::SET_VEHICLE_MOD(vehicle, 13, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 13) - 1, 1);
			VEHICLE::SET_VEHICLE_MOD(vehicle, 15, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 15) - 1, 1);
			VEHICLE::SET_VEHICLE_MOD(vehicle, 16, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, 16) - 1, 1);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, 1);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, 1);
			VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, WINDOWTINT_GREEN);
		}

	void CVehicle::maxUpgrade(Vehicle vehicle) {
			VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
			VEHICLE::SET_VEHICLE_WHEEL_TYPE(vehicle, 9);
			for (int i = 0; i < 49; i++)
				VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, 1);

			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 17, TRUE);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 18, TRUE);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 19, TRUE);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 20, TRUE);
			VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, 20, 20, 20);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 21, TRUE);
			VEHICLE::TOGGLE_VEHICLE_MOD(vehicle, 22, TRUE);

			VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(vehicle);
			VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(vehicle, FALSE);
			VEHICLE::SET_VEHICLE_WHEELS_CAN_BREAK(vehicle, FALSE);
			VEHICLE::SET_VEHICLE_HAS_STRONG_AXLES(vehicle, TRUE);
			VEHICLE::SET_VEHICLE_DIRT_LEVEL(vehicle, 0.0f);

			VEHICLE::SET_VEHICLE_WINDOW_TINT(vehicle, 1);
			for (int i = 0; i < 4; i++)
				VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(vehicle, i, 1);
		}

	void CVehicle::bypassKick(Vehicle vehicle)
		{
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", 0);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, false);

			/* old kick bypass */
			/*Player player = PLAYER::PLAYER_ID();
			int var;
			DECORATOR::DECOR_REGISTER("Player_Vehicle", 3);
			DECORATOR::DECOR_REGISTER("Veh_Modded_By_Player", 3);
			DECORATOR::DECOR_SET_INT(vehicle, "Player_Vehicle", NETWORK::_NETWORK_HASH_FROM_PLAYER_HANDLE(player));
			DECORATOR::DECOR_SET_INT(vehicle, "Veh_Modded_By_Player", CUtil::$(PLAYER::GET_PLAYER_NAME(player)));
			DECORATOR::DECOR_SET_INT(vehicle, "Not_Allow_As_Saved_Veh", 0);
			if (DECORATOR::DECOR_EXIST_ON(vehicle, "MPBitset"))
			var = DECORATOR::DECOR_GET_INT(vehicle, "MPBitset");
			GAMEPLAY::SET_BIT(&var, 3);
			DECORATOR::DECOR_SET_INT(vehicle, "MPBitset", var);
			VEHICLE::SET_VEHICLE_IS_STOLEN(vehicle, false);*/
		}

	Vehicle CVehicle::spawn(Hash model, Ped playerPed, Vector3 playerPos, bool vDelete, bool vWrap, bool vMax)
		{
			Vehicle vehicle = 0; int NetID = 0;

			//Delete old vehicle
			if (vDelete) {
				if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
					AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
				}
				int old = PLAYER::GET_PLAYERS_LAST_VEHICLE();
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(old);
				VEHICLE::DELETE_VEHICLE(&old);
			}

			//Get player heading
			float direction = ENTITY::GET_ENTITY_HEADING(playerPed);

			if (!STREAMING::IS_MODEL_IN_CDIMAGE(model)) return 0;

			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model)) WAIT(0);

			//if player is offline
			if (!NETWORK::NETWORK_IS_IN_SESSION()) {
				vehicle = VEHICLE::CREATE_VEHICLE(model, playerPos.x, playerPos.y, playerPos.z, direction, TRUE, TRUE);

				if (vWrap) {
					if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
						AI::CLEAR_PED_TASKS_IMMEDIATELY(playerPed);
					}
					PED::SET_PED_INTO_VEHICLE(playerPed, vehicle, -1);
				}

				VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, TRUE, TRUE, TRUE);

				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

				if (!ENTITY::DOES_ENTITY_EXIST(vehicle)) return 0;

				if (vMax)
					maxUpgrade(vehicle);

				return vehicle;
			}

			//rest if player is online
			vehicle = VEHICLE::CREATE_VEHICLE(model, playerPos.x, playerPos.y, playerPos.z, direction, TRUE, TRUE);
			NetID = NETWORK::VEH_TO_NET(vehicle);
			if (!NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(NetID))
				WAIT(0);

			bypassKick(vehicle);

			ENTITY::_SET_ENTITY_REGISTER(NetID, TRUE);

			if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(NetID)) NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NetID, TRUE);

			if (playerPed == PLAYER::PLAYER_PED_ID() && vWrap)
				PED::SET_PED_INTO_VEHICLE(playerPed, vehicle, -1); \

				VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, TRUE, TRUE, TRUE);

			WAIT(0);
			if (vMax)
				maxUpgrade(vehicle);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
			//fade in and out, just cause
			NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, TRUE, FALSE);
			NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, TRUE);

			//SET_ENTITY_AS_NO_LONGER_NEEDED(&vehicle);

			return vehicle;
		}

	Vehicle CVehicle::spawn(Hash model, Ped playerPed, bool vDelete, bool vWrap, bool vMax)
		{
			return spawn(model, playerPed, ENTITY::GET_ENTITY_COORDS(playerPed, 1), vDelete, vWrap, vMax);
		}

	Vehicle CVehicle::spawn(char* toSpawn, Ped playerPed, bool vDelete, bool vWrap, bool vMax) {
			return spawn(CUtil::$(toSpawn), playerPed, vDelete, vWrap, vMax);
		}

	Vehicle CVehicle::clone(Ped ped) {
			Vehicle pedVeh = NULL;
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE))
				pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, FALSE);
			else
				pedVeh = PED::GET_VEHICLE_PED_IS_IN(ped, TRUE);
			if (ENTITY::DOES_ENTITY_EXIST(pedVeh)) {
				Vehicle playerVeh = spawn(ENTITY::GET_ENTITY_MODEL(pedVeh), playerPed, 0, 1, 0);//CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, GET_ENTITY_HEADING(playerPed), TRUE, TRUE);
				auto veh2net = NETWORK::VEH_TO_NET(playerVeh);
				if (NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(veh2net)) {
					// 1
					NETWORK::SET_NETWORK_ID_CAN_MIGRATE(veh2net, 1);
					NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(veh2net, 1);
				}
				else {
					CUtil::notifyError("Unknown Fatal Error");				// Make note of an error here, you got problems boyo
																			//Vehicle playerVeh = CREATE_VEHICLE(vehicleModelHash, playerPosition.x, playerPosition.y, playerPosition.z, GET_ENTITY_HEADING(playerPed), TRUE, TRUE);
				}
				bypassKick(playerVeh);
				PED::SET_PED_INTO_VEHICLE(playerPed, playerVeh, -1);
				int primaryColor, secondaryColor;
				VEHICLE::GET_VEHICLE_COLOURS(pedVeh, &primaryColor, &secondaryColor);
				VEHICLE::SET_VEHICLE_COLOURS(playerVeh, primaryColor, secondaryColor);
				if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(pedVeh)) {
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::GET_IS_VEHICLE_SECONDARY_COLOUR_CUSTOM(pedVeh)) {
					int r, g, b;
					VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(pedVeh, &r, &g, &b);
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(playerVeh, r, g, b);
				}
				if (VEHICLE::IS_THIS_MODEL_A_CAR(ENTITY::GET_ENTITY_MODEL(pedVeh)) || VEHICLE::IS_THIS_MODEL_A_BIKE(ENTITY::GET_ENTITY_MODEL(pedVeh))) {
					VEHICLE::SET_VEHICLE_MOD_KIT(playerVeh, 0);
					VEHICLE::SET_VEHICLE_WHEEL_TYPE(playerVeh, VEHICLE::GET_VEHICLE_WHEEL_TYPE(pedVeh));
					for (int i = 0; i <= 24; i++) {
						if (i > 16 && i < 23)
							VEHICLE::TOGGLE_VEHICLE_MOD(playerVeh, i, VEHICLE::IS_TOGGLE_MOD_ON(pedVeh, i));
						else
							VEHICLE::SET_VEHICLE_MOD(playerVeh, i, VEHICLE::GET_VEHICLE_MOD(pedVeh, i), VEHICLE::GET_VEHICLE_MOD_VARIATION(pedVeh, i));
					}
					int tireSmokeColor[3], pearlescentColor, wheelColor;
					VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(pedVeh, &tireSmokeColor[0], &tireSmokeColor[1], &tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(playerVeh, tireSmokeColor[0], tireSmokeColor[1], tireSmokeColor[2]);
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(pedVeh));
					VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVeh, VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(pedVeh));
					VEHICLE::GET_VEHICLE_EXTRA_COLOURS(pedVeh, &pearlescentColor, &wheelColor);
					VEHICLE::SET_VEHICLE_EXTRA_COLOURS(playerVeh, pearlescentColor, wheelColor);
					if (VEHICLE::IS_VEHICLE_A_CONVERTIBLE(pedVeh, 0)) {
						int convertableState = VEHICLE::GET_CONVERTIBLE_ROOF_STATE(pedVeh);
						if (convertableState == 0 || convertableState == 3 || convertableState == 5)
							VEHICLE::RAISE_CONVERTIBLE_ROOF(playerVeh, 1);
						else
							VEHICLE::LOWER_CONVERTIBLE_ROOF(playerVeh, 1);
					}
					for (int i = 0; i <= 3; i++) {
						VEHICLE::_SET_VEHICLE_NEON_LIGHT_ENABLED(playerVeh, i, VEHICLE::_IS_VEHICLE_NEON_LIGHT_ENABLED(pedVeh, i));
					}
					for (int i = 0; i <= 11; i++) {
						if (VEHICLE::DOES_EXTRA_EXIST(pedVeh, i))
							VEHICLE::SET_VEHICLE_EXTRA(playerVeh, i, !VEHICLE::IS_VEHICLE_EXTRA_TURNED_ON(pedVeh, i));
					}
					if ((VEHICLE::GET_VEHICLE_LIVERY_COUNT(pedVeh) > 1) && VEHICLE::GET_VEHICLE_LIVERY(pedVeh) >= 0) {
						VEHICLE::SET_VEHICLE_LIVERY(playerVeh, VEHICLE::GET_VEHICLE_LIVERY(pedVeh));
					}
					int neonColor[3];
					VEHICLE::_GET_VEHICLE_NEON_LIGHTS_COLOUR(pedVeh, &neonColor[0], &neonColor[1], &neonColor[2]);
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(playerVeh, neonColor[0], neonColor[1], neonColor[2]);
					VEHICLE::SET_VEHICLE_WINDOW_TINT(playerVeh, VEHICLE::GET_VEHICLE_WINDOW_TINT(pedVeh));
					VEHICLE::SET_VEHICLE_DIRT_LEVEL(playerVeh, VEHICLE::GET_VEHICLE_DIRT_LEVEL(pedVeh));
				}
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(ENTITY::GET_ENTITY_MODEL(pedVeh));
			}
			return pedVeh;
		}

	bool CVehicle::deleteVehicle(Ped ped) {
			if (PED::IS_PED_IN_ANY_VEHICLE(ped, 1)) {
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, 0);
				if (!NETWORK::NETWORK_IS_SESSION_STARTED()) {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
					VEHICLE::DELETE_VEHICLE(&vehicle);
				}
				else {
					if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle)) { CUtil::notifyMap("~r~Error: ~w~Could not get control", 0); return false; }
					NETWORK::SET_NETWORK_ID_CAN_MIGRATE(vehicle, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
					VEHICLE::DELETE_VEHICLE(&vehicle);
				}
			}
			else if (ENTITY::DOES_ENTITY_EXIST(VEHICLE::GET_LAST_DRIVEN_VEHICLE())) {
				Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(ped, 0);
				if (!NETWORK::NETWORK_IS_SESSION_STARTED()) {
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
					VEHICLE::DELETE_VEHICLE(&vehicle);
				}
				else {
					if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle)) { CUtil::notifyMap("~r~Error: ~w~Could not get control", 0); return false; }
					NETWORK::SET_NETWORK_ID_CAN_MIGRATE(vehicle, 1);
					ENTITY::SET_ENTITY_AS_MISSION_ENTITY(vehicle, true, true);
					VEHICLE::DELETE_VEHICLE(&vehicle);
				}
			}
			else {
				CUtil::notifyError("Vehicle Not Found");
				return false;
			}
			return true;
		}

	void CVehicle::setPlateText(Vehicle vehicle)
		{
			std::string plateTemp = l_menu.show_keyboard("Numberplate Text", VEHICLE::GET_VEHICLE_NUMBER_PLATE_TEXT(vehicle));
			if (plateTemp == "")
				CUtil::notifyError("Input cannot be Blank");
			else
			{
				VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(vehicle, GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
			}
		}

	void CVehicle::manualSelect(bool playerType)
		{
			Ped playerPed = PLAYER::PLAYER_PED_ID();
			//if (playerType)
			//	playerPed = sel.pedID;
			std::string tempmodel = l_menu.show_keyboard("Vehicle Model", "");
			if (tempmodel == "")
				CUtil::notifyError("Input cannot be Blank");
			else
			{
				if (STREAMING::IS_MODEL_VALID(CUtil::$(tempmodel)))//tempmodel.c_str;
					spawn(CUtil::$(tempmodel), playerPed, 1, 1, 0);
				else
					CUtil::notifyError("Invalid Vehicle");
			}
		}

	void CVehicle::loop_rainbow(Vehicle vehicle, NativeMenu::CMenu &menu)
	{
		if (!menu.p_vehicle->rFade && menu.p_vehicle->rUpdate < GAMEPLAY::GET_GAME_TIMER())
		{
			menu.p_vehicle->rUpdate = GAMEPLAY::GET_GAME_TIMER() + 25;
			if (menu.p_vehicle->rBody)
			{
				VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, rand() % 255, rand() % 255, rand() % 255);
				if (VEHICLE::GET_IS_VEHICLE_PRIMARY_COLOUR_CUSTOM(vehicle))
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, rand() % 255, rand() % 255, rand() % 255);
			}
			if (menu.p_vehicle->rNeon)
			{
				VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, rand() % 255, rand() % 255, rand() % 255);
			}
			if (menu.p_vehicle->rTyre)
			{
				VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, rand() % 255, rand() % 255, rand() % 255);
			}
		}

		//rainbow car fade
		if (menu.p_vehicle->rFade)
		{
			static int    rs = 255, gs = 0, bs = 0;
			{
				if (rs > 0 && bs == 0)
				{
					rs--;
					gs++;
				}
				if (gs > 0 && rs == 0)
				{
					gs--;
					bs++;
				}
				if (bs > 0 && gs == 0)
				{
					rs++;
					bs--;
				}
				if (menu.p_vehicle->rPrimary)
				{
					VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(vehicle, rs, gs, bs);
				}
				if (menu.p_vehicle->rSecondary)
				{
					VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(vehicle, rs, gs, bs);
				}
				if (menu.p_vehicle->rNeon)
				{
					VEHICLE::_SET_VEHICLE_NEON_LIGHTS_COLOUR(vehicle, rs, gs, bs);
				}
				if (menu.p_vehicle->rTyre)
				{
					VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(vehicle, rs, gs, bs);
				}
				if (menu.p_vehicle->rMenu)
				{
					menu.scroller.r = rs;
					menu.scroller.g = gs;
					menu.scroller.b = bs;
					menu.titleText.r = rs;
					menu.titleText.g = gs;
					menu.titleText.b = bs;
					menu.options.r = rs;
					menu.options.g = gs;
					menu.options.b = bs;
				}
			}
		}
	}

	void CNetwork::controlID(Entity netid)
		{
			int tick = 0;

			while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
				tick++;
			}
		}

	void CNetwork::controlEnt(Entity entity)
		{
			int tick = 0;
			while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
			{
				NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
				tick++;
			}
			if (NETWORK::NETWORK_IS_SESSION_STARTED())
			{
				int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
				controlID(netID);
				NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
			}
		}

	void CNetwork::dropWeapon(char *weapon, Ped recievingPed) {
			Hash pedm = CUtil::$("csb_stripper_01");
			Hash weaponh = CUtil::$(weapon);
			Vector3 coords = ENTITY::GET_ENTITY_COORDS(recievingPed, 1);
			STREAMING::REQUEST_MODEL(pedm);
			while (!STREAMING::HAS_MODEL_LOADED(pedm))
				WAIT(0);
			if (STREAMING::HAS_MODEL_LOADED(pedm)) {
				Ped ped = PED::CREATE_PED(26, pedm, coords.x, coords.y, coords.z + 5.f, 0, 1, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(pedm);
				ENTITY::SET_ENTITY_VISIBLE(ped, 0, 0);
				WEAPON::GIVE_WEAPON_TO_PED(ped, weaponh, 9999, 1, 1);
				WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(ped, 1);
				WEAPON::SET_PED_DROPS_WEAPON(ped);
				PED::APPLY_DAMAGE_TO_PED(ped, 9999, 1);
				ENTITY::SET_ENTITY_HEALTH(ped, 0);
				ENTITY::SET_ENTITY_COLLISION(ped, 0, 0);
				ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ped);
			}
		}

	void CNetwork::kickPlayer(Player player) {
			if (NETWORK::NETWORK_IS_HOST()) {
				if (PLAYER::PLAYER_ID() == player)
					CUtil::notifyError("You cannot Kick yourself you tard");
				else NETWORK::NETWORK_SESSION_KICK_PLAYER(player);
			}
			else CUtil::notifyError("You are not ~y~Host");
		}

	void CNetwork::attackCops(Ped playerPed) {

			Vector3 targetloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
			Hash model = 0x5E3DA4A4;
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			//Vector3 targetloc = coordsOf(playerPed);
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				WAIT(0);
			int createdModel = PED::CREATE_PED(26, model, targetloc.x, targetloc.y, targetloc.z, 1, 1, 0);

			ENTITY::SET_ENTITY_INVINCIBLE(createdModel, false);

			Hash weapon = CUtil::$("weapon_pistol");
			WEAPON::GIVE_WEAPON_TO_PED(createdModel, weapon, weapon, 9999, 9999);
			AI::TASK_COMBAT_PED(createdModel, playerPed, 1, 1);
			ENTITY::SET_ENTITY_INVINCIBLE(createdModel, false);
			PED::SET_PED_COMBAT_ABILITY(createdModel, 100);
			PED::SET_PED_CAN_SWITCH_WEAPON(createdModel, true);
			AI::TASK_COMBAT_PED(createdModel, playerPed, 1, 1);
			PED::SET_PED_AS_ENEMY(createdModel, 1);
			PED::SET_PED_COMBAT_RANGE(createdModel, 1000);
			PED::SET_PED_KEEP_TASK(createdModel, true);
			PED::SET_PED_AS_COP(createdModel, 1);
			PED::SET_PED_ALERTNESS(createdModel, 1000);
		}

	void CNetwork::attckSwat(Ped playerPed) {

			Vector3 targetloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			Hash stripper = CUtil::$("s_m_y_swat_01");
			Hash railgun = CUtil::$("weapon_stungun");
			STREAMING::REQUEST_MODEL(stripper);
			while (!STREAMING::HAS_MODEL_LOADED(stripper))
				WAIT(0);

			int createdPED = PED::CREATE_PED(26, stripper, targetloc.x, targetloc.y, targetloc.z, 1, 1, 0);
			ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
			PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
			WEAPON::GIVE_WEAPON_TO_PED(createdPED, railgun, railgun, 9999, 9999);
			PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
			AI::TASK_COMBAT_PED(createdPED, playerPed, 1, 1);
			PED::SET_PED_ALERTNESS(createdPED, 1000);
			PED::SET_PED_COMBAT_RANGE(createdPED, 1000);
		}

	void CNetwork::attackJesus(Ped playerPed) {

			Vector3 targetloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			//Hash model = $("u_m_m_model_01");
			//Hash weapon = $("WEAPON_RAILGUN");
			Hash model = 0xCE2CB751;
			Hash weapon = 0x6D544C99;
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				WAIT(0);

			int createdPED = PED::CREATE_PED(26, model, targetloc.x, targetloc.y, targetloc.z, 1, 1, 0);
			ENTITY::SET_ENTITY_INVINCIBLE(createdPED, false);
			PED::SET_PED_COMBAT_ABILITY(createdPED, 100);
			WEAPON::GIVE_WEAPON_TO_PED(createdPED, weapon, weapon, 9999, 9999);
			PED::SET_PED_CAN_SWITCH_WEAPON(createdPED, true);
			AI::TASK_COMBAT_PED(createdPED, playerPed, 1, 1);
			PED::SET_PED_ALERTNESS(createdPED, 1000);
			PED::SET_PED_COMBAT_RANGE(createdPED, 1000);
		}

	void CNetwork::attackSwatRiot(Ped playerPed) {

			Vector3 targetloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			Hash guysex = CUtil::$("s_m_y_swat_01");
			STREAMING::REQUEST_MODEL(guysex);
			while (!STREAMING::HAS_MODEL_LOADED(guysex))
				WAIT(0);
			int createdGuySex = PED::CREATE_PED(26, guysex, targetloc.x, targetloc.y, targetloc.z, 1, 1, 0);

			ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
			int vehmodel = CUtil::$("riot");
			STREAMING::REQUEST_MODEL(vehmodel);

			while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);

			Vehicle veh = CVehicle::spawn("riot", createdGuySex, 0, 0, 1);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			Hash railgun = CUtil::$("weapon_bullpupshotgun");
			WEAPON::GIVE_WEAPON_TO_PED(createdGuySex, railgun, railgun, 9999, 9999);
			PED::SET_PED_INTO_VEHICLE(createdGuySex, veh, -1);
			ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
			PED::SET_PED_COMBAT_ABILITY(createdGuySex, 100);
			PED::SET_PED_CAN_SWITCH_WEAPON(createdGuySex, true);
			AI::TASK_COMBAT_PED(createdGuySex, playerPed, 1, 1);
			PED::SET_PED_AS_ENEMY(createdGuySex, 1);
			PED::SET_PED_COMBAT_RANGE(createdGuySex, 1000);
			PED::SET_PED_KEEP_TASK(createdGuySex, true);
			PED::SET_PED_AS_COP(createdGuySex, 1000);
			PED::SET_PED_ALERTNESS(createdGuySex, 1000);
		}

	void CNetwork::sendCops(Ped playerPed) {

			Vector3 targetloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			Hash guysex = CUtil::$("s_m_y_cop_01");
			STREAMING::REQUEST_MODEL(guysex);
			while (!STREAMING::HAS_MODEL_LOADED(guysex))
				WAIT(0);
			int createdGuySex = PED::CREATE_PED(26, guysex, targetloc.x, targetloc.y, targetloc.z, 1, 1, 0);

			ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
			//
			int vehmodel = CUtil::$("police3");
			STREAMING::REQUEST_MODEL(vehmodel);

			while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
			//			Vector3 coords = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER_PED_ID(), 0.0, 5.0, 0.0);
			Vehicle veh = CVehicle::spawn("police3", createdGuySex, 0, 0, 1);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			//
			Hash railgun = CUtil::$("weapon_pistol");
			WEAPON::GIVE_WEAPON_TO_PED(createdGuySex, railgun, railgun, 0, 1);
			PED::SET_PED_INTO_VEHICLE(createdGuySex, veh, -1);
			AI::TASK_COMBAT_PED(createdGuySex, playerPed, 1, 1);
			ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
			PED::SET_PED_COMBAT_ABILITY(createdGuySex, 100);
			PED::SET_PED_CAN_SWITCH_WEAPON(createdGuySex, true);
			AI::TASK_COMBAT_PED(createdGuySex, playerPed, 1, 1);
			PED::SET_PED_AS_ENEMY(createdGuySex, 1);
			PED::SET_PED_COMBAT_RANGE(createdGuySex, 1000);
			PED::SET_PED_KEEP_TASK(createdGuySex, true);
			PED::SET_PED_AS_COP(createdGuySex, 1000);
			PED::SET_PED_ALERTNESS(createdGuySex, 1000);
		}

	void CNetwork::attackTanks(Ped playerPed) {

			Vector3 targetloc = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
			if (!ENTITY::DOES_ENTITY_EXIST(playerPed)) return;
			Hash guysex = CUtil::$("s_m_y_marine_01");
			STREAMING::REQUEST_MODEL(guysex);
			while (!STREAMING::HAS_MODEL_LOADED(guysex))
				WAIT(0);
			int createdGuySex = PED::CREATE_PED(26, guysex, targetloc.x, targetloc.y, targetloc.z, 1, 1, 0);

			ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
			//
			int vehmodel = CUtil::$("rhino");
			STREAMING::REQUEST_MODEL(vehmodel);

			while (!STREAMING::HAS_MODEL_LOADED(vehmodel)) WAIT(0);
			//			Vector3 coords = GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(PLAYER_PED_ID(), 0.0, 5.0, 0.0);
			Vehicle veh = CVehicle::spawn("rhino", createdGuySex, 0, 0, 1);
			VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(veh);
			//
			PED::SET_PED_INTO_VEHICLE(createdGuySex, veh, -1);
			AI::TASK_COMBAT_PED(createdGuySex, playerPed, 1, 1);
			ENTITY::SET_ENTITY_INVINCIBLE(createdGuySex, false);
			PED::SET_PED_COMBAT_ABILITY(createdGuySex, 100);
			PED::SET_PED_CAN_SWITCH_WEAPON(createdGuySex, true);
			AI::TASK_COMBAT_PED(createdGuySex, playerPed, 1, 1);
			PED::SET_PED_AS_ENEMY(createdGuySex, 1);
			PED::SET_PED_COMBAT_RANGE(createdGuySex, 1000);
			PED::SET_PED_KEEP_TASK(createdGuySex, true);
			PED::SET_PED_AS_COP(createdGuySex, 1000);
			PED::SET_PED_ALERTNESS(createdGuySex, 1000);
		}

	void CNetwork::shootPed(Player selectedPlayer)
		{
			Ped selectedPed = PLAYER::GET_PLAYER_PED(selectedPlayer);
			Vector3 pedLoc = ENTITY::GET_ENTITY_COORDS(selectedPed, 1);
			Vector3 targetLoc = PED::GET_PED_BONE_COORDS(selectedPed, 24818, 0.f, 0.f, 0.f);
			Ped shooterPed;
			PED::GET_CLOSEST_PED(pedLoc.x, pedLoc.y, pedLoc.z, 45.f, 1, 1, &shooterPed, 1, 1, 1);
			Vector3 shooterLoc = ENTITY::GET_ENTITY_COORDS(shooterPed, 1);
			GAMEPLAY::SHOOT_SINGLE_BULLET_BETWEEN_COORDS(shooterLoc.x, shooterLoc.y, shooterLoc.z + 2.f, targetLoc.x, targetLoc.y, targetLoc.z, 300, 1, CUtil::$("weapon_heavysniper"), shooterPed, 1, 1, 345.f);
		}

	void CNetwork::soloSesh(int lagTime) {
			if (NETWORK::NETWORK_IS_SESSION_ACTIVE()) {
				CUtil::notifyMap("~g~Bumping to Solo Session", 1);
				Sleep(lagTime);
			}
			return;
		}

	void CNetwork::killAll() {
			for (int i = 0; i <= 32; i++) {
				WAIT(0);
				if (i == PLAYER::PLAYER_ID())
					continue;
				if (PLAYER::IS_PLAYER_PLAYING(i)) {
					int Handle = PLAYER::GET_PLAYER_PED(i);
					Vector3 pos = ENTITY::GET_ENTITY_COORDS(Handle, 1);
					if (!ENTITY::DOES_ENTITY_EXIST(Handle)) continue;
					FIRE::ADD_EXPLOSION(pos.x, pos.y, pos.z, 29, 0.5f, true, false, 5.0f);
				}
				if (i == 32) {
					break;
				}
			}
		}

	void CNetwork::loop_drawMarker(Player player, NativeMenu::RGBA bannerRect)
		{
			Entity e;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::GET_PLAYER_PED(player), 0))
				e = PED::GET_VEHICLE_PED_IS_IN(PLAYER::GET_PLAYER_PED(player), 0);
			else
				e = PLAYER::GET_PLAYER_PED(player);
			Vector3 draw = ENTITY::GET_ENTITY_COORDS(e, 1);
			GRAPHICS::DRAW_MARKER(0, draw.x, draw.y, draw.z + 2.5f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, bannerRect.r, bannerRect.g, bannerRect.b, 225, 1, 1, 0, 1, 0, 0, 0);
		}
		
	void CNetwork::whosTalking()
		{

			for (int i = 0; i <= 32; i++)
			{
				if (i == PLAYER::PLAYER_ID())continue;
				int Handle = PLAYER::GET_PLAYER_PED(i);

				if (NETWORK::NETWORK_IS_PLAYER_TALKING(Handle))
				{
					char* handle = (char*)PLAYER::GET_PLAYER_NAME(i);
					CUtil::notifyBottom(handle);
				}
			}
		}

	void CNetwork::ESP(Player target, Ped playerPed, NativeMenu::RGBA bannerRect)
		{
			if (target != PLAYER::PLAYER_ID() && ENTITY::DOES_ENTITY_EXIST(playerPed))
			{
				int r = bannerRect.r, g = bannerRect.g, b = bannerRect.b;
				Vector3 entitylocation = ENTITY::GET_ENTITY_COORDS(playerPed, 1);
				Vector3 top1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
				Vector3 top2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z + .8f, NULL };
				Vector3 top3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
				Vector3 top4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z + .8f, NULL };
				Vector3 bottom1world = { entitylocation.x + 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
				Vector3 bottom2world = { entitylocation.x - 0.3f, NULL, entitylocation.y + 0.3f, NULL, entitylocation.z - .8f, NULL };
				Vector3 bottom3world = { entitylocation.x + 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };
				Vector3 bottom4world = { entitylocation.x - 0.3f, NULL, entitylocation.y - 0.3f, NULL, entitylocation.z - .8f, NULL };

				GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top2world.x, top2world.y, top2world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, top4world.x, top4world.y, top4world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, top3world.x, top3world.y, top3world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, top3world.x, top3world.y, top3world.z, r, g, b, 255);

				GRAPHICS::DRAW_LINE(bottom1world.x, bottom1world.y, bottom1world.z, bottom2world.x, bottom2world.y, bottom2world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(bottom2world.x, bottom2world.y, bottom2world.z, bottom4world.x, bottom4world.y, bottom4world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom4world.x, bottom4world.y, bottom4world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(bottom3world.x, bottom3world.y, bottom3world.z, bottom1world.x, bottom1world.y, bottom1world.z, r, g, b, 255);

				GRAPHICS::DRAW_LINE(top1world.x, top1world.y, top1world.z, bottom1world.x, bottom1world.y, bottom1world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(top2world.x, top2world.y, top2world.z, bottom2world.x, bottom2world.y, bottom2world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(top3world.x, top3world.y, top3world.z, bottom3world.x, bottom3world.y, bottom3world.z, r, g, b, 255);
				GRAPHICS::DRAW_LINE(top4world.x, top4world.y, top4world.z, bottom4world.x, bottom4world.y, bottom4world.z, r, g, b, 255);

				Vector3 locationOne = entitylocation;
				Vector3 locationTwo = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), false);
				GRAPHICS::DRAW_LINE(locationOne.x, locationOne.y, locationOne.z, locationTwo.x, locationTwo.y, locationTwo.z, r, g, b, 255);
			}
		}

	void CNetwork::moneyDrop(Vector3 coords)
		{
			unsigned int prop_alien_egg_01 = 1803116220;
			//int bagAmount = GAMEPLAY::GET_RANDOM_INT_IN_RANGE(11000, 11999);
			if (STREAMING::HAS_MODEL_LOADED(PickupTypeMoneyPaperBag))
				STREAMING::REQUEST_MODEL(PickupTypeMoneyPaperBag);
			if (STREAMING::HAS_MODEL_LOADED(prop_alien_egg_01))
				STREAMING::REQUEST_MODEL(prop_alien_egg_01);
			//while (!STREAMING::HAS_MODEL_LOADED(PickupTypeMoneyPaperBag)) WAIT(0);
			for (int i = 0; i > 5; i++) {
				GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(0.f, 1.f);
				OBJECT::CREATE_AMBIENT_PICKUP(PickupTypeMoneyPaperBag, coords.x, coords.y, coords.z + GAMEPLAY::GET_RANDOM_FLOAT_IN_RANGE(1.f, 1.8f), 0, 2000, prop_alien_egg_01, 0, 1);
				OBJECT::CREATE_AMBIENT_PICKUP(PickupTypeMoneyPurse, coords.x, coords.y, coords.z + 1.f, 6, 2000, prop_alien_egg_01, 1, 1);

			}
			//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(0x1E9A99F8);
		}

	void CNetwork::loop_fuckCam(Player Target)
		{
			Ped playerPed = PLAYER::GET_PLAYER_PED(Target);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
			FIRE::ADD_EXPLOSION(pCoords.x, pCoords.y, pCoords.z + 15, ExplosionTypeBlimp, 999999.5f, false, true, 1.0f);
		}

	void CNetwork::loop_annoyBomb(Player Target)
		{
			Ped playerPed = PLAYER::GET_PLAYER_PED(Target);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
			FIRE::ADD_EXPLOSION(pCoords.x, pCoords.y, pCoords.z, ExplosionTypeBlimp, 9.0f, true, false, 0.0f);
		}

	void CNetwork::loop_forcefield(Player Target)
		{
			Ped playerPed = PLAYER::GET_PLAYER_PED(Target);
			Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, 0);
			FIRE::ADD_EXPLOSION(pCoords.x, pCoords.y, pCoords.z, ExplosionTypeCar, 9.0f, false, true, 0.0f);
		}

}

class VehicleInfo {
private:
	/* Meta Info */
	std::string mName;				//Meta Plaintext Model Name
	std::string cName;				//Meta User-Defined Name
	Hash hash;						//Meta DWORD Model Hash

	/* Paint */
	int hColour;					//Paint HUD Colour
	int hLightColour;				//Paint HUD Light Colour
	int priType;					//Paint Primary Type
	int priCol;						//Paint	Primaty Colour
	int secType;					//Paint Secondary Type
	int secCol;						//Paint Secondary Colour
	int secR = 0; 					//Paint Secondary R Val (0-255)
	int secG = 0; 					//Paint Secondary G Val (0-255)
	int secB = 0; 					//Paint Secondary B Val (0-255)
	int priR = 0; 					//Paint Primary R Val (0-255)
	int priG = 0; 					//Paint Primary G Val (0-255)
	int priB = 0;					//Paint Primary B Val (0-255)
	int Prnd;						//Paint
	int pCol;						//Paint Pearlescent Colour
	int wCol;						//Paint Wheel Colour

	bool nEnabled;					//Paint Neon Enabled
	int neonR = 255;				//Paint Neon R Val (0-255)
	int neonG = 255;				//Paint Neon G Val (0-255)
	int neonB = 255;				//Paint Neon B Val (0-255)
	int smokeR = 255;				//Paint Tyre Smoke R Val (0-255)
	int smokeG = 255;				//Paint Tyre Smoke G Val (0-255)
	int smokeB = 255;				//Paint Tyre Smoke B Val (0-255)

	/* Mod Details */
	int wType;						//MOD Wheel Type
	int wTint;						//MOD Window Tint
	int pIndex;						//MOD Plate Index
	char* pText;					//MOD Plate Text

	/* Handling Info */

	/* Vehicle Meta */
	float pFade;					//VMeta Paint Fade
	float eHealth;					//VMeta Engine Health
	bool tBullet;					//VMeta Bulletproof Tyres !GET_VEHICLE_TYRES_CAN_BURST(veh);
	bool tCustom;					//VMeta Custom Tyres GET_VEHICLE_MOD_VARIATION(veh, 23);
	bool eExist[10];				//VMeta Vehicle Extras Bool Array

public:
	VehicleInfo(Vehicle vehicle) {
		this->hash = ENTITY::GET_ENTITY_MODEL(vehicle);
		this->mName = UI::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(this->hash));
	}
};