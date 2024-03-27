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
#include <stdio.h>
#include <list>
#include <climits>
using namespace std;




//---------------------------------------------------------------------
float angle =0.0;
float theta = 20.0;
int gunTimerCounter = 0;
int gunWait = 0;
float gunAngleIncrement = 2;
float alienX, alienZ, modelAngle, liftOffHeight =0;
bool fireBullet, liftOff = false;
float bulletHorz, bulletVert = 0;
int tick = 0;


struct particle
{
	int t;
	float col;
	float size;
	float pos[3];
	float vel[3];
};
list<particle> particleList;



std::vector<Vertex> generateDomeVertices(int slices, int stacks, float radius){
	std::vector<Vertex> vertices;
	for(int i =0; i <= stacks; ++i){
		float stackAngle = M_PI_2 - (float)i / stacks * M_PI_2;
		float xz = radius * cosf(stackAngle);
		float y = radius * sinf(stackAngle);
		float t = (float)i/stacks;

		for(int j =0; j<= slices; ++j){
			float sliceAngle = 2*M_PI * j /slices;
			float x = xz*cosf(sliceAngle);
			float z = xz*sinf(sliceAngle);
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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
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
void handleLiftOff(unsigned char key, int x, int y){
    switch (key){
        case 32:
            liftOff = true;
            break;
        case 13:
            liftOffHeight = 0;
            liftOff = false;
            break;
    }
}
float cam_angle = 1,look_x=1, look_z=-1, eye_x=-40, eye_z = 40;  //Camera parameters
void special(int key, int x, int y) {
    float new_eye_x = eye_x, new_eye_z = eye_z;
    float radian_conversion = M_PI / 180.0; // Radians per degree
    float turn_angle = 5.0 * radian_conversion; // 5 degrees in radians

    if (key == GLUT_KEY_LEFT) cam_angle -= turn_angle;
    else if (key == GLUT_KEY_RIGHT) cam_angle += turn_angle;
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

void displayAlienModel(float shadowMat[16]){
    glPushMatrix();
        glPushMatrix();
            glPushMatrix();
                glEnable(GL_LIGHTING);
                glTranslatef(10,0,10);
                drawAlien(false, -theta, fireBullet, bulletHorz, bulletVert);
                glDisable(GL_LIGHTING);
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(10,0.2,10);
            glMultMatrixf(shadowMat);
            glDisable(GL_LIGHTING);
            glColor3f(0.1, 0.1, 0.1);
            drawAlien(true, -theta,  fireBullet, bulletHorz, bulletVert); // Draw the shadow
        glPopMatrix();
    glPopMatrix();
}

//-------------------------------------------------------------------
void display(void)
{
    float light[] = {20.0f, 100.0f, 20.0f, 1.0f};  //Light's position (directly above the origin)
    float spotDir[] = {1,-1,0};
    float spotPosn[] = {10,20,10,1};
    float shadowMat[16] = {spotPosn[1],0,0,0, -spotPosn[0],0,-spotPosn[2],-1,0,0,spotPosn[1],0,0,0,0,spotPosn[1]};

    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluPerspective(60., 0.5, 0.1, 200.); // Adjust the field of view and clipping planes
    
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float cameraHeight = 15; // Adjust the camera height as needed
	gluLookAt(eye_x, cameraHeight, eye_z, look_x, cameraHeight, look_z, 0, 1, 0); // Adjust the eye position and look at position
    std::vector<Vertex> skyDomeVertices = generateDomeVertices(30,30,150);
	glPushMatrix();
        glEnable(GL_TEXTURE_2D);
        drawSurfaceofRevolution(skyDomeVertices, 30, 30);
        glDisable(GL_TEXTURE_2D); // Disable texture mapping
	glPopMatrix();

    glPushMatrix();
        
        if(liftOff){
            glTranslatef(0,liftOffHeight,0);
        } 
        glRotatef(angle,0,1,0);
        glPushMatrix();
            glEnable(GL_DEPTH_TEST);
            glTranslatef(5,50,0);
            glLightfv(GL_LIGHT0, GL_POSITION, light);
            glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
            glLightfv(GL_LIGHT1, GL_POSITION, spotPosn);
            spaceShip();                //
        glPopMatrix();
    glPopMatrix();
        
    drawFloor(100);     //A tessellated floor plane
    glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        glTranslatef(90,0,-40);
            list<particle>::iterator it;
            for (it = particleList.begin(); it != particleList.end(); it++)
            {
                drawParticle(it->col, it->size, it->pos[0], it->pos[1], it->pos[2]);
            }        
            glPushMatrix();
            glScalef(5,5,5);
            drawVolcano();
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glPushMatrix();
            glPushMatrix();
                glTranslatef(0,0.2,0);    
                spiral(false);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,0.1,0);    
                glMultMatrixf(shadowMat);
                glDisable(GL_LIGHTING);
                glColor3f(0.1, 0.1, 0.1);
                spiral(true);
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();
            glTranslatef(13,0,1);
            glPushMatrix();
                glTranslatef(0,0.2,0);    
                spiral(false);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0,0.1,0);    
                glMultMatrixf(shadowMat);
                glDisable(GL_LIGHTING);
                glColor3f(0.1, 0.1, 0.1);
                spiral(true);
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();



    //draw alien and it's shadow
    // Draw alien and its shadow
    glPushMatrix();
        glTranslatef(0,0,0);
        displayAlienModel(shadowMat);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(15,0,0);
        displayAlienModel(shadowMat);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-15,0,0);
        displayAlienModel(shadowMat);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-30,0,0);
        displayAlienModel(shadowMat);
    glPopMatrix();
    glutSwapBuffers();       //Double buffered animation
}

void newParticle()
{
	particle p = {0};
	p.pos[0] = 4*rand()/(float) RAND_MAX-2;
	p.pos[1] = 20;    //This point is at the top end of the smoke stack
	p.pos[2] = 4*rand()/(float) RAND_MAX-2;

	p.vel[0] = 0;
	p.vel[1] = 0.3;
	p.vel[2] = 0;

	p.col = 1;
	p.size = 10;

	particleList.push_back(p);
}

void updateQueue()
{
	const int LIFETIME = 100;
	list<particle>::iterator it;
	particle p;
	int tval;
	float delta;
	//Remove particles that have passed lifetime

	if (!particleList.empty())
	{   
        
		p = particleList.front();
		if (p.t > LIFETIME) particleList.pop_front();
        if (p.pos[1] < 1) particleList.pop_front();


	}

	for (it = particleList.begin(); it != particleList.end(); it++)
	{
		tval = it->t;
		it->t = tval + 1;
		delta = (float)tval / (float)LIFETIME;

		
		for (int i = 0; i < 3; i++)
			(it->pos[i]) += it->vel[i];

		it->size = delta  * 30 + 10;	//(5 - 25)
		it->col = 1 - delta;		// (1 - 0)

	}

    if(tick % 2 == 0){
        newParticle();   //Create a new particle every sec.
    }
}

//---------------------------------------------------------------------
void spaceShipTimer(int val){
    tick++;
    if (tick == INT_MAX) tick = 0;
    updateQueue();
	static int lastTime = 0;
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f; // Convert milliseconds to seconds
    if (val < 600) {
        glutPostRedisplay();
        float angleIncrement = 10.0f * deltaTime; // Adjust speed as needed
        float valIncrement = 0.1f * deltaTime;   // Adjust speed as needed
        // Adjust angle and val based on deltaTime for smoother animation
        if (liftOff){
            
            liftOffHeight += 1;
        }else {
            
            angle -= angleIncrement;
            val += valIncrement;
            // Wrap angle around when it reaches -360 degrees
            if (angle <= -360) {
                angle += 360;
            }
        }
        
        
        //simple timer for the animation of the aliens gun
        if (gunTimerCounter < 40){
            gunTimerCounter += 1;
            theta += gunAngleIncrement;
        } else {
            theta += 0;
            if (gunWait < 50){
                gunWait += 1;
                if (gunAngleIncrement > 0){
                    fireBullet = (bulletVert > -7);
                    bulletHorz += 1;
                    bulletVert -= 0.001* gunWait * gunWait;
                }
            } else {
                gunWait = 0;
                gunAngleIncrement*=-1;
                gunTimerCounter = 0;
                fireBullet = false;
                bulletHorz = 0;
                bulletVert = 0;
            }

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
    glutKeyboardFunc(handleLiftOff);
    glutMainLoop();
    return 0;
}
