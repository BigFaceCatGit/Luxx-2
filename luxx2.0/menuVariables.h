#ifndef ALPHA_MENUVARIABLES_H
#define ALPHA_MENUVARIABLES_H

namespace Variables
{
	class CPlayer
	{
	public:
		bool pGodMode = false;
		bool pDemiGod = false;
		bool neverWanted = false;
		bool pInvisible = false;
		bool pCleanPlayer = false;
		bool pSuperJump = false;
		bool pFastRun = false;
		bool pSuperRun = false;
		bool pFastSwim = false;
		bool pNoRagdoll = false;
		bool pShrink = false;
		bool pNightVision = false;
		bool pSlowMotion = false;
		bool pCollision = false;
	};

	class CNetwork
	{
	public:
		bool boxESP = false;
		bool showTalking = false;
		bool drawMarker = false;
		//bool boxESP = false;

	};

	class CWeapon
	{
	public:
		int ammoModType = 0;

		bool unlimitedAmmo = false;
		bool explosiveBullets = false;
		bool fireAmmo = false;
		bool explosiveHands = false;
		bool infiniteParachutes = false;
		bool ammoType = false;
		float damageModifier = 1.0f;
		bool rapidFire = false;
		bool noRecoil = false;
		bool noSpread = false;
		bool noReload = false;
	};

	class CVehicle
	{
	public:
		/* Spawn Variables */
		bool sDelete = true; //Deletes old vehicle
		bool sWrap = true; //Wraps in to new vehicle
		bool sMax = false; //Max Upgrades new vehicle
		bool sPlaneAir = false; //Spawns Plane in air
		bool sNeon = false; //Spawns new vehicle with default Neon

		/* Stores Hash and Name of Vehicle */
		struct vStore {
			std::string Name;
			Hash Hash;
		};
		/* Stores Favourite Vehicles in Vector */
		std::vector<fVehicle> fVehicles;

		/* Rainbow Val Stuff */
		bool rActive = false;
		bool rFade = true;
		bool rBody = true;
		bool rNeon = true;
		bool rTyre = true;
		bool rPrimary = true;
		bool rSecondary = true;
		bool rMenu = false;
		int rUpdate;

		/* ModShop Variables */
		int sMod = 0; //Currently Selected Mod
		char* sModName = "*invalid*";
		Vehicle sVehicle;

		/* Handling Shit Goes Here */
		float accelMult = 1.f;
		bool handleTest;
	};

	class CMisc {
	public:
		bool printFps = false;
		bool printSpeed = false;
	};
}

#endif