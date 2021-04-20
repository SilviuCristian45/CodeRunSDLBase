#include "circle.h"

void plotPoints(SDL_Renderer *renderer, int x, int y, Circle circle) {
    SDL_SetRenderDrawColor(renderer,
                           static_cast<Uint8>(circle.color.r),
                           static_cast<Uint8>(circle.color.g),
                           static_cast<Uint8>(circle.color.b),
                           static_cast<Uint8>(circle.color.a));
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) + x,
                        static_cast<int>(circle.center.y) + y);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) + x,
                        static_cast<int>(circle.center.y) - y);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) - x,
                        static_cast<int>(circle.center.y) - y);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) - x,
                        static_cast<int>(circle.center.y) + y);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) + y,
                        static_cast<int>(circle.center.y) + x);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) + y,
                        static_cast<int>(circle.center.y) - x);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) - y,
                        static_cast<int>(circle.center.y) - x);
    SDL_RenderDrawPoint(renderer,
                        static_cast<int>(circle.center.x) - y,
                        static_cast<int>(circle.center.y) + x);
}

void plotLines(SDL_Renderer *renderer, int x, int y, Circle circle) {
    SDL_SetRenderDrawColor(renderer,
                           static_cast<Uint8>(circle.color.r),
                           static_cast<Uint8>(circle.color.g),
                           static_cast<Uint8>(circle.color.b),
                           static_cast<Uint8>(circle.color.a));
    SDL_RenderDrawLine(renderer,
                       static_cast<int>(circle.center.x) - x,
                       static_cast<int>(circle.center.y) + y,
                       static_cast<int>(circle.center.x) + x,
                       static_cast<int>(circle.center.y) + y);
    SDL_RenderDrawLine(renderer,
                       static_cast<int>(circle.center.x) - x,
                       static_cast<int>(circle.center.y) - y,
                       static_cast<int>(circle.center.x) + x,
                       static_cast<int>(circle.center.y) - y);
    SDL_RenderDrawLine(renderer,
                       static_cast<int>(circle.center.x) - y,
                       static_cast<int>(circle.center.y) + x,
                       static_cast<int>(circle.center.x) + y,
                       static_cast<int>(circle.center.y) + x);
    SDL_RenderDrawLine(renderer,
                       static_cast<int>(circle.center.x) - y,
                       static_cast<int>(circle.center.y) - x,
                       static_cast<int>(circle.center.x) + y,
                       static_cast<int>(circle.center.y) - x);
}

void SDL_DrawCircle(SDL_Renderer *renderer, Circle circle) {
    int currentY = static_cast<int>(circle.radius);
    int d = static_cast<int>((1.0f / 4.0f) - circle.radius);

    for (int currentX = 0; currentX <= ceil(circle.radius / sqrt(2.0f)); currentX++) {

        plotPoints(renderer, currentX, currentY, circle);
        d += 2 * currentX + 1;

        if ( d > 0) {
            d += 2 - 2 * currentY;
            currentY--;
        }
    }
}

void SDL_FillCircle(SDL_Renderer *renderer, Circle circle) {
    int currentY = static_cast<int>(circle.radius);
    int d = static_cast<int>((1.0f / 4.0f) - circle.radius);

    for (int currentX = 0; currentX <= ceil(circle.radius / sqrt(2.0f)); currentX++) {

        plotLines(renderer, currentX, currentY, circle);
        d += 2 * currentX + 1;

        if ( d > 0) {
            d += 2 - 2 * currentY;
            currentY--;
        }
    }
}
