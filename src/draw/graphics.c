/*
MIT License

Copyright (c) 2022 Fellipe Augusto Ugliara

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "draw/graphics.h"
#include "engine/engine.h"

void point_draw(point_t point, SDL_Color color) {
  filledCircleRGBA(engine->render, point.x, point.y, 3, color.r, color.g,
                   color.b, color.a);
  SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00, SDL_ALPHA_TRANSPARENT);
}

void circle_draw(circle_t circle, SDL_Color color) {
  circleRGBA(engine->render, circle.c.x, circle.c.y, circle.r, color.r, color.g,
             color.b, color.a);
  SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00, SDL_ALPHA_TRANSPARENT);
}

void rect_draw(rect_t rect, SDL_Color color) {
  rectangleRGBA(engine->render, rect.ptl.x, rect.ptl.y, rect.ptl.x + rect.s.x,
                rect.ptl.y + rect.s.y, color.r, color.g, color.b, color.a);
  SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00, SDL_ALPHA_TRANSPARENT);
}

void line_draw(line_t line, SDL_Color color) {
  lineRGBA(engine->render, line.p1.x, line.p1.y, line.p2.x, line.p2.y, color.r,
           color.g, color.b, color.a);
  SDL_SetRenderDrawColor(engine->render, 0x00, 0x00, 0x00, SDL_ALPHA_TRANSPARENT);
}
