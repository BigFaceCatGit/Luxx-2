#ifndef ALPHA_HACK_H 
#define ALPHA_HACK_H

class CHack;

class CHack {
public:
	/* declare our structs */
	static CWorld* m_pCWorld;
	static CPed*   m_pCPedPlayer;
	static CWeaponInfo* m_pCWeapon;

	/* our main loop */
	static void mainLoop();
};

#endif