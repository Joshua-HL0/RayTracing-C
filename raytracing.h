#ifndef RAY_TRACING_H
#define RAY_TRACING_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400

#define COLOUR_WHITE 0xff, 0xff, 0xff, 0xff
#define COLOUR_BLACK 0x00, 0x00, 0x00, 0x00
#define COLOUR_YELLOW 0xff, 0xff, 0x00, 0xff

#define COLOUR_RAY COLOUR_YELLOW
#define RAY_COUNT 250
#define RAY_WIDTH 2

typedef struct {
    int x;
    int y;
    int radius;
} Circle;

typedef struct {
    double x;
    double y;
    double bearing;
} Ray;


SDL_Renderer *renderer;

void draw_circle(Circle *circle);
void draw_rays(Ray rays[RAY_COUNT], Circle object);
void calculate_rays(Ray rays[RAY_COUNT], Circle object);
void render_all(Ray rays[RAY_COUNT], Circle circle);
void init_rays(Ray rays[RAY_COUNT], Circle object);

#endif
