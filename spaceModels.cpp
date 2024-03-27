//  ========================================================================
//  COSC363: Computer Graphics (2024);  James Suddaby
//
//  RspaceModels.cpp
//  A collection of functions for generating the models for an alien scene
//  ========================================================================

#include <cmath>
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include "spaceModels.h"
#include "loadTGA.h"
using namespace std;
GLuint txId[10];   //Texture ids

void loadTexture()				
{
	glGenTextures(3, txId); 	// Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]); 
    loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/pano10.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[1]);  //
    loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/ship_texture.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
    loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/glass_texture1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}

//A sky dome surface of revolution
void drawSurfaceofRevolution(const std::vector<Vertex>& vertices, int slices, int stacks)
{
	glBindTexture(GL_TEXTURE_2D, txId[0]);   //replace with a texture
	for(int i=0; i< stacks; ++i){
		glBegin(GL_QUAD_STRIP);
		for(int j=0; j <= slices; ++j){
			int index1 = i*(slices + 1) + j;
			int index2 = (i + 1) * (slices + 1) + j;

			glTexCoord2f(vertices[index1].s,  vertices[index1].t);
			glVertex3f(vertices[index1].x,vertices[index1].y,vertices[index1].z);

			glTexCoord2f(vertices[index2].s, vertices[index2].t);
			glVertex3f(vertices[index2].x,vertices[index2].y,vertices[index2].z);
		}
		glEnd();
	}
}


void drawFloor(float size)
{
	float white[4] = {1, 1, 1, 1};
	float black[4] = {0, 0, 0, 1};
	glColor4f(0.2, 0.2, 0.2, 1.0);  //The floor has a gray colour
	glNormal3f(0.0, 1.0, 0.0);		//Normal vector of the floor
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	//The floor is made up of several tiny squares on a 400 x 400 grid. Each square has a unit size.
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	float height = 0;
	for(int i = -size; i < size; i+=1)
	{
		for(int j = -size;  j < size; j+=1)
		{
			glVertex3f(i, height, j);
			glVertex3f(i, height, j+1);
			glVertex3f(i+1, height, j+1);
			glVertex3f(i+1, height, j);
		}
	}
	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR,white);

}


//--------------- Space Ship  --------------------------------------
// This is a base for the space ship 
// The spaceshipe is made from two gluCylinders, a gluSphere and a 
// glutSolidCone for a light that sticks out the bottom
//------------------------------------------------------------------

void spaceShip()
{	
	GLfloat mat_emission[] = {0.8, 0.8, 0.8, 1.0}; // Emissive material properties
	GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
	glScalef(10,10,10);
	
    glPushMatrix();
		glPushMatrix();
			glRotatef(90,-1,0,0);
			glScalef(0.9,1,0.9);
			glColor3f(1.0, 1.0, 1.0); // Set color to white
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, txId[1]); 
			GLUquadric *basepart = gluNewQuadric();
			gluQuadricTexture(basepart, GL_TRUE); // Enable texture coordinates
        	gluQuadricNormals(basepart, GLU_SMOOTH); 
			glBindTexture(GL_TEXTURE_2D, txId[1]);   //replace with a texture
			gluCylinder(basepart,2,0.7,0.2,30,30);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glRotatef(90,1,0,0);
			glScalef(0.9,1,0.9);
			glColor3f(1.0, 1.0, 1.0); // Set color to white
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, txId[1]); 
			GLUquadric *basepart2 = gluNewQuadric();
			gluQuadricTexture(basepart2, GL_TRUE); // Enable texture coordinates
        	gluQuadricNormals(basepart2, GLU_SMOOTH); 
			glBindTexture(GL_TEXTURE_2D, txId[1]);   //replace with a texture
			gluCylinder(basepart2,2,0.7,0.2,30,30);
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.62,0.93,0.93);
			glScalef(1,0.8,1);
			glTranslatef(0,0,0);
			glEnable(GL_TEXTURE_2D);
        	glBindTexture(GL_TEXTURE_2D, txId[2]);
			GLUquadric *ball = gluNewQuadric();
			gluQuadricTexture(ball, GL_TRUE); // Enable texture coordinates
        	gluQuadricNormals(ball, GLU_SMOOTH);
			gluSphere(ball,0.7,30,30);
		glPopMatrix();

		glPushMatrix();
			glColor3f(1,1,1);
			glEnable(GL_TEXTURE_2D);
        	glBindTexture(GL_TEXTURE_2D, txId[2]);
			glTranslatef(0.5,-0.5,0);
			glScalef(1,1,1);
			glRotatef(45,0,0,1);
			glPushMatrix();
				glRotatef(-90,1,0,0);
				glutSolidCone(0.2,0.5,20,20);
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glPushMatrix();
			glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
			glColor4f(1, 1, 1, 1);
			glDisable(GL_TEXTURE_2D);
			
			glTranslatef(0.501,-0.501,0);
			glScalef(1,1,1);
			glRotatef(45,0,0,1);
			glPushMatrix();
			glEnable(GL_LIGHTING);
				glRotatef(-90,1,0,0);
				glColor4f(1,1,1,1);
				glutSolidCylinder(0.19,0.01,30,30);
			glPopMatrix();
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glPopMatrix();
}
void drawAlien(bool shadow, float theta, bool fireBullet, float bulletHorz, float bulletVert)
{
	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
		glColor3f(0.5, 1.0, 0.2);}
	//Head
	glPushMatrix();
	  glTranslatef(0, 7.7, 0);
	  glutSolidSphere(1,20,20);
	  glPushMatrix();
	  	glTranslatef(0, 0.1, 0);
	  glPopMatrix();
	glPopMatrix();

	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
	glColor3f(0., 1., 0.);
	}		
	//Torso
	glPushMatrix();
	  glTranslatef(0, 5.5, 0);
	  glScalef(3.7, 2.5, 1.4);
	  glutSolidCube(1);
	glPopMatrix();

	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
	glColor3f(0., 1., 0.);
	}			
	//Legs
	glPushMatrix();
	  glTranslatef(0, 1, 0);
	  glRotatef(-90,1,0,0);
	  glScalef(2,2,2);
	  glutSolidCone(1,2,20,20);
	glPopMatrix();



	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
	glColor3f(0., 1., 0.);
	}		
	//Right arm
	glPushMatrix();
	  glTranslatef(-2.2, 6.5, 0);
	  glRotatef(theta,1,0,0);
	  glTranslatef(2.2,-6.5,0);
	  glTranslatef(-2.2,5,0);
	  glScalef(0.8, 4, 0.8);
	  glutSolidCube(1);
	glPopMatrix();
	
	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
	glColor3f(0., 0., 0.);
	}		
	//gun
	glPushMatrix();
		glTranslatef(-2.2, 6.5, 0);
		glRotatef(theta,1,0,0);
		glTranslatef(2.2,-6.5,0);
		glTranslatef(-2.2,2,0);
		glPushMatrix();
			glScalef(0.5, 1.5, 0.5);
			glutSolidCube(1);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0,1,-0.25);
			glScalef(0.5, 0.5, 1);
			glutSolidCube(1);
		glPopMatrix();
	glPopMatrix();

	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
		glColor3f(1., 0., 0.);
	}	
	//bullet
	if (fireBullet){
		glPushMatrix();
			glTranslatef(-2.2, 6.5, 0);
			glRotatef(theta,1,0,0);
			glTranslatef(2.2,-6.5,0);
			glTranslatef(-2.2,2,0);
			glPushMatrix();
				glTranslatef(0, -bulletHorz, bulletVert);
				glScalef(0.4,0.4,0.4);
				glutSolidSphere(0.5,10,10);
			glPopMatrix();
		glPopMatrix();
	}
	if (shadow){
		glColor3f(0.2,0.2,0.2);
	} else {
	glColor3f(0., 1., 0.);
	}		
	//Left arm
	glPushMatrix();
	  glTranslatef(2.2, 6.5, 0);
	  glRotatef(1.8*theta,1,0,0);
	  glTranslatef(-2.2,-6.5,0);
	  glTranslatef(2.2, 5, 0);
	  glScalef(0.8, 4, 0.8);
	  glutSolidCube(1);
	glPopMatrix();
}


void spiral(bool shadow)
{
	glPushMatrix();
		glDisable(GL_TEXTURE_2D);
		if (shadow)
		{
			glColor3f(0.2,0.2,0.2);
		} else 
		{
			glColor3f(1,1,0);
		}
		glBegin(GL_QUAD_STRIP);
		for(float t = 0; t<= 12.0; t+=0.1)
		{
			float y = t;
			float x = 2*cos(-3*t);
			float z = 2*sin(-3*t);
            glVertex3f(x, y, z);
            glVertex3f(x + 0.5, y + 0.5, z + 0.5);
		}
		glEnd();
	glPopMatrix();
}	

