#ifndef DISPLAY_H
#define DISPLAY_H

#include<stdio.h>
#include<SDL.h>
#include<stdint.h>
#include<stdbool.h>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern bool is_running;
extern uint32_t* color_buffer;
extern SDL_Texture* color_buffer_texture;
extern int window_width;
extern int window_height;

bool init_Window();
void render_color_buffer();
void setting_colorbuffer(uint32_t color);
void draw_rect(int x, int y, int width, int height, uint32_t color);
void destroy();

#endif 

