#ifndef _VEHICLE_STRUCTS
#define _VEHICLE_STRUCTS

static struct {
	std::string Name;
	Hash Hash;
} BoatHash[10] = {

	{ "Dinghy", VEHICLE_DINGHY },
	{ "Jetmax", VEHICLE_JETMAX },
	{ "Marquis", VEHICLE_MARQUIS },
	{ "Seashark", VEHICLE_SEASHARK },
	{ "Speeder", VEHICLE_SPEEDER },
	{ "Squalo", VEHICLE_SQUALO },
	{ "Submersible", VEHICLE_SUBMERSIBLE },
	{ "Toro", VEHICLE_TORO },
	{ "Tropic", VEHICLE_TROPIC },
	{ "Tug", VEHICLE_TUG }
};

static struct {
	std::string Name;
	Hash Hash;
} CommercialHash[9] = {

	{ "Benson", VEHICLE_BENSON },
	{ "Biff", VEHICLE_BIFF },
	{ "Hauler", VEHICLE_HAULER },
	{ "Mule", VEHICLE_MULE },
	{ "Packer", VEHICLE_PACKER },
	{ "Phantom", VEHICLE_PHANTOM },
	{ "Pounder", VEHICLE_POUNDER },
	{ "Stockade", VEHICLE_STOCKADE },
	{ "Stockade Snow", VEHICLE_STOCKADE3 }
};

static struct {
	std::string Name;
	Hash Hash;
} CompactHash[8] = {

	{ "Blista", VEHICLE_BLISTA },
	{ "Brioso R/A", VEHICLE_BRIOSO },
	{ "Dilettante", VEHICLE_DILETTANTE },
	{ "Dilettante (Security)", VEHICLE_DILETTANTE2 },
	{ "Issi", VEHICLE_ISSI2 },
	{ "Panto", VEHICLE_PANTO },
	{ "Prairie", VEHICLE_PRAIRIE },
	{ "Rhapsody", VEHICLE_RHAPSODY }

};

static struct {
	std::string Name;
	Hash Hash;
} CoupesHash[14] = {

	{ "Cognoscenti Cabrio", VEHICLE_COGCABRIO },
	{ "Exemplar", VEHICLE_EXEMPLAR },
	{ "F620", VEHICLE_F620 },
	{ "Felon", VEHICLE_FELON },
	{ "Felon GT", VEHICLE_FELON2 },
	{ "Jackal", VEHICLE_JACKAL },
	{ "Oracle", VEHICLE_ORACLE2 },
	{ "Oracle XS", VEHICLE_ORACLE },
	{ "Sentinel", VEHICLE_SENTINEL2 },
	{ "Sentinel XS", VEHICLE_SENTINEL },
	{ "Windsor", VEHICLE_WINDSOR },
	{ "Windsor Drop", VEHICLE_WINDSORDROP },
	{ "Zion", VEHICLE_ZION },
	{ "Zion Cabrio", VEHICLE_ZION2 }

};

static struct {
	std::string Name;
	Hash Hash;
} CyclesHash[6] = {

	{ "BMX", VEHICLE_BMX },
	{ "Cruiser", VEHICLE_CRUISER },
	{ "Endurex Race Bike", VEHICLE_ENDUREX },
	{ "Fixter", VEHICLE_FIXTER },
	{ "Scorcher", VEHICLE_SCORCHER },
	{ "Tri-Cycles Race Bike", VEHICLE_TRIBIKE },

};

static struct {
	std::string Name;
	Hash Hash;
} EmergencyHash[13] = {

	{ "Ambulance", VEHICLE_AMBULANCE },
	{ "FIB (Buffalo)", VEHICLE_FIBBUFFALO },
	{ "FIB (Granger)", VEHICLE_FIBGRANGER },
	{ "Firetruck", VEHICLE_FIRETRUK },
	{ "Lifeguard (Granger)", VEHICLE_LGUARD },
	{ "Parkranger (Granger)", VEHICLE_PRANGER },
	{ "Police bike", VEHICLE_POLICEB },
	{ "Police cruiser", VEHICLE_POLICE },
	{ "Police cruiser 2", VEHICLE_POLICE3 },
	{ "Police prison bus", VEHICLE_PBUS },
	{ "Police transporter", VEHICLE_POLICET },
	{ "Sheriff cruiser", VEHICLE_SHERIFF },
	{ "Sheriff SUV (Granger)", VEHICLE_SHERIFF2 },

};

static struct {
	std::string Name;
	Hash Hash;
} SuperHash[26] = {

	{ "Pfister 811", VEHICLE_PFISTER },
	{ "Adder", VEHICLE_ADDER },
	{ "Banshee", VEHICLE_BANSHEE2 },
	{ "Bullet", VEHICLE_BULLET },
	{ "Cheetah", VEHICLE_CHEETAH },
	{ "Entity XF", VEHICLE_ENTITYXF },
	{ "ETR1", VEHICLE_ETR1 },
	{ "FMJ", VEHICLE_FMJ },
	{ "Infernus", VEHICLE_INFERNUS },
	{ "Itali GTB", VEHICLE_ITALIGTB },
	{ "Itali GTB Custom", VEHICLE_ITALIGTBCUSTOM },
	{ "Progen GP1", VEHICLE_GP1 },
	{ "Nero", VEHICLE_NERO },
	{ "Osiris", VEHICLE_OSIRIS },
	{ "Penetrator", VEHICLE_PENETRATOR },
	{ "LE-7B", VEHICLE_LE7B },
	{ "Reaper", VEHICLE_REAPER },
	{ "Rocket Voltic", VEHICLE_ROCKETVOLTIC },
	{ "Sultan RS", VEHICLE_SULTANRS },
	{ "T20", VEHICLE_T20 },
	{ "Tempesta", VEHICLE_TEMPESTA },
	{ "Turismo R", VEHICLE_TURISMOR },
	{ "Tyrus", VEHICLE_TYRUS },
	{ "Voltic", VEHICLE_VOLTIC },
	{ "X80 Proto", VEHICLE_X80 },
	{ "Zentorno", VEHICLE_ZENTORNO },
};

static struct {
	std::string Name;
	Hash Hash;
} Gunrunning[16] = {
	{ "APC", VEHICLE_APC }, //apc
	{ "Ardent", VEHICLE_ARDENT }, //ardent
	{ "Caddy 3", VEHICLE_CADDY3 }, //caddy3
	{ "Cheetah 2", VEHICLE_CHEETAH2 }, //cheetah2
	{ "Dune", VEHICLE_DUNE3 }, //dune3
	{ "Halftrack", VEHICLE_HALFTRACK }, //halftrack
	{ "Hauler2", VEHICLE_HAULER2 }, //hauler2
	{ "Insurgent 3", VEHICLE_INSURGENT3 }, //insurgent3
	{ "Nightshark", VEHICLE_NIGHTSHARK }, //nightshark
	{ "Oppressor", VEHICLE_OPRESSOR }, //oppressor
	{ "Phantom 3", VEHICLE_PHANTOM3 }, //phantom3
	{ "Tampa 3", VEHICLE_TAMPA3 }, //tampa3
	{ "Technical", VEHICLE_TECHNICAL3 }, //technical3
	{ "Torero", VEHICLE_TORERO }, //torero
	{ "Vagner", VEHICLE_VAGNER }, //vagner
	{ "Xa-21", VEHICLE_XA21 } //xa21
};

static struct {
	std::string Name;
	Hash hash;
} smugglerRun[19] = {
	{ "Vigilante", VEHICLE_VIGILANTE },
	{ "Bombushka", VEHICLE_BOMBUSHKA },
	{ "Alpha Z1", VEHICLE_ALPHAZ1 },
	{ "Tula", VEHICLE_TULA },
	{ "Hunter", VEHICLE_HUNTER },
	{ "Rogue", VEHICLE_ROGUE },
	{ "Pyro", VEHICLE_PYRO },
	{ "Mogul", VEHICLE_MOGUL },
	{ "Nokota", VEHICLE_NOKOTA },
	{ "Molotok", VEHICLE_MOLOTOK },
	{ "Seabreeze", VEHICLE_SEABREEZE },
	{ "Havok", VEHICLE_HAVOK },
	{ "Microlight", VEHICLE_MICROLIGHT },
	{ "Howard", VEHICLE_HOWARD },
	{ "Starling", VEHICLE_STARLING },
	{ "Rapid GT3", VEHICLE_RAPIDGT3 },
	{ "Retinue", VEHICLE_RETINUE },
	{ "Cyclone", VEHICLE_CYCLONE },
	{ "Visione", VEHICLE_VISIONE }
};

#endif