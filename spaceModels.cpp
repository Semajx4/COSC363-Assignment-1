//  ========================================================================
//  COSC363: Computer Graphics (2024);  University of Canterbury.
//
//  RailModels.cpp
//  A collection of functions for generating the models for a railway scene
//  ========================================================================

#include <cmath>
#include <GL/freeglut.h>
#include "spaceModels.h"

//--------------- GROUND PLANE ----------------------------------------
// This is a square shaped region on the xz-plane of size 400x400 units
// centered at the origin.  This region is constructed using small quads
// of unit size, to facilitate rendering of spotlights
//---------------------------------------------------------------------
void floor()
{
	float white[4] = {1, 1, 1, 1};
	float black[4] = {0, 0, 0, 1};
	glColor4f(0.7, 0.7, 0.7, 1.0);  //The floor has a gray colour
	glNormal3f(0.0, 1.0, 0.0);		//Normal vector of the floor
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	//The floor is made up of several tiny squares on a 400 x 400 grid. Each square has a unit size.
	glBegin(GL_QUADS);
	for(int i = -200; i < 200; i++)
	{
		for(int j = -200;  j < 200; j++)
		{
			glVertex3f(i, 0, j);
			glVertex3f(i, 0, j+1);
			glVertex3f(i+1, 0, j+1);
			glVertex3f(i+1, 0, j);
		}
	}
	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR,white);

}


//--------------- MODEL BASE --------------------------------------
// This is a common base for the locomotive and wagons
// The base is of rectangular shape (20 length x 10 width x 2 height)
// and has wheels and connectors attached.
//-----------------------------------------------------------------
void spaceShip()
{
    //glColor4f(0.2, 0.2, 0.2, 1.0);   //Base color
	glTranslatef(0,30,0);
	glScalef(20,20,20);
	
    glPushMatrix();
		//glTranslatef(0.0, 4.0, 0.0);
		//glScalef(20.0, 10.0, 10.0);     //Size 20x10 units, thickness 2 units.
		glPushMatrix();
			glColor3f(0.64,0.65,0.64);
			glRotatef(90,-1,0,0);
			glScalef(0.9,1,0.9);
			GLUquadric *basepart;
			basepart = gluNewQuadric();
			gluCylinder(basepart,2,0.7,0.2,30,30);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.64,0.65,0.64);
			glRotatef(90,1,0,0);
			glScalef(0.9,1,0.9);
			//glTranslatef(0,-1,0);
			GLUquadric *basepart2;
			basepart2 = gluNewQuadric();
			gluCylinder(basepart2,2,0.7,0.2,30,30);
		glPopMatrix();
		glPushMatrix();
			glColor3f(0.62,0.93,0.93);
			glScalef(1,0.8,1);
			glTranslatef(0,0,0);
			GLUquadric *ball;
			ball = gluNewQuadric();
			gluSphere(ball,0.7,30,30);
		glPopMatrix();
		//qluQuadricDrawStyle(q, GLU_FILL);
		glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(0.5,-0.5,0);
			glScalef(1,1,1);
			glRotatef(45,0,0,1);
			glPushMatrix();
				glRotatef(-90,1,0,0);
				glutSolidCone(0.2,0.5,20,20);
			glPopMatrix();

		glPopMatrix();

	glPopMatrix();


 
}

