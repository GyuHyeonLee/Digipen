// RenderTest.cpp
// -- test of Render class
// cs200 5/17
//
// Visual Studio command prompt:
//   cl /EHsc RenderTest.cpp Render.cpp Affine.lib opengl32.lib glew32.lib
//      SDL2.lib SDL2main.lib /link /subsystem:console
// Linux command line:
//   g++ RenderTest.cpp Render.cpp Affine.cpp -lGL -lGLEW -lSDL2

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "Render.h"
#include "Affine.h"
using namespace std;


const float PI = 4.0f * atan(1.0f);
const Point O(0,0,0);
const Vector EX(1,0,0),
             EY(0,1,0),
             EZ(0,0,1);
const Vector GRAY(0.95f,0.95f,0.95f),
             BLACK(0,0,0);


class Client {
  public:
    Client(void);
    ~Client(void);
    void draw(double dt);
    void resize(int W, int H);
  private:
    float sq_rate,
          sq_scale;
    Vector sq_axis;
    Point sq_center;
    vector<Point> temp_vertices;
    Render *render;
    double time;
};


Client::Client(void) {
  sq_rate = 2*PI/7.0f;
  sq_scale = 1.2f;
  sq_axis = EZ;
  sq_center = O;
  time = 0;
  render = new Render();
}


Client::~Client(void) {
  delete render;
}


void Client::draw(double dt) {
  const Point sq_verts[4] = { Point(-0.5f,-0.5f,0), Point(0.5f,-0.5f,0),
                              Point(0.5f,0.5f,0), Point(-0.5f,0.5f,0) };
  const int sq_edges[8] = { 0,1, 1,2, 2,3, 3,0 };
  const int sq_faces[6] = { 0,1,2, 0,2,3 };

  render->ClearBuffers(GRAY);

  Affine sq_map = translate(sq_center-O)
                  * rotate(sq_rate*(float)time,sq_axis)
                  * scale(sq_scale);

  temp_vertices.clear();
  for (int i=0; i < 4; ++i)
    temp_vertices.push_back(sq_map * sq_verts[i]);

  render->SetColor(BLACK);
  for (int i=0; i < 4; ++i)
    render->DrawLine(temp_vertices[sq_edges[2*i+0]],
                     temp_vertices[sq_edges[2*i+1]]);

  render->SetColor(Vector(0,0.8f,1));
  for (int i=0; i < 2; ++i)
    render->FillTriangle(temp_vertices[sq_faces[3*i+0]],
                         temp_vertices[sq_faces[3*i+1]],
                         temp_vertices[sq_faces[3*i+2]]);

  time += dt;
}


void Client::resize(int W, int H) {
  int D = min(W,H);
  glViewport(0,0,D,D);
}


/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
	
	argc = 0;
	argv = 0;
  // SDL: initialize and create a window
  SDL_Init(SDL_INIT_VIDEO);
  const char *title = "CS250: Render Test";
  int width = 600,
      height = 600;
  SDL_Window *window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED,width,height,
                                        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
  SDL_GLContext context = SDL_GL_CreateContext(window);

  // GLEW: get function bindings (if possible)
  GLenum value = glewInit();
  if (value != GLEW_OK) {
    cout << glewGetErrorString(value) << endl;
    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return -1;
  }

  // animation loop
  try {
    Client *client = new Client();
    Uint32 ticks_last = SDL_GetTicks();
    bool done = false;
    while (!done) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch (event.type) {
          case SDL_QUIT:
            done = true;
            break;
          case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
              done = true;
            break;
          case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
              client->resize(event.window.data1,event.window.data2);
            break;
        }
      }
      Uint32 ticks = SDL_GetTicks();
      double dt = 0.001*(ticks - ticks_last);
      ticks_last = ticks;
      client->draw(dt);
      SDL_GL_SwapWindow(window);
    }

    delete client;
  }

  catch (exception &e) {
    cout << e.what() << endl;
  }

  SDL_GL_DeleteContext(context);
  SDL_Quit();
  return 0;
}

