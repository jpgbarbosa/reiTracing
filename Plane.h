#ifndef _H_Plane#define _H_Plane/* Needed libraries. */#include <cmath>/* Defines the needed classes and their headers. */class Ray;#include "BasicStructures.h"#include "Object.h"/* Header for the Sphere class. */class Plane : public Object{private:	/* - - - - - - - - - - - - ATTRIBUTES - - - - - - - - - -*/        vector normal;public:	/* - - - - - - - CONSTRUCTOR & DESTRUCTOR - - - - - - - -*/	/* Constructor & destructor. */	explicit Plane(double x, double y, double z, vector n, double rC, double gC, double bC);	explicit Plane();	~Plane();	/* - - - - - - - OTHER METHODS - - - - - - - -*/	/* Determinates whether the ray intersects this sphere or not. */	bool intersects(Ray &ray, double &rT0, double &rT1);        void newDirection(Ray &ray, double &t);        void refractionRedirection(Ray &ray, double t);        void intersectionPointNormal(Ray &ray, vector &normalInt);	/* - - - - - - - GETTERS & SETTERS - - - - - - - -*/        vector getNormal();};#endif