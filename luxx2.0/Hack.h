#ifndef ALPHA_HACK_H 
#define ALPHA_HACK_H

class CHack;

class CHack {
public:
	/* declare our structs */
	static CWorld* m_pCWorld;
	static CPed*   m_pCPedPlayer;
	static CWeaponInfo* m_pCWeapon;
	static CAmmo* m_pCAmmo;
	static CVehicle* m_pCVehicle;
	static CVehicleHandling* m_pCVehicleHandling;

	static CWorld m_CWorld;
	static CWeaponInfo m_CWeapon;
	static CVehicle m_CVehicle;
	static CVehicleHandling m_CVehicleHandling;

	/* our main loop */
	static void mainLoop();
};

#endif