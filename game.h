
#ifndef _EWATC_GAME
#define _EWATC_GAME

enum
{
	MAP_TILE_WIDTH = 64,
	MAP_TILE_HEIGHT = 64,
	MAX_NUM_ENTITIES = 128,
	MAX_MAP_COLUMNS = (640/64),
	MAX_MAP_ROWS = (480/64)
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
	Location loc;
	int velocity;
	Direction dir;
	Rect hitBox;
	EntityState state;
	
	// TODO Rendering
};

struct MapTile
{
	int tileId;
	bool top;
	bool bottom;
	bool left;
	bool right;
};

struct Map
{
	MapTile tile[MAX_MAP_ROWS][MAX_MAP_COLUMNS];
};

struct PlayingField
{
	Entity entities[MAX_NUM_ENTITIES];
	Map map;
};

void StartGame();

#endif
