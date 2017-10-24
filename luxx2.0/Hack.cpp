#include "stdafx.h"

/* Initialise Reclass Shit */
CWorld* CHack::m_pCWorld = nullptr;
CPed* CHack::m_pCPedPlayer = nullptr;
CWeaponInfo* CHack::m_pCWeapon = nullptr;
CAmmo* CHack::m_pCAmmo = nullptr;
CVehicle* CHack::m_pCVehicle = nullptr;
CVehicleHandling* CHack::m_pCVehicleHandling = nullptr;

CVehicleHandling CHack::m_CVehicleHandling;

/* Initialise Class Variables */
Variables::CPlayer m_player;
Variables::CWeapon m_weapon;
Variables::CMisc m_misc;
Variables::CNetwork m_network;
Variables::CVehicle m_vehicle;

/* Initialise Functions */
Features::CUtil m_CUtil;
Features::CVehicle m_CVehicle;
Features::CPlayer m_CPlayer;
Features::CWeapon m_CWeapon;
Features::CNetwork m_CNetwork;

/* Generate Function Pointers */
Features::CUtil* m_pCUtil = &m_CUtil;
Features::CVehicle* m_pCVehicle = &m_CVehicle;
Features::CPlayer* m_pCPlayer = &m_CPlayer;
Features::CWeapon* m_pCWeapon = &m_CWeapon;
Features::CNetwork* m_pCNetwork = &m_CNetwork;

/* Initialise Menu Variables & Generate Pointer */
NativeMenu::CMenu menu(m_player, m_weapon, m_misc, m_network, m_vehicle);
NativeMenu::CMenu* p_menu = &menu;

/* Currently Selected Player */
Player selectPlayer;

Ini theme("theme");

/* Test Vars */
float fAccel;

void loops()
{
	/* Common variables */
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	/* loops up in here */

	/* Vehicle Hotkeys */
	if (m_vehicle.hRepair)
		p_menu->HotKey([] { m_pCVehicle->repair(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, p_menu->repairKey);
	if (m_vehicle.hClean)
		p_menu->HotKey([] { m_pCVehicle->clean(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, p_menu->cleanKey);
	if (m_vehicle.hMax)
		p_menu->HotKey([] { m_pCVehicle->maxUpgrade(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, p_menu->upgradeKey);
	if (m_vehicle.hFlip)
		p_menu->HotKey([] { VEHICLE::SET_VEHICLE_ON_GROUND_PROPERLY(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, p_menu->flipKey);
	if (m_vehicle.hAir)
		p_menu->HotKey([] { m_pCVehicle->repair(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, p_menu->airKey);

	/* Gameplay Hotkeys */
	p_menu->HotKey([] { CHooking::unLoad(); }, p_menu->unloadKey);
	p_menu->HotKey([] { m_pCUtil->tpToMarker(); }, p_menu->teleKey);

	/*if (GetAsyncKeyState(p_menu->repairKey) & 1) {
		m_pCVehicle->repair(VEHICLE::GET_LAST_DRIVEN_VEHICLE());
	}	if (GetAsyncKeyState(p_menu->unloadKey) & 1) {
		p_menu->drawSubtitle("Unloading...");
		CHooking::unLoad();
	}
	if (GetAsyncKeyState(p_menu->teleKey) & 1) {
		m_pCUtil->tpToMarker();
	}*/

	if (m_player.pGodMode) {
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
	}

	if (m_player.pDemiGod) {
		CHack::m_pCWorld->CPedLocalPlayer->fHealth = CHack::m_pCWorld->CPedLocalPlayer->fHealthMax;
	}

	if (m_player.pInvisible) {
		ENTITY::SET_ENTITY_VISIBLE(playerPed, false, false);
	}

	if (m_player.neverWanted) {
		//CHack::m_pCWorld->CPedLocalPlayer->pCPlayerInfo->CWantedData.dwWantedLvl = 0;
		//CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling->fAcceleration = m_vehicle.accelMult;
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(player);
	}

	if (m_player.pCleanPlayer) {
		m_pCPlayer->cleanPlayer();
	}

	if (m_player.pSuperJump) {
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	if (m_player.pFastRun) {
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49f);
	}

	if (m_player.pSuperRun) {
		m_pCPlayer->superRun();
	}

	if (m_player.pFastSwim) {
		PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(player, 1.49f);
	}

	if (m_player.pNoRagdoll) {
		PED::SET_PED_CAN_RAGDOLL(playerPed, false);
		PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(playerPed, false);
	}

	if (m_player.pShrink) {
		PED::SET_PED_CONFIG_FLAG(playerPed, 223, true);
	}

	if (m_player.pNightVision) {
		GRAPHICS::SET_NIGHTVISION(true);
	}

	if (m_player.pSlowMotion) {
		GAMEPLAY::SET_TIME_SCALE(0.4f);
	}

	if (m_player.pCollision) {
		ENTITY::SET_ENTITY_COLLISION(playerPed, false, true);
	}

	if (m_weapon.unlimitedAmmo) {
		//WEAPON::SET_PED_INFINITE_AMMO_CLIP(playerPed, true);
		m_pCWeapon->infiniteAmmo();
	}

	if (m_weapon.explosiveBullets) {
		GAMEPLAY::SET_EXPLOSIVE_AMMO_THIS_FRAME(player);
	}

	if (m_weapon.fireAmmo) {
		GAMEPLAY::SET_FIRE_AMMO_THIS_FRAME(player);
	}

	if (m_weapon.explosiveHands) {
		GAMEPLAY::SET_EXPLOSIVE_MELEE_THIS_FRAME(player);
	}

	if (m_weapon.infiniteParachutes) {
		m_pCWeapon->infiniteParachute();
	}

	if (m_weapon.ammoType) {
		m_pCWeapon->ammoModification(m_weapon.ammoModType);
	}

	if (m_weapon.damageModifier > 1.0f) {
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, m_weapon.damageModifier);
	}
	else if (m_weapon.damageModifier == 1.0f) {
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, 1.0f);
	}

	if (m_weapon.rapidFire) {
		m_pCWeapon->rapidFire();
	}

	if (m_weapon.noRecoil) {
		CHack::m_pCWorld->CPedLocalPlayer->pCWeaponManager->CWeaponCur->fRecoilMultiplier = 0.0f;
	}

	if (m_weapon.noSpread) {
		CHack::m_pCWorld->CPedLocalPlayer->pCWeaponManager->CWeaponCur->fSpread = 0.0f;
	}

	if (m_weapon.noReload) {
		CHack::m_pCWorld->CPedLocalPlayer->pCWeaponManager->CWeaponCur->fReloadTimeMultiplier = 0.0f;
	}

	if (m_misc.printFps) {
		m_pCUtil->printFPS();
	}

	if (m_misc.printSpeed) {
		m_pCUtil->printSpeed();
	}

	if (m_network.showTalking) {
		m_pCNetwork->whosTalking();
	}

	if (m_vehicle.handleTest) {
		if (CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast != nullptr &&
			CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling != nullptr)
		{
			if (CHack::m_pCVehicleHandling != CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling) {
				if (CHack::m_pCVehicleHandling != nullptr) {
					CHack::m_pCVehicleHandling->fAcceleration = CHack::m_CVehicleHandling.fAcceleration;
					CHack::m_pCVehicleHandling->fBrakeForce = CHack::m_CVehicleHandling.fBrakeForce;
					CHack::m_pCVehicleHandling->fCamberStiffnesss = CHack::m_CVehicleHandling.fCamberStiffnesss;
					CHack::m_pCVehicleHandling->fDeformationDamageMult = CHack::m_CVehicleHandling.fDeformationDamageMult;
					CHack::m_pCVehicleHandling->fSuspensionLowerLimit = CHack::m_CVehicleHandling.fSuspensionLowerLimit;
				}
				else
					p_menu->drawSubtitle("m_pCVehicleHandling == nullptr");
				CHack::m_pCVehicleHandling = CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling;
				CHack::m_CVehicleHandling = *CHack::m_pCVehicleHandling;
				if (fAccel != CHack::m_CVehicleHandling.fAcceleration)
					CHack::m_CVehicleHandling.fAcceleration = fAccel;
				//CHack::m_CVehicleHandling.getAccel();
			}
			else
				p_menu->drawSubtitle("m_pCVehicleHandling == pCVehicleHandling");
		}
		else
			p_menu->drawSubtitle("pCVehicleLast || pCVehicleHandling == nullptr");
	}

	if (m_vehicle.rActive) {
		m_pCVehicle->loop_rainbow(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), *p_menu);
	}

	/* Lobby Loops */
	for (int i = 0; i < 30; i++)
	{
		Ped playerPed = PLAYER::GET_PLAYER_PED(i);
		Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, true);

		bool validPlayer = NETWORK::NETWORK_IS_PLAYER_CONNECTED(i);

		if (p_menu->moneyDrop[i])
		{
			if (!validPlayer) p_menu->moneyDrop[i] = false;
			else if (p_menu->ExplodeDelay < GetTickCount())
			{
				m_pCNetwork->moneyDrop(coords);
			}
		}
		if (p_menu->fuckCamera[i])
		{
			if (!validPlayer) p_menu->fuckCamera[i] = false;
			else if (p_menu->ExplodeDelay < GetTickCount())
			{
				m_pCNetwork->loop_fuckCam(i);
			}
		}
		if (p_menu->freezePlayer[i])
		{
			if (!validPlayer) p_menu->freezePlayer[i] = false;
			else if (p_menu->ExplodeDelay - 50 < GetTickCount())
			{
				//m_pCNetwork->clearpTasks(i);
			}
		}
		if (p_menu->annoyLoop[i])
		{
			if (!validPlayer) p_menu->annoyLoop[i] = false;
			else if (p_menu->ExplodeDelay < GetTickCount())
			{
				m_pCNetwork->loop_annoyBomb(i);
			}
		}
		if (p_menu->forcefield[i])
		{
			if (!validPlayer) p_menu->forcefield[i] = false;
			else if (p_menu->ExplodeDelay < GetTickCount())
			{
				m_pCNetwork->loop_forcefield(i);
			}
		}
		if (p_menu->killPed [i])
		{
			if (!validPlayer) p_menu->killPed[i] = false;
			//	else
			//		online::betterPedMoney(i);
		}
		if (p_menu->trackPlayer[i]) {
			if (!validPlayer) p_menu->trackPlayer[i] = false;
			else
				m_pCNetwork->ESP(i, playerPed, p_menu->titleRect);
		}

		if (p_menu->StealthDelay < GetTickCount())	p_menu->StealthDelay = GetTickCount() + 2000;
		if (p_menu->ExplodeDelay < GetTickCount())  p_menu->ExplodeDelay = GetTickCount() + 200;

	}
}

void modelChanger()
{
	p_menu->Title("MODEL OPTIONS");
	//refresh model
	//input custom model
	//random model
	//subs here with models
}

void animationOps()
{
	p_menu->Title("ANIMATION OPTIONS");
}

void selfOptions()
{
	p_menu->Title("SELF OPTIONS");

	p_menu->Submenu("Model options", modelChanger, { "Become any model in the game." });
	p_menu->Submenu("Animation options", animationOps, { "Choose any animation, you desire." });

	p_menu->ToggleCallback("Invincibility", &m_player.pGodMode, nullptr, [] { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_ID(), false); }, { "Become a God." });
	p_menu->Toggle("Demi-god", &m_player.pDemiGod, { "Explosives will ~r~kill~s~ you." });
	p_menu->ToggleCallback("Invisibility", &m_player.pInvisible, nullptr, [] {  ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false); }, { "Be a total ~c~ghost~s~." });
	p_menu->Toggle("Never wanted", &m_player.neverWanted, { "Once toggled, cops will turn a blind-eye." });
	p_menu->OptionCallBack("Give armour and health", [] { Features::CPlayer::healArmor(); }, { "Give health and armour in desperate situations!" });
	p_menu->OptionCallBack("Clean player", [] { Features::CPlayer::cleanPlayer(); }, { "When you're ~~c~dirty~s~." });
	p_menu->Toggle("Loop clean player", &m_player.pCleanPlayer, { "will clean you automatically." });
	p_menu->Toggle("Super jump", &m_player.pSuperJump, { "Jump ~g~higher~s~ than usual." });
	p_menu->ToggleCallback("Fast run", &m_player.pFastRun, nullptr, [] { PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.f); }, { "Run ~g~faster~s~ than usual." });
	p_menu->Toggle("Super run", &m_player.pSuperRun, { "Run even faster!" });
	p_menu->ToggleCallback("Fast swim", &m_player.pFastSwim, nullptr, [] { PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.f); }, { "Swim like ~b~Phelps~s~. " });
	p_menu->ToggleCallback("No ragdoll", &m_player.pNoRagdoll, nullptr, [] { PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false); PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false); });
	p_menu->ToggleCallback("Shrink", &m_player.pShrink, nullptr, [] { PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false); }, { "Be a ~b~cute~s~ midget." });
	p_menu->ToggleCallback("Night vision", &m_player.pNightVision, nullptr, [] { GRAPHICS::SET_NIGHTVISION(false); });
	p_menu->ToggleCallback("Slow motion", &m_player.pSlowMotion, nullptr, [] { GAMEPLAY::SET_TIME_SCALE(1.f); }, { "Slow the world down." });
	p_menu->OptionCallBack("Clone", [] { Features::CGameplay::clonePed(PLAYER::PLAYER_PED_ID()); });
	p_menu->ToggleCallback("Collision", &m_player.pCollision, nullptr, [] { ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, false); }, { "Collide with nothing." });
}

void attackerMenu() {
	p_menu->Title("Send Attackers");
	p_menu->OptionCallBack("Railgun Jesus", [] { m_pCNetwork->attackJesus(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "PRAISE THE LAAAWWD!" });
	p_menu->OptionCallBack("Naughty Cops 1", [] { m_pCNetwork->attackCops(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	p_menu->OptionCallBack("Naughty Cops 2", [] { m_pCNetwork->sendCops(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	p_menu->OptionCallBack("SWAT Team", [] { m_pCNetwork->attckSwat(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	p_menu->OptionCallBack("SWAT Team (Riot)", [] { m_pCNetwork->attackSwatRiot(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	p_menu->OptionCallBack("Tanks", [] {m_pCNetwork->attackTanks(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
}

void networkPlayer() {
	p_menu->Title(PLAYER::GET_PLAYER_NAME(selectPlayer));
	p_menu->OptionCallBack("Give Weapons", [] { m_pCWeapon->giveAllGuns(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "Give Player All Weapons" }); //1
	p_menu->OptionCallBack("Remove Weapons", [] {m_pCWeapon->removeAllWeapons(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "No ~q~Weps~s~ for u" }); //private																	   //p_menu->OptionCallback("Give Tronbike", "~r~Only works when close, this will crash you"); //test 1
	p_menu->OptionCallBack("Clone Vehicle", [] {m_pCVehicle->clone(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "Like theft but funnier" }); //2
	p_menu->Submenu("Send Attackers", attackerMenu, { "Like ~y~MerryWeather~s~, but without the bills" }); //3
	p_menu->OptionCallBack("Give Firework Launcher", [] {m_pCNetwork->dropWeapon("WEAPON_FIREWORK", PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "WIP" }); //4
	//p_menu->OptionCallback("Kick From Vehicle", [] {playerKickVeh(sel.pedID); }, ""); //private																										 //p_menu->OptionCallback("Delete Vehicle", [] {delete_vehicle(sel.pedID); }, ""); //private
	p_menu->OptionCallBack("Shoot Player", [] {m_pCNetwork->shootPed(selectPlayer); }, { "Random Ped Snipes Player" });
	p_menu->Toggle("Drop 2k Bags", &p_menu->moneyDrop[selectPlayer], { "RISKY AS ~r~FUCK~s~ (bad idea)" }); //test 5
	p_menu->Toggle("Freeze Player", &p_menu->freezePlayer[selectPlayer], { "" }); //test
	p_menu->Toggle("Fuck Camera", &p_menu->fuckCamera[selectPlayer], { "Like the most intense drunk cam ever" }); //test
	p_menu->Toggle("Annoying Loop", &p_menu->annoyLoop[selectPlayer], { "Doesn't do damage, however is irritating as balls" }); //test
	p_menu->Toggle("Forcefield", &p_menu->forcefield[selectPlayer], { "Makes everything 10x Harder" }); //test														  //p_menu->OptionCallback("TP to Me"); //4
	p_menu->Toggle("Explosion Loop", &p_menu->explodePlayer[selectPlayer], { "Take a wild guess what it does" });
	p_menu->Toggle("Track Player", &p_menu->trackPlayer[selectPlayer], { "Track Player's movement with ~g~ESP~s~" });
	p_menu->OptionCallBack("TP to Player", [] {m_pCUtil->tpToPlayer(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" }); //5
	//p_menu->OptionCallback("TP to Waypoint", "WIP"); //6
	//p_menu->OptionCallback("Clone Crash"); //private
	//p_menu->OptionCallback("Send Warning Text", [] {online::player::sendText(sel.ID, sel.sName + ", ya bish ~g~gitfukt ~r~<3"s); }, "");
	if (NETWORK::NETWORK_IS_HOST())
		p_menu->OptionCallBack("Kick Player", [] { m_pCNetwork->kickPlayer(selectPlayer); }, { "Host Only" });

}

void playerList() {
	p_menu->Title("Player Index");
	for (int i = 0; i < 32; i++) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			if (p_menu->aPlayer(PLAYER::GET_PLAYER_NAME(i), i, networkPlayer))
				selectPlayer = i;
	}
	if (m_network.drawMarker)
		m_pCNetwork->loop_drawMarker(p_menu->getOption() - 1, p_menu->titleRect);

	/*old test option for drawing player info - useful for debug*/
	/*if (testOptions) {
		drawPlayerInfo(currentOption - 1);
	}*/
}

void network()
{
	p_menu->Title("NETWORK");
	//p_menu->OptionCallBack("Hello bish", [] {  NativeMenu::CMenu::drawSubtitle("Sup"); });
	p_menu->Submenu("Player List", playerList, { "Shows all the ~b~Players~s~  in your lobby" });
	p_menu->Toggle("Box ESP", &m_network.boxESP, { "Draw a box around each player." });
	p_menu->Toggle("Show Talking", &m_network.showTalking, { "Displays who's talking in a lobby" });
}

void pedManagement()
{
	p_menu->Title("PED MANAGER");
}

void savedLocations()
{
	p_menu->Title("SAVED LOCATIONS");
}

void interiors()
{
	p_menu->Title("INTERIORS");
	p_menu->Teleport("Union Depository", { 2.6968f, -667.0166f, 16.1306f });
	p_menu->Teleport("Pac Standard Vault", { 255.8510f, 217.0300f, 101.6833f });
	p_menu->Teleport("Stadium Interior", { -255.4026f, -2022.913f, 30.9743f });
	p_menu->Teleport("Lesters House", { 1273.898f, -1719.304f, 54.771f });
	p_menu->Teleport("Meth Lab Trevor", { 1391.773f, 3608.716f, 38.942f });
	p_menu->Teleport("Strip Club DJ Booth", { 126.135f, -1278.583f, 29.270f });
	p_menu->Teleport("Humane Labs And Research", { 3617.231f, 3739.871f, 28.6901f });
	p_menu->Teleport("Slaughterhouse", { -80.557f, 6220.006f, 31.090f });
	p_menu->Teleport("IAA Office", { 117.220f, -620.938f, 206.047f });
	p_menu->Teleport("FIB Office Top", { 135.733f, -749.216f, 258.152f });
	p_menu->Teleport("10 Car Garage Back Room", { 223.193f, -967.322f, 99.000f });
	p_menu->Teleport("Humane Laps Tunnel", { 3525.495f, 3705.301f, 20.992f });
	p_menu->Teleport("Burnt FIB Building", { 160.868f, -745.831f, 250.063f });
	p_menu->Teleport("Fort Zancudo ATC", { -2358.132f, 3249.754f, 101.451f });
	p_menu->Teleport("Michael's House", { -813.6030f, 179.4740f, 71.1577f });
	p_menu->Teleport("Franklin's Mansion", { 7.1190f, 536.6150f, 176.0280f });
	p_menu->Teleport("Trevor's Trailer", { 1972.6100f, 3817.0400f, 33.4283f });
}

void shopsLocations()
{
	p_menu->Title("SHOP LOCATIONS");
	p_menu->Teleport("Ponsonbys", { -159.2996f, -304.3292f, 39.7333f });
	p_menu->Teleport("Mask Shop", { -1338.16f, -1278.11f, 4.87f });
	p_menu->Teleport("Ammunation", { 247.3652f, -45.8777f, 69.9411f });
}

void miscLocations()
{
	p_menu->Title("Misc. locations");
	p_menu->Teleport("Skyhigh", { -129.9f, 8130.8f, 6705.6f });
	p_menu->Teleport("Out to sea", { 1845.673f, -13787.4884f, 0.0000f });
	p_menu->Teleport("Lighthouse", { 3433.6570f, 5175.4090f, 35.8053f });
	p_menu->Teleport("Coral Reef", { 106.6972f, 7282.0550f, 1.8821f });
	p_menu->Teleport("Del-Pierro Pier", { -1600.0930f, -1041.8920f, 130.0209f });
	p_menu->Teleport("Observatory Roof", { 438.804f, 1076.097f, 352.411f });
	p_menu->Teleport("Kortz Center", { -2243.810f, 264.048f, 174.615f });
	p_menu->Teleport("Mine Shaft", { -595.342f, 2086.008f, 131.412f });
	p_menu->Teleport("Windmill Top", { 2026.677f, 1842.684f, 133.313f });
	p_menu->Teleport("Playboy Mansion", { -1475.234f, 167.088f, 55.841f });
	p_menu->Teleport("Movie Theatre", { 293.089f, 180.466f, 104.301f });
	p_menu->Teleport("Crane Top", { -119.8790f, -977.3570f, 304.2491f });
	p_menu->Teleport("Calafia Train Bridge", { -517.8690f, 4425.2842f, 89.7951f });
}

void usefulLocations()
{
	p_menu->Title("USEFUL LOCATIONS");
	p_menu->Teleport("Los Santos Custom", { -354.6175f, -121.153f, 38.6982f });
	p_menu->Teleport("Airport", { -1102.2910f, -2894.5160f, 13.9467f });
	p_menu->Teleport("Mount Chiliad", { 495.0000f, 5586.0000f, 794.0000f });
	p_menu->Teleport("Maze Bank", { -74.94243f, -818.63446f, 326.174347f });
	p_menu->Teleport("Eclipse Towers", { -792.36f, 296.86f, 87.84f });
	p_menu->Teleport("Mors Mutual", { 408.923f, -1633.860f, 30.29f });
	p_menu->Teleport("Sandy Shores Airport", { 1741.4960f, 3269.2570f, 41.6014f, });
	p_menu->Teleport("Casino and Horsetrack", { 925.329f, 46.152f, 80.908f });
	p_menu->Teleport("Vinewood Sign", { 711.362f, 1198.134f, 348.526f });
	p_menu->Teleport("McKenzie Airfield", { 2121.8564f, 4796.1143f, 41.1517f });
}

void scaryLocations()
{
	p_menu->Title("Weird locations");
	p_menu->Teleport("Sunken Body", { -3161.078f, 3001.998f, -37.974f });
	p_menu->Teleport("Sunken UFO", { 762.426f, 7380.371f, -111.377f });
	p_menu->Teleport("Sunken Hatch", { 4273.950f, 2975.714f, -170.746f, });
	p_menu->Teleport("Ghost", { 3059.620f, 5564.246f,197.091f });
	p_menu->Teleport("Bolingbroke Penitentiary", { 1679.0490f, 2513.7110f, 45.5619f });
	p_menu->Teleport("Alcatraz", { -2159.147f, 5196.89f, 20.00f });
}

void teleport()
{
	p_menu->Title("TELEPORTATION");
	//p_menu->Submenu("Saved locations", savedLocations, { "Save your locations for quick access." });
	p_menu->OptionCallBack("Teleport to map marker", [] { Features::CTeleport::teleportToWaypoint(); }, { "When walking is too overrated." });
	p_menu->OptionCallBack("Teleport to closest vehicle", [] { Features::CTeleport::teleportToVehicle(); }, { "Let ~b~LUXX~s~ find you a vehicle." });

	p_menu->Teleport("Los Santos Customs", { -354.6175f, -121.153f, 38.6982f });
	p_menu->Teleport("Airport", { -1102.2910f, -2894.5160f, 13.9467f });
	p_menu->Teleport("Mount Chilliad", { 495.0000f, 5586.0000f, 794.0000f });
	p_menu->Teleport("Ponsonbys", { -159.2996f, -304.3292f, 39.7333f });
	p_menu->Teleport("Ammunation", { 247.3652f, -45.8777f, 69.9411f });

	p_menu->Submenu("Interiors", interiors, { "Teleport to an interior around the map." });
	p_menu->Submenu("Useful Locations", usefulLocations, { "Useful locations around the map." });
	p_menu->Submenu("Shops", shopsLocations, { "Teleport to one of the shops around the map" });
	p_menu->Submenu("Misc Locations", miscLocations, { "Teleport to a misc location." });
	p_menu->Submenu("Weird Locations", scaryLocations, { "Teleport to a weird location" });
}

void boats()
{
	p_menu->Title("BOATS");
	for (auto vehicle : BoatHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void commercialCars()
{
	p_menu->Title("COMMERCIAL");
	for (int i = 0; i < 9; i++) {
		p_menu->aVehicle(CommercialHash[i].Name, CommercialHash[i].Hash);
	}
}

void compactCars()
{
	p_menu->Title("COMPACT");
	for (auto vehicle : CompactHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void coupesCars()
{
	p_menu->Title("COUPES");
	for (auto vehicle : CoupesHash)	p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void cyclesShite()
{
	p_menu->Title("CYCLES");
	for (auto vehicle : CyclesHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void emergencyCars()
{
	p_menu->Title("EMERGENCY");
		for (auto vehicle : EmergencyHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void superCars()
{
	p_menu->Title("SUPER CARS");
	for (auto vehicle : SuperHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void sportsCars() {
	p_menu->Title("SPORTS CARS");
	for (auto vehicle : SportHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void sportsClassic() {
	p_menu->Title("SPORTS CLASSIC");
	for (auto vehicle : SportsClassic) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void muscleCars() {
	p_menu->Title("MUSCLE CARS");
	for (auto vehicle : MuscleHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void sedanCars() {
	p_menu->Title("SUPER CARS");
	for (auto vehicle : SuperHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void suvCars() {
	p_menu->Title("SUPER CARS");
	for (auto vehicle : SuperHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void offroadCars() {
	p_menu->Title("SUPER CARS");
	for (auto vehicle : SuperHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void motorCycles() {

}

void planes() {
	p_menu->Title("PLANES");
	for (auto vehicle : PlaneHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);

}

void helicopters() {
	p_menu->Title("HELICOPTERS");
	for (auto vehicle : HelicopterHash) p_menu->aVehicle(vehicle.Name, vehicle.Hash);
}

void vansCars() {

}

void militaryCars() {

}

void utilityCars() {

}

void serviceCars() {

}

void industrialCars() {

}

void trailers() {

}

void v_spawnSettings() {
	p_menu->Title("SPAWNER SETTINGS");
	p_menu->Toggle("Wrap In Spawned", &m_vehicle.sWrap, { "Puts player in New Vehicle" });
	p_menu->Toggle("Spawn Maxed", &m_vehicle.sMax, { "~g~Max Upgrades~s~ new Vehicle" });
	p_menu->Toggle("Spawn Airplane in Air", &m_vehicle.sPlaneAir, { "Spawns ~y~Planes~s~ in the air" });
	p_menu->Toggle("Neon Enabled", &m_vehicle.sNeon, { "Enables Default ~q~Neon~s~" });
	p_menu->Toggle("Delete Old Vehicle", &m_vehicle.sDelete, { "~r~Deletes~s~ old Vehicle" });
}

Hash stoH(std::string str) {
	DWORD doubleWord;
	std::string dwordHexString = str;
	std::stringstream dwordStream;
	dwordStream << dwordHexString;
	dwordStream >> std::hex >> doubleWord;
	return doubleWord;
}

void v_test() {
	for (int i = 0; i < m_vehicle.fVehicles.size(); i++) {
	}
	for (int i = 0; i < 150; i++) {
		if (m_pCUtil->receiveVeh(i).name.length() < 1) return;
		m_vehicle.fVehicles[i] = m_pCUtil->receiveVeh(i);
	}
}

void v_favourite() {
	p_menu->Title("FAVOURITE VEHICLES");
	p_menu->OptionCallBack("Refresh List", [] { v_test(); });
	for (auto vehicle : m_vehicle.fVehicles) p_menu->aVehicle(vehicle.name, vehicle.hash);
}

void v_spawner()
{
	p_menu->Title("VEHICLE SPAWNER");
	p_menu->Submenu("Favourite Vehicles", v_favourite, { "Store your favourite vehicles for faster access" }); //1
	p_menu->Submenu("Spawn Settings", v_spawnSettings, { "Adjust Spawn Settings" }); //1
	p_menu->Submenu("Super", superCars, {}); //2
	p_menu->Submenu("Sports", sportsCars, {}); //3
	p_menu->Submenu("Sports Classics", sportsClassic, {}); //4
	p_menu->Submenu("Coupes", coupesCars, {});//5
	p_menu->Submenu("Muscle", muscleCars, {});//6
	p_menu->Submenu("Sedan", sedanCars, {});//7
	p_menu->Submenu("Compacts", compactCars, {});//8
	p_menu->Submenu("SUV", suvCars, {});//9
	p_menu->Submenu("Offroad", offroadCars, {});//10
	p_menu->Submenu("Motorcycles", motorCycles, {});//11
	p_menu->Submenu("Cycles", cyclesShite, {});//12
	p_menu->Submenu("Planes", planes, {});//12
	p_menu->Submenu("Helicopters", helicopters, {});//12
	p_menu->Submenu("Boats", boats, {});//13
	p_menu->Submenu("Vans", vansCars, {});//13
	p_menu->Submenu("Commercial", commercialCars, {});//14
	p_menu->Submenu("Military", militaryCars, {});//15
	p_menu->Submenu("Emergency", emergencyCars, {});//16
	p_menu->Submenu("Utility", utilityCars, {});//17
	p_menu->Submenu("Service", serviceCars, {});//18
	p_menu->Submenu("Industrial", industrialCars, {});//19
	p_menu->Submenu("Trailers", trailers, {});//19
	p_menu->OptionCallBack("Search", [] { m_pCVehicle->manualSelect(false); }, { "Manually Enter Vehicle Name" });//20
	//p_menu->OptionCallback("Random Vehicle", [] {vehicle::random(); }, "Spawns a random vehicle WIP");//21
}

void v_handlingEditor() {
	p_menu->Title("HANDLING EDITOR");
	fAccel = CHack::m_CVehicleHandling.getAccel();
	p_menu->Float("fAcceleration", &fAccel, 0.f, 1000.f, 0.1f, { "Acceleration Test" });

}

void v_modGeneric() {
	p_menu->Title(m_vehicle.sModName);
	if (VEHICLE::GET_VEHICLE_MOD_KIT(VEHICLE::GET_LAST_DRIVEN_VEHICLE()) != 0)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), 0);
	}
	for (int i = -1; i < VEHICLE::GET_NUM_VEHICLE_MODS(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), m_vehicle.sMod); i++) {
		p_menu->VehicleMod(i);
	}
}

void v_customs() {
	p_menu->Title("OPVLs Modshop");

	if (VEHICLE::GET_VEHICLE_MOD_KIT(VEHICLE::GET_LAST_DRIVEN_VEHICLE()) != 0)
	{
		VEHICLE::SET_VEHICLE_MOD_KIT(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), 0);
	}

	p_menu->OptionCallBack("Performance Upgrade", [] { m_pCVehicle->baseUpgrade(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, {});
	p_menu->OptionCallBack("Max Upgrade", [] { m_pCVehicle->maxUpgrade(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, {});

	for (int i = 0; i < 17; i++) {
		if (VEHICLE::GET_NUM_VEHICLE_MODS(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), i))
			p_menu->VehicleModType(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), i, v_modGeneric);
	}

	p_menu->OptionCallBack("Factory Fresh", [] { m_pCVehicle->stockUpgrade(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, {});
	//p_menu->Submenu("Benny's Mods", Benny_Generic, {});
	//p_menu->ToggleCallback("UNK17", VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK17), [] {TOGGLE_VEHICLE_MOD(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK17, !VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK17)); }, "Greatly Increases Acceleration");
	//p_menu->ToggleCallback("Turbo", VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_TURBO), [] {TOGGLE_VEHICLE_MOD(GET_LAST_DRIVEN_VEHICLE(), MOD_TURBO, !VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_TURBO)); }, "Greatly Increases Acceleration");
	//p_menu->ToggleCallback("UNK19", VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK19), [] {TOGGLE_VEHICLE_MOD(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK19, !VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK19)); }, "Greatly Increases Acceleration");
	//p_menu->ToggleCallback("Tiresmoke", VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_TIRESMOKE), [] {TOGGLE_VEHICLE_MOD(GET_LAST_DRIVEN_VEHICLE(), MOD_TIRESMOKE, !VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_TIRESMOKE)); }, "Greatly Increases Acceleration");
	//p_menu->ToggleCallback("UNK21", VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK21), [] {TOGGLE_VEHICLE_MOD(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK21, !VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_UNK21)); }, "Greatly Increases Acceleration");
	//p_menu->ToggleCallback("Xenon Lights", VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_XENONLIGHTS), [] {TOGGLE_VEHICLE_MOD(GET_LAST_DRIVEN_VEHICLE(), MOD_XENONLIGHTS, !VEHICLE::IS_TOGGLE_MOD_ON(GET_LAST_DRIVEN_VEHICLE(), MOD_XENONLIGHTS)); }, "Greatly Increases Acceleration");
	//p_menu->Submenu("Window Tints", windowSubmenu, {});
	//if (GET_NUM_VEHICLE_MODS(GET_LAST_DRIVEN_VEHICLE(), MOD_FRONTWHEELS) > 1)
	//	p_menu->Submenu("Wheels", wheelSubmenu, {});
	//		p_menu->OptionCallback("Wheels ~b~>>", {});
	//if (GET_NUM_VEHICLE_MODS(GET_LAST_DRIVEN_VEHICLE(), MOD_BACKWHEELS) > 1)
	//	p_menu->Submenu("Wheels", wheelSubmenu, {});

}

void v_hotkeys() {
	p_menu->Title("VEHICLE HOTKEYS");
	p_menu->Toggle("Repair", &m_vehicle.hRepair, { "Repairs Vehicle: RSHIFT + R" });
	p_menu->Toggle("Clean", &m_vehicle.hClean, { "Cleans Vehicle: RSHIFT + C" });
	p_menu->Toggle("Max Upgrade", &m_vehicle.hMax, { "Applies Max Upgrades: RSHIFT + U" });
	p_menu->Toggle("Air Ride", &m_vehicle.hAir, { "Enables/Disables Air Suspension: RSHIFT + A" });
	p_menu->Toggle("Set on Ground", &m_vehicle.hAir, { "Sets Car Upright: RSHIFT + F" });
	p_menu->Toggle("Launch", &m_vehicle.hLaunch, { "Launches Vehicle: RSHIFT + L" });
	p_menu->Toggle("Horn Boost", &m_vehicle.hBoost, { "Horn = Faster: H" });
}

void v_options()
{
	p_menu->Title("VEHICLE OPTIONS");
	p_menu->Submenu("Vehicle spawner", v_spawner, { "Spawn ~b~any~s~ vehicle on the go." }, v_favourite);
	p_menu->Submenu("LS Mods", v_customs, {"~r~WIP~s~"});
	p_menu->OptionCallBack("Repair Vehicle", [] { m_pCVehicle->repair(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, { "Like brand new" });
	p_menu->OptionCallBack("Paint Random", [] { m_pCVehicle->paintRandom(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), 1, 1, 1, 1, 1); }, { "Like a gay rainbow" });
	p_menu->Toggle("Rainbow Vehicle", &m_vehicle.rActive, { "Peng AF M9" });
	p_menu->Toggle("Handling Test", &m_vehicle.handleTest, { "WIP" });
	p_menu->Submenu("Handling Editor", v_handlingEditor, { "~r~very WIP" });
	p_menu->OptionCallBack("Delete Vehicle", [] { m_pCVehicle->deleteVehicle(PLAYER::PLAYER_PED_ID()); });
	p_menu->Submenu("Hotkeys", v_hotkeys, { "Manage Vehicle Hotkeys" });
}

void wp_gunshop()
{
	p_menu->Title("GUNSHOP", "shopui_title_gr_gunmod", "shopui_title_gr_gunmod");
	for (char* weapon : weaponNames) {
		p_menu->Weapon(weapon);
	}
}

void wp_ammoMods()
{
	p_menu->Title("AMMO MODIFICATION", "shopui_title_gr_gunmod", "shopui_title_gr_gunmod");
	p_menu->Toggle("Toggle ammo modification", &m_weapon.ammoType, { "Main toggle for ammo modification." });

	if (m_weapon.ammoType) {
		p_menu->OptionCallBack("Stinger", [] { m_weapon.ammoModType = WEAPON_STINGER; });
		p_menu->OptionCallBack("Fireworks", [] { m_weapon.ammoModType = WEAPON_FIREWORK; });
		p_menu->OptionCallBack("Grenade", [] { m_weapon.ammoModType = WEAPON_GRENADE; });
		p_menu->OptionCallBack("Snowball", [] { m_weapon.ammoModType = WEAPON_SNOWBALL; });
		p_menu->OptionCallBack("Flare", [] { m_weapon.ammoModType = WEAPON_FLARE; });
		p_menu->OptionCallBack("Flare gun", [] { m_weapon.ammoModType = WEAPON_FLARE_GUN; });
		p_menu->OptionCallBack("Molotov", [] { m_weapon.ammoModType = WEAPON_MOLOTOV; });
		p_menu->OptionCallBack("Vehicle rocket", [] { m_weapon.ammoModType = WEAPON_VEHICLE_ROCKET; });
	}
}

void wp_options()
{
	p_menu->Title("WEAPON OPTIONS", "shopui_title_gr_gunmod", "shopui_title_gr_gunmod");
	p_menu->Submenu("Gunshop", wp_gunshop, { "View and get all guns." });
	p_menu->Submenu("Ammo modification", wp_ammoMods, { "Modify your ~r~ammunition~s~." });
	p_menu->OptionCallBack("Give all weapons", [] { m_pCWeapon->giveAllGuns(PLAYER::PLAYER_PED_ID()); }, { "Get ~b~all~s~ weapons for free." });
	p_menu->OptionCallBack("Replenish all weapons", [] { m_pCWeapon->replenishAllGuns(PLAYER::PLAYER_PED_ID()); }, { "Replenish ~b~all~s~ weapons." });
	p_menu->OptionCallBack("Upgrade all weapons", [] { m_pCWeapon->upgradeAllGuns(PLAYER::PLAYER_PED_ID()); }, { "Upgrade ~b~all~s~ weapons." });
	p_menu->OptionCallBack("Remove all weapons", [] { m_pCWeapon->removeAllWeapons(PLAYER::PLAYER_PED_ID()); }, { "Why would you do that?" });
	p_menu->Toggle("No recoil", &m_weapon.noRecoil, { "Shoot with ease." });
	p_menu->Toggle("No spread", &m_weapon.noSpread, { "Shoot a laser." });
	p_menu->Toggle("No reload", &m_weapon.noReload, { "Same as infinite ammunition." });
	p_menu->Toggle("Infinite ammunition", &m_weapon.unlimitedAmmo, { "You will ~g~never~s~ run out of bullets." });
	p_menu->Toggle("Explosive ammunition", &m_weapon.explosiveBullets, { "Explosive bullets. Yay!" });
	p_menu->Toggle("Fire ammunition", &m_weapon.fireAmmo, { "Not as powerful as explosive bullets." });
	p_menu->Toggle("Explosive hands", &m_weapon.explosiveHands, { "When weapons just don't work." });
	p_menu->Toggle("Rapid fire", &m_weapon.rapidFire, { "Hopefully, you will shoot faster." });
	p_menu->Float("Weapon damage modifier", &m_weapon.damageModifier, 1.0f, 50.0f, 0.1f, { "Modify your ~g~weapon~s~ damage." });
	p_menu->Toggle("Infinite parachutes", &m_weapon.infiniteParachutes, { "When you run out of parachutes mid-air." });
}

void t_options()
{
	p_menu->Title("TIME OPTIONS");
}

void wo_options()
{
	p_menu->Title("WORLD OPTIONS");
}

void o_options()
{
	p_menu->Title("OBJECT MANIPULATOR");
}

void m_options()
{
	p_menu->Title("MISC. OPTIONS");
	p_menu->Toggle("Print FPS", &m_misc.printFps, { "Draws the current framerate" });
	p_menu->Toggle("Print Speed", &m_misc.printSpeed, { "In place for a working speedo rn" });
}

void w_shooter()
{
	p_menu->Title("SHOOTER OPTIONS"); // Memes
}

void mainRect()
{
	p_menu->Title("Main banner");
	p_menu->Int("Red", &p_menu->titleRect.r, 0, 255, 1, { "Customize the ~r~red~s~ channel." });
	p_menu->Int("Green", &p_menu->titleRect.g, 0, 255, 1, { "Customize the ~g~green~s~ channel." });
	p_menu->Int("Blue", &p_menu->titleRect.b, 0, 255, 1, { "Customize the ~b~blue~s~ channel." });
}

void colourVariant()
{
	p_menu->Title("Colour variant");
	p_menu->Int("Red", &p_menu->optionCounterColour.r, 0, 255, 1, { "Customize the ~r~red~s~ channel." });
	p_menu->Int("Green", &p_menu->optionCounterColour.g, 0, 255, 1, { "Customize the ~g~green~s~ channel." });
	p_menu->Int("Blue", &p_menu->optionCounterColour.b, 0, 255, 1, { "Customize the ~b~blue~s~ channel." });
}

void tTest() {
	p_menu->titleRect; //config.read_rgba("Theme", "Banner");
}

void settings()
{
	p_menu->Title("SETTINGS");
	p_menu->Submenu("Main banner", mainRect, { "Customize the main banner." });
	p_menu->Submenu("Colour variant", colourVariant, { "Customize the main colour." });
	p_menu->OptionCallBack("Reload Config", [] { m_pCUtil->loadConfig(1, p_menu); });
	p_menu->OptionCallBack("load header", [] {m_pCUtil->loadTheme(1, p_menu); });
	p_menu->OptionCallBack("Save Theme", [] { m_pCUtil->saveTheme(1, *p_menu); });
	p_menu->OptionCallBack("test sign in", [] { m_pCUtil->signIn(); });
}

MenuFunc NativeMenu::MAIN_MENU()
{
	p_menu->Title("MAIN MENU");
	p_menu->Submenu("Online", network, { "Extra Online Functions" });
	p_menu->Submenu("Self", selfOptions, { "Character Only Functions" });
//	p_menu->Submenu("Ped management", pedManagement, { "Spawn and manage ~b~PEDs~s~", "and make them your bodyguard!" });
	p_menu->Submenu("Vehicle", v_options, { "~q~Modify~s~, ~g~Repair~s~, ~r~Fuck With~s~" });
	p_menu->Submenu("Weapon options", wp_options, { "Your own mobile ~r~gunstore~s~." });
	p_menu->Submenu("Teleport", teleport, { "Be ~b~anywhere~s~ at any time." });
	//p_menu->Submenu("Time options", timeOptions, { "Control the time." });
	p_menu->Submenu("World", wo_options, { "Is this a ~y~God~s~ simulator?" });
	//p_menu->Submenu("Object manipulator", ObjectMan, { "Spawn and edit objects." });
	p_menu->Submenu("Misc. options", m_options, { "Options where they ~c~don't really belong~s~." });
	//p_menu->Submenu("Shooter options", shooterOptions, { "This is for you, NUP." });
	p_menu->Submenu("Settings", settings, { "Customize ~c~LUXX~s~ to your own liking." });
}

void CHack::mainLoop()
{
	loops();
	p_menu->Main();
}