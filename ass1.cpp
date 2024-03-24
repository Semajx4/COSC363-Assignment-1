//  ========================================================================
//  COSC363: Computer Graphics (2024);  University of Canterbury.
//  James Suddaby
//  FILE NAME: ass1.cpp
//  ========================================================================

#include <math.h>
#include <GL/freeglut.h>
#include "spaceModels.h"
#include <vector>
#include <GL/gl.h>



//---------------------------------------------------------------------
float angle=0.0;

std::vector<Vertex> generateDomeVertices(int slices, int stacks, float radius){
	std::vector<Vertex> vertices;
	for(int i =0; i <= stacks; ++i){
		float stackAngle = M_PI/2 - (float)i / stacks * M_PI;
		float xy = radius * cosf(stackAngle);
		float z = radius * sinf(stackAngle);
		float t = (float)i/stacks;

		for(int j =0; j<= slices; ++j){
			float sliceAngle = 2*M_PI * j /slices;
			float x = xy*cosf(sliceAngle);
			float y = xy*sinf(sliceAngle);
			float s = (float)j/slices;

			vertices.push_back({x,y,z,s,t});
		}
	}
	return vertices;
}
void initialize(void) 
{
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    loadTexture();
    glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    
//	Define light's diffuse, specular properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);    //Default, only for LIGHT0
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);   //Default, only for LIGHT0
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);    

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT,0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT,GL_SHININESS, 50);
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor (0, 0, 0, 1);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90., 1.0, 10.0, 1000.0);
    
}
bool checkCollision(float x, float z) {
    // Define the bounding box of each wall (you can adjust these values according to your wall positions and dimensions)
    float wallMinX = -1000, wallMaxX = 1000;
    float wallMinZ = -1000, wallMaxZ = 1000;

    // Check if the new position intersects with any wall
    if (x >= wallMinX && x <= wallMaxX && z >= wallMinZ && z <= wallMaxZ) {
        return false; // Collision detected
    }
    return true; // No collision
}
float cam_angle = 0,look_x, look_z=-1, eye_x, eye_z = 20;  //Camera parameters
void special(int key, int x, int y) {
    float new_eye_x = eye_x, new_eye_z = eye_z;

    if (key == GLUT_KEY_LEFT) cam_angle -= 0.1;
    else if (key == GLUT_KEY_RIGHT) cam_angle += 0.1;
    else if (key == GLUT_KEY_DOWN) {
        new_eye_x -= 0.1 * sin(cam_angle);
        new_eye_z += 0.1 * cos(cam_angle);
    } else if (key == GLUT_KEY_UP) {
        new_eye_x += 0.1 * sin(cam_angle);
        new_eye_z -= 0.1 * cos(cam_angle);
    }

    // Check for collision with walls
    if (!checkCollision(new_eye_x, new_eye_z)) {
        eye_x = new_eye_x;
        eye_z = new_eye_z;
        
    }
	look_x = eye_x + 100*sin(cam_angle);
	look_z = eye_z - 100*cos(cam_angle);
	glutPostRedisplay();
}


//-------------------------------------------------------------------
void display(void)
{
    float light[] = {20.0f, 100.0f, 20.0f, 1.0f};  //Light's position (directly above the origin)
    float spotDir[] = {1,-1,0};
    float spotPosn[] = {-18,14,0,1};
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(90., 0.5, 1., 600.); // Adjust the field of view and clipping planes

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float cameraHeight = 15; // Adjust the camera height as needed
	gluLookAt(eye_x, cameraHeight, eye_z, look_x, cameraHeight, look_z, 0, 1, 0); // Adjust the eye position and look at position
    std::vector<Vertex> vertices = generateDomeVertices(30,30,500);

	glPushMatrix();
		//glTranslatef(eye_x, 0, eye_z);
        glEnable(GL_TEXTURE_2D);

        skyDome(vertices, 30, 30);

        glDisable(GL_TEXTURE_2D); // Disable texture mapping

	glPopMatrix();

    //gluLookAt (-80, 80, 250, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    //glPushMatrix();
        //glTranslatef(0,5,0);
        //walls();
    //glPopMatrix();

    //;glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
    glPushMatrix();
        glRotatef(angle,0,1,0);
        
        glPushMatrix();
            glTranslatef(0,23,0);
            glLightfv(GL_LIGHT0, GL_POSITION, light);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
            glLightfv(GL_LIGHT1, GL_POSITION, spotPosn);
            spaceShip();                //Toy train locomotive
        glPopMatrix();
        //glRotatef(10.5,0,1,0);
        /*glPushMatrix();
            glTranslatef(0,1,-120);
            //wagon();                //Toy wagon 
        glPopMatrix();
        glRotatef(10.5,0,1,0);
        glPushMatrix();
            glTranslatef(0,1,-120);
            //wagon();                //Toy wagon 
        glPopMatrix();
        glRotatef(10.5,0,1,0);
        glPushMatrix();
            glTranslatef(0,1,-120);
            //wagon();                //Toy wagon 
        glPopMatrix();*/
    glPopMatrix();
    
    //floor();                 //A tessellated floor plane
    glPushMatrix();
        glRotatef(-angle*3,0,1,0);
        glTranslatef(0,3,0);    
        spiral();
    glPopMatrix();
   //tracks(120, 10);         //Circular tracks with mean radius 120 units, width 10 units
   glutSwapBuffers();       //Double buffered animation
}

//---------------------------------------------------------------------
void spaceShipTimer(int val){
	static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds

    if (val < 600) {
        glutPostRedisplay();

        // Adjust angle and val based on deltaTime for smoother animation
        float angleIncrement = 10.0f * deltaTime; // Adjust speed as needed
        float valIncrement = 0.1f * deltaTime;   // Adjust speed as needed
        angle -= angleIncrement;
        val += valIncrement;

        // Wrap angle around when it reaches -360 degrees
        if (angle <= -360) {
            angle += 360;
        }

        lastTime = currentTime;
        glutTimerFunc(16, spaceShipTimer, val); // Aim for approximately 60 frames per second (1000 ms / 60)
    }
}
//---------------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800); 
    glutInitWindowPosition(5, 5);
    glutCreateWindow("Assignment 1");
    initialize();
    glutTimerFunc(16,spaceShipTimer,0);
    glutDisplayFunc(display); 
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}
