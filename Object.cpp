#include "Object.h"
#include "Ray.h"

//Constructor
Object::Object() { }
//Destructor
Object::~Object() {}

/* Returns the colour of this Object. */
double Object::getR() {return c.r;}
double Object::getG() {return c.g;}
double Object::getB() {return c.b;}

double Object::getReflection() {return reflection;}
double Object::getPower() { return power;}
colour Object::getSpecular() { return specular;}
colour Object::getDiffuse() { return diffuse;}
void Object::setReflection(double v) {reflection = v;}
void Object::setPower(double v) {power = v;}
void Object::setSpecularR(double v) {specular.r = v;}
void Object::setSpecularG(double v) {specular.g = v;}
void Object::setSpecularB(double v) {specular.b = v;}
void Object::setDiffuseR(double v) {diffuse.r = v;}
void Object::setDiffuseG(double v) {diffuse.g = v;}
void Object::setDiffuseB(double v) {diffuse.b = v;}

