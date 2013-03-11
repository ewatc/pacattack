
#ifndef _EWATCE_H
#define _EWATCE_H

#include <SDL.h>
#include "log.h"
#include "ewatceconfig.h"

bool ewatceInitialize();
void ewatceShutdown();

SDL_Surface* ewatceGetScreenSurface();


#endif