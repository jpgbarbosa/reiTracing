#include "Object.h"
#include "Ray.h"

/* In the constructor, we set the centre of the object and its colour. */
Object::Object(double x, double y, double z, double rC, double gC, double bC)
{
    centre.x = x;
    centre.y = y;
    centre.z = z;

    c.r = rC;
    c.g = gC;
    c.b = bC;
}

Object::Object() { }


/* Returns the colour of this sphere. */
double Object::getR() {return c.r;}
double Object::getG() {return c.g;}
double Object::getB() {return c.b;}

double Object::getReflection() {return reflection;}
double Object::getShininess() { return shininess;}
colour Object::getSpecular() { return specular;}
colour Object::getDiffuse() { return diffuse;}
void Object::setReflection(double v) {reflection = v;}
void Object::setShininess(double v) {shininess = v;}
void Object::setSpecularR(double v) {specular.r = v;}
void Object::setSpecularG(double v) {specular.g = v;}
void Object::setSpecularB(double v) {specular.b = v;}
void Object::setDiffuseR(double v) {diffuse.r = v;}
void Object::setDiffuseG(double v) {diffuse.g = v;}
void Object::setDiffuseB(double v) {diffuse.b = v;}
