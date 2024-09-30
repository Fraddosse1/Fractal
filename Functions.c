#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
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

    while(j<i && VectNorm(z)<2)
    {
        z = z*z + c;
        j++;
    }

    if (j==i)
        return 1;
    else
        return 0;
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
            if(Sequence(z, i))
            {
                SDL_SetRenderDrawColor(Render,255,255,255,255);
                SDL_RenderDrawPoint(Render, c, l);
            }

            else
            {
                SDL_SetRenderDrawColor(Render,0,0,0,0);
                SDL_RenderDrawPoint(Render, c, l);
            }
        }
    }
}