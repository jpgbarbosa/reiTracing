/***  main.c ***/
#include <stdio.h>
#include "typedefs.h"
#include "maindecl.h"
int main()
{
  int line_y, pixel_x;
  t_3d scrnx,scrny,firstray,ray;
  t_color color;
  double dis,line[SCREENWIDTH][3];
  setup();
  viewing(&scrnx,&scrny,&firstray);
  startpic(outfilename,sizey,sizex);
  for(line_y=0;line_y<sizey;line_y++)
  {
    for(pixel_x=0;pixel_x<sizex;pixel_x++)
    {    
      ray.x = firstray.x + pixel_x*scrnx.x
              - line_y*scrny.x;
      ray.y = firstray.y + pixel_x*scrnx.y
              - line_y*scrny.y;
      ray.z = firstray.z + pixel_x*scrnx.z
              - line_y*scrny.z;
      normalize(&ray);
      /* actual ray trace */
      dis = intersect(-1,&eyep,&ray,&color);
      if( dis > 0 )
      {      /* ray intersected object */
        line[pixel_x][0] = color.r;
        line[pixel_x][1] = color.g;
        line[pixel_x][2] = color.b;
	  }      
      else
      {      /* use background color */
        line[pixel_x][0] = background.r;
        line[pixel_x][1] = background.g;
        line[pixel_x][2] = background.b;
      }

    }    
    /* Output line of pixels */
    linepic(line);
    if (line_y % 10 == 0)
    {    
      printf( "\nDone line %d", line_y );
      fflush( stdout );
    }    
  }  
  endpic();
}