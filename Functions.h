#ifndef FUNCTIONS
#define FUNCTIONS

#include <complex.h>

#define H 1080       // Height of the screen resolution
#define W 1920       // Width of the screen resolution
#define iMax 600     // Maximum iterations
#define Xmax 1.0       // Maximum coordinate on the X-axis ( !FLOAT VALUE! )
#define Xmin -2.0      // Minimum coordinate on the X-axis ( !FLOAT VALUE! )
#define Ymax 1.0       // Maximum coordinate on the Y-axis ( !FLOAT VALUE! )
#define Ymin -1.0      // Minimum coordinate on the Y-axis ( !FLOAT VALUE! )

/*
    Init_SDL :
    => Initializes SDL2 

    -- Return type : VOID
*/
void InitSDL(SDL_Window** Window, SDL_Renderer** Render);

/*
    PixelConvert :
    => Converts each pixel in the screen to a complex plane coordinate Z using the following formula :
        >> Z_real = Xpixel *( (Xmax - Xmin)/W ) + Xmin
        >> Z_imag = YpiYel *( (YmaY - Ymin)/H ) + Ymin

        >>> Result : Z = ( Xpixel *( (Xmax - Xmin)/W ) + Xmin ) + ( YpiYel *( (YmaY - Ymin)/H ) + Ymin )*I
    
    -- Return type : DOUBLE COMPLEX
*/
double complex PixelConvert(int Px, int Py);

/*
    VectNorm :
    => Calculates the norm N of a 2 spacial plane vector ( a complex plane in this case ) using the following formula :
        >>>  N = csqrt(creal(z)*creal(z) + cimag(z)*cimag(z));

    -- Return type : FLOAT
*/
float VectNorm(double complex z);

/*
    Sequence :
    => Calculatres the "Zn+1 = Zn + C" sequence iMax times with C as a parameter and Z a complex plane coordinate.
        - If at any point through the calculations VecNorm(Z)>2, then Z is considered as unrelated to the Mandelbrot set
        - The function returns the maximum of iterations before reaching VecNorm(Z)>2

    -- Return type : INT
*/
int Sequence(double complex c);

/*
    DrawPixelColor :
    => Draws each pixel of the screen according to a "random" generated RGBA color using the number of iterations as a parameter

    -- Return type : VOID
*/
void DrawPixelColor(SDL_Renderer* Render, int i, int c, int l);

/*
    RenderFractal :
    => Uses DrawPixelColor to draw each pixel of the screen accordingly to its number of iterations

    -- Return type : VOID
*/
void RenderFractal(SDL_Renderer* Render);

#endif