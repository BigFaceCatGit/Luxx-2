#include "stdafx.h"

#define TELEPORT_KEY VK_F4

CWorld* CHack::m_pCWorld = nullptr;
CPed*	CHack::m_pCPedPlayer = nullptr;
CWeaponInfo* CHack::m_pCWeapon = nullptr;
NativeMenu::CMenu menu;

Variables::CPlayer m_player;
Variables::CWeapon m_weapon;
Variables::CMisc m_misc;
Variables::CNetwork m_network;
Variables::CVehicle m_vehicle;

int selectPlayer;

void loops()
{
	/* Common variables */
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	/* loops up in here */

	/* hotkeys */
	if (GetAsyncKeyState(menu.repairKey) & 1) {
		Features::CUtil::tpToMarker();
	}

	if (GetAsyncKeyState(menu.unloadKey) & 1) {
		menu.drawSubtitle("Unloading...");
		CHooking::unLoad();
	}

	if (m_player.pGodMode) {
		ENTITY::SET_ENTITY_INVINCIBLE(player, true);
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
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
	}

	if (m_player.pCleanPlayer) {
		Features::CPlayer::cleanPlayer();
	}

	if (m_player.pSuperJump) {
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
	}

	if (m_player.pFastRun) {
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49f);
	}

	if (m_player.pSuperRun) {
		Features::CPlayer::superRun();
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
		Features::CWeapon::infiniteAmmo();
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
		Features::CWeapon::infiniteParachute();
	}

	if (m_weapon.ammoType) {
		Features::CWeapon::ammoModification(m_weapon.ammoModType);
	}

	if (m_weapon.damageModifier > 1.0f) {
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, m_weapon.damageModifier);
	}
	else if (m_weapon.damageModifier == 1.0f) {
		PLAYER::SET_PLAYER_WEAPON_DAMAGE_MODIFIER(player, 1.0f);
	}

	if (m_weapon.rapidFire) {
		Features::CWeapon::rapidFire();
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
		Features::CUtil::printFPS();
	}

	if (m_misc.printSpeed) {
		Features::CUtil::printSpeed();
	}

	if (m_network.boxESP) {
		Features::CNetwork::ESP(selectPlayer, PLAYER::GET_PLAYER_PED(selectPlayer), menu.titleRect);
	}

	if (m_network.showTalking) {
		Features::CNetwork::whosTalking();
	}

	if (m_vehicle.handleTest) {
		CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling->fAcceleration = 15.f;
		CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling->fBrakeForce = 15.f;
		CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling->fCamberStiffnesss = 0.5;
		CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling->fDeformationDamageMult = 15.f;
		CHack::m_pCWorld->CPedLocalPlayer->pCVehicleLast->pCVehicleHandling->fSuspensionLowerLimit = 0.1;
	}
}

void modelChanger()
{
	menu.Title("MODEL OPTIONS");
	//refresh model
	//input custom model
	//random model
	//subs here with models
}

void animationOps()
{
	menu.Title("ANIMATION OPTIONS");
}

void selfOptions()
{
	menu.Title("SELF OPTIONS");

	menu.Submenu("Model options", modelChanger, { "Become any model in the game." });
	menu.Submenu("Animation options", animationOps, { "Choose any animation, you desire." });

	menu.ToggleCallback("Invincibility", &m_player.pGodMode, nullptr, [] { ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_ID(), false); }, { "Become a God." });
	menu.Toggle("Demi-god", &m_player.pDemiGod, { "Explosives will ~r~kill~s~ you." });
	menu.ToggleCallback("Invisibility", &m_player.pInvisible, nullptr, [] {  ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, false); }, { "Be a total ~c~ghost~s~." });
	menu.Toggle("Never wanted", &m_player.neverWanted, { "Once toggled, cops will turn a blind-eye." });
	menu.OptionCallBack("Give armour and health", [] { Features::CPlayer::healArmor(); }, { "Give health and armour in desperate situations!" });
	menu.OptionCallBack("Clean player", [] { Features::CPlayer::cleanPlayer(); }, { "When you're ~~c~dirty~s~." });
	menu.Toggle("Loop clean player", &m_player.pCleanPlayer, { "will clean you automatically." });
	menu.Toggle("Super jump", &m_player.pSuperJump, { "Jump ~g~higher~s~ than usual." });
	menu.ToggleCallback("Fast run", &m_player.pFastRun, nullptr, [] { PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.f); }, { "Run ~g~faster~s~ than usual." });
	menu.Toggle("Super run", &m_player.pSuperRun, { "Run even faster!" });
	menu.ToggleCallback("Fast swim", &m_player.pFastSwim, nullptr, [] { PLAYER::SET_SWIM_MULTIPLIER_FOR_PLAYER(PLAYER::PLAYER_ID(), 1.f); }, { "Swim like ~b~Phelps~s~. " });
	menu.ToggleCallback("No ragdoll", &m_player.pNoRagdoll, nullptr, [] { PED::SET_PED_CAN_RAGDOLL(PLAYER::PLAYER_PED_ID(), false); PED::SET_PED_CAN_RAGDOLL_FROM_PLAYER_IMPACT(PLAYER::PLAYER_PED_ID(), false); });
	menu.ToggleCallback("Shrink", &m_player.pShrink, nullptr, [] { PED::SET_PED_CONFIG_FLAG(PLAYER::PLAYER_PED_ID(), 223, false); }, { "Be a ~b~cute~s~ midget." });
	menu.ToggleCallback("Night vision", &m_player.pNightVision, nullptr, [] { GRAPHICS::SET_NIGHTVISION(false); });
	menu.ToggleCallback("Slow motion", &m_player.pSlowMotion, nullptr, [] { GAMEPLAY::SET_TIME_SCALE(1.f); }, { "Slow the world down." });
	menu.OptionCallBack("Clone", [] { Features::CGameplay::clonePed(PLAYER::PLAYER_PED_ID()); });
	menu.ToggleCallback("Collision", &m_player.pCollision, nullptr, [] { ENTITY::SET_ENTITY_COLLISION(PLAYER::PLAYER_PED_ID(), true, false); }, { "Collide with nothing." });
}

void attackerMenu() {
	menu.Title("Send Attackers");
	menu.OptionCallBack("Railgun Jesus", [] { Features::CNetwork::attackJesus(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "PRAISE THE LAAAWWD!" });
	menu.OptionCallBack("Naughty Cops 1", [] { Features::CNetwork::attackCops(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	menu.OptionCallBack("Naughty Cops 2", [] { Features::CNetwork::sendCops(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	menu.OptionCallBack("SWAT Team", [] { Features::CNetwork::attckSwat(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	menu.OptionCallBack("SWAT Team (Riot)", [] { Features::CNetwork::attackSwatRiot(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
	menu.OptionCallBack("Tanks", [] {Features::CNetwork::attackTanks(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" });
}

void networkPlayer() {
	menu.Title(PLAYER::GET_PLAYER_NAME(selectPlayer));
	menu.OptionCallBack("Give Weapons", [] { Features::CWeapon::giveAllGuns(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "Give Player All Weapons" }); //1
	menu.OptionCallBack("Remove Weapons", [] {Features::CWeapon::removeAllWeapons(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "No ~q~Weps~s~ for u" }); //private																	   //addOption("Give Tronbike", "~r~Only works when close, this will crash you"); //test 1
	menu.OptionCallBack("Clone Vehicle", [] {Features::CVehicle::clone(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "Like theft but funnier" }); //2
	menu.Submenu("Send Attackers", attackerMenu, { "Like ~y~MerryWeather~s~, but without the bills" }); //3
	menu.OptionCallBack("Give Firework Launcher", [] {Features::CNetwork::dropWeapon("WEAPON_FIREWORK", PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "WIP" }); //4
	//addOption("Kick From Vehicle", [] {playerKickVeh(sel.pedID); }, ""); //private																										 //addOption("Delete Vehicle", [] {delete_vehicle(sel.pedID); }, ""); //private
	menu.OptionCallBack("Shoot Player", [] {Features::CNetwork::shootPed(selectPlayer); }, { "Random Ped Snipes Player" });
	menu.Toggle("Drop 2k Bags", &menu.moneyDrop[selectPlayer], { "RISKY AS ~r~FUCK~s~ (bad idea)" }); //test 5
	menu.Toggle("Freeze Player", &menu.freezePlayer[selectPlayer], { "" }); //test
	menu.Toggle("Fuck Camera", &menu.fuckCamera[selectPlayer], { "Like the most intense drunk cam ever" }); //test
	menu.Toggle("Annoying Loop", &menu.annoyLoop[selectPlayer], { "Doesn't do damage, however is irritating as balls" }); //test
	menu.Toggle("Forcefield", &menu.forcefield[selectPlayer], { "Makes everything 10x Harder" }); //test														  //addOption("TP to Me"); //4
	menu.Toggle("Explosion Loop", &menu.explodePlayer[selectPlayer], { "Take a wild guess what it does" });
	menu.Toggle("Track Player", &menu.trackPlayer[selectPlayer], { "Track Player's movement with ~g~ESP~s~" });
	menu.OptionCallBack("TP to Player", [] {Features::CUtil::tpToPlayer(PLAYER::GET_PLAYER_PED(selectPlayer)); }, { "" }); //5
	//addOption("TP to Waypoint", "WIP"); //6
	//addOption("Clone Crash"); //private
	//addOption("Send Warning Text", [] {online::player::sendText(sel.ID, sel.sName + ", ya bish ~g~gitfukt ~r~<3"s); }, "");
	if (NETWORK::NETWORK_IS_HOST())
		menu.OptionCallBack("Kick Player", [] { Features::CNetwork::kickPlayer(selectPlayer); }, { "Host Only" });

}

void playerList() {
	menu.Title("Player Index");
	for (int i = 0; i < 32; i++) {
		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(i))
			if (menu.aPlayer(PLAYER::GET_PLAYER_NAME(i), i, networkPlayer))
				selectPlayer = i;
	}
	if (m_network.drawMarker)
		Features::CNetwork::loop_drawMarker(menu.getOption() - 1, menu.titleRect);

	/*old test option for drawing player info - useful for debug*/
	/*if (testOptions) {
		drawPlayerInfo(currentOption - 1);
	}*/
}

void network()
{
	menu.Title("NETWORK");
	//menu.OptionCallBack("Hello bish", [] {  NativeMenu::CMenu::drawSubtitle("Sup"); });
	menu.Submenu("Player List", playerList, { "Shows all the ~b~Players~s~  in your lobby" });
	menu.Toggle("Box ESP", &m_network.boxESP, { "Draw a box around each player." });
	menu.Toggle("Show Talking", &m_network.showTalking, { "Displays who's talking in a lobby" });
}

void pedManagement()
{
	menu.Title("PED MANAGER");
}

void savedLocations()
{
	menu.Title("SAVED LOCATIONS");
}

void interiors()
{
	menu.Title("INTERIORS");
	menu.Teleport("Union Depository", { 2.6968f, -667.0166f, 16.1306f });
	menu.Teleport("Pac Standard Vault", { 255.8510f, 217.0300f, 101.6833f });
	menu.Teleport("Stadium Interior", { -255.4026f, -2022.913f, 30.9743f });
	menu.Teleport("Lesters House", { 1273.898f, -1719.304f, 54.771f });
	menu.Teleport("Meth Lab Trevor", { 1391.773f, 3608.716f, 38.942f });
	menu.Teleport("Strip Club DJ Booth", { 126.135f, -1278.583f, 29.270f });
	menu.Teleport("Humane Labs And Research", { 3617.231f, 3739.871f, 28.6901f });
	menu.Teleport("Slaughterhouse", { -80.557f, 6220.006f, 31.090f });
	menu.Teleport("IAA Office", { 117.220f, -620.938f, 206.047f });
	menu.Teleport("FIB Office Top", { 135.733f, -749.216f, 258.152f });
	menu.Teleport("10 Car Garage Back Room", { 223.193f, -967.322f, 99.000f });
	menu.Teleport("Humane Laps Tunnel", { 3525.495f, 3705.301f, 20.992f });
	menu.Teleport("Burnt FIB Building", { 160.868f, -745.831f, 250.063f });
	menu.Teleport("Fort Zancudo ATC", { -2358.132f, 3249.754f, 101.451f });
	menu.Teleport("Michael's House", { -813.6030f, 179.4740f, 71.1577f });
	menu.Teleport("Franklin's Mansion", { 7.1190f, 536.6150f, 176.0280f });
	menu.Teleport("Trevor's Trailer", { 1972.6100f, 3817.0400f, 33.4283f });
}

void shopsLocations()
{
	menu.Title("SHOP LOCATIONS");
	menu.Teleport("Ponsonbys", { -159.2996f, -304.3292f, 39.7333f });
	menu.Teleport("Mask Shop", { -1338.16f, -1278.11f, 4.87f });
	menu.Teleport("Ammunation", { 247.3652f, -45.8777f, 69.9411f });
}

void miscLocations()
{
	menu.Title("Misc. locations");
	menu.Teleport("Skyhigh", { -129.9f, 8130.8f, 6705.6f });
	menu.Teleport("Out to sea", { 1845.673f, -13787.4884f, 0.0000f });
	menu.Teleport("Lighthouse", { 3433.6570f, 5175.4090f, 35.8053f });
	menu.Teleport("Coral Reef", { 106.6972f, 7282.0550f, 1.8821f });
	menu.Teleport("Del-Pierro Pier", { -1600.0930f, -1041.8920f, 130.0209f });
	menu.Teleport("Observatory Roof", { 438.804f, 1076.097f, 352.411f });
	menu.Teleport("Kortz Center", { -2243.810f, 264.048f, 174.615f });
	menu.Teleport("Mine Shaft", { -595.342f, 2086.008f, 131.412f });
	menu.Teleport("Windmill Top", { 2026.677f, 1842.684f, 133.313f });
	menu.Teleport("Playboy Mansion", { -1475.234f, 167.088f, 55.841f });
	menu.Teleport("Movie Theatre", { 293.089f, 180.466f, 104.301f });
	menu.Teleport("Crane Top", { -119.8790f, -977.3570f, 304.2491f });
	menu.Teleport("Calafia Train Bridge", { -517.8690f, 4425.2842f, 89.7951f });
}

void usefulLocations()
{
	menu.Title("USEFUL LOCATIONS");
	menu.Teleport("Los Santos Custom", { -354.6175f, -121.153f, 38.6982f });
	menu.Teleport("Airport", { -1102.2910f, -2894.5160f, 13.9467f });
	menu.Teleport("Mount Chiliad", { 495.0000f, 5586.0000f, 794.0000f });
	menu.Teleport("Maze Bank", { -74.94243f, -818.63446f, 326.174347f });
	menu.Teleport("Eclipse Towers", { -792.36f, 296.86f, 87.84f });
	menu.Teleport("Mors Mutual", { 408.923f, -1633.860f, 30.29f });
	menu.Teleport("Sandy Shores Airport", { 1741.4960f, 3269.2570f, 41.6014f, });
	menu.Teleport("Casino and Horsetrack", { 925.329f, 46.152f, 80.908f });
	menu.Teleport("Vinewood Sign", { 711.362f, 1198.134f, 348.526f });
	menu.Teleport("McKenzie Airfield", { 2121.8564f, 4796.1143f, 41.1517f });
}

void scaryLocations()
{
	menu.Title("Weird locations");
	menu.Teleport("Sunken Body", { -3161.078f, 3001.998f, -37.974f });
	menu.Teleport("Sunken UFO", { 762.426f, 7380.371f, -111.377f });
	menu.Teleport("Sunken Hatch", { 4273.950f, 2975.714f, -170.746f, });
	menu.Teleport("Ghost", { 3059.620f, 5564.246f,197.091f });
	menu.Teleport("Bolingbroke Penitentiary", { 1679.0490f, 2513.7110f, 45.5619f });
	menu.Teleport("Alcatraz", { -2159.147f, 5196.89f, 20.00f });
}

void teleport()
{
	menu.Title("TELEPORTATION");
	//menu.Submenu("Saved locations", savedLocations, { "Save your locations for quick access." });
	menu.OptionCallBack("Teleport to map marker", [] { Features::CTeleport::teleportToWaypoint(); }, { "When walking is too overrated." });
	menu.OptionCallBack("Teleport to closest vehicle", [] { Features::CTeleport::teleportToVehicle(); }, { "Let ~b~LUXX~s~ find you a vehicle." });

	menu.Teleport("Los Santos Customs", { -354.6175f, -121.153f, 38.6982f });
	menu.Teleport("Airport", { -1102.2910f, -2894.5160f, 13.9467f });
	menu.Teleport("Mount Chilliad", { 495.0000f, 5586.0000f, 794.0000f });
	menu.Teleport("Ponsonbys", { -159.2996f, -304.3292f, 39.7333f });
	menu.Teleport("Ammunation", { 247.3652f, -45.8777f, 69.9411f });

	menu.Submenu("Interiors", interiors, { "Teleport to an interior around the map." });
	menu.Submenu("Useful Locations", usefulLocations, { "Useful locations around the map." });
	menu.Submenu("Shops", shopsLocations, { "Teleport to one of the shops around the map" });
	menu.Submenu("Misc Locations", miscLocations, { "Teleport to a misc location." });
	menu.Submenu("Weird Locations", scaryLocations, { "Teleport to a weird location" });
}

void v_spawnSettings() {
	menu.Title("SPAWNER SETTINGS");
}

void boats()
{
	menu.Title("BOATS");
	for (int i = 0; i < 10; i++) {
		menu.Vehicle(BoatHash[i].Name, BoatHash[i].Hash);
	}
}

void commercialCars()
{
	menu.Title("COMMERCIAL");
	for (int i = 0; i < 9; i++) {
		menu.Vehicle(CommercialHash[i].Name, CommercialHash[i].Hash);
	}
}

void compactCars()
{
	menu.Title("COMPACT");
	for (int i = 0; i < 9; i++) {
		menu.Vehicle(CommercialHash[i].Name, CommercialHash[i].Hash);
	}
}

void coupesCars()
{
	menu.Title("COUPES");
	for (int i = 0; i < 14; i++) {
		menu.Vehicle(CoupesHash[i].Name, CoupesHash[i].Hash);
	}
}

void cyclesShite()
{
	menu.Title("CYCLES");
	for (int i = 0; i < 6; i++) {
		menu.Vehicle(CyclesHash[i].Name, CyclesHash[i].Hash);
	}
}

void emergencyCars()
{
	menu.Title("EMERGENCY");
	for (int i = 0; i < 13; i++) {
		menu.Vehicle(EmergencyHash[i].Name, EmergencyHash[i].Hash);
	}
}

void superCars()
{
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void sportsCars() {
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void sportsClassic() {
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void muscleCars() {
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void sedanCars() {
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void suvCars() {
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void offroadCars() {
	menu.Title("SUPER CARS");
	for (auto vehicle : SuperHash) menu.Vehicle(vehicle.Name, vehicle.Hash);
}

void motorCycles() {

}

void planes() {

}

void helicopters() {

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

void vehicleSpawner()
{
	menu.Title("VEHICLE SPAWNER");
	menu.Submenu("Spawn Settings", v_spawnSettings, { "Adjust Spawn Settings" }); //1
	menu.Submenu("Super", superCars, {}); //2
	menu.Submenu("Sports", sportsCars, {}); //3
	menu.Submenu("Sports Classics", sportsClassic, {}); //4
	menu.Submenu("Coupes", coupesCars, {});//5
	menu.Submenu("Muscle", muscleCars, {});//6
	menu.Submenu("Sedan", sedanCars, {});//7
	menu.Submenu("Compacts", compactCars, {});//8
	menu.Submenu("SUV", suvCars, {});//9
	menu.Submenu("Offroad", offroadCars, {});//10
	menu.Submenu("Motorcycles", motorCycles, {});//11
	menu.Submenu("Cycles", cyclesShite, {});//12
	menu.Submenu("Planes", planes, {});//12
	menu.Submenu("Helicopters", helicopters, {});//12
	menu.Submenu("Boats", boats, {});//13
	menu.Submenu("Vans", vansCars, {});//13
	menu.Submenu("Commercial", commercialCars, {});//14
	menu.Submenu("Military", militaryCars, {});//15
	menu.Submenu("Emergency", emergencyCars, {});//16
	menu.Submenu("Utility", utilityCars, {});//17
	menu.Submenu("Service", serviceCars, {});//18
	menu.Submenu("Industrial", industrialCars, {});//19
	menu.Submenu("Trailers", trailers, {});//19
	menu.OptionCallBack("Search", [] { Features::CVehicle::manualSelect(false); }, { "Manually Enter Vehicle Name" });//20
	//addOption("Random Vehicle", [] {vehicle::random(); }, "Spawns a random vehicle WIP");//21
}

void vehicleOptions()
{
	menu.Title("VEHICLE OPTIONS");
	menu.Submenu("Vehicle spawner", vehicleSpawner, { "Spawn ~b~any~s~ vehicle on the go." });
	menu.OptionCallBack("Repair Vehicle", [] { Features::CVehicle::repair(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, { "Like brand new" });
	menu.OptionCallBack("Max Upgrade", [] { Features::CVehicle::maxUpgrade(VEHICLE::GET_LAST_DRIVEN_VEHICLE()); }, { "Warranty = Void" });
	menu.OptionCallBack("Paint Random", [] { Features::CVehicle::paintRandom(VEHICLE::GET_LAST_DRIVEN_VEHICLE(), 1, 1, 1, 1, 1); }, { "Like a gay rainbow" });
	menu.OptionCallBack("Delete Vehicle", [] { Features::CVehicle::deleteVehicle(PLAYER::PLAYER_PED_ID()); });
}

void gunshopOptions()
{
	menu.Title("GUNSHOP", "shopui_title_gr_gunmod", "shopui_title_gr_gunmod");
	for (char* weapon : weaponNames) {
		menu.Weapon(weapon);
	}
}

void ammoMods()
{
	menu.Title("AMMO MODIFICATION", "shopui_title_gr_gunmod", "shopui_title_gr_gunmod");
	menu.Toggle("Toggle ammo modification", &m_weapon.ammoType, { "Main toggle for ammo modification." });

	if (m_weapon.ammoType) {
		menu.OptionCallBack("Stinger", [] { m_weapon.ammoModType = WEAPON_STINGER; });
		menu.OptionCallBack("Fireworks", [] { m_weapon.ammoModType = WEAPON_FIREWORK; });
		menu.OptionCallBack("Grenade", [] { m_weapon.ammoModType = WEAPON_GRENADE; });
		menu.OptionCallBack("Snowball", [] { m_weapon.ammoModType = WEAPON_SNOWBALL; });
		menu.OptionCallBack("Flare", [] { m_weapon.ammoModType = WEAPON_FLARE; });
		menu.OptionCallBack("Flare gun", [] { m_weapon.ammoModType = WEAPON_FLARE_GUN; });
		menu.OptionCallBack("Molotov", [] { m_weapon.ammoModType = WEAPON_MOLOTOV; });
		menu.OptionCallBack("Vehicle rocket", [] { m_weapon.ammoModType = WEAPON_VEHICLE_ROCKET; });
	}
}

void weaponOptions()
{
	menu.Title("WEAPON OPTIONS", "shopui_title_gr_gunmod", "shopui_title_gr_gunmod");
	menu.Submenu("Gunshop", gunshopOptions, { "View and get all guns." });
	menu.Submenu("Ammo modification", ammoMods, { "Modify your ~r~ammunition~s~." });
	menu.OptionCallBack("Give all weapons", [] { Features::CWeapon::giveAllGuns(PLAYER::PLAYER_PED_ID()); }, { "Get ~b~all~s~ weapons for free." });
	menu.OptionCallBack("Replenish all weapons", [] { Features::CWeapon::replenishAllGuns(PLAYER::PLAYER_PED_ID()); }, { "Replenish ~b~all~s~ weapons." });
	menu.OptionCallBack("Upgrade all weapons", [] { Features::CWeapon::upgradeAllGuns(PLAYER::PLAYER_PED_ID()); }, { "Upgrade ~b~all~s~ weapons." });
	menu.OptionCallBack("Remove all weapons", [] { Features::CWeapon::removeAllWeapons(PLAYER::PLAYER_PED_ID()); }, { "Why would you do that?" });
	menu.Toggle("No recoil", &m_weapon.noRecoil, { "Shoot with ease." });
	menu.Toggle("No spread", &m_weapon.noSpread, { "Shoot a laser." });
	menu.Toggle("No reload", &m_weapon.noReload, { "Same as infinite ammunition." });
	menu.Toggle("Infinite ammunition", &m_weapon.unlimitedAmmo, { "You will ~g~never~s~ run out of bullets." });
	menu.Toggle("Explosive ammunition", &m_weapon.explosiveBullets, { "Explosive bullets. Yay!" });
	menu.Toggle("Fire ammunition", &m_weapon.fireAmmo, { "Not as powerful as explosive bullets." });
	menu.Toggle("Explosive hands", &m_weapon.explosiveHands, { "When weapons just don't work." });
	menu.Toggle("Rapid fire", &m_weapon.rapidFire, { "Hopefully, you will shoot faster." });
	menu.Float("Weapon damage modifier", &m_weapon.damageModifier, 1.0f, 50.0f, 0.1f, { "Modify your ~g~weapon~s~ damage." });
	menu.Toggle("Infinite parachutes", &m_weapon.infiniteParachutes, { "When you run out of parachutes mid-air." });
}

void timeOptions()
{
	menu.Title("TIME OPTIONS");
}

void worldOptions()
{
	menu.Title("WORLD OPTIONS");
}

void ObjectMan()
{
	menu.Title("OBJECT MANIPULATOR");
}

void miscOptions()
{
	menu.Title("MISC. OPTIONS");
	menu.Toggle("Print FPS", &m_misc.printFps, { "Draws the current framerate" });
	menu.Toggle("Print Speed", &m_misc.printSpeed, { "In place for a working speedo rn" });
}

void shooterOptions()
{
	menu.Title("SHOOTER OPTIONS"); // Memes
}

void mainRect()
{
	menu.Title("Main banner");
	menu.Int("Red", &menu.titleRect.r, 0, 255, 1, { "Customize the ~r~red~s~ channel." });
	menu.Int("Green", &menu.titleRect.g, 0, 255, 1, { "Customize the ~g~green~s~ channel." });
	menu.Int("Blue", &menu.titleRect.b, 0, 255, 1, { "Customize the ~b~blue~s~ channel." });
}

void colourVariant()
{
	menu.Title("Colour variant");
	menu.Int("Red", &menu.optionCounterColour.r, 0, 255, 1, { "Customize the ~r~red~s~ channel." });
	menu.Int("Green", &menu.optionCounterColour.g, 0, 255, 1, { "Customize the ~g~green~s~ channel." });
	menu.Int("Blue", &menu.optionCounterColour.b, 0, 255, 1, { "Customize the ~b~blue~s~ channel." });
}

void settings()
{
	menu.Title("SETTINGS");
	menu.Submenu("Main banner", mainRect, { "Customize the main banner." });
	menu.Submenu("Colour variant", colourVariant, { "Customize the main colour." });
	menu.OptionCallBack("Reload Config", [] { Features::CUtil::loadConfig(1, menu); });
}

MenuFunc NativeMenu::MAIN_MENU()
{
	menu.Title("MAIN MENU");
	menu.Submenu("Online", network, { "Extra Online Functions" });
	menu.Submenu("Self", selfOptions, { "Character Only Functions" });
//	menu.Submenu("Ped management", pedManagement, { "Spawn and manage ~b~PEDs~s~", "and make them your bodyguard!" });
	menu.Submenu("Vehicle", vehicleOptions, { "~q~Modify~s~, ~g~Repair~s~, ~r~Fuck With~s~" });
	menu.Submenu("Weapon options", weaponOptions, { "Your own mobile ~r~gunstore~s~." });
	menu.Submenu("Teleport", teleport, { "Be ~b~anywhere~s~ at any time." });
	//menu.Submenu("Time options", timeOptions, { "Control the time." });
	menu.Submenu("World", worldOptions, { "Is this a ~y~God~s~ simulator?" });
	//menu.Submenu("Object manipulator", ObjectMan, { "Spawn and edit objects." });
	menu.Submenu("Misc. options", miscOptions, { "Options where they ~c~don't really belong~s~." });
	//menu.Submenu("Shooter options", shooterOptions, { "This is for you, NUP." });
	menu.Submenu("Settings", settings, { "Customize ~c~LUXX~s~ to your own liking." });
}

void CHack::mainLoop()
{
	loops();
	menu.Main();
}