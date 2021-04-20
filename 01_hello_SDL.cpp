#include <SDL.h>
#include <glm/glm/glm.hpp>
#include "testbun/circle.h"

#include <iostream>

//define window dimensions
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

SDL_Window *window = nullptr;
SDL_Renderer *windowRenderer;
SDL_Event currentEvent;

bool quit = false;
bool animationQuit = false;
int mouseX, mouseY;

glm::vec4 backgroundColor;
glm::vec2 point1, point2;

Circle circleEmpty;
Circle circle;

Circle circleGravity;

SDL_Rect ground;

bool right = true;

float elapsedTime,speed = 50.0f;

const float MASS = 50.0f;
const float acceleration = 10.0f;
bool isOnGround = false;

bool initWindow() {

    bool success = true;

    // Try to initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {

        std::cout << "SDL initialization failed" << std::endl;
        success = false;
    } else {

        // Try to create the window
        window = SDL_CreateWindow("Fereastra de test",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  WINDOW_WIDTH,
                                  WINDOW_HEIGHT,
                                  SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);

        if(window == nullptr) {

            std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
            success = false;
        } else {

            // Create a renderer for the current window
            windowRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

            if(windowRenderer == nullptr) {

                std::cout << "Failed to create the renderer: " << SDL_GetError() << std::endl;
                success = false;
            }
        }
    }

    return success;
}

void destroyWindow() {

    // Destroy window
    SDL_DestroyWindow(window);
    window = nullptr;

    // Quit SDL
    SDL_Quit();
}

void initScene() {

    backgroundColor = glm::vec4(255.0f, 255.0f, 255.0f, 255.0f);
    //initializam cercul
    //circleEmpty.center.x = 100.0f;
    //circleEmpty.center.y = 100.0f;
    //circleEmpty.radius = 25.0f;
    //circleEmpty.color = glm::vec4(100.0f,100.0f,100.0f,255.0f);

    circle.center.x = 200.0f;
    circle.center.y = 200.0f;
    circle.radius = 25.0f;
    circle.color = glm::vec4(100.0f,100.0f,100.0f,255.0f);

    //init the circle for gravity test
    circleGravity.center.x = 350.0f;
    circleGravity.center.y = 350.0f;
    circleGravity.radius = 45.0f;
    circle.color = glm::vec4(50.0f,25.0f,18.0f,255.0f);

    //init the ground
    ground.x = 150;
    ground.y = 700;
    ground.w = 800;
    ground.h = 150;
}

void processEvent(SDL_Event event) {

    // User requests quit
    if(event.type == SDL_QUIT) {

        quit = true;
    }

    // Mouse event -> pressed button
    if(event.type == SDL_MOUSEBUTTONDOWN) {

        if(event.button.button == SDL_BUTTON_LEFT) {

            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "Left mouse button pressed at (" << mouseX << ", " << mouseY << ")" << std::endl;
            //stergem linia anterioara
            //point1.x = point1.y = point2.x = point2.y = 0.0f;
            //setam coordonatele la mouseX mouseY
            point1.x = point2.x =  static_cast<float> (mouseX);
            point1.y = point2.y = static_cast<float> (mouseY);
        }

        if(event.button.button == SDL_BUTTON_RIGHT) {

            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "Right mouse button pressed at (" << mouseX << ", " << mouseY << ")" << std::endl;
        }
    }

    if(event.type == SDL_MOUSEBUTTONUP){
        std::cout<<" mouse button up";
    }

    // Mouse event -> mouse movement
    if(event.type == SDL_MOUSEMOTION) {

        if(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_LMASK) {

            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "Left mouse drag at (" << mouseX << ", " << mouseY << ")" << std::endl;
            point2.x = mouseX;
            point2.y = mouseY;
        }

        if(SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_RMASK) {

            SDL_GetMouseState(&mouseX, &mouseY);
            std::cout << "Right mouse drag at (" << mouseX << ", " << mouseY << ")" << std::endl;
        }
    }

    // Keyboard event
    if(event.type == SDL_KEYDOWN) {

        switch(event.key.keysym.sym) {

            case SDLK_ESCAPE:
                quit = true;
                break;
            case SDLK_r:
                std::cout << "R key pressed" << std::endl;
                animationQuit = !animationQuit;//oprim animatia sau o pornim
                std::cout << "animation is fking " << animationQuit << "\n";
                break;

            default:
                break;
        }
    }
}

void animate(){
    if(right){//daca mergem la dreapta
        if (circle.center.x <= 400.0f)//daca nu am ajuns
            circle.center.x += (50.0f * elapsedTime);
        else//daca am ajuns
            right = false;
    }
    else {//daca mergem la stanga
        if(circle.center.x >= 100.0f)//daca nu am ajuns la punctul din stanga
            circle.center.x -= (50.0f * elapsedTime);
        else //daca am ajuns
            right = true;
    }

    //for(int i = 0; i < 100000000; i++);
}

void animate2(){
    circle.center = circle.center + glm::normalize(point2 - circle.center) * speed * elapsedTime;
}

void gravity(){
    //luam distanta intre cerc si ground .
    glm::vec2 groundPosition(ground.x, ground.y);
    float distance = glm::distance(circle.center, groundPosition );


    if (!isOnGround && circle.center.y <= ground.y){//daca nu e pe pamant , il aducem pe pamant
        float greutate = (MASS * acceleration) / distance;
        circle.center.y += greutate;// impartim cu distanta
        std::cout << "distance : " << distance << " viteza de cadere" << greutate << std::endl;
    }
    else isOnGround = true;
}

void drawFrame() {
    Uint32 start = SDL_GetTicks();
    // clear background
    SDL_SetRenderDrawColor(windowRenderer,
                           static_cast<Uint8>(backgroundColor.r),
                           static_cast<Uint8>(backgroundColor.g),
                           static_cast<Uint8>(backgroundColor.b),
                           static_cast<Uint8>(backgroundColor.a));
    SDL_RenderClear(windowRenderer);

    // draw the scene
    //TODO
    //SDL_SetRenderDrawColor(windowRenderer,0,0,0,255);
    //SDL_RenderDrawLine(windowRenderer,point1.x,point1.y,point2.x,point2.y);
    //SDL_DrawCircle(windowRenderer, circleEmpty);
    SDL_FillCircle(windowRenderer, circle);
    SDL_FillCircle(windowRenderer, circleGravity);

    SDL_SetRenderDrawColor(windowRenderer, 100, 30, 80, 255);
    SDL_RenderFillRect(windowRenderer, &ground);

    if(animationQuit)
        animate2();

    gravity();
    // render to window
    SDL_RenderPresent(windowRenderer);
    Uint32 end = SDL_GetTicks();
    elapsedTime = (end-start)/1000.0f;//convertim in milisecunde
}

int main(int argc, char* args[]) {

    // unused parameters
    (void)argc;
    (void)args;

    if(!initWindow()) {

        std::cout << "Failed to initialize SDL" << std::endl;
        SDL_Quit();
        return -1;
    }

    initScene();

    // game loop
    while (!quit) {

        // Handle events in queue (non-blocking)
        if(SDL_PollEvent(&currentEvent) != 0) {

            // process any event that has occurred
            processEvent(currentEvent);
        }

        // render the frame
        drawFrame();
    }

    destroyWindow();
    return 0;
}
