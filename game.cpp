#include "game.h"
#include "ewatce.h"

// Test

bool GameInit();
void GameShutdown();
void GameLoop();
bool GameInputEvent(const SDL_Event &event);
bool GameLogic();
void GameRender();

void initGameInfo();
Entity CreatePlayer(int locX, int locY, int velocity, Direction dir);
Entity CreateDot(int locX, int locY);
void AddEntityToMap(Map &map, const Entity &entity);
Entity RemoveEntityFromMap(Map &map, int id);

Entity* FindEntityInMap(Map &map, int guid);

GameInfo gGame;

void StartGame()
{
    if (GameInit()) {
        // Game initialization succes, start the game loop
        GameLoop();
    }

    // Game exiting, clean up
    GameShutdown();
}

bool GameInit()
{
	initGameInfo();

    Entity player = CreatePlayer(0, // loc x
						  0, // loc y
						0, // velocity
						DIRECTION_RIGHT);

	gGame.playerId = player.guid;
	AddEntityToMap(gGame.field.map, player);

	// TODO load images

    return true;
}

void GameShutdown()
{
    // Release resources for game here
}

void GameLoop()
{
    bool timeToQuit = false;
    SDL_Event event;

    while (!timeToQuit) {
        // Handle SDL events, and Input
        while (SDL_PollEvent(&event) && !timeToQuit) {
            switch (event.type) {
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                timeToQuit = GameInputEvent(event);
                break;
            case SDL_QUIT:
                timeToQuit = true;
                break;
            }
        }

        // Do Game logic
		if (!timeToQuit) {
			timeToQuit = GameLogic();
		}

        // Render Result
		if (!timeToQuit) {
			GameRender();
		}

        // Sleep until time to run again
    }
}

bool GameLogic()
{
	bool timeToQuit = false;

	// Movement
	// - collision walls, entity movement
	for (int i=0; i<MAX_NUM_ENTITIES; ++i) {
		Entity *entity = &gGame.field.map.entity[i];
		if (entity->velocity > 0) {
			// based on direction check if there is a wall
            // TODO determine x and y
            int xTile = entity->loc.y / MAP_TILE_HEIGHT;
            int yTile = entity->loc.x / MAP_TILE_WIDTH;
			if (!gGame.field.map.tile[yTile][xTile].side[entity->dir]) {
				// no wall
				switch (entity->dir) {
				case DIRECTION_UP:
					entity->loc.y -= entity->velocity;
					if (entity->loc.y < 0) {
						entity->loc.y = 0;
					}
					break;
				case DIRECTION_LEFT:
					entity->loc.x -= entity->velocity;
					if (entity->loc.x < 0) {
						entity->loc.x = 0;
					}
					break;
				case DIRECTION_RIGHT:
					entity->loc.x -= entity->velocity;
					if (entity->loc.x > MAP_WIDTH_IN_PIXELS) {
						entity->loc.y = MAP_WIDTH_IN_PIXELS - 1;
					}
					break;
				case DIRECTION_DOWN:
					entity->loc.y -= entity->velocity;
					if (entity->loc.y > MAP_HEIGHT_IN_PIXELS) {
						entity->loc.y = MAP_HEIGHT_IN_PIXELS - 1;
					}
					break;
				}
			}
		}
	}

	// collision checking
	// - between entities, ie player and dots
	//		- consequences, player eating dot, increase score


	return timeToQuit;
}

void GameRender()
{
	unsigned int color;
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = MAP_WIDTH_IN_PIXELS;
	rect.h = MAP_HEIGHT_IN_PIXELS;

    // Get color in surface format
    color = ewatceRGB2Color(0, 255, 0); // green

	// clear the background
	SDL_FillRect(ewatceGetScreenSurface(), &rect, color);

	// tiles

	// pacman, entity
	// - debug draw hit boxes
}

bool GameInputEvent(const SDL_Event &event)
{
    bool timeToQuit = false;
	Entity *player;

    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
			player = FindEntityInMap(gGame.field.map, gGame.playerId);
			player->dir = DIRECTION_LEFT;
			player->velocity = 1;
			break;
        case SDLK_RIGHT:
			player = FindEntityInMap(gGame.field.map, gGame.playerId);
			player->dir = DIRECTION_RIGHT;
			player->velocity = 1;
			break;
        case SDLK_UP:
			player = FindEntityInMap(gGame.field.map, gGame.playerId);
			player->dir = DIRECTION_UP;
			player->velocity = 1;
			break;
        case SDLK_DOWN:
			player = FindEntityInMap(gGame.field.map, gGame.playerId);
			player->dir = DIRECTION_DOWN;
			player->velocity = 1;
            break;
        case SDLK_ESCAPE:
            timeToQuit = true;
            break;
        default:
            // do nothing
            break;
        }
    case SDL_KEYUP:
        // only acting on key down events?
		// for now, yes
        break;
    }

    return timeToQuit;
}

void initGameInfo()
{
	gGame.playerId = -1;

	for (int i=0; i<MAX_NUM_ENTITIES; ++i) {
		gGame.field.map.entity[i].type = ENTITY_TYPE_UNKNOWN;
	}

	// TODO: Load Map
	for (int row=0; row<MAX_MAP_ROWS; ++row) {
		for (int column; column<MAX_MAP_COLUMNS; ++column) {
			gGame.field.map.tile[row][column].tileId = 0;
			gGame.field.map.tile[row][column].side[0] = 1;
			gGame.field.map.tile[row][column].side[1] = 1;
			gGame.field.map.tile[row][column].side[2] = 1;
			gGame.field.map.tile[row][column].side[3] = 1;
		}
	}

	// TODO do more
}

Entity CreateEntity(int locX, int locY, int velocity, Direction dir)
{
	Entity entity;
	static int guid = 0;

	entity.loc.x = locX;
	entity.loc.y = locY;
	entity.velocity = velocity;
	entity.dir = dir;
	entity.hitBox.top = 0;
	entity.hitBox.left = 0;
	entity.hitBox.width = 32;
	entity.hitBox.height = 32;
	entity.guid = guid++;

	return entity;
}

Entity CreatePlayer(int locX, int locY, int velocity, Direction dir)
{
	Entity entity;

	entity = CreateEntity(locX, locY, velocity, dir);
	entity.type = ENTITY_TYPE_PAC;

	return entity;
}

Entity CreateDot(int locX, int locY)
{
	Entity entity;

	entity = CreateEntity(locX, locY, 0, DIRECTION_RIGHT);
	entity.type = ENTITY_TYPE_DOT;

    return entity;
}

Entity* FindEntityInMap(Map &map, int guid)
{
	for (int i=0; i<MAX_NUM_ENTITIES; ++i) {
		if (map.entity[i].guid == guid) {
			return &map.entity[i];
		}
	}

	return NULL;
}

void AddEntityToMap(Map &map, const Entity &entity)
{
	int i;

	for (i=0; i<MAX_NUM_ENTITIES; ++i) {
		if (map.entity[i].type == ENTITY_TYPE_UNKNOWN) {
				// found empty entry
				break;
		}
	}

	if (i < MAX_NUM_ENTITIES) {
		map.entity[i] = entity;
	} else {
		// error
	}
}

Entity RemoveEntityFromMap(Map &map, int id)
{
	Entity entity;

	for (int i=0; i<MAX_NUM_ENTITIES; ++i) {
		if (map.entity[i].type != ENTITY_TYPE_UNKNOWN) {
			if (map.entity[i].guid == id) {
				// found entity to remove
				map.entity[i].type = ENTITY_TYPE_UNKNOWN;
				entity = map.entity[i];
				return entity;
			}
		}
	}

	// error
	return entity;
}

