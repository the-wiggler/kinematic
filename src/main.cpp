////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //   - Copyright (c) 2025 Tyler Wiggins. All Rights Reserved. -                                                           //
  //   - This program is free to use for educational purposes. -                                                            //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "InitializePath.h"

int main(int argc, char *argv[]) {
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("KINEMATIC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE_X, WINDOW_SIZE_Y, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    TTF_Init();

    // load font
    TTF_Font* arial = TTF_OpenFont("assets/arial.ttf", 16);
    TTF_Font* arialSmall = TTF_OpenFont("assets/arial.ttf", 24);
    if (!arial) std::cout << "FAILED TO LOAD FONT" << TTF_GetError() << std::endl;

    // create text surfaces
    SDL_Surface* commandInfoSurface;
    SDL_Texture* commandInfoTexture;
    SDL_Surface* velocityInputSurface = nullptr;
    SDL_Texture* velocityInputTexture = nullptr;
    SDL_Surface* angleInputSurface = nullptr;
    SDL_Texture* angleInputTexture = nullptr;
    SDL_Surface* iheightInputSurface = nullptr;
    SDL_Texture* iheightInputTexture = nullptr;

    // creates a texture that that points can be rendered on
    SDL_Texture* pathTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    // colors
    SDL_Color white = {255, 255, 255};

    bool running = true;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // LOOP THAT KEEPS THE PROGRAM OPEN                                                                      //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    while (running) {
        SDL_StartTextInput();

        // displays the text that asks for input velocity
        velocityInputSurface = TTF_RenderText_Solid(arial, "Input Velocity: ", white);
        velocityInputTexture = SDL_CreateTextureFromSurface(renderer, velocityInputSurface);
        int textWidth, textHeight;
        SDL_QueryTexture(velocityInputTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect velocityTextRect = {10, 10, textWidth, textHeight};
        SDL_RenderCopy(renderer, velocityInputTexture, NULL, &velocityTextRect);
        SDL_RenderPresent(renderer);

        // displays the text that asks for input angle
        angleInputSurface = TTF_RenderText_Solid(arial, "Input Angle: ", white);
        angleInputTexture = SDL_CreateTextureFromSurface(renderer, angleInputSurface);
        SDL_QueryTexture(angleInputTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect angleTextRect = {10, 10, textWidth, textHeight};
        SDL_RenderCopy(renderer, angleInputTexture, NULL, &angleTextRect);
        SDL_RenderPresent(renderer);

        // displays the text that asks for input height
        iheightInputSurface = TTF_RenderText_Solid(arial, "Input Initial Height: ", white);
        iheightInputTexture = SDL_CreateTextureFromSurface(renderer, iheightInputSurface);
        SDL_QueryTexture(iheightInputTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect iheightTextRect = {10, 10, textWidth, textHeight};
        SDL_RenderCopy(renderer, iheightInputTexture, NULL, &iheightTextRect);
        SDL_RenderPresent(renderer);

        std::string velocity_input = "";
        std::string angle_input = "";
        std::string iheight_input = "";

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // USER INPUT                                                                                            //
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool velocity_input_pass = false;
        while (!velocity_input_pass) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    velocity_input_pass = true;
                }
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        velocity_input_pass = true;
                    } 
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        velocity_input.pop_back();
                    }
                }
                else if (event.type == SDL_TEXTINPUT) {
                        velocity_input += event.text.text;
                }
            }

            SDL_RenderClear(renderer);
            
            // Free old surface and texture
            if (velocityInputSurface) {
                SDL_FreeSurface(velocityInputSurface);
                velocityInputSurface = nullptr;
            }
            if (velocityInputTexture) {
                SDL_DestroyTexture(velocityInputTexture);
                velocityInputTexture = nullptr;
            }
            
            // Create new surface and texture with updated text
            velocityInputSurface = TTF_RenderText_Solid(arial, ("Input Velocity: " + velocity_input).c_str(), white);
            velocityInputTexture = SDL_CreateTextureFromSurface(renderer, velocityInputSurface);
            
            // Get dimensions and render
            SDL_QueryTexture(velocityInputTexture, NULL, NULL, &textWidth, &textHeight);
            velocityTextRect = {10, 10, textWidth, textHeight};
            SDL_RenderCopy(renderer, velocityInputTexture, NULL, &velocityTextRect);
            
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
        //////////////////////////////////
                bool angle_input_pass = false;
        while (!angle_input_pass) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    angle_input_pass = true;
                }
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        angle_input_pass = true;
                    } 
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        angle_input.pop_back();
                    }
                }
                else if (event.type == SDL_TEXTINPUT) {
                        angle_input += event.text.text;
                }
            }

            SDL_RenderClear(renderer);
            
            // Free old surface and texture
            if (angleInputSurface) {
                SDL_FreeSurface(angleInputSurface);
                angleInputSurface = nullptr;
            }
            if (angleInputTexture) {
                SDL_DestroyTexture(angleInputTexture);
                angleInputTexture = nullptr;
            }
            
            // Create new surface and texture with updated text
            angleInputSurface = TTF_RenderText_Solid(arial, ("Input Angle: " + angle_input).c_str(), white);
            angleInputTexture = SDL_CreateTextureFromSurface(renderer, angleInputSurface);
            
            // Get dimensions and render
            SDL_QueryTexture(angleInputTexture, NULL, NULL, &textWidth, &textHeight);
            angleTextRect = {10, 10, textWidth, textHeight};
            SDL_RenderCopy(renderer, angleInputTexture, NULL, &angleTextRect);
            
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
        //////////////////////////////////
                bool iheight_input_pass = false;
        while (!iheight_input_pass) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                    iheight_input_pass = true;
                }
                else if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        iheight_input_pass = true;
                    } 
                    else if (event.key.keysym.sym == SDLK_BACKSPACE) {
                        iheight_input.pop_back();
                    }
                }
                else if (event.type == SDL_TEXTINPUT) {
                        iheight_input += event.text.text;
                }
            }

            SDL_RenderClear(renderer);
            
            // Free old surface and texture
            if (iheightInputSurface) {
                SDL_FreeSurface(iheightInputSurface);
                iheightInputSurface = nullptr;
            }
            if (iheightInputTexture) {
                SDL_DestroyTexture(iheightInputTexture);
                iheightInputTexture = nullptr;
            }
            
            // Create new surface and texture with updated text
            iheightInputSurface = TTF_RenderText_Solid(arial, ("Input Initial Height: " + iheight_input).c_str(), white);
            iheightInputTexture = SDL_CreateTextureFromSurface(renderer, iheightInputSurface);
            
            // Get dimensions and render
            SDL_QueryTexture(iheightInputTexture, NULL, NULL, &textWidth, &textHeight);
            iheightTextRect = {10, 10, textWidth, textHeight};
            SDL_RenderCopy(renderer, iheightInputTexture, NULL, &iheightTextRect);
            
            SDL_RenderPresent(renderer);
            SDL_Delay(16);
        }
        //////////////////////////////////


        // create text box for commands
        commandInfoSurface = TTF_RenderText_Solid(arial, "Commands: <r> - reset", white);
        commandInfoTexture = SDL_CreateTextureFromSurface(renderer, commandInfoSurface);
        SDL_QueryTexture(commandInfoTexture, NULL, NULL, &textWidth, &textHeight);
        SDL_Rect commandTextRect = {10, WINDOW_SIZE_Y - 20, textWidth, textHeight};

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // RUNS THE PATH CALCULATIONS --> Important                                                              //
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        InitializePath pathInit;

        // converts the input strings into usable double variables for calculation
        pathInit.initial_velocity = std::stod(velocity_input);
        pathInit.initial_angle = std::stod(angle_input);
        pathInit.initial_height = std::stod(iheight_input);

        pathInit.boundsInitialize();
        pathInit.projectileArrayInitialize();
        pathInit.projectileArrayScale();

        SDL_SetRenderTarget(renderer, pathTexture);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        // MAPS THE POINTS FOR THE PROJECTILES ON THE SCREEN                                                     //
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < PATH_RESOLUTION; i++) {
            SDL_RenderClear(renderer);

            // renders the rectangles to pathTexture
            SDL_SetRenderTarget(renderer, pathTexture);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect pointRect = {static_cast<int>(pathInit.path_array_x[i]), static_cast<int>(-pathInit.path_array_y[i] + WINDOW_SIZE_Y / 2), 1, 1}; // you need the negative in front of path array since there's a stupid coordinate system
            SDL_RenderFillRect(renderer, &pointRect);

            // resets the renderer to display to the window
            SDL_SetRenderTarget(renderer, NULL);

            // displays pathTexture
            SDL_RenderCopy(renderer, pathTexture, NULL, NULL);

            // displays commandInfoTexture
            SDL_RenderCopy(renderer, commandInfoTexture, NULL, &commandTextRect);

            // displays a leading rectangle that acts as the "projectile"
            if (i < PATH_RESOLUTION - 1) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_Rect leadingPointRect = {static_cast<int>(pathInit.path_array_x[i]), static_cast<int>(-pathInit.path_array_y[i] + WINDOW_SIZE_Y / 2), 3, 3};
                SDL_RenderFillRect(renderer, &leadingPointRect);
            }

            SDL_RenderPresent(renderer);
            SDL_Delay(1);
        }

        SDL_RenderClear(renderer);
        SDL_SetRenderTarget(renderer, pathTexture);

        // the impact point (assumes the final element of path_array is the ending - it should be because of the element that was added in projectileScaleArray)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect end_rect = {static_cast<int>(pathInit.path_array_x[PATH_RESOLUTION]), static_cast<int>(pathInit.path_array_y[PATH_RESOLUTION] + WINDOW_SIZE_Y / 2), 3, 3};
        SDL_RenderFillRect(renderer, &end_rect);
        
        // the max height reached
        int max_index = 0;
        for (int i = 1; i < PATH_RESOLUTION; i++) { if (pathInit.path_array_y[i] > pathInit.path_array_y[max_index]) { max_index = i; } }
        double max_x = pathInit.path_array_x[max_index];
        double max_y = pathInit.path_array_y[max_index];
        SDL_SetRenderDrawColor(renderer, 255, 204, 0, 255);
        SDL_Rect max_rect = {static_cast<int>(max_x), static_cast<int>(-max_y + WINDOW_SIZE_Y / 2), 3, -3};
        SDL_RenderFillRect(renderer, &max_rect);

        // resets the renderer to display to the window
        SDL_SetRenderTarget(renderer, NULL);

        // displays pathTexture
        SDL_RenderCopy(renderer, pathTexture, NULL, NULL);

        // displays commandInfoTexture
        SDL_RenderCopy(renderer, commandInfoTexture, NULL, &commandTextRect);
       
        SDL_RenderPresent(renderer);

        // stops the rendering loop until a certain command is executed
        bool wait_for_reset = true;
        while (wait_for_reset) {
            while (SDL_PollEvent(&event)) {
                // quits the program
                if (event.type == SDL_QUIT) {
                    running = false;
                    wait_for_reset = false;
                // re-renders the projectile when the letter "r" is pressed
                } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r) {
                    wait_for_reset = false;
                }
            }
            SDL_Delay(16);
        }
    SDL_FreeSurface(commandInfoSurface);
    SDL_DestroyTexture(commandInfoTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(pathTexture);
    TTF_CloseFont(arial);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
