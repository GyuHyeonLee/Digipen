// Headerphile.com OpenGL Tutorial part 1
// A Hello World in the world of OpenGL ( creating a simple windonw and setting
// background color ) Source code is an C++ adaption / simplicication of :
// https://www.opengl.org/wiki/Tutorial1:_Creating_a_Cross_Platform_OpenGL_3.2_Context_in_SDL_(C_/_SDL)
// Compile : clang++ main.cpp -lGL -lSDL2 -std=c++11 -o Test

// C++ Headers
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>

std::string programName = "SDL2 Glew OpenGL";

// Our SDL_Window ( just like with SDL2 wihout OpenGL)
SDL_Window* mainWindow;

// Our opengl context handle
SDL_GLContext mainContext;

bool SetOpenGLAttributes();
void PrintSDL_GL_Attributes();
void CheckSDLError(int line);
bool RunGameAndContinue();
void Cleanup();


bool Init()
{
    // Initialize SDL's Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\n";
        return false;
    }

    // Create our window centered at 512x512 resolution
    mainWindow =
        SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED, 512, 512, SDL_WINDOW_OPENGL);

    // Check that everything worked out okay
    if (!mainWindow)
    {
        std::cout << "Unable to create window\n";
        CheckSDLError(__LINE__);
        return false;
    }

    // Create our opengl context and attach it to our window
    mainContext = SDL_GL_CreateContext(mainWindow);

    SetOpenGLAttributes();

    // This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    PrintSDL_GL_Attributes();

    return true;
}

bool SetOpenGLAttributes()
{
    // Set our OpenGL version.
    // SDL_GL_CONTEXT_CORE gives us only the newer version, deprecated functions are
    // disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Most video cards should be able to run 3.3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Turn on double buffering with a 24bit Z buffer.
    // You may need to change this to 16 or 32 for your system
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return true;
}

#ifdef __EMSCRIPTEN__
#include <emscripten.h>

void main_loop(void*)
{
    if (!RunGameAndContinue())
        emscripten_cancel_main_loop();
}
#endif

int main(int /*argc*/, char* /*argv*/ [])
{
    if (!Init())
        return -1;

    // Clear our buffer with a black background
    // This is the same as :
    //      SDL_SetRenderDrawColor(&renderer, 255, 0, 0, 255);
    //      SDL_RenderClear(&renderer);
    //
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(mainWindow);
#ifndef __EMSCRIPTEN__
    auto loop = true;
    while(loop)
        loop = RunGameAndContinue();
#else
    int simulate_infinite_loop = 1;
    int match_browser_framerate = -1;
    emscripten_set_main_loop_arg(&main_loop, nullptr, match_browser_framerate, simulate_infinite_loop);
#endif

    Cleanup();

    return 0;
}

bool RunGameAndContinue()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return false;

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return false;
                    break;
                case SDLK_r:
                    // Cover with red and update
                    glClearColor(1.0, 0.0, 0.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(mainWindow);
                    break;
                case SDLK_g:
                    // Cover with green and update
                    glClearColor(0.0, 1.0, 0.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(mainWindow);
                    break;
                case SDLK_b:
                    // Cover with blue and update
                    glClearColor(0.0, 0.0, 1.0, 1.0);
                    glClear(GL_COLOR_BUFFER_BIT);
                    SDL_GL_SwapWindow(mainWindow);
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}

void Cleanup()
{
    // Delete our OpengL context
    SDL_GL_DeleteContext(mainContext);

    // Destroy our window
    SDL_DestroyWindow(mainWindow);

    // Shutdown SDL 2
    SDL_Quit();
}

void CheckSDLError(int line = -1)
{
    std::string error = SDL_GetError();

    if (error != "")
    {
        std::cout << "SLD Error : " << error << std::endl;

        if (line != -1)
            std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

void PrintSDL_GL_Attributes()
{
    int value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}
