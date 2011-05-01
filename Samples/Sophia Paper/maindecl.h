/*** maindecl.h ***/
#include "constants.h"
#include "funcdefs.h"
/* intersection routines */
double (*objint[])()={intsph,intbox,
                      inttri,intsup};
/* normal routines */
int (*objnrm[])()={nrmsph,nrmbox,
                   nrmtri,nrmsup};
/* global variables */
int nlight;               /* presently in use */
int lightlim=LIGHTS;      /* maximum declared */
t_light light[LIGHTS];     /* array of lights */
int nobject;              /* presently in use */
int objectlim=OBJECTS;    /* maximun declared */
t_object object[OBJECTS]; /* array of objects */
int nsurface;             /* presently in use */
int surfacelim=SURFACES;  /* maximum declared */
t_surface surface[SURFACES]; /* array surfaces */
int sizex,sizey;               /* image sizes */
t_3d eyep,lookp,up;        /* view definition */
double hfov,vfov;            /* field of view */
int level,maxlevel;      /* reflection levels */
char *outfilename[];       /* pixel file name */
t_color background;       /* background color */