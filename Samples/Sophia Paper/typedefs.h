/*** typedefs.h ***/
typedef struct
{
  double x,y,z;
} t_3d;
typedef struct
{
  double r;      /* radius */
  double x,y,z; /* position */
} o_sphere;

typedef struct
{
  double sidehit;/* side intersected */
  double xs,ys,zs; /* size of sides */
  double x,y,z;  /* center position */
} o_box;

typedef struct
{
  t_3d nrm;     /* triangle normal */
  double d;      /* plane constant */
  t_3d e1,e2,e3;    /* edge vectors */
  double d1,d2,d3;/*plane constants */
} o_triangle;

typedef struct
{
  int sidehit; /* side intersected */
  double xs,ys,zs; /* size of sides */
  double x,y,z; /* center position */
  double pow;      /* n in formula */
  double a,b,c,r;  /* coefficients */
  double err;     /* error measure */
} o_superq;

typedef struct
{
  int id;       /* object number */
  int objtyp;     /* object type */
  int surfnum; /* surface number */
  union
  {  
    o_sphere   *p_sphere;
    o_box      *p_box;
    o_triangle *p_triangle;
    o_superq   *p_superq;
  } objpnt;    /* object pointer */
} t_object;

typedef struct
{
  double x,y,z;  /* position */
  double bright;
} t_light;

typedef struct
{
  double ar,ag,ab; /* ambient r,g,b */
  double dr,dg,db; /* diffuse r,g,b */
  double sr,sg,sb;/* specular r,g,b */
  double coef;     /* specular coef */
  double refl;    /* reflection 0-1 */
  double transp;/* transparency 0-1 */
} t_surface;

typedef struct
{
  double r,g,b; /* red,green,blue */
} t_color;