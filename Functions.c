#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "Functions.h"

double complex PixelConvert(int H, int W, int Px, int Py, float Xmax, float Xmin, float Ymax, float Ymin)
{
    double complex z = (Px*((Xmax-Xmin)/W) + Xmin) + (Py*((Ymax-Ymin)/H) + Ymin)*I;
    return z;
}

float VectNorm(double complex z)
{
    return csqrt(creal(z)*creal(z) + cimag(z)*cimag(z));
}

int Sequence(double complex c, int i)
{
    double complex z = 0;
    int j = 0;

    while(j<i && VectNorm(z)<=2)
    {
        z = z*z + c;
        j++;
    }

    if (j==i)
        return 0;
    else
        return j;
}

void DrawPixelColor(SDL_Renderer* Render, int i, int c, int l)
{
    float KR = (2*M_PI)/150;
    float KG = (2*M_PI)/80;
    float KB = (2*M_PI)/60;

    Uint8 R = (Uint8)((255 / 2) * (1 + sin(KR*i + 0)));
    Uint8 G = (Uint8)((255 / 2) * (1 + sin(KG*i + M_PI/2)));
    Uint8 B = (Uint8)((255 / 2) * (1 + sin(KB*i + M_PI)));
    Uint8 A = 255;

    SDL_SetRenderDrawColor(Render, R, G, B, A);

    SDL_RenderDrawPoint(Render, c, l);
}


void RenderFractal(SDL_Renderer* Render, int i, int H, int W, float Xmax, float Xmin, float Ymax, float Ymin)
{
    int l, c;
    double complex z;

    for(l=0; l<H; l++)
    {
        for(c=0; c<W; c++)
        {
            z = PixelConvert(H, W, c, l, Xmax, Xmin, Ymax, Ymin);
            DrawPixelColor(Render, Sequence(z, i), c, l);
        }
    }
}