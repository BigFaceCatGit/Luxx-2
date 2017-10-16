#include "stdafx.h"

Scaleform gGlareHandle;

/* change shite here for version and menu name */
constexpr char* menuName = "LUXX";
constexpr char* menuVersion = "Version: 2.0.1";

namespace NativeMenu {

	CMenu::CMenu() { }

	CMenu::~CMenu() { }

	void CMenu::nextOption()
	{
		if (currentOption < optionCount)
			currentOption++;
		else
			currentOption = 1;
		resetButtonState();
	}

	void CMenu::previousOption()
	{
		if (currentOption > 1)
			currentOption--;
		else
			currentOption = optionCount;
		resetButtonState();
	}

	void CMenu::drawSubtitle(char* text)
	{
		UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
		UI::_ADD_TEXT_COMPONENT_SCALEFORM(text);
		UI::END_TEXT_COMMAND_PRINT(2000, 1);
	}

	bool CMenu::currentMenu(void* current)
	{
		if (current = currentSubmenu)
			return true;

		return false;
	}

	void CMenu::changeSubmenu(void* newSubmenu)
	{
		lastSubmenu[submenuLevel] = currentSubmenu;
		lastOption[submenuLevel] = currentOption;
		currentOption = 1;
		currentSubmenu = reinterpret_cast<SubmenuHandler>(newSubmenu);
		submenuLevel++;
		resetButtonState();
	}

	void CMenu::PrintText(std::string text, int font, float x, float y, float scaleX, float scaleY, RGBA rgba, int position, bool outline)
	{
		if (position == 2) {
			UI::SET_TEXT_WRAP(menux - menuWidth / 2, menux + menuWidth / 2 - optionRightMargin / 2.0f);
		}
		UI::SET_TEXT_JUSTIFICATION(position);

		UI::SET_TEXT_FONT(font);
		if (font == 0) {
			scaleY *= 0.75f;
			y += 0.003f;
		}

		if (outline)
			UI::SET_TEXT_OUTLINE();

		UI::SET_TEXT_SCALE(0.0f, scaleY);
		UI::SET_TEXT_COLOUR(rgba.r, rgba.g, rgba.b, rgba.a);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(CharAdapter(text));
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
	}

	void CMenu::DrawRect(float x, float y, float width, float height, RGBA rgba)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, rgba.r, rgba.g, rgba.b, rgba.a);
	}

	void CMenu::DrawSprite(std::string textureDict, std::string textureName, float x, float y, float width, float height, float rotation, RGBA rgba)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(CharAdapter(textureDict))) {
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(CharAdapter(textureDict), false);
		}
		else {
			GRAPHICS::DRAW_SPRITE(CharAdapter(textureDict), CharAdapter(textureName), x, y, width, height, rotation, rgba.r, rgba.g, rgba.b, rgba.a);
		}
	}

	void CMenu::DrawGlare(float pX, float pY, float sX, float sY, RGBA rgba)
	{
		gGlareHandle = GRAPHICS::REQUEST_SCALEFORM_MOVIE("MP_MENU_GLARE");
		GRAPHICS::DRAW_SCALEFORM_MOVIE(gGlareHandle, pX, pY, sX, sY, rgba.r, rgba.g, rgba.b, rgba.a, false);
	}

	void CMenu::menuBeep(std::string sound)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, CharAdapter(sound), "HUD_FRONTEND_DEFAULT_SOUNDSET", false);
	}

	void CMenu::Title(std::string title, std::string textureDict, std::string textureName)
	{
		optionCount = 0;

		PrintText(menuName, titleFont, menux, menuy - 0.03f, 0.85f, 0.85f, titleText, 0, true);
		PrintText(title, 0, (menux - secondTitleX), (menuy + secondTitleY), 0.475f, 0.475f, optionCounterColour, 1, false);
		PrintText(menuVersion, 0, (menux - thirdTitleX), (menuy + thirdTitleY), 0.475f, 0.475f, optionCounterColour, 2, false);

		/* main header */
		if (textureDict.size() > 0 || textureName.size() > 0) {
			backgroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, textureDict, textureName,
					menux, menuy - 0.0075f, menuWidth, titleHeight, 0.0f, titleSpriteRect));
		}
		else {
			DrawRect(menux, menuy - 0.0075f, menuWidth, titleHeight, titleRect);
		}
	}

	bool CMenu::Submenu(std::string text, void* submenu, std::vector<std::string> details)
	{
		Option(text, details);

		bool thisOption = false;

		if (currentOption == optionCount)
			thisOption = true;

		char* arrowTexture;

		if (thisOption) {
			arrowTexture = "arrowright";
		}
		else {
			arrowTexture = "arrowright";
		}

		bool doDraw = false;
		float textureY;

		if (currentOption <= 16 && optionCount <= 16) {
			doDraw = true;
			textureY = (optionCount * optionHeight + (menuy + 0.016f));
		}
		else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption) {
			doDraw = true;
			textureY = ((optionCount - (currentOption - 16)) * optionHeight + (menuy + 0.016f));
		}

		if (doDraw) {
			int resX, resY;
			GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&resX, &resY);
			float ratio = (float)resX / (float)resY;
			float boxSz = 0.020f; //25
			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "commonmenu", arrowTexture,
					menux + menuWidth / 2.0f - optionRightMargin, (textureY + mainoptiony), boxSz / ratio, boxSz, 0.0f, thisOption ? optionCounterColour : options)
			);
		}

		if (optionPress && currentOption == optionCount) {
			changeSubmenu(submenu);
			return true;
		}
		return false;
	}

	bool CMenu::Option(std::string text, std::vector<std::string> details)
	{
		optionCount++;

		bool thisOption = false;
		if (currentOption == optionCount) thisOption = true;

		bool doDraw = false;
		float optiony;
		float optiontexty;

		if (currentOption <= 16 && optionCount <= 16)
		{
			doDraw = true;
			optiony = optionCount * optionHeight + (menuy + textureTextOffset);
			optiontexty = (optionCount * optionHeight + menuy);
		}
		else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption)
		{
			doDraw = true;
			optiony = (optionCount - (currentOption - 16)) * optionHeight + (menuy + textureTextOffset);
			optiontexty = ((optionCount - (currentOption - 16)) * optionHeight + menuy);
		}

		if (doDraw) {
			DrawRect(menux, optiony, menuWidth, optionHeight, optionsrect);
			if (thisOption) {
				if (HighlTextureIndex < 1 || HighlTextureIndex >= TextureDicts.size()) {

					highlightsDrawCalls.push_back(
						std::bind(&CMenu::DrawRect, this, menux, optiony, menuWidth, optionHeight, scroller
						));

					//DrawRect(menux, optiony, menuWidth, optionHeight, scroller);
				}
				else {
					highlightsDrawCalls.push_back(
						std::bind(&CMenu::DrawSprite, this, TextureDicts[HighlTextureIndex], TextureNames[HighlTextureIndex],
							menux, optiony, menuWidth, optionHeight, 0.0f, scroller)
					);
				}
				if (details.size() > 0) {
					this->details = details;
				}
			}
			PrintText(text, 0, (menux - menuWidth / 2.0f) + menuTextMargin, (optiontexty + mainoptiony), optionTextSize, optionTextSize, thisOption ? optionsBlack : options, 1, false);
		}
		return false;
	}

	bool CMenu::OptionCallBack(std::string text, std::function<void()> function, std::vector<std::string> details)
	{
		Option(text, details);

		if (optionPress && currentOption == optionCount) {
			resetButtonState();
			function();
			return true;
		}
		return false;
	}

	/* our main toggle function with checkboxes */
	bool CMenu::Toggle(std::string text, bool* boolean, std::vector<std::string> details)
	{
		Option(text, details);

		bool thisOption = false;

		if (currentOption == optionCount)
			thisOption = true;

		//char* tickBoxTexture;
		RGBA optionColours;
		optionColours = options;

		/*if (thisOption) {
		tickBoxTexture = *boolean ? "shop_box_tickb" : "shop_box_blankb";
		}
		else {
		tickBoxTexture = *boolean ? "shop_box_tick" : "shop_box_blank";
		}*/

		if (*boolean) {
			optionColours.r = 30;
			optionColours.g = 144;
			optionColours.b = 255;
		}
		else {
			optionColours.r = 14; //80
			optionColours.g = 14; //85
			optionColours.b = 14; //90
		}

		bool doDraw = false;
		float textureY;

		if (currentOption <= 16 && optionCount <= 16) {
			doDraw = true;
			textureY = (optionCount * optionHeight + (menuy + 0.016f));
		}
		else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption) {
			doDraw = true;
			textureY = ((optionCount - (currentOption - 16)) * optionHeight + (menuy + 0.016f));
		}

		if (doDraw) {
			int resX, resY;
			GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&resX, &resY);
			float ratio = (float)resX / (float)resY;
			float boxSz = 0.03f;

			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "commonmenu", "common_medal",
					menux + menuWidth / 2.0f - optionRightMargin, (textureY + mainoptiony), boxSz / ratio, boxSz, 0.0f, optionColours)
			);

			//Can be used for something else :eyes:
			/*if (*boolean) {
			foregroundDrawCalls.push_back(
			std::bind(&CMenu::DrawSprite, this, "commonmenu", "mp_specitem_cash",
			menux + menuWidth / 2.0f - optionRightMargin, (textureY + mainoptiony), boxSz / ratio, boxSz, 0.0f, optionColours)
			);
			}*/
		}

		if (optionPress && currentOption == optionCount) {
			//need to do this since it will just be flicking on/off
			resetButtonState();
			*boolean ^= 1;

			return true;
		}
		return false;
	}

	bool CMenu::ToggleCallback(std::string text, bool* boolean, std::function<void()> trueFunc, std::function<void()> falseFunc, std::vector<std::string> details)
	{
		Toggle(text, boolean, details);

		if (*(bool*)boolean) {
			if (trueFunc != nullptr) trueFunc();

			return true;
		}
		else {
			if (falseFunc != nullptr) falseFunc();

			return true;
		}

		return false;
	}

	bool CMenu::Int(std::string text, int* var, int min, int max, int step, std::vector<std::string> details)
	{
		Option(text, details);

		bool thisOption = false;

		if (currentOption == optionCount)
			thisOption = true;

		if (currentOption <= 16 && optionCount <= 16)
			PrintText("[ " + std::to_string(*var) + " ]", 0, menux + menuWidth / 2.0f - optionRightMargin, ((optionCount * optionHeight + menuy) + mainoptiony), optionTextSize, optionTextSize, thisOption ? optionsBlack : options, 2, false);
		else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption)
			PrintText("[ " + std::to_string(*var) + " ]", 0, menux + menuWidth / 2.0f - optionRightMargin, (((optionCount - (currentOption - 16)) * optionHeight + menuy) + mainoptiony), optionTextSize, optionTextSize, thisOption ? optionsBlack : options, 2, false);

		if (currentOption == optionCount) {
			if (leftPress) {
				if (*var <= min) *var = max;
				else *var -= step;

				leftPress = false;
				return true;
			}
			if (*var < min) *var = max;
			if (rightPress) {
				if (*var >= max) *var = min;
				else *var += step;

				rightPress = false;
				return true;
			}
			if (*var > max) *var = min;
		}
		return false;
	}

	bool CMenu::Float(std::string text, float* var, float min, float max, float step, std::vector<std::string> details)
	{
		Option(text, details);

		bool thisOption = false;
		if (currentOption == optionCount)
			thisOption = true;

		char buf[100];
		_snprintf_s(buf, sizeof(buf), "%.5f", *var);

		if (currentOption <= 16 && optionCount <= 16)
			PrintText("[ " + std::string(buf) + " ]", 0, menux + menuWidth / 2.0f - optionRightMargin, ((optionCount * optionHeight + menuy) + mainoptiony), optionTextSize, optionTextSize, thisOption ? optionsBlack : options, 2, false);
		else if (optionCount > currentOption - 16 && optionCount <= currentOption)
			PrintText("[ " + std::string(buf) + " ]", 0, menux + menuWidth / 2.0f - optionRightMargin, (((optionCount - (currentOption - 16)) * optionHeight + menuy) + mainoptiony), optionTextSize, optionTextSize, thisOption ? optionsBlack : options, 2, false);

		if (currentOption == optionCount) {
			if (leftPress) {
				if (*var <= min) *var = max;
				else *var -= step;

				leftPress = false;
				return true;
			}
			if (*var < min) *var = max;
			if (rightPress) {
				if (*var >= max) *var = min;
				else *var += step;

				rightPress = false;
				return true;
			}
			if (*var > max) *var = min;
		}
		return false;
	}

	bool CMenu::Teleport(std::string text, Vector3_t location)
	{
		Option(text);

		if (optionPress && currentOption == optionCount) {
			resetButtonState();

			Entity handle = PLAYER::PLAYER_PED_ID();

			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
				handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(handle, location.x, location.y, location.z, false, false, false);
			STREAMING::LOAD_ALL_OBJECTS_NOW();

			return true;
		}
		return false;
	}

	bool CMenu::Weapon(std::string weapon) {
		std::string displayName = weapon;
		displayName = displayName.substr(7, displayName.length());
		std::transform(displayName.begin(), displayName.end(), displayName.begin(), ::tolower);
		displayName[0] = toupper(displayName[0]);

		Option(displayName);

		if (weapon == "WEAPON_PROXMINE") {
			weapon = "WEAPON_PROXIMINE";
		}
		else if (weapon == "WEAPON_PETROLCAN") {
			weapon = "WEAPON_JERRY_CAN";
		}
		else if (weapon == "WEAPON_BZGAS" || weapon == "WEAPON_SMOKEGRENADE") {
			weapon = "WEAPON_THROWN_BZ_GAS";
		}
		else if (weapon == "WEAPON_STICKYBOMB") {
			weapon = "WEAPON_THROWN_STICKY";
		}
		else if (weapon == "WEAPON_GRENADE") {
			weapon = "WEAPON_THROWN_GRENADE";
		}
		else if (weapon == "WEAPON_MINIGUN") {
			weapon = "WEAPON_HEAVY_MINIGUN";
		}
		else if (weapon == "WEAPON_RPG") {
			weapon = "WEAPON_HEAVY_RPG";
		}
		else if (weapon == "WEAPON_GRENADELAUNCHER" || weapon == "WEAPON_GRENADELAUNCHER_SMOKE") {
			weapon = "WEAPON_HEAVY_GRENADE_LAUNCHER";
		}
		else if (weapon == "WEAPON_HEAVYSNIPER") {
			weapon = "WEAPON_SNIPER_HEAVY";
		}
		else if (weapon == "WEAPON_SNIPERRIFLE") {
			weapon = "WEAPON_SNIPER";
		}
		else if (weapon == "WEAPON_BULLPUPSHOTGUN") {
			weapon = "WEAPON_SHOTGUN_BULLPUP";
		}
		else if (weapon == "WEAPON_ASSAULTSHOTGUN") {
			weapon = "WEAPON_SHOTGUN_ASSAULT";
		}
		else if (weapon == "WEAPON_SAWNOFFSHOTGUN") {
			weapon = "WEAPON_SHOTGUN_SAWNOFF";
		}
		else if (weapon == "WEAPON_PUMPSHOTGUN") {
			weapon = "WEAPON_SHOTGUN_PUMP";
		}
		else if (weapon == "WEAPON_COMBATMG") {
			weapon = "WEAPON_LMG_COMBAT";
		}
		else if (weapon == "WEAPON_MG") {
			weapon = "WEAPON_LMG";
		}
		else if (weapon == "WEAPON_ADVANCEDRIFLE") {
			weapon = "WEAPON_RIFLE_ADVANCED";
		}
		else if (weapon == "WEAPON_CARBINERIFLE") {
			weapon = "WEAPON_RIFLE_CARBINE";
		}
		else if (weapon == "WEAPON_ASSAULTRIFLE") {
			weapon = "WEAPON_RIFLE_ASSAULT";
		}
		else if (weapon == "WEAPON_ASSAULTSMG") {
			weapon = "WEAPON_SMG_ASSAULT";
		}
		else if (weapon == "WEAPON_MICROSMG") {
			weapon = "WEAPON_SMG_MICRO";
		}
		else if (weapon == "WEAPON_PISTOL50") {
			weapon = "WEAPON_PISTOL_50";
		}
		else if (weapon == "WEAPON_APPISTOL") {
			weapon = "WEAPON_PISTOL_AP";
		}
		else if (weapon == "WEAPON_COMBATPISTOL") {
			weapon = "WEAPON_PISTOL_COMBAT";
		}
		bool doDraw = false;
		float textureY;

		if (currentOption <= 16 && optionCount <= 16) {
			doDraw = true;
			textureY = (optionCount * optionHeight + (menuy + 0.016f));
		}
		else if ((optionCount > (currentOption - 16)) && optionCount <= currentOption) {
			doDraw = true;
			textureY = ((optionCount - (currentOption - 16)) * optionHeight + (menuy + 0.016f));
		}

		if (doDraw) {
			int resX, resY;
			GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&resX, &resY);
			float ratio = (float)resX / (float)resY;
			float boxSz = 0.045f;
			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "mpkillquota", weapon,
					menux + menuWidth / 2.0f - optionRightMargin - 0.018f, (textureY + mainoptiony), boxSz / ratio + 0.032f, boxSz, 0.0f, white)
			);
		}

		if (optionPress && currentOption == optionCount) {
			resetButtonState();

			return true;
		}

		return false;
	}

	bool NativeMenu::bdeletevehicle = true;
	bool NativeMenu::bspawninvehicle = true;

	int SpawnVehicle(Hash model, Vector3 pos)
	{
		Vehicle vehicle = 0; int NetID = 0;

		//If player has spawned a vehicle previously, delete old vehicle
		if (bdeletevehicle) {
			int old = PLAYER::GET_PLAYERS_LAST_VEHICLE();
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(old);
			VEHICLE::DELETE_VEHICLE(&old);
		}

		//Get player heading
		float direction = ENTITY::GET_ENTITY_HEADING(PLAYER::PLAYER_PED_ID());

		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_A_VEHICLE(model))
		{
			STREAMING::REQUEST_MODEL(model);

			//test
			//WAIT(500);

			while (!STREAMING::HAS_MODEL_LOADED(model)) {
				return 0;
			}
		}

		//if player is offline
		if (!NETWORK::NETWORK_IS_IN_SESSION()) {
			vehicle = VEHICLE::CREATE_VEHICLE(model, pos.x, pos.y, pos.z, direction, TRUE, TRUE);

			// if bool is true, teleport into spawned vehicle
			if (bspawninvehicle)
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);

			VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, TRUE, TRUE, TRUE);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			return vehicle;
		}

		//rest if player is online
		vehicle = VEHICLE::CREATE_VEHICLE(model, pos.x, pos.y, pos.z, direction, TRUE, TRUE);
		NetID = NETWORK::VEH_TO_NET(vehicle);
		if (!NETWORK::NETWORK_DOES_NETWORK_ID_EXIST(NetID))
			WAIT(0);

		ENTITY::_SET_ENTITY_REGISTER(NetID, TRUE);

		if (NETWORK::NETWORK_GET_ENTITY_IS_NETWORKED(NetID)) NETWORK::SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(NetID, TRUE);

		if (bspawninvehicle)
			PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), vehicle, -1);

		VEHICLE::SET_VEHICLE_ENGINE_ON(vehicle, TRUE, TRUE, TRUE);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);
		//fade in and out, just cause
		NETWORK::NETWORK_FADE_OUT_ENTITY(vehicle, TRUE, FALSE);
		NETWORK::NETWORK_FADE_IN_ENTITY(vehicle, TRUE);

		return vehicle;
	}

	bool CMenu::Vehicle(std::string name, Hash model)
	{
		Vector3 pos = ENTITY::GET_ENTITY_COORDS(PLAYER::PLAYER_PED_ID(), true);
		Option(name);

		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model)) return 0;

		if (optionPress && currentOption == optionCount) {
			resetButtonState();

			if (!STREAMING::HAS_MODEL_LOADED(model)) {
				STREAMING::REQUEST_MODEL(model);
				WAIT(0);
			}

			Features::CVehicle::spawn(model, PLAYER::PLAYER_PED_ID(), 1, 1, 0);
			return true;
		}
		return false;
	}

	void CMenu::DrawDetails(std::vector<std::string> details, float y)
	{
		for (auto i = 0; i < details.size(); i++) {
			PrintText(details[i], 0, (menux - menuWidth / 2.0f) + menuTextMargin, i * optionHeight + y, optionTextSize, optionTextSize, options, 1, false);
		}

		auto tempoptions = optionsrect;
		auto tinyFooter = optionCounterColour;
		RGBA temp = { 14, 14, 14, 175 };

		DrawRect(menux, y - footerOffset, menuWidth, optionHeight / 5, { 14, 14, 14, 175 });
		DrawRect(menux, y, menuWidth, optionHeight / 8, tinyFooter);

		tempoptions.a = 255;

		backgroundDrawCalls.push_back(
			std::bind(&CMenu::DrawRect, this,
				menux, (y)+(details.size() * optionHeight) / 2, menuWidth, optionHeight * details.size(), temp));

	}

	void CMenu::resetButtonState() {
		optionPress = false;
		leftPress = false;
		rightPress = false;
		upPress = false;
		downPress = false;
	}

	void CMenu::disableKeys()
	{
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlNextCamera, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleCinCam, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlPhone, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterMichael, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterFranklin, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterTrevor, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterMultiplayer, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlCharacterWheel, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMeleeAttackLight, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMeleeAttackHeavy, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMeleeAttackAlternate, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMultiplayerInfo, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMapPointOfInterest, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlRadioWheelLeftRight, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleNextRadio, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehiclePrevRadio, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlRadioWheelUpDown, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleNextRadioTrack, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehiclePrevRadioTrack, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleRadioWheel, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleDuck, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleSelectNextWeapon, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleSelectPrevWeapon, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleAttack, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleAttack2, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleExit, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlContext, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectWeapon, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleHeadlight, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleRoof, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleHorn, true);

		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleAim, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehiclePassengerAim, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlFrontendSocialClub, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlFrontendSocialClubSecondary, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlReplayStartStopRecording, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlInteractionMenu, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSaveReplayClip, true);
	}

	void CMenu::DrawMenu()
	{
		/* grab texture size */
		Vector3 texture = GRAPHICS::GET_TEXTURE_RESOLUTION("commonmenu", "arrowright");

		int maxOptionCount = optionCount > 16 ? 16 : optionCount;

		float footerTextY;
		float footerBackY;

		if (optionCount > 16) {
			footerTextY = 17 * optionHeight + menuy;
		}
		else {
			footerTextY = (optionCount + 1) * optionHeight + menuy;
		}
		footerBackY = footerTextY + textureTextOffset;

		/* footer */
		DrawRect(menux, footerBackY, menuWidth, optionHeight, { 14, 14, 14, 175 });

		backgroundDrawCalls.push_back(
			std::bind(&CMenu::DrawSprite, this, TextureDicts[TitleTextureIndex], TextureNames[TitleTextureIndex],
				menux, footerBackY, menuWidth, optionHeight, 0.0f, titleRect)
		);

		/* option counter */
		PrintText(std::to_string(currentOption) + "/" + std::to_string(optionCount),
			0, menux - 0.1f, (footerTextY + mainoptiony), optionTextSize, optionTextSize, optionCounterColour, 2, false);

		/* options background */
		DrawRect(menux, (((menuy + optionHeight) + ((maxOptionCount)* optionHeight) / 2) + mainoptiony), menuWidth, optionHeight * (maxOptionCount), { 14, 14, 14, 150 });

		/* info box */
		if (details.size() > 0)
			DrawDetails(details, footerBackY + optionHeight / 1.5f);

		/* draws our globe */
		foregroundDrawCalls.push_back(
			std::bind(&CMenu::DrawGlare, this, globex, globey, globeSzX, globeSzY, globeColor)
		);

		/* bar under our main title rect */
		DrawRect(menux, barunderRect, menuWidth, 0.032f, secondRect);

		/*
		Indicators
		Included with cheeky cheeky resolution calculator (1920x1080 for now). We need to change this to make it automatic.
		*/
		if (currentOption == 1) {
			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "commonmenu", "arrowright",
					menux, (((maxOptionCount + 1) * optionHeight + (menuy + 0.0175f)) + mainoptiony), texture.x / (float)1920, texture.y / (float)1080, 90.0f, optionCounterColour)
			);
		}
		else if (currentOption == optionCount) {
			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "commonmenu", "arrowright",
					menux, (((maxOptionCount + 1) * optionHeight + (menuy + 0.0175f)) + mainoptiony), texture.x / (float)1920, texture.y / (float)1080, 270.0f, optionCounterColour)
			);
		}
		else {
			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "commonmenu", "arrowright",
					menux, (((maxOptionCount + 1) * optionHeight + (menuy + 0.0125f)) + mainoptiony), texture.x / (float)1920, texture.y / (float)1080, 270.0f, optionCounterColour)
			);
			foregroundDrawCalls.push_back(
				std::bind(&CMenu::DrawSprite, this, "commonmenu", "arrowright",
					menux, (((maxOptionCount + 1) * optionHeight + (menuy + 0.0250f)) + mainoptiony), texture.x / (float)1920, texture.y / (float)1080, 90.0f, optionCounterColour)
			);
		}

		for (auto f : backgroundDrawCalls) { f(); }
		for (auto f : highlightsDrawCalls) { f(); }
		for (auto f : foregroundDrawCalls) { f(); }
		backgroundDrawCalls.clear();
		highlightsDrawCalls.clear();
		foregroundDrawCalls.clear();
		details.clear();

		if (currentOption > optionCount) currentOption = optionCount;
		if (currentOption < 1) currentOption = 1;
	}

	void CMenu::OpenMenuMonitor()
	{
		/* does it all */
		DrawMenu();
		disableKeys();

		/* up */
		if (GetAsyncKeyState(upKey) & 1) {
			menuBeep("NAV_UP_DOWN");
			previousOption();
		}

		/* down */
		if (GetAsyncKeyState(downKey) & 1) {
			menuBeep("NAV_UP_DOWN");
			nextOption();
		}

		/* back/close */
		if (GetAsyncKeyState(backKey) & 1) {
			menuBeep("BACK");
			if (currentSubmenu == MAIN_MENU) {
				currentSubmenu = nullptr;
			}
			else {
				submenuLevel--;
				currentSubmenu = lastSubmenu[submenuLevel];
				currentOption = lastOption[submenuLevel];
			}
		}

		if (GetAsyncKeyState(selectKey) & 1) {
			menuBeep("SELECT");
			resetButtonState();
			optionPress = true;
		}

		/* left */
		if (GetAsyncKeyState(leftKey) & 1) {
			menuBeep("NAV_UP_DOWN");
			leftPress = true;
		}

		/* right */
		if (GetAsyncKeyState(rightKey) & 1) {
			menuBeep("NAV_UP_DOWN");
			rightPress = true;
		}
	}

	void CMenu::ClosedMenuMonitor()
	{
		/* open menu */
		if (GetAsyncKeyState(openKey) & 1) {
			menuBeep("SELECT");
			currentSubmenu = MAIN_MENU;
			submenuLevel = 0;
			currentOption = 1;
		}
	}

	void CMenu::Main()
	{
		if (currentSubmenu != nullptr) {
			currentSubmenu();
			OpenMenuMonitor();
		}
		else {
			ClosedMenuMonitor();
		}
	}
}

