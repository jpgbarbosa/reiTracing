#ifndef _BASIC_STRUCTURES_H#define _BASIC_STRUCTURES_H/* The defines used all over the program.*//* This value must be used due to precision errors. */#define EPSLON 0.00000001/* The depth of the ray tracing algorithm and finally the configuration of the * screen. */#define SCREEN_W 1600#define SCREEN_H 1200#define MAX_DEPTH 10/* The different types of visualization. */#define LOOKING_AHEAD 1#define LOOKING_DOWN 2#define LOOKING_UP 3#define LOOKING_BACK 4#define LOOKING_RIGHT 5#define LOOKING_LEFT 6/* Declarations of some functions. */void buildScene(int no);void renderImage();/* The struct that defines a given point. */struct point{    double x, y, z;	    point& operator += (const point &p2)    {        this->x += p2.x;        this->y += p2.y;        this->z += p2.z;        return *this;    }};/* The struct that defines a given vector. */struct vector{    double x, y, z;    vector& operator += (const vector &v2)    {	this->x += v2.x;        this->y += v2.y;        this->z += v2.z;        return *this;    }	    vector& operator /= (double c)    {        this->x /= c;        this->y /= c;        this->z /= c;        return *this;    }};/* Redefinition of operations over points. */inline point operator * (double t, const point &p){    point p2 = {p.x * t, p.y * t, p.z * t};    return p2;}inline double operator * (const point &p, const point &p2){    double t = p.x * p2.x + p.y * p2.y + p.z * p2.z;    return t;}inline vector operator - (const point &p1, const point &p2){    vector v = {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };    return v;}/* Redefinition of operations involving points and vectors. */inline point operator + (const point &p, const vector &v){    point p2 = {p.x + v.x, p.y + v.y, p.z + v.z };    return p2;}inline point operator - (const point &p, const vector &v){    point p2 = {p.x - v.x, p.y - v.y, p.z - v.z };    return p2;}/* Redefinition of operations over vectors. */inline vector operator + (const vector &v1, const vector &v2){    vector v = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };    return v;}inline vector operator * (double c, const vector &v){    vector v2 = {v.x *c, v.y * c, v.z * c };    return v2;}inline vector operator / (double c, const vector &v){    vector v2 = {v.x / c, v.y / c, v.z / c };    return v2;}inline vector operator - (const vector &v1, const vector &v2){    vector v = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };    return v;}inline double operator * (const vector &v1, const vector &v2 ){    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;}/* The struct that the defines a given colour. */struct colour{    double r, g, b;    inline colour & operator += (const colour &c2 )    {        this->r +=  c2.r;        this->g += c2.g;        this->b += c2.b;        return *this;    }    inline colour & operator = (double t )    {        this->r =  t;        this->g = t;        this->b = t;        return *this;    }};/* Redefinition of operations over colours. */inline colour operator * (const colour &c1, const colour &c2 ){    colour c = {c1.r * c2.r, c1.g * c2.g, c1.b * c2.b};    return c;}inline colour operator + (const colour &c1, const colour &c2 ){    colour c = {c1.r + c2.r, c1.g + c2.g, c1.b + c2.b};    return c;}inline colour operator * (double coef, const colour &c ){    colour c2 = {c.r * coef, c.g * coef, c.b * coef};    return c2;}inline colour operator / (const colour &c, double coef){    colour c2 = {c.r / coef, c.g / coef, c.b / coef};    return c2;}#endif