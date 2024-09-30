#ifndef FUNCTIONS
#define FUNCTIONS

#include <complex.h>

double complex PixelConvert(int H, int W, int Px, int Py, float Xmax, float Xmin, float Ymax, float Ymin);
float VectNorm(double complex z);
int Sequence(double complex c, int i);
void DrawPixelColor(SDL_Renderer* Render, int i, int c, int l);
void RenderFractal(SDL_Renderer* Render, int i, int H, int W, float Xmax, float Xmin, float Ymax, float Ymin);

#endif