#include "Display.h"

SDL_Window* window;
SDL_Renderer* renderer;
bool is_running;
uint32_t* color_buffer;
SDL_Texture* color_buffer_texture;
int window_width;
int window_height;

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


void myrenderer(void) {
    SDL_SetRenderDrawColor(renderer, 1, 225, 0, 255);
    SDL_RenderClear(renderer);
    draw_rect(25, 25, 100, 65, 0xFFA23211);
    render_color_buffer();
    setting_colorbuffer(0xFFFFFFF00);
    SDL_RenderPresent(renderer);
}


void setup() {
    color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);


    color_buffer_texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,window_width,window_height); 

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