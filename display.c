#include  "Display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool is_running = false;
uint32_t* color_buffer = NULL;
SDL_Texture* color_buffer_texture = NULL;
int window_width = 800;
int window_height = 600;

bool init_Window(void) {


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        return false;
    }

    SDL_DisplayMode my_display;
    SDL_GetCurrentDisplayMode(0, &my_display);

    window_width = my_display.w;
    window_height = my_display.h;


    window = SDL_CreateWindow("My Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);

    if (!window) {
        fprintf(stderr, "Error Creating Window");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error renderering");
        return false;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    return true;
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
    for (int h = x; h < height; h++) {
        for (int w = y; w < width; w++) {
            color_buffer[(window_width * h) + w] = color;

        }
    }
}


void setting_colorbuffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;

        }
    }
}



void render_color_buffer() {

    SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer, (int)(window_width * sizeof(uint32_t)));

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}





void destroy() {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}