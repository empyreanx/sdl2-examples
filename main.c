#include <SDL.h>
#include <SDL_image.h>

#include <stdbool.h>
#include <stdint.h>

void print_sdl_error()
{
    printf("Error: %s\n", SDL_GetError());
}

void print_img_error()
{
    printf("Error: %s\n", IMG_GetError());
}

static struct
{
    bool sdl;
    bool img;
    SDL_Window* win;
    SDL_Renderer* renderer;
    SDL_Texture* tex;
} state;

static bool startup()
{
    memset(&state, 0, sizeof(state));

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        print_sdl_error();
        return false;
    }

    state.sdl = true;

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        print_img_error();
        return false;
    }

    state.img = true;

    return true;
}

static void shutdown()
{
    if (state.renderer)
        SDL_DestroyRenderer(state.renderer);

    if (state.win)
        SDL_DestroyWindow(state.win);

    if (state.img)
        IMG_Quit();

    if (state.sdl)
        SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (!startup())
    {
        shutdown();
        return -1;
    }

    state.win = SDL_CreateWindow("Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);

    if (state.win == NULL)
    {
        print_sdl_error();
        shutdown();
        return -1;
    }


    state.renderer = SDL_CreateRenderer(state.win, -1, SDL_RENDERER_ACCELERATED |
                                                       SDL_RENDERER_PRESENTVSYNC);

    if (state.renderer == NULL)
    {
        print_sdl_error();
        shutdown();
        return -1;
    }

    state.tex = IMG_LoadTexture(state.renderer, "tex.png");

    if (state.tex == NULL)
    {
        print_img_error();
        shutdown();
        return -1;
    }

    bool done = false;

    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            done = true;
                            break;
                    }
                    break;
            }
        }

        SDL_RenderClear(state.renderer);
        SDL_RenderCopy(state.renderer, state.tex, NULL, NULL);
        SDL_RenderPresent(state.renderer);
    }

    shutdown();

    return 0;
}
