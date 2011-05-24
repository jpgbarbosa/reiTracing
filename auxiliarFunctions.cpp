#include <cmath>
#include "BasicStructures.h"

using namespace std;

extern int screenWidth, screenHeight;

/* Antialiasing function. */
void antiAliasing(float *pixels, int aliasingTimes)
{
     int i, j, k;

    /* Antialiasing techniques:
     * Given all the calculated colours from the ray tracing process, we
     * pick up all the values around it and calculate its mean. That mean
     * will be the final colour of the pixel.
     */
    for (k = 0; k < aliasingTimes; k++)
    {
        for( i = 1; i < screenHeight - 1; i++)
        {
            for (j = 1; j < screenWidth - 1; j++)
            {
                /* RED. */
                double value;
                value = pixels[(i-1)*(screenWidth*3) + (j-1)*3]
                            + pixels[(i-1)*(screenWidth*3) + j*3]
                              + pixels[(i-1)*(screenWidth*3) + (j+1)*3]
                                + pixels[i*(screenWidth*3) + (j-1)*3]
                                  + pixels[i*(screenWidth*3) + j*3]
                                    + pixels[i*(screenWidth*3) + (j+1)*3]
                                      + pixels[(i+1)*(screenWidth*3) + (j-1)*3]
                                        + pixels[(i+1)*(screenWidth*3) + j*3]
                                          + pixels[(i+1)*(screenWidth*3) + (j+1)*3];

                if (abs(pixels[i*(screenWidth*3) + j*3] - value / 9) > ANTIALIASING_LIMIT)
                    pixels[i*(screenWidth*3) + j*3] = value / 9;

                /* GREEN. */
                value = pixels[(i-1)*(screenWidth*3) + (j-1)*3 + 1]
                            + pixels[(i-1)*(screenWidth*3) + j*3 + 1]
                              + pixels[(i-1)*(screenWidth*3) + (j+1)*3 + 1]
                                + pixels[i*(screenWidth*3) + (j-1)*3 + 1]
                                  + pixels[i*(screenWidth*3) + j*3 + 1]
                                    + pixels[i*(screenWidth*3) + (j+1)*3 + 1]
                                      + pixels[(i+1)*(screenWidth*3) + (j-1)*3 + 1]
                                        + pixels[(i+1)*(screenWidth*3) + j*3 + 1]
                                          + pixels[(i+1)*(screenWidth*3) + (j+1)*3 + 1];

                if (abs(pixels[i*(screenWidth*3) + j*3 + 1] - value / 9) > ANTIALIASING_LIMIT)
                    pixels[i*(screenWidth*3) + j*3 + 1] = value / 9;

                /* BLUE. */
                value = pixels[(i-1)*(screenWidth*3) + (j-1)*3 + 2]
                            + pixels[(i-1)*(screenWidth*3) + j*3 + 2]
                              + pixels[(i-1)*(screenWidth*3) + (j+1)*3 + 2]
                                + pixels[i*(screenWidth*3) + (j-1)*3 + 2]
                                  + pixels[i*(screenWidth*3) + j*3 + 2]
                                    + pixels[i*(screenWidth*3) + (j+1)*3 + 2]
                                      + pixels[(i+1)*(screenWidth*3) + (j-1)*3 + 2]
                                        + pixels[(i+1)*(screenWidth*3) + j*3 + 2]
                                          + pixels[(i+1)*(screenWidth*3) + (j+1)*3 + 2];

                if (abs(pixels[i*(screenWidth*3) + j*3 + 2] - value / 9) > ANTIALIASING_LIMIT)
                    pixels[i*(screenWidth*3) + j*3 + 2] = value / 9;
            }
        }
    }
}
