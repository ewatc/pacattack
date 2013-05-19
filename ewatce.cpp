#include "ewatce.h"
#include <SDL_ttf.h>


static SDL_Surface* gScreenSurface;
static TTF_Font* gDefaultFont;

bool ewatceInitialize()
{
    // Initialize logging system...
    OpenLog(std::string(EWATCE_LOGFILENAME));

    LOGINF("Initializing....");

    // Initalize SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
        LOGCRT("SDL_Init failed, error=[%s]", SDL_GetError());
        return false;
    }

    LOGINF("SDL Initialized");

    // Hide Cursor
    SDL_ShowCursor(SDL_DISABLE);

    // Enable Unicode support
    SDL_EnableUNICODE(1);

    // Initialize SDL Video Mode
    gScreenSurface = SDL_SetVideoMode(EWATCE_SCREEN_WIDTH,
                                      EWATCE_SCREEN_HEIGHT,
                                      EWATCE_SCREEN_BITDEPTH,
                                      EWATCE_SCREEN_PARAMS);
    if (!gScreenSurface) {
        LOGCRT("SDL_SetVideoMode failed, error=[%s]", SDL_GetError());
        return false;
    }

    // Initialize TTF Support
    if (TTF_Init() == -1) {
        LOGCRT("TTF_Init failed, error=[%s]", TTF_GetError());
        return false;
    }

    gDefaultFont = TTF_OpenFont(EWATCE_DEFAULT_FONT_FILE, EWATCE_DEFAULT_FONT_SIZE);
    if(!gDefaultFont) {
        LOGCRT("TTF_OpenFont failed, file=[%s] error=[%s]",
               EWATCE_DEFAULT_FONT_FILE,
               TTF_GetError());
        return false;
    }

    // Set Window Caption
    SDL_WM_SetCaption(EWATCE_WNDCAPTION, NULL);

    return true;
}

void ewatceShutdown()
{
    // Close default font
    if (gDefaultFont) {
        TTF_CloseFont(gDefaultFont);
        gDefaultFont = NULL;
    }

    // Shutdown TTF Support
    TTF_Quit();

    // Shutdown SDL
    SDL_Quit();

    // Close logging system...
    CloseLog();
}

SDL_Surface* ewatceGetScreenSurface()
{
    return gScreenSurface;
}

unsigned int ewatceRGB2Color(unsigned char red,
                             unsigned char green,
                             unsigned char blue)
{
    return SDL_MapRGB(ewatceGetScreenSurface()->format,
                      red,
                      green,
                      blue);
}

TTF_Font* ewatceGetDefaultFont()
{
    return gDefaultFont;
}
