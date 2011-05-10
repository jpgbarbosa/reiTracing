/* 
 * File:   Object.h
 * Author: Ivo
 *
 * Created on 6 de Maio de 2011, 16:27
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include "BasicStructures.h"

class Object
{
protected:
        /* The centre of the object. */
	point centre;
	/* The colour of this object. */
	colour c;
	/* Coeficients used for the Lambert and Blinn-Phong Effects. */
	double reflection, shininess;
	colour diffuse, specular;

public:
        /* - - - - - - - CONSTRUCTOR & DESTRUCTOR - - - - - - - -*/
        explicit Object(double x, double y, double z, double rC, double gC, double bC);
        explicit Object();
        
	/* - - - - - - - OTHER METHODS - - - - - - - -*/

	/* - - - - - - - GETTERS & SETTERS - - - - - - - -*/
        double getR();
	double getG();
	double getB();

	double getReflection();
	double getShininess();
	colour getSpecular();
	colour getDiffuse();

	void setReflection(double v);
	void setShininess(double v);
	void setSpecularR(double v);
	void setSpecularG(double v);
	void setSpecularB(double v);
	void setDiffuseR(double v);
	void setDiffuseG(double v);
	void setDiffuseB(double v);
};

#endif	/* OBJECT_H */

