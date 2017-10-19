#ifndef ALPHA_MENUFEATURES_H
#define ALPHA_MENUFEATURES_H
#include "menuBase.h"
/*
weapon array. Useful for give ammo, replenish all, upgrade all and maybe more
*/
constexpr static Hash weaponlist[] = {

	//Melee
	-1716189206, 1737195953,
	1317494643, -1786099057,
	-2067956739, 1141786504,
	-102323637, -1834847097,
	-102973651, -656458692,
	-581044007, -1951375401,
	-538741184, -1810795771,
	419712736, -853065399, //14

						   //Handguns
						   453432689, 1593441988,
						   -1716589765, -1076751822,
						   -771403250, 137902532,
						   -598887786, -1045183535,
						   584646201, 911657153,
						   1198879012, //11

									   //SMGs and Machine guns
									   324215364, -619010992,
									   736523883, -270015777,
									   171789620, -1660422300,
									   2144741730, 1627465347,
									   -1121678507,  //9

													 //Assault Rifles
													 -1074790547, -2084633992,
													 -1357824103, -1063057011,
													 2132975508, 1649403952, //6

																			 //Sniper Rifles
																			 100416529, 205991906,
																			 -952879014, //3

																						 //Shotguns
																						 487013001, 2017895192,
																						 -1654528753, -494615257,
																						 -1466123874, 984333226,
																						 -275439685, 317205821, //8

																												//Heavy weapons
																												-1568386805, -1312131151,
																												1119849093, 2138347493,
																												1834241177, 1672152130,
																												1305664598, 125959754, //8

																																	   //Thrown weapons
																																	   -1813897027, 741814745,
																																	   -1420407917, -1600701090,
																																	   615608432, 101631238,
																																	   883325847, 1233104067,
																																	   600439132, 126349499,
																																	   -37975472, -1169823560, //12

																																							   //Parachute
																																							   -72657034 //1

};

constexpr static char* weaponNames[] = {
	"WEAPON_KNIFE", "WEAPON_NIGHTSTICK", "WEAPON_HAMMER", "WEAPON_BAT", "WEAPON_GOLFCLUB", "WEAPON_CROWBAR",
	"WEAPON_PISTOL", "WEAPON_COMBATPISTOL", "WEAPON_APPISTOL", "WEAPON_PISTOL50", "WEAPON_MICROSMG", "WEAPON_SMG",
	"WEAPON_ASSAULTSMG", "WEAPON_ASSAULTRIFLE", "WEAPON_CARBINERIFLE", "WEAPON_ADVANCEDRIFLE", "WEAPON_MG",
	"WEAPON_COMBATMG", "WEAPON_PUMPSHOTGUN", "WEAPON_SAWNOFFSHOTGUN", "WEAPON_ASSAULTSHOTGUN", "WEAPON_BULLPUPSHOTGUN",
	"WEAPON_STUNGUN", "WEAPON_SNIPERRIFLE", "WEAPON_HEAVYSNIPER", "WEAPON_GRENADELAUNCHER", "WEAPON_GRENADELAUNCHER_SMOKE",
	"WEAPON_RPG", "WEAPON_MINIGUN", "WEAPON_GRENADE", "WEAPON_STICKYBOMB", "WEAPON_SMOKEGRENADE", "WEAPON_BZGAS",
	"WEAPON_MOLOTOV", "WEAPON_SNSPISTOL", "WEAPON_SPECIALCARBINE", "WEAPON_HEAVYPISTOL", "WEAPON_BULLPUPRIFLE", "WEAPON_HOMINGLAUNCHER",
	"WEAPON_PROXMINE", "WEAPON_SNOWBALL", "WEAPON_VINTAGEPISTOL", "WEAPON_DAGGER", "WEAPON_FIREWORK", "WEAPON_MUSKET",
	"WEAPON_MARKSMANRIFLE", "WEAPON_HEAVYSHOTGUN", "WEAPON_GUSENBERG", "WEAPON_HATCHET", "WEAPON_RAILGUN",
	"WEAPON_COMBATPDW", "WEAPON_KNUCKLE", "WEAPON_MARKSMANPISTOL"
};

namespace Features {

	class CPlayer
	{
	public:
		static void healArmor();
		static void cleanPlayer();
		static void superRun();
	};

	class CNetwork
	{
	public:
		static void ESP(Player target, Ped playerPed, NativeMenu::RGBA bannerRect);
		static void moneyDrop(Vector3 coords);
		static void loop_fuckCam(Player Target);
		static void loop_annoyBomb(Player Target);
		static void loop_forcefield(Player Target);
		static void controlID(Entity netid);
		static void controlEnt(Entity entity);
		static void dropWeapon(char * weapon, Ped recievingPed);
		static void kickPlayer(Player player);
		static void attackCops(Ped playerPed);
		static void attckSwat(Ped playerPed);
		static void attackJesus(Ped playerPed);
		static void attackSwatRiot(Ped playerPed);
		static void sendCops(Ped playerPed);
		static void attackTanks(Ped playerPed);
		static void shootPed(Player selectedPlayer);
		static void soloSesh(int lagTime);
		static void killAll();
		static void loop_drawMarker(Player player, NativeMenu::RGBA bannerRect);
		static void whosTalking();
	};

	class CWeapon
	{
	public:
		static void giveAllGuns(Ped ped);
		static void replenishAllGuns(Ped ped);
		static void upgradeAllGuns(Ped ped);
		static void removeAllWeapons(Ped ped);
		static void infiniteParachute();
		static void ammoModification(Hash type);
		static void rapidFire();
		static void infiniteAmmo();
	};

	class CTeleport
	{
	public:
		static void teleportToWaypoint();
		static void teleportToVehicle();
	};

	class CGameplay
	{
	public:
		static Ped clonePed(Ped ped);
		static void applyForceToEntity(Entity e, float x, float y, float z);
	};

	class CVehicle
	{
	public:
		static void repair(Vehicle vehicle);
		static void paintRandom(Vehicle vehicle, bool primary, bool secondary, bool neon, bool wheels, bool tyresmoke);
		static void stockUpgrade(Vehicle vehicle);
		static void baseUpgrade(Vehicle vehicle);
		static void maxUpgrade(Vehicle vehicle);
		static void bypassKick(Vehicle vehicle);
		static Vehicle spawn(Hash model, Ped playerPed, Vector3 playerPos, bool vDelete, bool vWrap, bool vMax);
		static Vehicle spawn(Hash model, Ped playerPed, bool vDelete, bool vWrap, bool vMax);
		static Vehicle spawn(char * toSpawn, Ped playerPed, bool vDelete, bool vWrap, bool vMax);
		static Vehicle clone(Ped ped);
		static bool deleteVehicle(Ped ped);
		static void setPlateText(Vehicle vehicle);
		static void manualSelect(bool playerType);
	};

	class CUtil
	{
	public:
		struct RGBA {
			int r, g, b, a;
		};

		static Hash $(std::string str);
		static void notifyMap(std::string msg, BOOL blink);
		static void notifyError(std::string msg);
		static void notifyBottom(char * msg);
		static void notifyClan(char * msg);
		static char * AddStrings(char * string1, char * string2);
		static int StringToInt(char * text);
		static std::string IntToString(int integer);
		static std::string FloatToString(float flt);
		static float StringToFloat(std::string str);
		static DWORD StringToDWORD(std::string str);
		static std::string DocumentsPath(bool trailing);
		static void WriteINI(std::string section, std::string key, std::string value);
		static void WriteINIRGBA(NativeMenu::RGBA rgba, std::string section, std::string key);
		static void WriteMenuColorDefault();
		static void CreateFolder(std::string path);
		static void WriteLocINI(std::string section, std::string key, std::string value);
		static void saveTheme(bool notify, NativeMenu::CMenu &menu);
		static void saveKeyBinds(bool notify, NativeMenu::CMenu &menu);
		static void saveSpeedo(bool notify, NativeMenu::CMenu &menu);
		static void saveConfig(bool notify, NativeMenu::CMenu &menu);
		static std::string ReadIniKey(std::string section, std::string key);
		static std::string ReadIniKey(std::string fileName, std::string section, std::string key);
		static bool DoesKeyExist(std::string section, std::string key);
		static NativeMenu::RGBA ReadINIRGBA(std::string section, std::string key);
		static std::string ReadPresetKey(std::string name, std::string section, std::string key);
		static bool DoesPresetKeyExists(std::string name, std::string section, std::string key);
		static int GetNumberOfObjectFromFile(std::string name);
		static void loadTheme(bool notify, NativeMenu::CMenu &menu);
		static void loadKeyBinds(bool notify, NativeMenu::CMenu &menu);
		static void loadSpeedo(bool notify, NativeMenu::CMenu &menu);
		static void loadConfig(bool notify, NativeMenu::CMenu &menu);
		static double CalcAverageTick();
		static float CalcSpeed(bool mphOut, Vehicle veh);
		static void printFPS();
		static void printSpeed();
		static bool isPlayerFriend(Player player);
		static Vector3 getBlipMarker();
		static void tpToMarker();
		static void tpToObjective();
		static void tpToCar();
		static void tpToCoords(float x, float y, float z);
		static void tpToCoords(Entity ent, Vector3 coords);
		static void tpToPlayer(Ped playerPed);
	};
}

#endif