#ifndef SDL2_CIRCLE_CIRCLE_H
#define SDL2_CIRCLE_CIRCLE_H

#include <SDL.h>
#include <glm/glm/glm.hpp>

struct Circle {
    float radius;
    glm::vec2 center;
    glm::vec4 color;

    Circle() {
        radius = 0.0f;
        center = glm::vec2(0.0f, 0.0f);
        color = glm::vec4(0.0f, 0.0f, 0.0f, 255.0f);
    }

    Circle(float r, glm::vec2 c, glm::vec4 col) {
        radius = r;
        center = c;
        color = col;
    }
};

void plotPoints(SDL_Renderer *renderer, int x, int y, Circle circle);
void plotLines(SDL_Renderer *renderer, int x, int y, Circle circle);
void SDL_DrawCircle(SDL_Renderer *renderer, Circle circle);
void SDL_FillCircle(SDL_Renderer *renderer, Circle circle);

#endif //SDL2_CIRCLE_CIRCLE_H
