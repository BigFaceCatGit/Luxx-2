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
		bool vehSpawnDelete = true;
		bool vehWrapInSpawned = true;
		bool vehSpawnMaxed = false;
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