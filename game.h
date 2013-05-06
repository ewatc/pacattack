
#ifndef _EWATC_GAME
#define _EWATC_GAME

#include <SDL.h>

enum
{
	MAP_HEIGHT_IN_PIXELS = 64*4, // FIX ME TODO
	MAP_WIDTH_IN_PIXELS = 64*4,
	MAP_TILE_WIDTH = 64,
	MAP_TILE_HEIGHT = 64,
	MAX_NUM_ENTITIES = 128,
	MAX_MAP_COLUMNS = (MAP_WIDTH_IN_PIXELS/MAP_TILE_WIDTH),
	MAX_MAP_ROWS = (MAP_HEIGHT_IN_PIXELS/MAP_TILE_HEIGHT)
};

enum {
	IMAGE_TILES = 0,
	IMAGE_PACMAN = 1,
	IMAGE_DOT = 2,
	IMAGE_MAX
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

enum {
	WALL_UP		= 0x01,
	WALL_DOWN	= 0x02,
	WALL_LEFT	= 0x04,
	WALL_RIGHT	= 0x08
};

struct MapTile
{
	int tileId;
	unsigned int side;
};

struct Map
{
	MapTile tile[MAX_MAP_ROWS][MAX_MAP_COLUMNS];
	Entity entity[MAX_NUM_ENTITIES];
	Entity player;
};

struct PlayingField
{
	Map map;
};

struct GameInfo
{
	PlayingField field;
	int playerId;
	SDL_Surface *images[IMAGE_MAX];
};



void StartGame();

#endif
