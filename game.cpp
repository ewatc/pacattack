#include "game.h"
#include "ewatce.h"

// Test

bool GameInit();
void GameShutdown();
void GameLoop();
bool GameInputEvent(const SDL_Event &event);

void initGameInfo();
Entity CreatePlayer(int locX, int locY, int velocity, DIRECTION dir);
Entity CreateDot(int locX, int locY);
void AddEntityToMap(Map &map, const Entity &entity);
Entity RemoveEntityFromMap(Map &map, int id);

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

        // Render Result

        // Sleep until time to run again
    }
}

bool GameInputEvent(const SDL_Event &event)
{
    bool timeToQuit = false;

    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
        case SDLK_RIGHT:
        case SDLK_UP:
        case SDLK_DOWN:
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
	
	for (int row=0; row<MAX_MAP_ROWS; ++row) {
		for (int column; column<MAX_MAP_COLUMNS; ++column) {
			gGame.field.map.tile[row][column].tileId = 0;
			gGame.field.map.tile[row][column].top = 1;
			gGame.field.map.tile[row][column].bottom = 1;
			gGame.field.map.tile[row][column].left = 1;
			gGame.field.map.tile[row][column].right = 1;
		}
	}
	
	// TODO do more
}

Entity CreateEntity(int locX, int locY, int velocity, DIRECTION dir)
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

Entity CreatePlayer(int locX, int locY, int velocity, DIRECTION dir)
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

