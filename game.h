
#ifndef _EWATC_GAME
#define _EWATC_GAME

enum
{
	MAP_HEIGHT_IN_PIXELS = 480,
	MAP_WIDTH_IN_PIXELS = 640,
	MAP_TILE_WIDTH = 64,
	MAP_TILE_HEIGHT = 64,
	MAX_NUM_ENTITIES = 128,
	MAX_MAP_COLUMNS = (MAP_WIDTH_IN_PIXELS/MAP_TILE_WIDTH),
	MAX_MAP_ROWS = (MAP_HEIGHT_IN_PIXELS/MAP_TILE_HEIGHT)
};

enum EntityType
{
	ENTITY_TYPE_UNKNOWN,
	ENTITY_TYPE_PAC,
	ENTITY_TYPE_DOT
};

enum EntityState
{
	ENTITY_STATE_DEAD,
	ENTITY_STATE_ALIVE
};

enum Direction
{
	DIRECTION_UP,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_DOWN
};

struct Location
{
	int x;
	int y;
};

struct Rect
{
	int top;
	int left;
	int width;
	int height;
};

struct Entity
{
	EntityType type;
	int guid;
	Location loc;
	int velocity;
	Direction dir;
	Rect hitBox;
	EntityState state;
	
	// TODO Rendering
	// animation state == EntityState + Direction
	// frame number
	int renderFrameNumber;
};

struct MapTile
{
	int tileId;
	bool side[4];
};

struct Map
{
	MapTile tile[MAX_MAP_ROWS][MAX_MAP_COLUMNS];
	Entity entity[MAX_NUM_ENTITIES];
};

struct PlayingField
{
	Map map;
};

struct GameInfo
{
	PlayingField field;
	int playerId;
};



void StartGame();

#endif
