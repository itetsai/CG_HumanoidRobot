
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include "../freeglut-3.0.0/include/glut.h"
#endif


// This is the main project file for VC++ application project 
// generated using an Application Wizard.

#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

static int action = 0;
static GLuint inner_mode = GL_SMOOTH;
static GLuint tex_state = GL_TRUE;
static int state_chang;


int bodycolor[3][3];//機器人身體顏色

#pragma
int state = 1;

static int WinWidth = 1200;
static int WinHeight = 1200;


void draw_Sphere(float radius) 
{
	glPushMatrix();
	glColor4ub(219, 156, 53, 0);
	glutSolidSphere(radius, 50.0, 50.0);
	glPopMatrix();
}

void draw_ColorSphere(float radius,float a, float b, float c) 
{
	glPushMatrix();						//肘關節
	glColor4ub(a, b, c, 0);
	glutSolidSphere(radius, 30.0, 30.0);
	glPopMatrix();
}

float Body[4];
void drawBody(float BOX_SIZE, float a)
{

	glPushMatrix();

	glBegin(GL_QUADS);

	//Top face
	glColor3ub(bodycolor[0][0], bodycolor[0][1], bodycolor[0][2]);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2 * a, -BOX_SIZE / 2*0.5);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2 * a, BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2 * a, BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2 * a, -BOX_SIZE / 2 * 0.5);

	//Bottom face
	glColor3ub(bodycolor[0][0], bodycolor[0][1], bodycolor[0][2]);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2 * 0.5);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2 * 0.5);

	//Left face
	glColor3ub(bodycolor[1][0], bodycolor[1][1], bodycolor[1][2]);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2 * 0.5);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2 * 0.5);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2 * a, BOX_SIZE / 2 * 0.5);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2 * a, -BOX_SIZE / 2 * 0.5);

	//Right face
	glColor3ub(bodycolor[1][0], bodycolor[1][1], bodycolor[1][2]);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2 * a, -BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2 * a, BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2 * 0.5);

	glEnd();

	glBegin(GL_QUADS);

	//Front face

	glColor3ub(bodycolor[2][0], bodycolor[2][1], bodycolor[2][2]);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2 * a, BOX_SIZE / 2 * 0.5);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2 * a, BOX_SIZE / 2 * 0.5);

	//Back face
	glColor3ub(bodycolor[2][0], bodycolor[2][1], bodycolor[2][2]);
	glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2 * 0.5);
	glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2 * a, -BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2 * a, -BOX_SIZE / 2 * 0.5);
	glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2 * 0.5);

	glEnd();

	glPopMatrix();
}

float left_hand[3][4];//[關節][轉動量 and xyz軸]
float left_hand_finger[5][3][4];//[手指][指關節][轉動量 and xyz軸]
float left_two[4];
float left2_two[4];
void draw_lefthand()
{
	glPushMatrix();
	glRotatef(left_hand[0][0], left_hand[0][1], left_hand[0][2], left_hand[0][3]);				//臂關節1

	glRotatef(left_two[0], left_two[1], left_two[2], left_two[3]);

	glColor3ub(219, 156, 53);
	glutSolidSphere(10.0, 30.0, 30.0);
	
	glTranslatef(-25, 0.0, 0.0);


	glPushMatrix();
	glScalef(4, 1 , 1);
	glColor3ub(255, 177, 98);//color
	glutSolidSphere(7.0, 30.0, 30.0);
	glPopMatrix();


	glTranslatef(-25, 0.0, 0.0);

	glPushMatrix();

	glRotatef(left_hand[1][0], left_hand[1][1], left_hand[1][2], left_hand[1][3]);			//臂關節2
	glRotatef(left2_two[0], left2_two[1], left2_two[2], left2_two[3]);

	glPushMatrix();						
	glColor3ub(219, 156, 53);
	glutSolidSphere(6.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(-22.0, 0.0, 0.0);		//下臂

	glPushMatrix();						//下臂
	glScalef(4, 1, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(6.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(-15.0, 0.0, 0.0);	

	 //掌關節
	glPushMatrix();
	glTranslatef(-8.0, 0, 0);		//掌
	glRotatef(left_hand[2][0], left_hand[2][1], left_hand[2][2], left_hand[2][3]);

	glPushMatrix();
	glColor3ub(219, 156, 53);
	glutSolidSphere(3, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(-7.0, 0, 0);
	glPushMatrix();
	glColor3ub(255, 102, 125);
	glScalef(1, 1, 0.5);
	glutSolidSphere(8, 30.0, 30.0);
	glPopMatrix();

	

	glTranslatef(-10.0, 0.0, 0);

#pragma region finger

	glPushMatrix();//姆指接掌關節
	
	glTranslatef(8, 9, 0.0);
	glRotatef(left_hand_finger[0][0][0], left_hand_finger[0][0][1], left_hand_finger[0][0][2], left_hand_finger[0][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//姆指節1

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//姆指中關節
	glRotatef(left_hand_finger[0][1][0], left_hand_finger[0][1][1], left_hand_finger[0][1][2], left_hand_finger[0][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3.0, 0, 0.0);//姆指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(0, 177, 98);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//食指接掌關節
   //------------------------------------------------------------食指
	glTranslatef(2, 6, 0.0);
	glRotatef(left_hand_finger[1][0][0], left_hand_finger[1][0][1], left_hand_finger[1][0][2], left_hand_finger[1][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//食指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//食指中關節
	glRotatef(left_hand_finger[1][1][0], left_hand_finger[1][1][1], left_hand_finger[1][1][2], left_hand_finger[1][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3.0, 0, 0.0);//食指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3, 0, 0.0);//食指上關節
	glRotatef(left_hand_finger[1][2][0], left_hand_finger[1][2][1], left_hand_finger[1][2][2], left_hand_finger[1][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-2.5, 0.0, 0.0); //食指節1
	glPushMatrix();

	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//中指接掌關節
				   //------------------------------------------------------------中指
	glTranslatef(0.5, 1.5, .0);
	glRotatef(left_hand_finger[2][0][0], left_hand_finger[2][0][1], left_hand_finger[2][0][2], left_hand_finger[2][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//中指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//中指中關節
	glRotatef(left_hand_finger[2][1][0], left_hand_finger[2][1][1], left_hand_finger[2][1][2], left_hand_finger[2][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3.0, 0, 0.0);//中指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3, 0, 0.0);//中指上關節
	glRotatef(left_hand_finger[2][2][0], left_hand_finger[2][2][1], left_hand_finger[2][2][2], left_hand_finger[2][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-2.5, 0.0, 0.0); //中指節1
	glPushMatrix();

	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//無名指接掌關節
				   //------------------------------------------------------------無名指
	glTranslatef(1, -3, -0.0);
	glRotatef(left_hand_finger[3][0][0], left_hand_finger[3][0][1], left_hand_finger[3][0][2], left_hand_finger[3][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//無名指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//無名指中關節
	glRotatef(left_hand_finger[3][1][0], left_hand_finger[3][1][1], left_hand_finger[3][1][2], left_hand_finger[3][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3.0, 0, 0.0);//無名指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3, 0, 0.0);//無名指上關節
	glRotatef(left_hand_finger[3][2][0], left_hand_finger[3][2][1], left_hand_finger[3][2][2], left_hand_finger[3][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-2.5, 0.0, 0.0); //無名指節1
	glPushMatrix();

	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//小指接掌關節
				   //------------------------------------------------------------小指
	glTranslatef(4,-7, -0.0);
	glRotatef(left_hand_finger[4][0][0], left_hand_finger[4][0][1], left_hand_finger[4][0][2], left_hand_finger[4][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//小指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-4, 0, 0);//小指中關節
	glRotatef(left_hand_finger[4][1][0], left_hand_finger[4][1][1], left_hand_finger[4][1][2], left_hand_finger[4][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3.0, 0, 0.0);//小指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-3, 0, 0.0);//小指上關節
	glRotatef(left_hand_finger[4][2][0], left_hand_finger[4][2][1], left_hand_finger[4][2][2], left_hand_finger[4][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(-2.5, 0.0, 0.0); //小指節1
	glPushMatrix();
	glRotatef(20.0, 0, 1, 1.0);
	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

#pragma endregion

	glPopMatrix();//掌關節
	glPopMatrix();//臂關節2
	glPopMatrix();//臂關節1
}

float right_hand[3][4];//[關節][轉動量 and xyz軸]
float right_hand_finger[5][3][4];//[手指][指關節][轉動量 and xyz軸]
float right_two[4];
float right2_two[4];
void draw_righthand()
{
	glPushMatrix();
	glRotatef(right_hand[0][0], right_hand[0][1], right_hand[0][2], right_hand[0][3]);				//臂關節1
	glRotatef(right_two[0], right_two[1], right_two[2], right_two[3]);

	glColor3ub(219, 156, 53);
	glutSolidSphere(10.0, 30.0, 30.0);

	glTranslatef(25, 0.0, 0.0);


	glPushMatrix();
	glScalef(4, 1 , 1);
	glColor3ub(255, 177, 98);//color
	glutSolidSphere(7.0, 30.0, 30.0);
	glPopMatrix();


	glTranslatef(25, 0.0, 0.0);

	glPushMatrix();

	glRotatef(right_hand[1][0], right_hand[1][1], right_hand[1][2], right_hand[1][3]);			//臂關節2
	glRotatef(right2_two[0], right2_two[1], right2_two[2], right2_two[3]);
	glPushMatrix();
	glColor3ub(219, 156, 53);
	glutSolidSphere(6.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(22.0, 0.0, 0.0);		//下臂

	glPushMatrix();						//下臂
	glScalef(4, 1 , 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(6.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(15.0, 0.0, 0.0);

	//掌關節
	glPushMatrix();
	glTranslatef(8.0, 0, 0);		//掌
	glRotatef(right_hand[2][0], right_hand[2][1], right_hand[2][2], right_hand[2][3]);

	glPushMatrix();
	glColor3ub(219, 156, 53);
	glutSolidSphere(3, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(7.0, 0, 0);
	glPushMatrix();
	glColor3ub(255, 102, 125);
	glScalef(1, 1, 0.5);
	glutSolidSphere(8, 30.0, 30.0);
	glPopMatrix();



	glTranslatef(10.0, 0.0, 0);

#pragma region finger

	glPushMatrix();//姆指接掌關節

	glTranslatef(-8, 9, 0.0);
	glRotatef(right_hand_finger[0][0][0], right_hand_finger[0][0][1], right_hand_finger[0][0][2], right_hand_finger[0][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//姆指節1

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//姆指中關節
	glRotatef(right_hand_finger[0][1][0], right_hand_finger[0][1][1], right_hand_finger[0][1][2], right_hand_finger[0][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3.0, 0, 0.0);//姆指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(0, 177, 98);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//食指接掌關節
				   //------------------------------------------------------------食指
	glTranslatef(-2, 6, 0.0);
	glRotatef(right_hand_finger[1][0][0], right_hand_finger[1][0][1], right_hand_finger[1][0][2], right_hand_finger[1][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//食指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//食指中關節
	glRotatef(right_hand_finger[1][1][0], right_hand_finger[1][1][1], right_hand_finger[1][1][2], right_hand_finger[1][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3.0, 0, 0.0);//食指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3, 0, 0.0);//食指上關節
	glRotatef(right_hand_finger[1][2][0], right_hand_finger[1][2][1], right_hand_finger[1][2][2], right_hand_finger[1][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(2.5, 0.0, 0.0); //食指節1
	glPushMatrix();

	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//中指接掌關節
				   //------------------------------------------------------------中指
	glTranslatef(-0.5, 1.5, .0);
	glRotatef(right_hand_finger[2][0][0], right_hand_finger[2][0][1], right_hand_finger[2][0][2], right_hand_finger[2][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//中指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//中指中關節
	glRotatef(right_hand_finger[2][1][0], right_hand_finger[2][1][1], right_hand_finger[2][1][2], right_hand_finger[2][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3.0, 0, 0.0);//中指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3, 0, 0.0);//中指上關節
	glRotatef(right_hand_finger[2][2][0], right_hand_finger[2][2][1], right_hand_finger[2][2][2], right_hand_finger[2][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(2.5, 0.0, 0.0); //中指節1
	glPushMatrix();

	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//無名指接掌關節
				   //------------------------------------------------------------無名指
	glTranslatef(-1, -3, -0.0);
	glRotatef(right_hand_finger[3][0][0], right_hand_finger[3][0][1], right_hand_finger[3][0][2], right_hand_finger[3][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//無名指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//無名指中關節
	glRotatef(right_hand_finger[3][1][0], right_hand_finger[3][1][1], right_hand_finger[3][1][2], right_hand_finger[3][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3.0, 0, 0.0);//無名指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3, 0, 0.0);//無名指上關節
	glRotatef(right_hand_finger[3][2][0], right_hand_finger[3][2][1], right_hand_finger[3][2][2], right_hand_finger[3][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(2.5, 0.0, 0.0); //無名指節1
	glPushMatrix();

	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();//小指接掌關節
				   //------------------------------------------------------------小指
	glTranslatef(-4, -7, -0.0);
	glRotatef(right_hand_finger[4][0][0], right_hand_finger[4][0][1], right_hand_finger[4][0][2], right_hand_finger[4][0][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//小指節3

	glPushMatrix();
	glScalef(1.2, 0.6, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(2.5, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(4, 0, 0);//小指中關節
	glRotatef(right_hand_finger[4][1][0], right_hand_finger[4][1][1], right_hand_finger[4][1][2], right_hand_finger[4][1][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3.0, 0, 0.0);//小指節2

	glPushMatrix();
	glScalef(1, 0.6, 1);
	glColor3ub(89, 197, 255);
	glutSolidSphere(2.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(3, 0, 0.0);//小指上關節
	glRotatef(right_hand_finger[4][2][0], right_hand_finger[4][2][1], right_hand_finger[4][2][2], right_hand_finger[4][2][3]);

	glPushMatrix();
	glColor3ub(0, 0, 0);
	glutSolidSphere(1.0, 30.0, 30.0);
	glPopMatrix();

	//-----------------------------
	glTranslatef(2.5, 0.0, 0.0); //小指節1
	glPushMatrix();
	glRotatef(20.0, 0, 1, 1.0);
	glScalef(1.0, 0.6, 1.0);
	glColor3ub(0, 177, 98);
	glutSolidSphere(1.7, 30.0, 30.0);
	glPopMatrix();

	glPopMatrix();

#pragma endregion

	glPopMatrix();//掌關節
	glPopMatrix();//臂關節2
	glPopMatrix();//臂關節1
}

float left_leg[3][4];//[關節][轉動量 and xyz軸]
void draw_leftleg()
{

	glPushMatrix();						//肘關節
	glRotatef(left_leg[0][0], left_leg[0][1], left_leg[0][2], left_leg[0][3]);

	glColor3ub(219, 156, 53);
	glutSolidSphere(8.0, 30.0, 30.0);


	glTranslatef(0, -25, 0.0);

	glPushMatrix();						//上臂
	glScalef(1.5, 4, 1);
	glColor3ub(255, 177, 98);//color
	glutSolidSphere(7.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(0,-25, 0.0);	//肘關節
	glRotatef(left_leg[1][0], left_leg[1][1], left_leg[1][2], left_leg[1][3]);

	glPushMatrix();						//肘關節
	glColor3ub(219, 156, 53);
	glutSolidSphere(6.0, 30.0, 30.0);
	

	glTranslatef(0, -22, 0.0);		//下臂

	glPushMatrix();						//下臂
	glScalef(1.5, 4, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(6.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(0, -20, 0.0);		//掌關節
	glRotatef(left_leg[2][0], left_leg[2][1], left_leg[2][2], left_leg[2][3]);
	glPushMatrix();

	glColor3ub(255, 102, 125);
	glutSolidSphere(6, 30.0, 30.0);

	glTranslatef(0, -7, 13.0);

	glColor3ub(0, 255, 255);
	glScalef(2, 1, 4);
	glutSolidCube(10);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

float right_leg[3][4];//[關節][轉動量 and xyz軸]

void draw_rightleg()
{

	glPushMatrix();						//肘關節
	glRotatef(right_leg[0][0], right_leg[0][1], right_leg[0][2], right_leg[0][3]);

	glColor3ub(219, 156, 53);
	glutSolidSphere(8.0, 30.0, 30.0);


	glTranslatef(0, -25, 0.0);

	glPushMatrix();						//上臂
	glScalef(1.5, 4, 1);
	glColor3ub(255, 177, 98);//color
	glutSolidSphere(7.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(0, -25, 0.0);	//肘關節
	glRotatef(right_leg[1][0], right_leg[1][1], right_leg[1][2], right_leg[1][3]);

	glPushMatrix();						//肘關節
	glColor3ub(219, 156, 53);
	glutSolidSphere(6.0, 30.0, 30.0);


	glTranslatef(0, -22, 0.0);		//下臂

	glPushMatrix();						//下臂
	glScalef(1.5, 4, 1);
	glColor3ub(255, 177, 98);
	glutSolidSphere(6.0, 30.0, 30.0);
	glPopMatrix();

	glTranslatef(0, -20, 0.0);		//掌關節
	glRotatef(right_leg[2][0], right_leg[2][1], right_leg[2][2], right_leg[2][3]);
	glPushMatrix();

	glColor3ub(255, 102, 125);
	glutSolidSphere(6, 30.0, 30.0);

	glTranslatef(0, -7, 13.0);

	glColor3ub(0, 255, 255);
	glScalef(2, 1, 4);
	glutSolidCube(10);
	glPopMatrix();

	glPopMatrix();

	glPopMatrix();
}

int rrr = 0;
int rr = 0;

float all_body[4];
float all_s[3];
float head_r[4];
float head_s[3];
float lefthand_s[3];
float righthand_s[3];
float leftleg_s[3];
float rightleg_s[3];
//畫機器人初始位置

float ball_r = 0;
float ball_s[3];
void draw(void)
{
	glNormal3f(-1.0, -4.0f, -1.0f);

	glTranslatef(-5.0, 15.0, -440.0);
	glRotatef(rrr, 0, 1, 0);
	glRotatef(rr, 1, 0, 0);

	glRotatef(all_body[0], all_body[1], all_body[2], all_body[3]);
	glTranslatef(all_s[0], all_s[1], all_s[2]);
	glPushMatrix();//身體
	glRotatef(Body[0], Body[1], Body[2], Body[3]);

	glPushMatrix();
	glTranslatef(ball_s[0], ball_s[1], ball_s[2]);
	glRotatef(100, rand()%10, rand() % 10, rand() % 10);
	glColor4ub(0, 255, 255, 0);
	glutWireSphere(ball_r, 30.0, 30.0);
	glPopMatrix();


	glTranslatef(0, 35, 0);
	drawBody(65, 1.5);
	



	glPushMatrix();
	glTranslatef(0 + head_s[0], 80 + head_s[1], 0 + head_s[2]);//head
	glRotatef(head_r[0], head_r[1], head_r[2], head_r[3]);
	draw_Sphere(30);

#pragma region eye++
	glPushMatrix();//eye
	glTranslatef(10, -2, 29);

	glPushMatrix();//右眼白
	glScalef(4, 1, 1);
	draw_ColorSphere(2, 255, 250, 250);
	glPopMatrix();

	glPushMatrix();//眼珠
	glTranslatef(0, -1, 1.5);
	draw_ColorSphere(2, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();//眉毛
	glTranslatef(0, 3, 1.5);
	glScalef(4, 1, 1);
	draw_ColorSphere(1, 0, 0, 0);
	glPopMatrix();

	glTranslatef(-20, 0, 0);

	glPushMatrix();//左眼白
	glScalef(4, 1, 1);
	draw_ColorSphere(2, 255, 250, 250);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, -1, 1.5);
	draw_ColorSphere(2, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 3, 1.5);
	glScalef(4, 1, 1);
	draw_ColorSphere(1, 0, 0, 0);
	glPopMatrix();

	glPopMatrix();
#pragma endregion

	glPushMatrix();//nose
	glTranslatef(0, -12, 26.5);
	draw_ColorSphere(2, 0, 0, 0);
	glPopMatrix();

	glPushMatrix();//mouth
	glTranslatef(0, -22, 20);
	glScalef(4, 1, 1);
	draw_ColorSphere(2, 255, 0, 0);
	glPopMatrix();

	glPopMatrix();
     
	

	glPushMatrix();
	glTranslatef(-42+lefthand_s[0], 40 + lefthand_s[1], 0 + lefthand_s[2]);//左手       
	draw_lefthand();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(42 + righthand_s[0], 40 + righthand_s[1], 0 + righthand_s[2]);//右手
	draw_righthand();
	glPopMatrix();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20 + leftleg_s[0], 0 + leftleg_s[1], 0 + leftleg_s[2]);//左腳
	draw_leftleg();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(20 + rightleg_s[0], 0 + rightleg_s[1], 0 + rightleg_s[2]);//右腳
	draw_rightleg();
	glPopMatrix();

	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(inner_mode);

	//Viewport 1
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
			
	gluPerspective(60.0, 1.0, 2.0, 4000);// fov, aspect ratio ,near,far

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	WinWidth = w;
	WinHeight = h;
	GLfloat aspect;
	aspect = (GLfloat)w / (GLfloat)h;
	if (aspect > 1.0f)
		glViewport((w - h) / 2.0f, 0, (GLsizei)h, (GLsizei)h);
	else
		glViewport(0, (h - w) / 2.0f, (GLsizei)w, (GLsizei)w);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 1.0f, 500.0f);
	glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
	GLfloat  ambientLight[] = { 1, 1, 1, 0.0f };
	GLfloat  diffuseLight[] = { 0, 0, 0, 1.0f };
	GLfloat  specular[] = { 0.4f, 0.4f, 0.4f, 0.4f };
	GLfloat  ambientLight2[] = { 0.9f, 0.1f, 0.1f, 1.0f };
	GLfloat  specular2[] = { 0.3f, 0.3f, 0.3f, 1.3f };
	GLfloat  specref[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat  pos[] = { 0.0f, 20.0f, -100.0f, 1.0f };
	GLfloat  dir[] = { 0.0f, 0.0f, -1.0f };

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ambientLight2);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular2);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 100);
	glLightfv(GL_LIGHT1, GL_POSITION, pos);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// All materials hereafter have full specular reflectivity with a high shine
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);


	glClearColor(0.8f, 0.8f, 0.8f, 0.0f);
}

int step = 0;
int step2 = 0;
int step3 = 0;
int delay_time = 0;
int v;
void standby()
{
	v = 0;
	step3 = 0;
	ball_r = 0;
	ball_s[0] = 0;
	ball_s[1] = 60;
	ball_s[2] = 75;
	step = 0;
	step2 = 0;
	state = 1;
	delay_time = 0;
	for (int i = 0; i < 3; i++)
	{
		all_s[i] = 0;
		head_s[i] = 0;
		lefthand_s[i] = 0;
		righthand_s[i] = 0;
		leftleg_s[i] = 0;
		rightleg_s[i] = 0;
	}
	for (int i = 0; i < 4; i++)
	{
		Body[i] = 0;
		all_body[i] = 0;
		left_two[i] = 0;
		right_two[i] = 0;
		head_r[i] = 0;
		left2_two[i] = 0;
		right2_two[i] = 0;
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
		{
			left_hand[i][j] = 0;
			right_hand[i][j] = 0;
			left_leg[i][j] = 0;
			right_leg[i][j] = 0;
		}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 5; k++)
			{
				left_hand_finger[k][i][j] = 0;
				right_hand_finger[k][i][j] = 0;
			}

	left_hand[0][0] = 90;
	left_hand[0][1] = 0;
	left_hand[0][2] = 0;
	left_hand[0][3] = 1;

	left_hand[2][0] = 90;
	left_hand[2][1] = 1;
	left_hand[2][2] = 0;
	left_hand[2][3] = 0;

	right_hand[0][0] = -90;
	right_hand[0][1] = 0;
	right_hand[0][2] = 0;
	right_hand[0][3] = 1;

	right_hand[2][0] = 90;
	right_hand[2][1] = 1;
	right_hand[2][2] = 0;
	right_hand[2][3] = 0;

}

void walk()
{
	if (all_body[0] < 5)
		all_body[0]++;
	all_body[1] = 1;
	all_body[2] = 0;
	all_body[3] = 0;
	if (left_hand[1][0] < 90)
		left_hand[1][0]++;
	left_hand[1][1] = 0;
	left_hand[1][2] = 1;
	left_hand[1][3] = 0;

	if (right_hand[1][0] > -90)
		right_hand[1][0]--;
	right_hand[1][1] = 0;
	right_hand[1][2] = 1;
	right_hand[1][3] = 0;

	if (left_leg[1][0] < 60)
		left_leg[1][0]++;
	left_leg[1][1] = 1;
	left_leg[1][2] = 0;
	left_leg[1][3] = 0;

	if (right_leg[1][0] < 60)
		right_leg[1][0]++;
	right_leg[1][1] = 1;
	right_leg[1][2] = 0;
	right_leg[1][3] = 0;

	switch (step)
	{
	case 0:
		if (left_two[0] < 70)
		{
			left_two[0]++;
			right_two[0]++;
			left_leg[0][0]++;
			right_leg[0][0]++;
		}
		else
			step = 1;
		break;
	case 1:
		if (left_two[0] > -70)
		{
			left_two[0]--;
			right_two[0]--;
			left_leg[0][0]--;
			right_leg[0][0]--;
		}
		else
			step = 0;
		break;
	}

	switch (step2)
	{
	case 0:
		if (all_s[1] < 7)
		{
			all_s[1]+=0.1;
		}
		else
			step2 = 1;
		break;
	case 1:
		if (all_s[1] > 0)
		{
			all_s[1] -= 0.1;
		}
		else
			step2 = 0;
		break;
	}

	left_two[1] = 0;
	left_two[2] = 1;
	left_two[3] = 0;

	right_two[1] = 0;
	right_two[2] = 1;
	right_two[3] = 0;

	left_leg[0][1] = 1;
	left_leg[0][2] = 0;
	left_leg[0][3] = 0;

	right_leg[0][1] = -1;
	right_leg[0][2] = 0;
	right_leg[0][3] = 0;

	glutPostRedisplay();
}

void Inverted()
{
	if (Body[0] < 90)
		Body[0]++;
	Body[1] = 1;
	Body[2] = 0;
	Body[3] = 0;
	
	if (left_two[0] < 90)
		left_two[0]++;
	left_two[1] = 0;
	left_two[2] = 1;
	left_two[3] = 0;

	if (right_two[0] < 90)
		right_two[0]++;
	right_two[1] = 0;
	right_two[2] = -1;
	right_two[3] = 0;
	switch (step)
	{
	case 0:
		if (left_hand[2][0] > 0)
		{
			left_hand[2][0]-=2;
			left_hand[2][1] = 1;
			left_hand[2][2] = 0;
			left_hand[2][3] = 0;
		}
		else
			step = 1;

		if (right_hand[2][0] > 0)
		{
			right_hand[2][0] -= 2;
			right_hand[2][1] = 1;
			right_hand[2][2] = 0;
			right_hand[2][3] = 0;
		}
		else
			step = 1;
		break;
	case 1:
		if (left_hand[2][0] < 90)
		{
			left_hand[2][0] += 2;
			left_hand[2][1] = 0;
			left_hand[2][2] = 1;
			left_hand[2][3] = 0;
		}
		else
			step = 2;
		if (right_hand[2][0] < 90)
		{
			right_hand[2][0] += 2;
			right_hand[2][1] = 0;
			right_hand[2][2] = -1;
			right_hand[2][3] = 0;
		}
		else
			step = 2;
		break;
	case 2:
		if (left_two[0] < 180)
		{
			left_two[0] += 1;
			left_two[1] = 0;
			left_two[2] = 1;
			left_two[3] = 0;
		}
		if (right_two[0] < 180)
		{
			right_two[0] += 1;
			right_two[1] = 0;
			right_two[2] = -1;
			right_two[3] = 0;
		}
		if (all_body[0] < 90)
			all_body[0]++;
		all_body[1] = 1;
		all_body[2] = 0;
		all_body[3] = 0;
		if (all_s[1] < 70)
			all_s[1] += 70.0/90.0;

		if (all_s[2] > -70)
			all_s[2] -= 70.0/90.0;


		if (left_leg[0][0] < 90)
			left_leg[0][0]++;
		left_leg[0][1] = 1;
		left_leg[0][2] = 0;
		left_leg[0][3] = 0;

		if (right_leg[0][0] < 90)
			right_leg[0][0]++;
		else
		{
			step = 3;
			delay_time = 100;
		}
		right_leg[0][1] = 1;
		right_leg[0][2] = 0;
		right_leg[0][3] = 0;
		break;
	case 3:
		if (delay_time <= 0)
		{
			if (head_s[1] < 30)
				head_s[1]++;
			else if (head_s[2] > -80)
				head_s[2]--;


			if (leftleg_s[0] > -50)
				leftleg_s[0]--;
			else if (leftleg_s[2] < 130)
				leftleg_s[2]++;
			else
				step = 4;

			if (rightleg_s[0] < 50)
				rightleg_s[0]++;
			else if (rightleg_s[2] < 130)
				rightleg_s[2]++;
			else
				step = 4;

			if (lefthand_s[1] > -63)
				lefthand_s[1]--;

			if (righthand_s[1] > -63)
				righthand_s[1]--;
		}
		else
			delay_time--;
		break;
	case 4:
		if (head_s[1] > -143)
			head_s[1]--;
		else if (head_s[2] < 0)
			head_s[2]++;
		else if (head_r[0] < 180)
		{
			head_r[0]++;
			head_r[1] = 1;
			head_r[2] = 0;
			head_r[3] = 0;
		}

		if (right_leg[0][0] > -90)
		{
			right_leg[0][0]--;
			right_leg[0][1] = 1;
			right_leg[0][2] = 0;
			right_leg[0][3] = 0;
		}
		else if (rightleg_s[0] > 0)
			rightleg_s[0]--;
		else if (rightleg_s[2] > 86)
			rightleg_s[2]--;
		else if (right_hand[2][0] > 0)
		{
			right_hand[2][0]--;
			right_hand[2][1] = 0;
			right_hand[2][2] = -1;
			right_hand[2][3] = 0;
		}
		else if (right_hand[1][0] < 90)
		{
			right_hand[1][0]++;
			right_hand[1][1] = 1;
			right_hand[1][2] = 0;
			right_hand[1][3] = 0;
		}


		if (left_leg[0][0] > -90)
		{
			left_leg[0][0]--;
			left_leg[0][1] = 1;
			left_leg[0][2] = 0;
			left_leg[0][3] = 0;
		}
		else if (leftleg_s[0] < 0)
			leftleg_s[0]++;
		else if (leftleg_s[2] > 86)
			leftleg_s[2]--;
		else if (left_hand[2][0] > 0)
		{
			left_hand[2][0]--;
			left_hand[2][1] = 0;
			left_hand[2][2] = 1;
			left_hand[2][3] = 0;
		}
		else if (left_hand[1][0] <90)
		{
			left_hand[1][0]++;
			left_hand[1][1] = 1;
			left_hand[1][2] = 0;
			left_hand[1][3] = 0;
		}
		break;
	}
	glutPostRedisplay();
}

void ChangeColor()
{
	switch (step)
	{
	case 0:
#pragma region ARM
		if (left_hand[0][0] > 0)
			left_hand[0][0]--;
		left_hand[0][1] = 0;
		left_hand[0][2] = 0;
		left_hand[0][3] = 1;

		if (left_hand[2][0] > 0)
			left_hand[2][0]--;
		left_hand[2][1] = 1;
		left_hand[2][2] = 0;
		left_hand[2][3] = 0;

		if (right_hand[0][0] < 0)
			right_hand[0][0]++;
		right_hand[0][1] = 0;
		right_hand[0][2] = 0;
		right_hand[0][3] = 1;

		if (right_hand[2][0] > 0)
			right_hand[2][0]--;
		right_hand[2][1] = 1;
		right_hand[2][2] = 0;
		right_hand[2][3] = 0;

		if (right_hand[1][0] < 90)
			right_hand[1][0]++;
		right_hand[1][1] = 0;
		right_hand[1][2] = -1;
		right_hand[1][3] = 0;

		if (left_hand[1][0] < 90)
			left_hand[1][0]++;
		left_hand[1][1] = 0;
		left_hand[1][2] = 1;
		left_hand[1][3] = 0;

#pragma endregion

#pragma region finger
		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (left_hand_finger[i][j][0] < 90)
				{
					left_hand_finger[i][j][0]++;
					left_hand_finger[i][j][1] = 0;
					left_hand_finger[i][j][2] = 1;
					left_hand_finger[i][j][3] = 0;
				}

		if (left_hand_finger[0][0][0] < 90)
		{
			left_hand_finger[0][0][0]++;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][0][0] < 90)
		{
			left_hand_finger[0][0][0]++;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][1][0] < 90)
		{
			left_hand_finger[0][1][0]++;
			left_hand_finger[0][1][1] = 0;
			left_hand_finger[0][1][2] = 0;
			left_hand_finger[0][1][3] = 1;
		}


		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (right_hand_finger[i][j][0] < 90)
				{
					right_hand_finger[i][j][0]++;
					right_hand_finger[i][j][1] = 0;
					right_hand_finger[i][j][2] = -1;
					right_hand_finger[i][j][3] = 0;
				}

		if (right_hand_finger[0][0][0] < 90)
		{
			right_hand_finger[0][0][0]++;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][0][0] < 90)
		{
			right_hand_finger[0][0][0]++;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][1][0] < 90)
		{
			right_hand_finger[0][1][0]++;
			right_hand_finger[0][1][1] = 0;
			right_hand_finger[0][1][2] = 0;
			right_hand_finger[0][1][3] = -1;
		}
		else
			step = 1;
#pragma endregion
		break;
	case 1:
		if (left_hand[0][0]>-30)
		{
			left_hand[0][0]--;
			left_hand[0][1] = 0;
			left_hand[0][2] = 1;
			left_hand[0][3] = 0;
		}

		if (right_hand[0][0] > -30)
		{
			right_hand[0][0]--;
			right_hand[0][1] = 0;
			right_hand[0][2] = -1;
			right_hand[0][3] = 0;
		}
		else
		{
			step = 2;
			delay_time = 250;
		}
		break;
	case 2:
		if (left_hand[0][0]<68)
		{
			left_hand[0][0] += 2;
			left_hand[0][1] = 0;
			left_hand[0][2] = 1;
			left_hand[0][3] = 0;
		}
			

		if (right_hand[0][0] < 68)
		{
			right_hand[0][0] += 2;
			right_hand[0][1] = 0;
			right_hand[0][2] = -1;
			right_hand[0][3] = 0;
		}
		else if (delay_time > 0)
		{
			delay_time--;
			for (int i = 0; i < 3; i++)
				for (int j = 0; j < 3; j++)
					bodycolor[i][j] = rand() % 255;
		}
		else
			step = 3;
		break;
	case 3:
#pragma region ARM

		if (left_hand[0][0]<90)
		{
			left_hand[0][0] +=0.1;
			left_hand[0][1] = 0;
			left_hand[0][2] = 1;
			left_hand[0][3] = 0;
		}


		if (right_hand[0][0] < 90)
		{
			right_hand[0][0] +=0.1;
			right_hand[0][1] = 0;
			right_hand[0][2] = -1;
			right_hand[0][3] = 0;
		}


		if (right_hand[1][0] > 0)
			right_hand[1][0]-=0.5;
		right_hand[1][1] = 0;
		right_hand[1][2] = -1;
		right_hand[1][3] = 0;

		if (left_hand[1][0] > 0)
			left_hand[1][0]-=0.5;
		left_hand[1][1] = 0;
		left_hand[1][2] = 1;
		left_hand[1][3] = 0;


		if (left_two[0] < 90)
			left_two[0]+=0.4;
		left_two[1] = 0;
		left_two[2] = 0;
		left_two[3] = 1;

		if (right_two[0] > -90)
			right_two[0] -= 0.4;
		right_two[1] = 0;
		right_two[2] = 0;
		right_two[3] = 1;
#pragma endregion

#pragma region finger
		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (left_hand_finger[i][j][0] > 0)
				{
					left_hand_finger[i][j][0]-=0.5;
					left_hand_finger[i][j][1] = 0;
					left_hand_finger[i][j][2] = 1;
					left_hand_finger[i][j][3] = 0;
				}

		if (left_hand_finger[0][0][0] > 0)
		{
			left_hand_finger[0][0][0] -= 0.5;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][0][0] > 0)
		{
			left_hand_finger[0][0][0] -= 0.5;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][1][0] > 0)
		{
			left_hand_finger[0][1][0] -= 0.5;
			left_hand_finger[0][1][1] = 0;
			left_hand_finger[0][1][2] = 0;
			left_hand_finger[0][1][3] = 1;
		}


		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (right_hand_finger[i][j][0] > 0)
				{
					right_hand_finger[i][j][0] -= 0.5;
					right_hand_finger[i][j][1] = 0;
					right_hand_finger[i][j][2] = -1;
					right_hand_finger[i][j][3] = 0;
				}

		if (right_hand_finger[0][0][0] > 0)
		{
			right_hand_finger[0][0][0] -= 0.5;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][0][0] > 0)
		{
			right_hand_finger[0][0][0] -= 0.5;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][1][0] > 0)
		{
			right_hand_finger[0][1][0] -= 0.5;
			right_hand_finger[0][1][1] = 0;
			right_hand_finger[0][1][2] = 0;
			right_hand_finger[0][1][3] = -1;
		}
#pragma endregion
		break;
	}

}

void AttackBall()
{
	switch (step)
	{
	case 0:
		if (left_two[0] < 10)
		{
			left_two[0]++;
			left_two[1] = 0;
			left_two[2] = 0;
			left_two[3] = 1;
		}

		if (right_two[0] < 10)
		{
			right_two[0]++;
			right_two[1] = 0;
			right_two[2] = 0;
			right_two[3] = -1;
		}

		if (left_hand[0][0] > 0)
			left_hand[0][0]--;
		left_hand[0][1] = 0;
		left_hand[0][2] = 0;
		left_hand[0][3] = 1;

		if (left_hand[2][0] > 0 && step2 == 0)
		{
			left_hand[2][0]-=1.5;
			left_hand[2][1] = 1;
			left_hand[2][2] = 0;
			left_hand[2][3] = 0;
			if (right_hand[2][0] == 0)
				step2 = 1;
		}
		else if (left_hand[2][0]<40)
		{
			left_hand[2][0]++;
			left_hand[2][1] = 0;
			left_hand[2][2] = -1;
			left_hand[2][3] = 0;
		}

		if (right_hand[0][0] < 0)
			right_hand[0][0]++;
		right_hand[0][1] = 0;
		right_hand[0][2] = 0;
		right_hand[0][3] = 1;


		if (right_hand[2][0] > 0 && step2 == 0)
		{
			right_hand[2][0] -= 1.5;
			right_hand[2][1] = 1;
			right_hand[2][2] = 0;
			right_hand[2][3] = 0;
			if (right_hand[2][0] == 0)
				step2 = 1;
		}
		else if(right_hand[2][0]<40)
		{
			right_hand[2][0]++;
			right_hand[2][1] = 0;
			right_hand[2][2] = 1;
			right_hand[2][3] = 0;
		}

		if (right_hand[1][0] < 75)
			right_hand[1][0]+=0.75;
		right_hand[1][1] = 0;
		right_hand[1][2] = -1;
		right_hand[1][3] = 0;

		if (left_hand[1][0] < 75)
		{
			left_hand[1][0] += 0.75;
			left_hand[1][1] = 0;
			left_hand[1][2] = 1;
			left_hand[1][3] = 0;
		}
		else
			step = 1;
		break;
	case 1:
		if (left_hand[0][0] < 75)
		{
			left_hand[0][0]++;
			left_hand[0][1] = 0;
			left_hand[0][2] = 1;
			left_hand[0][3] = 0;
		}

		if (right_hand[0][0] < 75)
		{
			right_hand[0][0]++;
			right_hand[0][1] = 0;
			right_hand[0][2] = -1;
			right_hand[0][3] = 0;
		}
		else
		{
			step = 2;
			delay_time = 500;
		}
		break;
	case 2:

		if (left_hand[0][0] > 50)
		{
			left_hand[0][0]-=0.05;
			left_hand[0][1] = 0;
			left_hand[0][2] = 1;
			left_hand[0][3] = 0;
		}

		if (right_hand[0][0] > 50)
		{
			right_hand[0][0]-=0.05;
			right_hand[0][1] = 0;
			right_hand[0][2] = -1;
			right_hand[0][3] = 0;
		}
		
		if (delay_time > 0)
		{
			ball_r += 0.1;
			delay_time--;
			ball_s[2] += 0.1;
		}
		else
		{
			step = 3;
			step2 = 0;
			delay_time = 150;
		}
		break;
	case 3:
		if (delay_time < 0)
		{
			if (left_hand[0][0] < 90)
			{
				left_hand[0][0] += 3;
				left_hand[0][1] = 0;
				left_hand[0][2] = 1;
				left_hand[0][3] = 0;
			}

			if (right_hand[0][0] < 90)
			{
				right_hand[0][0] += 3;
				right_hand[0][1] = 0;
				right_hand[0][2] = -1;
				right_hand[0][3] = 0;
			}

			if (left_two[0] > 0)
			{
				left_two[0]--;
				left_two[1] = 0;
				left_two[2] = 0;
				left_two[3] = 1;
			}

			if (right_two[0] > 0)
			{
				right_two[0]--;
				right_two[1] = 0;
				right_two[2] = 0;
				right_two[3] = -1;
			}

			if (right_hand[1][0] > 0)
				right_hand[1][0] -= 4;
			right_hand[1][1] = 0;
			right_hand[1][2] = -1;
			right_hand[1][3] = 0;

			if (left_hand[1][0] > 0)
			{
				left_hand[1][0] -= 4;
				left_hand[1][1] = 0;
				left_hand[1][2] = 1;
				left_hand[1][3] = 0;
			}

			if (left_hand[2][0] > 0 && step2 == 0)
			{
				left_hand[2][0] -= 8;
				left_hand[2][1] = 0;
				left_hand[2][2] = -1;
				left_hand[2][3] = 0;

				right_hand[2][0] -= 8;
				right_hand[2][1] = 0;
				right_hand[2][2] = 1;
				right_hand[2][3] = 0;

				if (left_hand[2][0] == 0)
					step2 = 1;
			}
			else if (left_hand[2][0] < 90)
			{
				left_hand[2][0] += 10;
				left_hand[2][1] = 1;
				left_hand[2][2] = -1;
				left_hand[2][3] = -1;

				right_hand[2][0] += 10;
				right_hand[2][1] = 1;
				right_hand[2][2] = 1;
				right_hand[2][3] = 1;
			}

			ball_s[2] += 10;
		}
		else
			delay_time--;
			
		break;
	}

}

void DefenceBall()
{
	switch (step)
	{
	case 0:
		if (right_hand[0][0] < 0)
			right_hand[0][0]++;
		right_hand[0][1] = 0;
		right_hand[0][2] = 0;
		right_hand[0][3] = 1;

		if (left_hand[0][0] > 0)
			left_hand[0][0]--;
		left_hand[0][1] = 0;
		left_hand[0][2] = 0;
		left_hand[0][3] = 1;

		if (left_hand[2][0]>-90)
			left_hand[2][0] -= 2;
		left_hand[2][1] = 1;
		left_hand[2][2] = 0;
		left_hand[2][3] = 0;

		if (right_hand[2][0] > -90)
			right_hand[2][0] -= 2;
		else
			step = 1;
		right_hand[2][1] = 1;
		right_hand[2][2] = 0;
		right_hand[2][3] = 0;
		break;
	case 1:

#pragma region finger
		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (left_hand_finger[i][j][0] < 90)
				{
					left_hand_finger[i][j][0]+=3;
					left_hand_finger[i][j][1] = 0;
					left_hand_finger[i][j][2] = 1;
					left_hand_finger[i][j][3] = 0;
				}

		if (left_hand_finger[0][0][0] < 90)
		{
			left_hand_finger[0][0][0]+=3;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][0][0] < 90)
		{
			left_hand_finger[0][0][0]+=3;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][1][0] < 90)
		{
			left_hand_finger[0][1][0]+=3;
			left_hand_finger[0][1][1] = 0;
			left_hand_finger[0][1][2] = 0;
			left_hand_finger[0][1][3] = 1;
		}


		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (right_hand_finger[i][j][0] < 90)
				{
					right_hand_finger[i][j][0]+=3;
					right_hand_finger[i][j][1] = 0;
					right_hand_finger[i][j][2] = -1;
					right_hand_finger[i][j][3] = 0;
				}

		if (right_hand_finger[0][0][0] < 90)
		{
			right_hand_finger[0][0][0]+=3;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][0][0] < 90)
		{
			right_hand_finger[0][0][0]+=3;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][1][0] < 90)
		{
			right_hand_finger[0][1][0]+=3;
			right_hand_finger[0][1][1] = 0;
			right_hand_finger[0][1][2] = 0;
			right_hand_finger[0][1][3] = -1;
		}
		else
			step = 1;
#pragma endregion

		if (left_hand[1][0] < 135)
			left_hand[1][0]+=3;
		left_hand[1][1] = 0;
		left_hand[1][2] = 0;
		left_hand[1][3] = -1;

		if (right_hand[1][0] < 135)
			right_hand[1][0] += 3;
		else
			step = 2;
		right_hand[1][1] = 0;
		right_hand[1][2] = 0;
		right_hand[1][3] = 1;


		if (left_hand[0][0] < 60)
			left_hand[0][0]+=60.0/45.0;
		left_hand[0][1] = 0;
		left_hand[0][2] = 0;
		left_hand[0][3] = 1;

		if (right_hand[0][0] < 60)
			right_hand[0][0]+=60.0/45.0;
		right_hand[0][1] = 0;
		right_hand[0][2] = 0;
		right_hand[0][3] = -1;

		if (left_leg[0][0] < 30)
			left_leg[0][0]++;
		left_leg[0][1] = 0;
		left_leg[0][2] = 0;
		left_leg[0][3] = -1;

		if (right_leg[0][0] < 30)
			right_leg[0][0]++;
		right_leg[0][1] = 0;
		right_leg[0][2] = 0;
		right_leg[0][3] = 1;

		if (left_leg[1][0] < 30)
			left_leg[1][0]++;
		left_leg[1][1] = 0;
		left_leg[1][2] = 0;
		left_leg[1][3] = 1;

		if (right_leg[1][0] < 30)
			right_leg[1][0]++;
		right_leg[1][1] = 0;
		right_leg[1][2] = 0;
		right_leg[1][3] = -1;
		break;
	case 2:
		ball_r = 150;
		ball_s[0] = 0;
		ball_s[1] = 5;
		ball_s[2] = 3;
		break;
	}

}

void axe_walk()
{


	if (all_s[1] <= 0 && all_s[1]>-45)
	{
		all_s[1] -= 0.5;
	}


	if (left_leg[0][0] < 90)
		left_leg[0][0]++;
	left_leg[0][1] = 1;
	left_leg[0][2] = 0;
	left_leg[0][3] = 0;

	if (right_leg[0][0] >-90)
		right_leg[0][0]--;
	right_leg[0][1] = 1;
	right_leg[0][2] = 0;
	right_leg[0][3] = 0;

	if (left_two[0] < 180)
		left_two[0] += 5;
	left_two[1] = -1;
	left_two[2] = 6;
	left_two[3] = 0;

	if (right_two[0] < 180)
		right_two[0] += 5;
	right_two[1] = -1;
	right_two[2] = -6;
	right_two[3] = 0;

	if (left_hand[2][0] < 180)
	{
		left_hand[2][0] += 2;
		left_hand[2][1] = 1;
		left_hand[2][2] = 0;
		left_hand[2][3] = 0;
	}

	if (right_hand[2][0] < 180)
	{
		right_hand[2][0] += 2;
		right_hand[2][1] = 1;
		right_hand[2][2] = 0;
		right_hand[2][3] = 0;
	}

	if (left_hand[1][0] < 30 && step2 == 0)
	{
		left_hand[1][0] += 1;
		left_hand[1][1] = 0;
		left_hand[1][2] = 0;
		left_hand[1][3] = 1;
		right_hand[1][0] += 1;
		right_hand[1][1] = 0;
		right_hand[1][2] = 0;
		right_hand[1][3] = -1;
		if (left_hand[1][0] == 29)
			step2 = 1;
	}
	else if (left_hand[1][0] > 0 && step2 == 1)
	{
		left_hand[1][0] -= 1;
		left_hand[1][1] = 0;
		left_hand[1][2] = 0;
		left_hand[1][3] = 1;
		right_hand[1][0] -= 1;
		right_hand[1][1] = 0;
		right_hand[1][2] = 0;
		right_hand[1][3] = -1;
		if (left_hand[1][0] == 1)
			step2 = 0;
	}

}

void Rotate_fly()
{
	if (left_two[0] < 90)
	{
		v = 0;
		left_two[0] += 5;
	}
	left_two[1] = 0;
	left_two[2] = 0;
	left_two[3] = -1;

	if (right_two[0] < 90)
		right_two[0] += 5;
	right_two[1] = 0;
	right_two[2] = 0;
	right_two[3] = 1;

	if (right_two[0] == 90)
		v += 1;
	all_body[0] += v;
	all_body[1] = 0;
	all_body[2] = 1;
	all_body[3] = 0;

	if (right_two[0] == 90)
	{
		all_s[1] += 2;
	}
}

void Mora()
{
	switch (step)
	{
	case 0:

#pragma region finger
		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (left_hand_finger[i][j][0] < 90)
				{
					left_hand_finger[i][j][0]+=3;
					left_hand_finger[i][j][1] = 0;
					left_hand_finger[i][j][2] = 1;
					left_hand_finger[i][j][3] = 0;
				}

		if (left_hand_finger[0][0][0] < 90)
		{
			left_hand_finger[0][0][0]+=3;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][0][0] < 90)
		{
			left_hand_finger[0][0][0]+=3;
			left_hand_finger[0][0][1] = 0;
			left_hand_finger[0][0][2] = 1;
			left_hand_finger[0][0][3] = 0;
		}

		if (left_hand_finger[0][1][0] < 90)
		{
			left_hand_finger[0][1][0]+=3;
			left_hand_finger[0][1][1] = 0;
			left_hand_finger[0][1][2] = 0;
			left_hand_finger[0][1][3] = 1;
		}


		for (int i = 1; i < 5; i++)
			for (int j = 0; j < 3; j++)
				if (right_hand_finger[i][j][0] < 90)
				{
					right_hand_finger[i][j][0]+=3;
					right_hand_finger[i][j][1] = 0;
					right_hand_finger[i][j][2] = -1;
					right_hand_finger[i][j][3] = 0;
				}

		if (right_hand_finger[0][0][0] < 90)
		{
			right_hand_finger[0][0][0]+=3;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][0][0] < 90)
		{
			right_hand_finger[0][0][0]+=3;
			right_hand_finger[0][0][1] = 0;
			right_hand_finger[0][0][2] = -1;
			right_hand_finger[0][0][3] = 0;
		}

		if (right_hand_finger[0][1][0] < 90)
		{
			right_hand_finger[0][1][0]+=3;
			right_hand_finger[0][1][1] = 0;
			right_hand_finger[0][1][2] = 0;
			right_hand_finger[0][1][3] = -1;
		}
#pragma endregion

		if (left2_two[0] > -45)
			left2_two[0]--;
		left2_two[1] = 0;
		left2_two[2] = 0;
		left2_two[3] = 1;


		if (right2_two[0] > -45)
			right2_two[0]--;
		right2_two[1] = 0;
		right2_two[2] = 0;
		right2_two[3] = -1;




		if (left_two[0] < 30)
			left_two[0]++;
		left_two[1] = 0;
		left_two[2] = 1;
		left_two[3] = 0;


		if (right_two[0] < 30)
			right_two[0]++;
		right_two[1] = 0;
		right_two[2] = -1;
		right_two[3] = 0;

		if (left_hand[0][0] > 30)
			left_hand[0][0]--;
		if (right_hand[0][0] < -30)
			right_hand[0][0]++;

		if (right_hand[2][0] > 0)
			right_hand[2][0]-=2;
		right_hand[2][1] = 1;
		right_hand[2][2] = 0;
		right_hand[2][3] = 0;

		if (left_hand[2][0] > 0)
			left_hand[2][0]-=2;
		left_hand[2][1] = 1;
		left_hand[2][2] = 0;
		left_hand[2][3] = 0;


		if (right_hand[1][0] < 135)
			right_hand[1][0]+=2;
		right_hand[1][1] = 0;
		right_hand[1][2] = -1;
		right_hand[1][3] = 0;

		if (left_hand[1][0] < 135)
			left_hand[1][0] += 2;
		else
			step = 1;
		left_hand[1][1] = 0;
		left_hand[1][2] = 1;
		left_hand[1][3] = 0;

		break;
	case 1:
		if (left2_two[0] < 30)
			left2_two[0]+=2;
		left2_two[1] = 0;
		left2_two[2] = 0;
		left2_two[3] = 1;

		if (right2_two[0] < 30)
			right2_two[0]+=2;
		else
			step = 2;

		right2_two[1] = 0;
		right2_two[2] = 0;
		right2_two[3] = -1;
		break;
	case 2:
		if (left2_two[0] > -45)
			left2_two[0]-=1.5;
		left2_two[1] = 0;
		left2_two[2] = 0;
		left2_two[3] = 1;

		if (right2_two[0] > -45)
			right2_two[0]-=1.5;
		else
			step = 3;
		right2_two[1] = 0;
		right2_two[2] = 0;
		right2_two[3] = -1;
		break;
	case 3:
		if (left2_two[0] < 30)
			left2_two[0]+=2;
		left2_two[1] = 0;
		left2_two[2] = 0;
		left2_two[3] = 1;

		if (right2_two[0] < 30)
			right2_two[0]+=2;
		right2_two[1] = 0;
		right2_two[2] = 0;
		right2_two[3] = -1;

		switch (step2)
		{
		case 0:
			break;
		case 1:
#pragma region Paper
			for (int i = 1; i < 5; i++)
				for (int j = 0; j < 3; j++)
					if (left_hand_finger[i][j][0] > 0)
					{
						left_hand_finger[i][j][0] -= 3;
						left_hand_finger[i][j][1] = 0;
						left_hand_finger[i][j][2] = 1;
						left_hand_finger[i][j][3] = 0;
					}

			if (left_hand_finger[0][0][0] > 0)
			{
				left_hand_finger[0][0][0] -= 3;
				left_hand_finger[0][0][1] = 0;
				left_hand_finger[0][0][2] = 1;
				left_hand_finger[0][0][3] = 0;
			}

			if (left_hand_finger[0][0][0] > 0)
			{
				left_hand_finger[0][0][0] -= 3;
				left_hand_finger[0][0][1] = 0;
				left_hand_finger[0][0][2] = 1;
				left_hand_finger[0][0][3] = 0;
			}

			if (left_hand_finger[0][1][0] > 0)
			{
				left_hand_finger[0][1][0] -= 3;
				left_hand_finger[0][1][1] = 0;
				left_hand_finger[0][1][2] = 0;
				left_hand_finger[0][1][3] = 1;
			}
#pragma endregion

			break;
		case 2:
#pragma region Scissor
			if (v == 0)
			{
				for (int j = 0; j < 3; j++)
					if (left_hand_finger[1][j][0] > 0)
					{
						left_hand_finger[1][j][0] -= 3;
						left_hand_finger[1][j][1] = 0;
						left_hand_finger[1][j][2] = 1;
						left_hand_finger[1][j][3] = 0;
					}
			}
			else if (left_hand_finger[1][0][0] < 9)
			{
				left_hand_finger[1][0][0] += 3;
				left_hand_finger[1][0][1] = 0;
				left_hand_finger[1][0][2] = 0;
				left_hand_finger[1][0][3] = -1;
			}


			if (v == 0)
			{
				for (int j = 0; j < 3; j++)
					if (left_hand_finger[2][j][0] > 0)
					{
						left_hand_finger[2][j][0] -= 3;
						left_hand_finger[2][j][1] = 0;
						left_hand_finger[2][j][2] = 1;
						left_hand_finger[2][j][3] = 0;
					}
				if (left_hand_finger[2][2][0] <= 0)
					v = 1;
			}
			else if (left_hand_finger[2][0][0] < 9)
				{
					left_hand_finger[2][0][0] += 3;
					left_hand_finger[2][0][1] = 0;
					left_hand_finger[2][0][2] = 0;
					left_hand_finger[2][0][3] = 1;
				}

#pragma endregion
			break;
		}

		switch (step3)
		{
		case 0:
			break;
		case 1:
#pragma region Paper

			for (int i = 1; i < 5; i++)
				for (int j = 0; j < 3; j++)
					if (right_hand_finger[i][j][0] > 0)
					{
						right_hand_finger[i][j][0] -= 3;
						right_hand_finger[i][j][1] = 0;
						right_hand_finger[i][j][2] = -1;
						right_hand_finger[i][j][3] = 0;
					}

			if (right_hand_finger[0][0][0] > 0)
			{
				right_hand_finger[0][0][0] -= 3;
				right_hand_finger[0][0][1] = 0;
				right_hand_finger[0][0][2] = -1;
				right_hand_finger[0][0][3] = 0;
			}

			if (right_hand_finger[0][0][0] > 0)
			{
				right_hand_finger[0][0][0] -= 3;
				right_hand_finger[0][0][1] = 0;
				right_hand_finger[0][0][2] = -1;
				right_hand_finger[0][0][3] = 0;
			}

			if (right_hand_finger[0][1][0] > 0)
			{
				right_hand_finger[0][1][0] -= 3;
				right_hand_finger[0][1][1] = 0;
				right_hand_finger[0][1][2] = 0;
				right_hand_finger[0][1][3] = -1;
			}
#pragma endregion
			break;
		case 2:
#pragma region Scissor
			if (v == 0)
			{
				for (int j = 0; j < 3; j++)
					if (right_hand_finger[1][j][0] > 0)
					{
						right_hand_finger[1][j][0] -= 3;
						right_hand_finger[1][j][1] = 0;
						right_hand_finger[1][j][2] = -1;
						right_hand_finger[1][j][3] = 0;
					}
			}
			else if (right_hand_finger[1][0][0] < 9)
			{
				right_hand_finger[1][0][0] += 3;
				right_hand_finger[1][0][1] = 0;
				right_hand_finger[1][0][2] = 0;
				right_hand_finger[1][0][3] = 1;
			}

			if (v == 0)
			{
				for (int j = 0; j < 3; j++)
					if (right_hand_finger[2][j][0] > 0)
					{
						right_hand_finger[2][j][0] -= 3;
						right_hand_finger[2][j][1] = 0;
						right_hand_finger[2][j][2] = -1;
						right_hand_finger[2][j][3] = 0;
					}
				if (right_hand_finger[2][2][0] <= 0)
					v = 1;
			}
			else if (right_hand_finger[2][0][0] < 9)
			{
				right_hand_finger[2][0][0] += 3;
				right_hand_finger[2][0][1] = 0;
				right_hand_finger[2][0][2] = 0;
				right_hand_finger[2][0][3] = -1;
			}

#pragma endregion
			break;
		}
		break;
	}


}

void Swim()
{
	switch (step)
	{
	case 0:
		if (all_body[0] < 90)
			all_body[0] += 0.5;
		else
			step = 1;
		all_body[1] = 1;
		all_body[2] = 0;
		all_body[3] = 0;

		if (left_leg[2][0] < 70)
			left_leg[2][0]++;
		left_leg[2][1] = 1;
		left_leg[2][2] = 0;
		left_leg[2][3] = 0;

		if (right_leg[2][0] < 70)
			right_leg[2][0]++;
		right_leg[2][1] = 1;
		right_leg[2][2] = 0;
		right_leg[2][3] = 0;
		
		if (left_hand[0][0] > -90)
			left_hand[0][0]--;
		left_hand[0][1] = 0;
		left_hand[0][2] = 0;
		left_hand[0][3] = 1;
		if (right_hand[0][0] < 90)
			right_hand[0][0]++;
		right_hand[0][1] = 0;
		right_hand[0][2] = 0;
		right_hand[0][3] = 1;

		if (left_hand[2][0] > 0)
			left_hand[2][0]--;
		left_hand[2][1] = 1;
		left_hand[2][2] = 0;
		left_hand[2][3] = 0;

		if (right_hand[2][0] > 0)
			right_hand[2][0]--;
		right_hand[2][1] = 1;
		right_hand[2][2] = 0;
		right_hand[2][3] = 0;
		break;
	case 1:
		if (left_leg[0][0] < 15 && step2 == 0)
		{
			left_leg[0][0]++;
			left_leg[0][1] = 1;
			left_leg[0][2] = 0;
			left_leg[0][3] = 0;
			right_leg[0][0]++;
			right_leg[0][1] = -1;
			right_leg[0][2] = 0;
			right_leg[0][3] = 0;
			if (left_leg[0][0] == 15)
				step2 = 1;
		}
		else if (left_leg[0][0] > -15)
		{
			left_leg[0][0]--;
			left_leg[0][1] = 1;
			left_leg[0][2] = 0;
			left_leg[0][3] = 0;
			right_leg[0][0]--;
			right_leg[0][1] = -1;
			right_leg[0][2] = 0;
			right_leg[0][3] = 0;
			if (left_leg[0][0] == -15)
				step2 = 0;
		}


		if (left_two[0] < 360)
		{
			left_two[0]++;
			left_two[1] = 0;
			left_two[2] = 1;
			left_two[3] = 0;

			if (left_two[0] < 180)
			{
				left_hand[0][0]-=0.2;
				left_hand[0][1] = 0;
				left_hand[0][2] = 0;
				left_hand[0][3] = 1;


				left_hand[1][0] -= 0.2;
				left_hand[1][1] = 0;
				left_hand[1][2] = 0;
				left_hand[1][3] = 1;
			}
			else if (left_two[0] <360)
			{
				left_hand[0][0]+=0.2;
				left_hand[0][1] = 0;
				left_hand[0][2] = 0;
				left_hand[0][3] = 1;

				if(left_hand[1][0]<0)
				left_hand[1][0] += 0.8;
				left_hand[1][1] = 0;
				left_hand[1][2] = 0;
				left_hand[1][3] = 1;
			}

			if (left_two[0] > 180 && left_two[0] < 270)
				head_r[0] += 1.3;
			else if (left_two[0] > 270 && left_two[0] < 360)
				head_r[0] -= 1.3;
			head_r[1] = 0;
			head_r[2] = -1;
			head_r[3] = 0;

			if (left_two[0] == 360)
				right_two[0] = 0;
		}
		else if (right_two[0] < 360)
		{
			right_two[0]++;
			right_two[1] = 0;
			right_two[2] = -1;
			right_two[3] = 0;

			if (right_two[0] < 180)
			{
				right_hand[0][0] += 0.2;
				right_hand[0][1] = 0;
				right_hand[0][2] = 0;
				right_hand[0][3] = 1;

				right_hand[1][0] += 0.2;
				right_hand[1][1] = 0;
				right_hand[1][2] = 0;
				right_hand[1][3] = 1;
			}
			else if (right_two[0] <360)
			{
				right_hand[0][0] -= 0.2;
				right_hand[0][1] = 0;
				right_hand[0][2] = 0;
				right_hand[0][3] = 1;

				if(right_hand[1][0]>0)
				right_hand[1][0] -= 0.8;
				right_hand[1][1] = 0;
				right_hand[1][2] = 0;
				right_hand[1][3] = 1;
			}

			if (right_two[0] > 180 && right_two[0] < 270)
				head_r[0] += 1.3;
			else if (right_two[0] > 270 && right_two[0] < 360)
				head_r[0] -= 1.3;
			head_r[1] = 0;
			head_r[2] = 1;
			head_r[3] = 0;

			if (right_two[0] == 360)
				left_two[0] = 0;
		}

		break;
	}
}

void Sit_ups()
{
	if (all_body[0] > -90)
	{
		all_body[1] = 1;
		all_body[2] = 0;
		all_body[3] = 0;

		all_body[0] --;
	}

	if (left_hand[1][0] < 95)
	{

		left_hand[1][0] ++;

		left_hand[1][1] = 0;
		left_hand[1][2] = 0;
		left_hand[1][3] = 1;

		left_two[1] = 0;
		left_two[2] = 1;
		left_two[3] = 0;
		if(left_two[0]<30)
		left_two[0] ++;
	}


	if (right_hand[1][0] < 95)
	{
		right_hand[1][0] ++;

		right_hand[1][1] = 0;
		right_hand[1][2] = 0;
		right_hand[1][3] = -1;

		right_two[1] = 0;
		right_two[2] = -1;
		right_two[3] = 0;
		if (right_two[0]<30)
		right_two[0] ++;
	}

	if (left_leg[1][0] < 90)
		left_leg[1][0] ++;
	left_leg[1][1] = 1;
	left_leg[1][2] = 0;
	left_leg[1][3] = 0;

	if (right_leg[1][0] < 90)
		right_leg[1][0] ++;
	right_leg[1][1] = 1;
	right_leg[1][2] = 0;
	right_leg[1][3] = 0;

	if (left_leg[0][0] > -45)
		left_leg[0][0] --;
	left_leg[0][1] = 1;
	left_leg[0][2] = 0;
	left_leg[0][3] = 0;

	if (right_leg[0][0] > -45)
		right_leg[0][0] --;
	right_leg[0][1] = 1;
	right_leg[0][2] = 0;
	right_leg[0][3] = 0;

	if (left_leg[2][0] < 45)
		left_leg[2][0] ++;
	left_leg[2][1] = 1;
	left_leg[2][2] = 0;
	left_leg[2][3] = 0;

	if (right_leg[2][0] < 45)
		right_leg[2][0] ++;
	right_leg[2][1] = 1;
	right_leg[2][2] = 0;
	right_leg[2][3] = 0;

	if (left_hand[1][0] == 95 && Body[0] != 70  && step2 == 0)
	{
	Body[0] += 1;
	Body[1] = 1;
	Body[2] = 0;
	Body[3] = 0;
	if (Body[0] == 70)
	step2 = 1;
	}

	if (left_hand[1][0] == 95 && Body[0] != 0 && step2 == 1)
	{
	Body[0] -= 1;
	Body[1] = 1;
	Body[2] = 0;
	Body[3] = 0;
	if (Body[0] == 0)
	step2 = 0;
	}
}

int s = 0;
void keyin(unsigned char key, int x, int y)
{
	if (state != 1) 
	{
		action = 0;
		standby();
	}

	switch (key)
	{
	case '+':
		s += 2;
		break;
	case '-':
		if(s>-4)
		s -= 2;
		break;
	case 'w':
		rr += 3;
		break;
	case 's':
		rr -= 3;
		break;
	case 'd':
		rrr += 3;
		break;
	case 'a':
		rrr -= 3;
		break;
	}
}

void timerFunction(int value)
{
	switch (action)
	{
	case 0:
		standby();
		break;
	case 1:
		walk();
		break;
	case 2:
		Inverted();
		break;
	case 3:
		ChangeColor();
		break;
	case 4:
		AttackBall();
		break;
	case 5:
		DefenceBall();
		break;
	case 6:
		axe_walk();
		break;
	case 7:
		Rotate_fly();
		break;
	case 8:
		Mora();
		break;
	case 9:
		Swim();
		break;
	case 10:
		Sit_ups();
		break;
	
	}
	glutPostRedisplay();
	glutTimerFunc(5+s, timerFunction, 1);
}

void ProcessMenu(int value)
{
	switch (value)
	{
	case 0:
		standby();
		action = 0;
		break;
	case 1:
		standby();
		action = 1;
		break;
	case 2:
		standby();
		action = 2;
		break;
	case 3:
		standby();
		action = 3;
		break;
	case 4:
		standby();
		action = 4;
		break;
	case 5:
		standby();
		action = 5;
		break;
	case 6:
		standby();
		action = 6;
		break;
	case 7:
		standby();
		action = 7;
		break;
	case 8:
		standby();
		step2 = rand() % 3;
		step3 = rand() % 3;
		action = 8;
		break;
	case 9:
		standby();
		action = 9;
		break;
	case 10:
		standby();
		action = 10;
		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	int main_menu, action_menu, count_menu;
	srand((unsigned)time(NULL));

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			bodycolor[i][j] = rand() % 255;
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);


	glutInitWindowSize(800,800);	//< Dual view
	//glutInitWindowSize(WinWidth, WinHeight);	//< Single view:600,600

	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);

	init();
	standby();


#pragma region MENU
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Standby", 0);
	glutAddMenuEntry("Walk", 1);
	glutAddMenuEntry("Inverted", 2);
	glutAddMenuEntry("ChangeColor", 3);
	glutAddMenuEntry("AttackBall", 4);
	glutAddMenuEntry("DefenceBall", 5);
	glutAddMenuEntry("Axe_walk", 6);
	glutAddMenuEntry("Rotate_fly", 7);
	glutAddMenuEntry("Mora", 8);
	glutAddMenuEntry("Swim", 9);
	glutAddMenuEntry("Sit - ups", 10);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
#pragma endregion




	glutKeyboardFunc(keyin);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutTimerFunc(5, timerFunction, 1);
	glutMainLoop();
	return 0;

}