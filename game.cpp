#include "game.h"
#include "ewatce.h"

// Test

bool GameInit();
void GameShutdown();
void GameLoop();
bool GameInputEvent(const SDL_Event &event);
bool GameLogic();
void GameRender();

void loadGameMap();
bool loadGameImages();

void initGameInfo();
Entity CreatePlayer(int locX, int locY, int velocity, Direction dir);
Entity CreateDot(int locX, int locY);
void AddEntityToMap(Map &map, const Entity &entity);
Entity RemoveEntityFromMap(Map &map, int id);
void AddPlayerToMap(Map &map, const Entity &entity);
Entity RemovePlayerFromMap(Map &map, int id);

bool CheckCollisionWithWall(const Map &map, int locX, int locY);
bool CheckCollisionWithWall(const Map &map, const Rect &cBox);

void UpdateEntityMovement(const Map &map, Entity &entity);

Entity* FindEntityInMap(Map &map, int guid);

void RenderUI();


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

    Entity player = CreatePlayer(32, // loc x
								 32, // loc y
								 0, // velocity
								 DIRECTION_RIGHT);

	gGame.playerId = player.guid;
	AddPlayerToMap(gGame.field.map, player);

	if (!loadGameImages()) {
		return false;
	}
	
	loadGameMap();

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
	unsigned int lastTick;
    unsigned int currentTick;
    unsigned int startTimeMs = SDL_GetTicks();

    while (!timeToQuit) {
        int sleepMs;
		lastTick = SDL_GetTicks();

        gGame.stats.runningTimeMs = lastTick - startTimeMs;
		
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
		currentTick = SDL_GetTicks();

		//wait the appropriate amount of time
		sleepMs = (1000/30) - (currentTick - lastTick);
		if(sleepMs > 0) {
			SDL_Delay(sleepMs);
		}
    }
}

bool GameLogic()
{
	bool timeToQuit = false;

	// Movement
	// - collision walls, entity movement

    // first check against the player
    UpdateEntityMovement(gGame.field.map, gGame.field.map.player);

    // second check against the rest of the entities
	for (int i=0; i< MAX_NUM_ENTITIES; ++i) {
        UpdateEntityMovement(gGame.field.map, gGame.field.map.entity[i]);
	}

	// collision checking
	// - between entities, ie player and dots
	//		- consequences, player eating dot, increase score
    // TODO

	LOGDBG("Player is located at: %d,%d",
	        gGame.field.map.player.loc.x,
			gGame.field.map.player.loc.y);

	return timeToQuit;
}

void GameRender()
{
	unsigned int color;
	SDL_Rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.w = EWATCE_SCREEN_WIDTH;
	rect.h = EWATCE_SCREEN_HEIGHT;

    // Get color in surface format
    color = ewatceRGB2Color(0, 255, 0); // green

	// clear the background

	SDL_FillRect(ewatceGetScreenSurface(), &rect, color);

	// tiles
	for (int y=0; y< MAX_MAP_ROWS; ++y) {
		for (int x=0; x< MAX_MAP_COLUMNS; ++x) {
			// draw tile
			SDL_Rect srcRect;
			SDL_Rect dstRect;
			
			srcRect.x = gGame.field.map.tile[y][x].tileId * MAP_TILE_WIDTH;
			srcRect.y = 0;
			srcRect.w = MAP_TILE_WIDTH;
			srcRect.h = MAP_TILE_HEIGHT;
			
			dstRect.x = x * MAP_TILE_WIDTH;
			dstRect.y = y * MAP_TILE_HEIGHT;
			dstRect.w = MAP_TILE_WIDTH;
			dstRect.h = MAP_TILE_HEIGHT;
			
			if (SDL_BlitSurface(gGame.images[IMAGE_TILES],
							    &srcRect,
							    ewatceGetScreenSurface(),
			                    &dstRect) != 0) {
				LOGERR("Unable to blit, error=[%s]", SDL_GetError());
			}
		}
	}

	// pacman, entity
	// - debug draw hit boxes
	if (gGame.field.map.player.type != ENTITY_TYPE_UNKNOWN) {
		SDL_Rect srcRect;
		SDL_Rect dstRect;

		srcRect.x = gGame.field.map.player.renderFrameNumber * 32;
		srcRect.y = 0;
		srcRect.w = 32;
		srcRect.h = 32;
		
		dstRect.x = gGame.field.map.player.loc.x - 16;
		dstRect.y = gGame.field.map.player.loc.y - 16;
		dstRect.w = 32;
		dstRect.h = 32;

        LOGDBG("Drawing Entity: %d @ %dx%d - tile %d.%dx%d.%d",
               gGame.field.map.player.guid,
               gGame.field.map.player.loc.x,
               gGame.field.map.player.loc.y,
               gGame.field.map.player.loc.x/MAP_TILE_WIDTH,
               gGame.field.map.player.loc.x%MAP_TILE_WIDTH,
               gGame.field.map.player.loc.y/MAP_TILE_HEIGHT,
               gGame.field.map.player.loc.y%MAP_TILE_HEIGHT);

		if (SDL_BlitSurface(gGame.images[IMAGE_PACMAN],
							&srcRect,
							ewatceGetScreenSurface(),
							&dstRect) != 0) {
			LOGERR("Unable to blit, error=[%s]", SDL_GetError());
		}

        int currTimeMs = SDL_GetTicks();
        int timeDiffMs = currTimeMs - gGame.field.map.player.renderFrameStartMs;
        if (timeDiffMs >= ANIMATION_TIME) {
            ++gGame.field.map.player.renderFrameNumber;
            gGame.field.map.player.renderFrameStartMs = currTimeMs;
        }

        if (gGame.field.map.player.renderFrameNumber >= gGame.field.map.player.renderFrames) {
            gGame.field.map.player.renderFrameNumber = 0;
        }
	}

    // Render the UI
    RenderUI();

	
	SDL_Flip(ewatceGetScreenSurface());
}

bool GameInputEvent(const SDL_Event &event)
{
    bool timeToQuit = false;
	Entity *player = &gGame.field.map.player;

    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_LEFT:
			player->pendingMove.dir = DIRECTION_LEFT;
			player->pendingMove.velocity = -1 * VELOCITY_FACTOR;
			LOGDBG("Player moving LEFT");
			break;
        case SDLK_RIGHT:
			player->pendingMove.dir = DIRECTION_RIGHT;
			player->pendingMove.velocity = 1 * VELOCITY_FACTOR;
			LOGDBG("Player moving RIGHT");
			break;
        case SDLK_UP:
			player->pendingMove.dir = DIRECTION_UP;
			player->pendingMove.velocity = -1 * VELOCITY_FACTOR;
			LOGDBG("Player moving UP");
			break;
        case SDLK_DOWN:
			player->pendingMove.dir = DIRECTION_DOWN;
			player->pendingMove.velocity = 1 * VELOCITY_FACTOR;
			LOGDBG("Player moving DOWN");
            break;
        case SDLK_ESCAPE:
            timeToQuit = true;
			LOGDBG("Player trying to quit");
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
	
	gGame.field.map.player.type = ENTITY_TYPE_UNKNOWN;

	// Init Map
	for (int row=0; row<MAX_MAP_ROWS; ++row) {
		for (int column; column<MAX_MAP_COLUMNS; ++column) {
			gGame.field.map.tile[row][column].tileId = 0;
			gGame.field.map.tile[row][column].side = 0;
		}
	}

	// Init stats
    memset(&gGame.stats, 0, sizeof(gGame.stats));
}

Entity CreateEntity(int locX, int locY, int velocity, Direction dir)
{
	Entity entity;
	static int guid = 0;

	entity.loc.x = locX;
	entity.loc.y = locY;
	entity.move.velocity = velocity;
    entity.move.dir = dir;
	entity.pendingMove = entity.move;
	entity.hitBox.top = 0;
	entity.hitBox.left = 0;
	entity.hitBox.width = 32;
	entity.hitBox.height = 32;
	entity.guid = guid++;
	entity.renderFrameNumber = 0;
    entity.renderFrames = 0;
    entity.renderFrameStartMs = 0;

	return entity;
}

Entity CreatePlayer(int locX, int locY, int velocity, Direction dir)
{
	Entity entity;

	entity = CreateEntity(locX, locY, velocity, dir);
	entity.type = ENTITY_TYPE_PAC;
    entity.renderFrames = 2;

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

void AddPlayerToMap(Map &map, const Entity &entity)
{
	map.player = entity;
}

Entity RemovePlayerFromMap(Map &map, int id)
{
	Entity entity;

	entity = map.player;
	
	// reset map player
	map.player.type = ENTITY_TYPE_UNKNOWN;

	// error
	return entity;
}

void loadGameMap()
{
	gGame.field.map.tile[0][0].tileId = 1;
	gGame.field.map.tile[0][0].side = WALL_UP|WALL_LEFT;
	gGame.field.map.tile[0][1].tileId = 4;
	gGame.field.map.tile[0][1].side = WALL_UP|WALL_DOWN;
	gGame.field.map.tile[0][2].tileId = 6;
	gGame.field.map.tile[0][2].side = WALL_UP;
	gGame.field.map.tile[0][3].tileId = 9;
	gGame.field.map.tile[0][3].side = WALL_UP|WALL_RIGHT;
	
	gGame.field.map.tile[1][0].tileId = 2;
	gGame.field.map.tile[1][0].side = WALL_LEFT|WALL_RIGHT;
	gGame.field.map.tile[1][1].tileId = 11;
	gGame.field.map.tile[1][1].side = WALL_UP|WALL_LEFT|WALL_DOWN|WALL_RIGHT;
	gGame.field.map.tile[1][2].tileId = 2;
	gGame.field.map.tile[1][2].side = WALL_RIGHT|WALL_LEFT;
	gGame.field.map.tile[1][3].tileId = 2;
	gGame.field.map.tile[1][3].side = WALL_RIGHT|WALL_LEFT;
	
	gGame.field.map.tile[2][0].tileId = 3;
	gGame.field.map.tile[2][0].side = WALL_LEFT;
	gGame.field.map.tile[2][1].tileId = 4;
	gGame.field.map.tile[2][1].side = WALL_UP|WALL_DOWN;
	gGame.field.map.tile[2][2].tileId = 5;
	gGame.field.map.tile[2][2].side = WALL_RIGHT|WALL_DOWN;
	gGame.field.map.tile[2][3].tileId = 2;
	gGame.field.map.tile[2][3].side = WALL_RIGHT|WALL_LEFT;
	
	gGame.field.map.tile[3][0].tileId = 10;
	gGame.field.map.tile[3][0].side = WALL_DOWN|WALL_LEFT;
	gGame.field.map.tile[3][1].tileId = 4;
	gGame.field.map.tile[3][1].side = WALL_UP|WALL_DOWN;
	gGame.field.map.tile[3][2].tileId = 4;
	gGame.field.map.tile[3][2].side = WALL_UP|WALL_DOWN;
	gGame.field.map.tile[3][3].tileId = 5;
	gGame.field.map.tile[3][3].side = WALL_RIGHT|WALL_DOWN;
}

bool loadGameImages()
{
	gGame.images[IMAGE_TILES] = SDL_LoadBMP("tiles.bmp");
	if (gGame.images[IMAGE_TILES] == NULL) {
		LOGERR("Unable to load file [%s]", "tiles.bmp");
		return false;
	}
	
	gGame.images[IMAGE_PACMAN] = SDL_LoadBMP("pacman.bmp");
	if (gGame.images[IMAGE_PACMAN] == NULL) {
		LOGERR("Unable to load file[%s]", "pacman.bmp");
		return false;
	}
	
	return true;
}

bool CheckCollisionWithWall(const Map &map, int locX, int locY)
{
    int xTile = locX / MAP_TILE_WIDTH;
    int yTile = locY / MAP_TILE_HEIGHT;
    int xTileOffset = locX % MAP_TILE_WIDTH;
    int yTileOffset = locY % MAP_TILE_HEIGHT;

    if (xTileOffset < MAP_TILE_WALL_WIDTH) {
        if (map.tile[yTile][xTile].side & WALL_LEFT) {
            return true;
        }
    } else if (xTileOffset > (MAP_TILE_WIDTH - MAP_TILE_WALL_WIDTH)) {
        if (map.tile[yTile][xTile].side & WALL_RIGHT) {
            return true;
        }
    }

    if (yTileOffset < MAP_TILE_WALL_HEIGHT) {
        if (map.tile[yTile][xTile].side & WALL_UP) {
            return true;
        }
    } else if (yTileOffset > (MAP_TILE_HEIGHT - MAP_TILE_WALL_HEIGHT)) {
        if (map.tile[yTile][xTile].side & WALL_DOWN) {
            return true;
        }
    }

    return false;
}

bool CheckCollisionWithWall(const Map &map, const Rect &cBox)
{
    int x;
    int y;

    // Check 4 corners

    // top left
    x = cBox.top;
    y = cBox.left;
    if (CheckCollisionWithWall(map, x, y)) {
        return true;
    }

    // top right
    x = cBox.top;
    y = cBox.left + cBox.width;
    if (CheckCollisionWithWall(map, x, y)) {
        return true;
    }

    // bottom left
    x = cBox.top + cBox.height;
    y = cBox.left;
    if (CheckCollisionWithWall(map, x, y)) {
        return true;
    }

    // bottom right
    x = cBox.top + cBox.height;
    y = cBox.left + cBox.width;
    if (CheckCollisionWithWall(map, x, y)) {
        return true;
    }

    // no collision
    return false;
}

void UpdateEntityMovement(const Map &map, Entity &entity)
{
    // Checking if entity is moving
    if (entity.move.velocity != 0) {
        bool hitWall = false;
        bool changeDirections = false;

        // movement
        switch (entity.move.dir) {
        case DIRECTION_UP:
        case DIRECTION_DOWN:
            entity.loc.y += entity.move.velocity;

            hitWall = CheckCollisionWithWall(map, Rect(entity.loc.x - 16, entity.loc.y - 16, 32, 32));
            if (hitWall) {
                // collided with wall, move player back
                LOGDBG("Entity %d hit U/D wall @ %dx%d",
                       entity.guid,
                       entity.loc.x,
                       entity.loc.y);

                entity.loc.y -= entity.move.velocity;

                entity.move.velocity = 0;
            }

            // Only allow changing movement when in the middle of the row if new direction is left or right
            if (entity.pendingMove.dir != DIRECTION_UP && entity.pendingMove.dir != DIRECTION_DOWN) {
                if ((entity.loc.y % MAP_TILE_HEIGHT) == (MAP_TILE_HEIGHT / 2)) {
                    if (!hitWall) {
                        // Check to make sure going in the new direction would not hit a wall
                        // before changing it.
                        hitWall = CheckCollisionWithWall(gGame.field.map,
                                                         Rect(entity.loc.x - 16 + entity.pendingMove.velocity, entity.loc.y - 16, 32, 32));
                        if (!hitWall) {
                            changeDirections = true;
                        }

                    }
                }
            } else {
                // always allow switching going back and forth
                changeDirections = true;
            }

            if (changeDirections) {
                LOGDBG("Entity %d changing movement dir %d velocity %d",
                       entity.guid,
                       entity.move.dir,
                       entity.move.velocity);

                entity.move = entity.pendingMove;
            }
            break;
        case DIRECTION_LEFT:
        case DIRECTION_RIGHT:
            entity.loc.x += entity.move.velocity;

            hitWall = CheckCollisionWithWall(gGame.field.map, Rect(entity.loc.x - 16, entity.loc.y - 16, 32, 32));
            if (hitWall) {
                // collided with wall, move player back
                LOGDBG("Entity %d hit L/R wall @ %dx%d",
                       entity.guid,
                       entity.loc.x,
                       entity.loc.y);

                entity.loc.x -= entity.move.velocity;

                entity.move.velocity = 0;
            }

            // Only allow changing movement when in the middle of the column if new direction is up or down
            if (entity.pendingMove.dir != DIRECTION_LEFT && entity.pendingMove.dir != DIRECTION_RIGHT) {
                if ((entity.loc.x % MAP_TILE_WIDTH) == (MAP_TILE_WIDTH / 2)) {
                    if (!hitWall) {
                        // Check to make sure going in the new direction would not hit a wall
                        // before changing it.
                        hitWall = CheckCollisionWithWall(gGame.field.map,
                                                         Rect(entity.loc.x - 16, entity.loc.y - 16 + entity.pendingMove.velocity, 32, 32));
                        if (!hitWall) {
                            changeDirections = true;
                        }
                    }
                }
            } else {
                // always allow switching going up and down
                changeDirections = true;
            }

            if (changeDirections) {
                LOGDBG("Entity %d changing movement dir %d velocity %d",
                       entity.guid,
                       entity.move.dir,
                       entity.move.velocity);

                entity.move = entity.pendingMove;
            }
            break;
        }
    } else {
        // start moving if needed
        LOGDBG("Entity %d changing movement dir %d velocity %d",
               entity.guid,
               entity.move.dir,
               entity.move.velocity);

        entity.move = entity.pendingMove;
    }
}

void RenderUI()
{
    SDL_Surface *textSurface;
    SDL_Color textColor;
    SDL_Rect dstRect;

    // Render text using this color
    textColor.r = 245;
    textColor.g = 245;
    textColor.b = 245;

    // Render text on temporary surface
    textSurface = TTF_RenderText_Solid(ewatceGetDefaultFont(), "AwesomeText", textColor);

    dstRect.x = MAP_WIDTH_IN_PIXELS + 10;
    dstRect.y = 0;
    dstRect.w = 200;
    dstRect.h = 200;

    // Blit that temporary surface with text on to the main surface
    if (SDL_BlitSurface(textSurface,
                        NULL, // no cropping of source
                        ewatceGetScreenSurface(),
                        &dstRect) != 0) {
        LOGERR("Unable to blit, error=[%s]", SDL_GetError());
    }
    SDL_FreeSurface(textSurface);


    // Render debug information
    char temp[128];
    snprintf(temp, sizeof(temp),
             "Game Time: %d.%01d s",
             gGame.stats.runningTimeMs/1000,
             gGame.stats.runningTimeMs%1000/100);
    textSurface = TTF_RenderText_Solid(ewatceGetDefaultFont(), temp, textColor);

    dstRect.y = 200;

    // Blit that temporary surface with text on to the main surface
    if (SDL_BlitSurface(textSurface,
                        NULL, // no cropping of source
                        ewatceGetScreenSurface(),
                        &dstRect) != 0) {
        LOGERR("Unable to blit, error=[%s]", SDL_GetError());
    }
    SDL_FreeSurface(textSurface);
}