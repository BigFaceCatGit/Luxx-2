#pragma once

//Addresses from GTAV.exe module
#define ADDRESS_WAYPOINT				0x1F59BB0		// old as fuck.
#define ADDRESS_INVEHICLE				0x1FD8438		//is player in vehicle? bool. old as fuck.

//offset from WORLD
#define OFFSET_PLAYER					0x08			//playerbase

//entity offsets
#define OFFSET_ENTITY_POSBASE			0x30			//base of a structure that contains entity coords
#define OFFSET_ENTITY_POSBASE_POS		0x50			//vector3
#define OFFSET_ENTITY_POS				0x90			//vector3
#define OFFSET_ENTITY_HEALTH			0x280			//entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX		0x2A0			//they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER			0x2A8			//base to a list of the last 3 entities that attacked the current entity

//player (entity) offsets
#define OFFSET_PER_FRAME				0x190			//per frame flags
#define OFFSET_PLAYER_ARMOR				0x14A0			//armour
#define OFFSET_PLAYER_INFO				0x10A8			//playerInfo struct
#define OFFSET_PLAYER_INFO_WANTED		0x798			//wanted level; DWORD
#define OFFSET_PLAYER_VEHICLE			0x14E0			//ptr to last used vehicle
#define OFFSET_PLAYER_LAND_SPEED		0XE8			//player land move speed
#define OFFSET_PLAYER_SWIM_SPEED		0XE4			//player swim move speed
#define OFFSET_PLAYER_STAMINA			0XC00			//player stamina
#define OFFSET_PLAYER_STAMINA_MAX		0XC04			//player stamina max
#define OFFSET_PLAYER_LOCAL_NAME		0X7C			//player local name

//vehicle offsets
#define OFFSET_C_VEHICLE				0x14E0
#define OFFSET_HANDLING					0x850
#define OFFSET_VEHICLE_HEALTH			0x82C			//vehicle health; 0.f-1000.f

//weapon offsets
#define OFFSET_WEAPON_MANAGER			0x10B8			//from playerbase
#define OFFSET_WEAPON_CURRENT			0x20			//from weapon manager
#define OFFSET_WEAPON_AMMOINFO			0x48			//from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX		0x28			//ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1	0x08			//ptr to cur ammo 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2	0x00			//ptr to cur ammo 2
#define OFFSET_WEAPON_AMMOINFO_CURAMMO	0x18			//offset to cur ammo

typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef int Scaleform;

#pragma pack(push, 1)
typedef struct
{
	float x;
	DWORD _paddingx;
	float y;
	DWORD _paddingy;
	float z;
	DWORD _paddingz;
} Vector3;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct
{
	float x;
	float y;
	float z;
} Vector3_t;
#pragma pack(pop)

struct Blip_t {
public:
	__int32 iID; //0x0000 
	__int8 iID2; //0x0004 
	char _0x0005[3];
	BYTE N000010FB; //0x0008 (80 = moves with player, some values will turn icon into map cursor and break it)
	char _0x0009[7];
	Vector3 coords;
	char _0x001C[6];
	BYTE bFocused; //0x0022   (Focused? 0100 0000)
	char _0x0023[5];
	char* szMessage; //0x0028 If not null, contains the string of whatever the blip says when selected.
	char _0x0030[16];
	int iIcon; //0x0040
	char _0x0044[4];
	DWORD dwColor; //0x0048 (Sometimes works?)
	char _0x004C[4];
	float fScale; //0x0050 
	__int16 iRotation; //0x0054 Heading
	BYTE bInfoIDType; //0x0056 GET_BLIP_INFO_ID_TYPE
	BYTE bZIndex; //0x0057 
	BYTE bDisplay; //0x0058  Also Visibility 0010
	BYTE bAlpha; //0x0059
};//Size=0x005A

struct BlipList {
public:
	Blip_t* m_Blips[1500]; //0x0000 

};//Size=0x2F18