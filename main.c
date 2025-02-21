#include "raytracing.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

int main(){

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("RayTracing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    Circle circle = {200, 200, 50};
    Ray rays[RAY_COUNT];

    draw_circle(&circle);
    init_rays(rays, circle);
    calculate_rays(rays, circle);

    bool Running = true;
    SDL_Event event;
    while (Running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT) Running = false;
        }
        
        
        render_all(rays, circle);
        SDL_Delay(30);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}



void render_all(Ray rays[RAY_COUNT], Circle circle){
    SDL_SetRenderDrawColor(renderer, COLOUR_BLACK);
    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(renderer, COLOUR_WHITE);
    draw_circle(&circle);

    SDL_SetRenderDrawColor(renderer, COLOUR_RAY);
    calculate_rays(rays, circle);
    draw_rays(rays, circle);

    SDL_RenderPresent(renderer);
}


void draw_circle(Circle *circle){
    
    SDL_SetRenderDrawColor(renderer, COLOUR_WHITE);

    int lowerX = circle->x - circle->radius;
    int lowerY = circle->y - circle->radius;
    int upperX = circle->x + circle->radius;
    int upperY = circle->y + circle->radius;
    int radiusSquared = circle->radius * circle->radius;

    for (int x = lowerX; x < upperX; x++){
        for (int y = lowerY; y < upperY; y++){
            int distanceSquared = ((x - circle->x) * (x - circle->x)) + ((y - circle->y) * (y - circle->y));
            if (distanceSquared < radiusSquared){
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}


void calculate_rays(Ray rays[RAY_COUNT], Circle object){
    int radiusSquared = object.radius * object.radius;
    
    for (int i = 0; i < RAY_COUNT; i++){
        
        bool boundaryCollision = false;
        bool objectCollision = false;

        double step = 1;
        double x = rays[i].x;
        double y = rays[i].y;
        double bearingRadians = rays[i].bearing * (M_PI / 180.0);

        while (!boundaryCollision && !objectCollision){
            x += step * cos(bearingRadians);
            y += step * sin(bearingRadians);
            
            if (x < 0 || x > WINDOW_WIDTH) boundaryCollision = true;
            if (y < 0 || y > WINDOW_HEIGHT) boundaryCollision = true; 

            double distanceSquared = (pow(x-object.x, 2)) + (pow(y-object.y, 2));
            if (distanceSquared < radiusSquared) break;
        }

        rays[i].x = x;
        rays[i].y = y;
    }
}

void init_rays(Ray rays[RAY_COUNT], Circle object){
    for (int i = 0; i < RAY_COUNT; i++){
        rays[i].x = object.x;
        rays[i].y = object.y;
        rays[i].bearing = ((double)360 / (double)RAY_COUNT) * (double)i;
    }
}

void draw_rays(Ray rays[RAY_COUNT], Circle object){
    SDL_SetRenderDrawColor(renderer, COLOUR_RAY);
    for (int i = 0; i < RAY_COUNT; i++){
        SDL_RenderDrawLine(renderer, object.x, object.y, rays[i].x, rays[i].y);
    }
}
