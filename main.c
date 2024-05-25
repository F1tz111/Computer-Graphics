#include<stdio.h>
#include<SDL.h>
#include<stdint.h>
#include<stdbool.h>

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


void process_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch (event.type) {
        case SDL_QUIT:
            is_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
                is_running = false;
            break;
        }
    }

}

void update() {}

void draw_grid() {
    for (int y = 0; y < window_height; y+=10) {
        for (int x = 0; x < window_width; x+=10) {
            
            color_buffer[(window_width) * y + x] = 0xFF333333;     
            
        }
        
    }


  
}


void render_color_buffer() {

    SDL_UpdateTexture(color_buffer_texture,NULL,color_buffer,(int)(window_width * sizeof(uint32_t))); 

    SDL_RenderCopy(renderer,color_buffer_texture,NULL,NULL);
}


void setting_colorbuffer(uint32_t color) {
    for (int y = 0; y < window_height; y++) {
        for (int x = 0; x < window_width; x++) {
            color_buffer[(window_width * y) + x] = color;
            
        }
    }
}

void myrenderer(void) {
    SDL_SetRenderDrawColor(renderer, 1, 225, 0, 255);
    SDL_RenderClear(renderer);
    draw_grid();
    render_color_buffer();
    setting_colorbuffer(0xFF0000000);
    SDL_RenderPresent(renderer);
}


void setup() {
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);


    color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,window_width,window_height); 

}


void destroy() {
    free(color_buffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

int main(int argc ,char* args[]) {
    is_running = init_Window();
  
    setup();
   
    
        while (is_running) {
            process_input();
            update();
            myrenderer();
        }
    
   
    destroy();
       
        return 0;
    
 
}