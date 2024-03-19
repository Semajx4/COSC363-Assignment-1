//  ========================================================================
//  COSC363: Computer Graphics (2024); CSSE  University of Canterbury.
//
//  FILE NAME: Yard.cpp
//  See Lab03.pdf for details.
//  ========================================================================
 
#include <iostream>
#include <cmath> 
#include <GL/freeglut.h>
#include "loadTGA.h"
using namespace std;

GLuint txId[8];   //Texture ids

float angle=0, look_x, look_z=-1., eye_x, eye_z;  //Camera parameters
//--------------------------------------------------------------------------------
void loadTexture()				
{
	glGenTextures(8, txId); 	// Create 2 texture ids

	glBindTexture(GL_TEXTURE_2D, txId[0]);  //Use this texture
    loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Tex1.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[1]);  //Use this texture
    loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Floor.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[2]);  //Use this texture
	loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Back.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[3]);  //Use this texture
	loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Front.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[4]);  //Use this texture
	loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Down.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[5]);  //Use this texture
	loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Up.tga");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	
	glBindTexture(GL_TEXTURE_2D, txId[6]);  //Use this texture
	loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Left.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, txId[7]);  //Use this texture
	loadTGA("/home/james/Documents/Assignment-1/363-assignment-1/Right.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);


}

//--------------------------------------------------------------------------------
bool checkCollision(float x, float z) {
    // Define the bounding box of each wall (you can adjust these values according to your wall positions and dimensions)
    float wallMinX = -13.5, wallMaxX = 13.5;
    float wallMinZ = -13.5, wallMaxZ = 13.5;

    // Check if the new position intersects with any wall
    if (x >= wallMinX && x <= wallMaxX && z >= wallMinZ && z <= wallMaxZ) {
        return false; // Collision detected
    }
    return true; // No collision
}
//--------------------------------------------------------------------------------------
void special(int key, int x, int y) {
    float new_eye_x = eye_x, new_eye_z = eye_z;

    if (key == GLUT_KEY_LEFT) angle -= 0.1;
    else if (key == GLUT_KEY_RIGHT) angle += 0.1;
    else if (key == GLUT_KEY_DOWN) {
        new_eye_x -= 0.1 * sin(angle);
        new_eye_z += 0.1 * cos(angle);
    } else if (key == GLUT_KEY_UP) {
        new_eye_x += 0.1 * sin(angle);
        new_eye_z -= 0.1 * cos(angle);
    }

    // Check for collision with walls
    if (!checkCollision(new_eye_x, new_eye_z)) {
        eye_x = new_eye_x;
        eye_z = new_eye_z;
        
    }
	look_x = eye_x + 100*sin(angle);
	look_z = eye_z - 100*cos(angle);
	glutPostRedisplay();
}

//--------------------------------------------------------------------------------

void initialise()
{ 
	loadTexture();	
	glEnable(GL_TEXTURE_2D);
	glClearColor(0., 1., 1., 1.);    //Background colour 	
	glEnable(GL_DEPTH_TEST);
}

//--------------------------------------------------------------------------------
void skybox(float D)
{
	glBindTexture(GL_TEXTURE_2D, txId[2]);   //replace with a texture
	glBegin(GL_QUADS);
	////////////////////// BACK WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(D, 2*D, D);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(D, 0, D);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(-D, 0, D);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(-D, 2*D, D);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[3]);   //replace with a texture
	glBegin(GL_QUADS);
	////////////////////// FRONT WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-D, 2*D, -D);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-D, 0, -D);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(D, 0, -D);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(D, 2*D, -D);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[4]);   //replace with a texture
	glBegin(GL_QUADS);
	////////////////////// DOWN WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-D, 0, -D);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-D, 0, D);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(D, 0, D);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(D, 0, -D);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, txId[5]);   //replace with a texture
	glBegin(GL_QUADS);
	////////////////////// UP WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-D, 2*D, D);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-D, 2*D, -D);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(D, 2*D, -D);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(D, 2*D, D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, txId[6]);   //replace with a texture
	glBegin(GL_QUADS);
	////////////////////// LEFT WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-D, 2*D, D);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-D, 0, D);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(-D, 0, -D);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(-D, 2*D, -D);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, txId[7]);   //replace with a texture
	glBegin(GL_QUADS);
	////////////////////// RIGHT WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(D, 2*D, -D);
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(D, 0, -D);
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(D, 0, D);
		glTexCoord2f(1.0f,1.0f);
		glVertex3f(D, 2*D, D);
	glEnd();
}

void walls()
{
	glBindTexture(GL_TEXTURE_2D, txId[0]);   //replace with a texture
	glRotatef(180,0,1,0);
	glBegin(GL_QUADS);

	////////////////////// BACK WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-15, 10, -15);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-15, -10, -15);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(15, -10, -15);

		glTexCoord2f(1.0f,1.0f);
		glVertex3f(15, 10, -15);

		////////////////////// FRONT WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-15, 10, 15);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-15, -10, 15);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(15, -10, 15);

		glTexCoord2f(1.0f,1.0f);
		glVertex3f(15, 10, 15);

		////////////////////// LEFT WALL ///////////////////////
		glTexCoord2f(0.0f,1.0f);
		glVertex3f(-15, 10, -15);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-15, -10, -15);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(-15, -10, 15);

		glTexCoord2f(1.0f,1.0f);
		glVertex3f(-15, 10, 15);

		////////////////////// RIGHT WALL ///////////////////////

		glTexCoord2f(0.0f,1.0f);
		glVertex3f(15, 10, -15);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(15, -10, -15);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(15, -10, 15);

		glTexCoord2f(1.0f,1.0f);
		glVertex3f(15, 10, 15);

	glEnd();
}
//--------------------------------------------------------------------------------

void floor()
{
	glBindTexture(GL_TEXTURE_2D, txId[1]);   //replace with a texture

	glBegin(GL_QUADS);
		glTexCoord2f(0.0f,16.0f);
		glVertex3f(-15, 10, -15);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-15, 10, 15);

		glTexCoord2f(16.0f,0.0f);
		glVertex3f(15, 10, 15);

		glTexCoord2f(16.0f,16.0f);
		glVertex3f(15, 10, -15);
	glEnd();
}

//--------------------------------------------------------------------------------

void display() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90., 0.5, 1., 90.); // Adjust the field of view and clipping planes

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float cameraHeight = 11.0; // Adjust the camera height as needed
	gluLookAt(eye_x, cameraHeight, eye_z, look_x, cameraHeight, look_z, 0, 1, 0); // Adjust the eye position and look at position

	glPushMatrix();
		glTranslatef(eye_x, 0, eye_z);
		skybox(50); // Adjust the skybox size
	glPopMatrix();
	glGetError();
	//floor();
	
	glutSwapBuffers();									
}

//--------------------------------------------------------------------------------

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
   glutInitWindowSize (1024, 512); 
   glutInitWindowPosition (10, 10);
   glutCreateWindow ("assignment");
   initialise();

   glutDisplayFunc(display); 
   glutSpecialFunc(special);
   glutMainLoop();
   return 0;
}
