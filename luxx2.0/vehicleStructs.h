#ifndef _VEHICLE_STRUCTS
#define _VEHICLE_STRUCTS

static struct {
	std::string Name;
	Hash Hash;
} BoatHash[21] = {

	{ "Dinghy", VEHICLE_DINGHY },
	{ "Dinghy (2-Seater)", VEHICLE_DINGHY2 },
	{ "Dinghy (New Map On Dash)", VEHICLE_DINGHY3 },
	{ "Dinghy (Yacht)", VEHICLE_DINGHY4 },
	{ "Jetmax", VEHICLE_JETMAX },
	{ "Marquis", VEHICLE_MARQUIS },
	{ "Predator", VEHICLE_PREDATOR },
	{ "Seashark (Speedophile)", VEHICLE_SEASHARK },
	{ "Seashark (Lifeguard)", VEHICLE_SEASHARK2 },
	{ "Seashark (Yacht)", VEHICLE_SEASHARK3 },
	{ "Speeder", VEHICLE_SPEEDER },
	{ "Speeder (Yacht)", VEHICLE_SPEEDER2 },
	{ "Squalo", VEHICLE_SQUALO },
	{ "Submersible", VEHICLE_SUBMERSIBLE },
	{ "Submersible (Kraken)", VEHICLE_SUBMERSIBLE2 },
	{ "Suntrap", VEHICLE_SUNTRAP },
	{ "Toro", VEHICLE_TORO },
	{ "Toro (Yacht)", VEHICLE_TORO2 },
	{ "Tropic", VEHICLE_TROPIC },
	{ "Tropic (Yacht)", VEHICLE_TROPIC2 },
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
	{ "Dilettante (Merryweather)", VEHICLE_DILETTANTE2 },
	{ "Issi", VEHICLE_ISSI2 },
	{ "Panto", VEHICLE_PANTO },
	{ "Prairie", VEHICLE_PRAIRIE },
	{ "Rhapsody", VEHICLE_RHAPSODY }

};

static struct {
	std::string Name;
	Hash Hash;
} CoupesHash[16] = {

	{ "Cognoscenti Cabrio", VEHICLE_COGCABRIO },
	{ "Exemplar", VEHICLE_EXEMPLAR },
	{ "F620", VEHICLE_F620 },
	{ "Faction", VEHICLE_FACTION },
	{ "Faction Custom", VEHICLE_FACTION2 },
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
} CyclesHash[8] = {

	{ "BMX", VEHICLE_BMX },
	{ "Cruiser", VEHICLE_CRUISER },
	{ "Endurex Race Bike", VEHICLE_ENDUREX },
	{ "Fixter", VEHICLE_FIXTER },
	{ "Scorcher", VEHICLE_SCORCHER },
	{ "Green Whippet Race Bike", VEHICLE_TRIBIKE },
	{ "Red Endurex Race Bike", VEHICLE_TRIBIKE2 },
	{ "Blue Tri-Cycles Race Bike", VEHICLE_TRIBIKE3 },
};

static struct {
	std::string Name;
	Hash Hash;
} EmergencyHash[23] = {

	{ "Ambulance", VEHICLE_AMBULANCE },
	{ "Barracks", VEHICLE_BARRACKS },
	{ "Barracks Semi", VEHICLE_BARRACKS2 },
	{ "Barracks (Dark Camo)", VEHICLE_BARRACKS3 },
	{ "Crusader", VEHICLE_BARRACKS },
	{ "FIB (Buffalo)", VEHICLE_FIBBUFFALO },
	{ "FIB (Granger)", VEHICLE_FIBGRANGER },
	{ "Firetruck", VEHICLE_FIRETRUK },
	{ "Lifeguard (Granger)", VEHICLE_LGUARD },
	{ "Parkranger (Granger)", VEHICLE_PRANGER },
	{ "Police (Bike)", VEHICLE_POLICEB },
	{ "Police (Stanier)", VEHICLE_POLICE },
	{ "Police (Buffalo)", VEHICLE_POLICE2 },
	{ "Police (Interceptor)", VEHICLE_POLICE3 },
	{ "Police (Undercover)", VEHICLE_POLICE4 },
	{ "Police (Snowy Rancher)", VEHICLE_POLICEOLD1 },
	{ "Police (Snowy Esperanto)", VEHICLE_POLICEOLD2 },
	{ "Prison Bus", VEHICLE_PBUS },
	{ "Police Transporter", VEHICLE_POLICET },
	{ "Rhino", VEHICLE_RHINO },
	{ "Riot", VEHICLE_RIOT },
	{ "Sheriff (Stanier)", VEHICLE_SHERIFF },
	{ "Sheriff SUV (Granger)", VEHICLE_SHERIFF2 },

};

static struct {
	std::string Name;
	Hash Hash;
} HelicopterHash[24] = {

	{ "Annihilator", VEHICLE_ANNIHILATOR },
	{ "Blimp ", VEHICLE_BLIMP },
	{ "Blimp (Xero)", VEHICLE_BLIMP2 },
	{ "Buzzard", VEHICLE_BUZZARD },
	{ "Buzzard (Gunless)", VEHICLE_BUZZARD2 },
	{ "Cargobob", VEHICLE_CARGOBOB },
	{ "Cargobob (Medical)", VEHICLE_CARGOBOB2 },
	{ "Cargobob (Trevor)", VEHICLE_CARGOBOB3 },
	{ "Cargobob (Yacht)", VEHICLE_CARGOBOB4 },
	{ "Frogger", VEHICLE_FROGGER},
	{ "Frogger (Trevor)", VEHICLE_FROGGER2 },
	{ "Havok", VEHICLE_HAVOK },
	{ "Hunter", VEHICLE_HUNTER },
	{ "Maverick", VEHICLE_MAVERICK },
	{ "Police Maverick", VEHICLE_POLMAV },
	{ "Savage", VEHICLE_SAVAGE },
	{ "Skylift", VEHICLE_SKYLIFT },
	{ "Supervolito", VEHICLE_SUPERVOLITO },
	{ "Supervolito Carbon", VEHICLE_SUPERVOLITO2 },
	{ "Swift", VEHICLE_SWIFT },
	{ "Swift (Gold)", VEHICLE_SWIFT2 },
	{ "Valkyrie", VEHICLE_VALKYRIE },
	{ "Valkyrie (MOD.0)", VEHICLE_VALKYRIE2 },
	{ "Volatus", VEHICLE_VOLATUS },

};

static struct {
	std::string Name;
	Hash Hash;
} MuscleHash[] = {

	{ "Blade", VEHICLE_BLADE },
	{ "Buccaneer", VEHICLE_BUCCANEER },
	{ "Buccaneer Custom", VEHICLE_BUCCANEER2 },
	{ "Chino", VEHICLE_CHINO },
	{ "Chino Custom", VEHICLE_CHINO2 },
	{ "Fränken Strange", VEHICLE_BTYPE2 },
	{ "Dominator", VEHICLE_DOMINATOR },
	{ "Dominator (Pisswasser)", VEHICLE_DOMINATOR2 },
	{ "Duke O'Death", VEHICLE_DUKES2 },
	{ "Dukes", VEHICLE_DUKES },
	{ "Faction Custom Donk", VEHICLE_FACTION3 },
	{ "Gauntlet", VEHICLE_GAUNTLET },
	{ "Gauntlet (Redwood)", VEHICLE_GAUNTLET2 },
	{ "Hotknife", VEHICLE_HOTKNIFE },
	{ "Minivan Custom", VEHICLE_MINIVAN2 },
	{ "Nightshade", VEHICLE_NIGHTSHADE },
	{ "Phoenix", VEHICLE_PHOENIX },
	{ "Picador", VEHICLE_PICADOR },
	{ "Ruiner", VEHICLE_RUINER },
	{ "Sabre GT", VEHICLE_SABREGT },
	{ "Sabre Turbo Custom", VEHICLE_SABREGT2 },
	{ "Slamvan", VEHICLE_SLAMVAN },
	{ "Slamvan (Lost Slamvan)", VEHICLE_SLAMVAN2 },
	{ "Slamvan Custom", VEHICLE_SLAMVAN3 },
	{ "Stalion", VEHICLE_STALION },
	{ "Stalion (Burger Shot)", VEHICLE_STALION2 },
	{ "Tampa", VEHICLE_TAMPA },
	{ "Tampa (Drift)", VEHICLE_TAMPA2 },
	{ "Tampa (Weaponised)", VEHICLE_TAMPA3 },
	{ "Tornado Custom", VEHICLE_TORNADO5 },
	{ "Tornado Rat Rod", VEHICLE_TORNADO6 },
	{ "Vigero", VEHICLE_VIGERO },
	{ "Virgo", VEHICLE_VIRGO },
	{ "Virgo Classic", VEHICLE_VIRGO3 },
	{ "Virgo Classic Custom", VEHICLE_VIRGO2 },
	{ "Voodoo Custom", VEHICLE_VOODOO },
	{ "Voodoo (Rusty)", VEHICLE_VOODOO2 },
};

static struct {
	std::string Name;
	Hash Hash;
} PlaneHash[31] = {

	{ "Alpha-Z1", VEHICLE_ALPHAZ1 },
	{ "Besra", VEHICLE_BESRA },
	{ "Bombushka", VEHICLE_BOMBUSHKA },
	{ "Cargoplane", VEHICLE_CARGOPLANE },
	{ "Cuban 800", VEHICLE_CUBAN800 },
	{ "Dodo", VEHICLE_DODO },
	{ "Duster", VEHICLE_DUSTER },
	{ "Howard", VEHICLE_HOWARD },
	{ "Hydra", VEHICLE_HYDRA },
	{ "Jet", VEHICLE_JET },
	{ "Lazer", VEHICLE_LAZER },
	{ "Luxor", VEHICLE_LUXOR },
	{ "Luxor Deluxe", VEHICLE_LUXOR },
	{ "Mammatus", VEHICLE_MAMMATUS },
	{ "Microlight", VEHICLE_MICROLIGHT },
	{ "Miljet", VEHICLE_MILJET },
	{ "Mogul", VEHICLE_MOGUL },
	{ "Molotok", VEHICLE_MOLOTOK },
	{ "Nimbus", VEHICLE_NIMBUS },
	{ "Nokota", VEHICLE_NOKOTA },
	{ "Pyro", VEHICLE_PYRO },
	{ "Rogue", VEHICLE_ROGUE },
	{ "Seabreeze", VEHICLE_SEABREEZE },
	{ "Shamal", VEHICLE_SHAMAL },
	{ "Starling", VEHICLE_STARLING },
	{ "Stunt", VEHICLE_STUNT },
	{ "Titan", VEHICLE_TITAN },
	{ "Tula", VEHICLE_TULA },
	{ "Velum", VEHICLE_VELUM },
	{ "Velum (5-Seater)", VEHICLE_VELUM2 },
	{ "Vestra", VEHICLE_VESTRA },
};

static struct {
	std::string Name;
	Hash Hash;
} SportHash[] = {

	{ "Alpha", VEHICLE_ALPHA },
	{ "Banshee", VEHICLE_BANSHEE },
	{ "Bestia GTS", VEHICLE_BESTIAGTS },
	{ "Blista Compact", VEHICLE_BLISTA2 },
	{ "Go Go Monkey Blista", VEHICLE_BLISTA3 },
	{ "Buffalo", VEHICLE_BUFFALO },
	{ "Buffalo 2", VEHICLE_BUFFALO2 },
	{ "Sprunk Buffalo", VEHICLE_BUFFALO3 },
	{ "Carbonizzare", VEHICLE_CARBONIZZARE },
	{ "Comet", VEHICLE_COMET2 },
	{ "Comet Retro Custom", VEHICLE_COMET3 },
	{ "Coquette", VEHICLE_COQUETTE },
	{ "Elegy", VEHICLE_ELEGY2 },
	{ "Elegy Retro Custom", VEHICLE_ELEGY },
	{ "Feltzer", VEHICLE_FELTZER2 },
	{ "Furore GT", VEHICLE_FUROREGT },
	{ "Fusilade", VEHICLE_FUSILADE },
	{ "Futo", VEHICLE_FUTO },
	{ "Jester", VEHICLE_JESTER },
	{ "Jester (Race)", VEHICLE_JESTER2 },
	{ "Khamelion", VEHICLE_KHAMELION },
	{ "Kuruma", VEHICLE_KURUMA },
	{ "Kuruma (Armoured)", VEHICLE_KURUMA2 },
	{ "Lynx", VEHICLE_LYNX },
	{ "Mamba", VEHICLE_MAMBA },
	{ "Massacaro", VEHICLE_MASSACRO },
	{ "Massacaro Race", VEHICLE_MASSACRO2 },
	{ "NineF", VEHICLE_NINEF },
	{ "NineF Convertible", VEHICLE_NINEF2 },
	{ "Omnis", VEHICLE_OMNIS },
	{ "Penumbra", VEHICLE_PENUMBRA },
	{ "Rapid GT", VEHICLE_RAPIDGT },
	{ "Rapid GT (Convertible)", VEHICLE_RAPIDGT2 },
	{ "Raptor", VEHICLE_RAPTOR },
	{ "Ruiner 2000", VEHICLE_RUINER2 },
	{ "Ruiner (Destroyed)", VEHICLE_RUINER3 },
	{ "Ruston", VEHICLE_RUSTON },
	{ "Schwarzer", VEHICLE_SCHWARZER },
	{ "Seven70", VEHICLE_SEVEN70 },
	{ "Specter", VEHICLE_SPECTER },
	{ "Specter Custom", VEHICLE_SPECTER2 },
	{ "Sultan", VEHICLE_SULTAN },
	{ "Surano", VEHICLE_SURANO },
	{ "Tropos", VEHICLE_TROPOS },
	{ "Verlierer", VEHICLE_VERLIERER2 },
};

static struct {
	std::string Name;
	Hash Hash;
} SportsClassic[] = {

	{ "Ardent", VEHICLE_ARDENT },
	{ "Casco", VEHICLE_CASCO },
	{ "Cheetah Classic", VEHICLE_CHEETAH2 },
	{ "Coquette Blackfin", VEHICLE_COQUETTE3 },
	{ "Coquette Classic", VEHICLE_COQUETTE2 },
	{ "Infernus Classic", VEHICLE_INFERNUS2},
	{ "JB700", VEHICLE_JB700 },
	{ "Lurcher", VEHICLE_LURCHER },
	{ "Manana", VEHICLE_MANANA },
	{ "Monroe", VEHICLE_MONROE },
	{ "Peyote", VEHICLE_PEYOTE },
	{ "Pigalle", VEHICLE_PIGALLE },
	{ "Rapid GT Classic", VEHICLE_RAPIDGT3 },
	{ "Retinue", VEHICLE_RETINUE },
	{ "Roosevelt", VEHICLE_BTYPE },
	{ "Roosevelt Valor", VEHICLE_BTYPE3 },
	{ "Stinger", VEHICLE_STINGER },
	{ "Stinger GT", VEHICLE_STINGERGT },
	{ "Stirling GT", VEHICLE_FELTZER3 },
	{ "Torero", VEHICLE_TORERO },
	{ "Tornado", VEHICLE_TORNADO },
	{ "Tornado (Convertible)", VEHICLE_TORNADO2 },
	{ "Tornado (Rusty)", VEHICLE_TORNADO3 },
	{ "Tornado (Mariachi)", VEHICLE_TORNADO4 },
	{ "Turismo Classic", VEHICLE_TURISMO2 },
	{ "Z-Type", VEHICLE_ZTYPE },
};

static struct {
	std::string Name;
	Hash Hash;
} SuperHash[] = {

	{ "Pfister 811", VEHICLE_PFISTER },
	{ "Adder", VEHICLE_ADDER },
	{ "Banshee", VEHICLE_BANSHEE2 },
	{ "Bullet", VEHICLE_BULLET },
	{ "Cheetah", VEHICLE_CHEETAH },
	{ "Cyclone", VEHICLE_CYCLONE },
	{ "Entity XF", VEHICLE_ENTITYXF },
	{ "ETR1", VEHICLE_ETR1 },
	{ "FMJ", VEHICLE_FMJ },
	{ "Infernus", VEHICLE_INFERNUS },
	{ "Itali GTB", VEHICLE_ITALIGTB },
	{ "Itali GTB Custom", VEHICLE_ITALIGTBCUSTOM },
	{ "Progen GP1", VEHICLE_GP1 },
	{ "Nero", VEHICLE_NERO },
	{ "Nero Custom", VEHICLE_NERO2 },
	{ "Osiris", VEHICLE_OSIRIS },
	{ "Penetrator", VEHICLE_PENETRATOR },
	{ "RE-7B", VEHICLE_LE7B },
	{ "Reaper", VEHICLE_REAPER },
	{ "Rocket Voltic", VEHICLE_ROCKETVOLTIC },
	{ "Sultan RS", VEHICLE_SULTANRS },
	{ "T20", VEHICLE_T20 },
	{ "Tempesta", VEHICLE_TEMPESTA },
	{ "Turismo R", VEHICLE_TURISMOR },
	{ "Tyrus", VEHICLE_TYRUS },
	{ "Vacca", VEHICLE_VACCA },
	{ "Vagner", VEHICLE_VAGNER },
	{ "Visione", VEHICLE_VISIONE },
	{ "Voltic", VEHICLE_VOLTIC },
	{ "X80 Proto", VEHICLE_X80 },
	{ "XA-21", VEHICLE_XA21 },
	{ "Zentorno", VEHICLE_ZENTORNO },
};


static struct {
	std::string Name;
	Hash Hash;
} Gunrunning[] = {
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