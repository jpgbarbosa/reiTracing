#ifndef _H_Object#define _H_Object/* Defines the needed classes and their headers. */class Ray;#include "BasicStructures.h"/* Header for the Sphere class. */class Object{protected:	/* - - - - - - - - - - - - ATTRIBUTES - - - - - - - - - -*/        /* The the centre and the colour of the object. */	point centre;	colour c;	/* Coeficients used for the Lambert and Blinn-Phong Effects. */	double reflection, refraction, shininess;	colour diffuse, specular;        int intersectionType;public:	/* - - - - - - - CONSTRUCTOR & DESTRUCTOR - - - - - - - -*/	/* Constructor & destructor. */	explicit Object();	~Object();	/* - - - - - - - OTHER METHODS - - - - - - - -*/        /* Method to find the intersection point of a ray with this object. */        virtual bool intersects(Ray &ray, double &rT0, double &rT1) = 0;        /* Given an intersection point, calculates the new direction of the ray. */        virtual void newDirection(Ray &ray, double &t) = 0;        /* Given an intersection point, calculates the new starting point of the         * ray after the refraction.         */        virtual bool refractionRedirection(Ray &ray, double t0, double t1) = 0;        /* Calculates the normal vector at the intersection point. */        virtual void intersectionPointNormal(Ray &ray, vector &normalInt) = 0;	/* - - - - - - - GETTERS & SETTERS - - - - - - - -*/        point getCentre();        int getIntersectionType();                double getR();	double getG();	double getB();	double getReflection();        double getRefraction();	double getShininess();	colour getSpecular();	colour getDiffuse();	void setReflection(double v);        void setRefraction(double v);	void setShininess(double v);	void setSpecular(double rC, double gC, double bC);	void setDiffuse(double rC, double gC, double bC);        };#endif