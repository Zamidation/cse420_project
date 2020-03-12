//icos_subdivide.cpp
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "SDL2/SDL.h"
#include <math.h>
#include <iostream>
#include <map>

//using namespace std;

#define PI 3.1416926

#define X .525731112119133606
#define Z .850650808352039932


float t = 1;
float ay = 0;   // rotation angle about y-axis
bool translate = false;

float a = 0;
float b = 0;
float c = 0;

void light_switch(int n);

void diffuse_color(GLfloat d[4], int p = 10)
{
  glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
}

void diffuse_color(float x = 1.0, float y = 1.0, float z = 0.0, float a = 0.5, int p = 10)
{
  //
  GLfloat diffuseMaterial[4] = { x, y, z, a };
  diffuse_color(diffuseMaterial, p);
  // glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  // glMaterialf(GL_FRONT, GL_SHININESS, 175.0);
}

void init(void)
{

   // GLfloat mat_specular[] = {1.0,1.0,1.0,1.0 };

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.5 };
   GLfloat light[] = //{ 1.0, 1.0, 1.0};
                     { .5, .5, .5};
   GLfloat light1[] = //{ 0.5, 0.5, 0.5};
                     { .25, .25, .25 };
   GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { -1.0, -1.0, -1.0, 0.0 };
   GLfloat light_position2[] = { 0.0, 0.0, 0.0, 1.0 };
   // GLfloat diffuseMaterial[4] = { 1, 1, 1, 1.0 };
   GLfloat diffuseMaterial[4] = { 0.9, 0.9, 0.0, 0.5 };

   // glClearColor (0.5, 0.5, 0.2, 0.0);

   glClearColor(0.0,0.0,0.0,0.0); // background color

   glShadeModel (GL_SMOOTH);

   glEnable(GL_DEPTH_TEST);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 175.0);

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT0, GL_AMBIENT, light );
   glLightfv(GL_LIGHT0, GL_SPECULAR, light );

   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1 );
   glLightfv(GL_LIGHT1, GL_AMBIENT, light1 );
   glLightfv(GL_LIGHT1, GL_SPECULAR, light1 );

   glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT2, GL_AMBIENT, light );
   glLightfv(GL_LIGHT2, GL_SPECULAR, light );

   // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   glEnable(GL_LIGHTING);

   light_switch(0);
   // glEnable(GL_LIGHT0);
   light_switch(1);
   // glEnable(GL_LIGHT1);
   light_switch(2);

   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   // glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100 );

   glOrtho(-5.0, 15.0, -5.0, 5.0, .1, 50);
   // glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 50 );
}

void personModel()
{
  // glTranslatef (1.0, 0.0, 0.0);
  // glRotatef(0, 1, 0, 0);
  // glTranslatef (-1.0, 0.0, 0.0);
  glPushMatrix();
  glTranslatef (0.0, 0.0, 2.0);//position (center) body
  glPushMatrix();//head
  // glPushMatrix();//left arm
  // glPushMatrix();//right arm
  // glPushMatrix();//left leg
  // glPushMatrix();//right leg
  glScalef(0.5, 1.5, 1.0);
  glutWireCube(1);
  glPopMatrix();
  glTranslatef(0.0, 1.0, 0.0);
  glScalef(0.5,0.5,0.5);
  glutWireCube(1);

  //CONTINUE HERE
  glPopMatrix();
}

static int count = 0;
void model(int model_number, int p = 9)
{
   switch (model_number)
   {
      case 0:
         glutWireCube(1.0);
         // glutSolidCone(1,1,10,10);
         break;
      case 1:

         glutSolidSphere(0.5,100,50);
         break;
      case 2:
         glBegin(GL_POLYGON);

            glVertex2f(0,0);
            glVertex2f(1,0);
            glVertex2f(1,1);
            glVertex2f(0,1);
         glEnd();

      default:
         break;
   }
   if (p == count){
      // glDisable(GL_LIGHT1);
      glPushMatrix();
      glTranslatef(0, 2.5 + .5*sin(ay) ,0);
      glScalef(.25,.50,.25);
      glRotatef(90,1,0,0);
      glutSolidCone(1,2,10,10);
      glPopMatrix();
      // glEnable(GL_LIGHT1);
   }
}

void CounterN()
{
   count = (count + 1) % 9;
}
void CounterB()
{
   if (count == 0)
      count = 9;
   count--;
}

float position[4] = {0,0,0,1};

float year_data[10] =   {0, 365/87.97, 365/224.7, 365/365, 1/1.88, 1/11.86  , 1/29.46  , 1/84.01  , 1/164.79 };
float day_data[10] =    {0, 58.6     , 243      , 1      , 1.03, 0.41   , 0.45   , 0.72   , 0.67   };

void planet(int model_number, float day_revolution, int p = 9)
{
   // glPushMatrix();
   glRotatef(ay * day_revolution,0,1,0);
   model(model_number, p);
   
   // glPopMatrix();
}

int lss[] = { GL_LIGHT0, GL_LIGHT1, GL_LIGHT2, GL_LIGHT3, GL_LIGHT4, GL_LIGHT5, GL_LIGHT6, GL_LIGHT7};
bool lsb[] = { false, false, false, false, false, false, false, false };
void light_switch(int n)
{
   if(lsb[n] == true)
   {
      lsb[n] = false;
      glDisable(lss[n]);
   }
   else
   {
      lsb[n] = true;
      glEnable(lss[n]);
   }
}

static bool onetime = false;

float distance = 5;

// GLfloat m
static bool u, d, l, r = false;
// static bool u = false, d = false, l = false, r = false;
void display(void)
{
   // gluPerspective()
   glMatrixMode(GL_PROJECTION); // position and aim the camera
   // glMatrixMode(GL_MODELVIEW);

   int p = 0;

   // glFrustum ()

   // glFrustum (-1.0, 1.0, -1.0, -1.0, 1, 50.0);

   // glTranslatef(0.0,1.0,-10.0);
   glLoadIdentity();

   gluPerspective(45,2, .01, 550);

   // if(u == false || d == false || l == false || r == false){
   //    t = 0.0;
   // }else{
   //    u = false;
   //    d = false;
   //    l = false;
   //    r = false;
   // }

   glTranslatef(a, b,-20+c);

   glRotatef(45,1,0,0);

   // gluLookAt(a, b, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   // gluLookAt(a, b, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // personModel();
   // glFlush();
   // return;

   // glColor3f ( 1, 0, 0 );	//This would have no effect
   glEnable( GL_CULL_FACE );
   glCullFace ( GL_BACK );

   int models = 1;
   if ( translate )
   {
      models = 0;
   }

   // diffuse_color(1.0, 0.0, 1.0, 0.5, 0);

   // glRotatef ( ay, 0, 1, 0 ); // spin of sun

   glPushMatrix();

   glScalef(10, 10, 10);

   glPushMatrix();   // Neptune Orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01,17.5,100,100);
   glPopMatrix();

   glPushMatrix();   // Uranus Orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01,15,100,100);
   glPopMatrix();

   glPushMatrix();   // Saturn Orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01,12.5,100,100);
   glPopMatrix();

   glPushMatrix();   // Jupiter orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01,10,100,100);
   glPopMatrix();

   glPushMatrix();   // Mars orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005,4,100,100);
   glPopMatrix();

   glPushMatrix();   // Earth orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005,3,100,100);
   glPopMatrix();

   glPushMatrix();   // Venus orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005,2,100,100);
   glPopMatrix();

   glPushMatrix();   // Mercury orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005,1,100,100);
   glPopMatrix();

   planet(models, day_data[8-p], p);   // sun
   glPopMatrix();

//-------------------------------------
if(onetime == false){
  onetime = true;
  float m[4][4];
  glGetFloatv(GL_PROJECTION, &m[0][0]);
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      std::cout << m[i][j] << "\t";
    }
    std::cout << std::endl;
  }
}
//-------------------------------------

   glFlush();

   // diffuse_color();

   p++;

   glPushMatrix();   // Mercury
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(2 * distance,0,0);
   glScalef(.38,.38,.38);
   planet(models, day_data[p], p);
   glPopMatrix();


   p++;

   glPushMatrix();   // Venus
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(4 * distance,0,0);
   glScalef(.95, .95, .95);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();

   glRotatef(ay* year_data[p], 0,1,0);

   glTranslatef ( 6 * distance, 0, 0 );
   // glScalef(.5,.5,.5);

   // glPushMatrix();
   // glRotatef(10*ay,1,0,0);
   // glRotatef(-ay,0,1,0);
   // model(2);
   // glPopMatrix();

   // diffuse_color(0, 0.7, 0.0, 0.0, 0.5);

   planet(models, day_data[p], p);    // earth

   glTranslatef (2, 0, 0 );
   // glScalef(.25,.25,.25);
   glScalef(.5,.5,.5);

   planet(models, 1); // moon

   //p++;

   glTranslatef (2, 0, 0 );
   glScalef(.5,.5,.5);

   planet(models, 10);  // moon of moon

   glPopMatrix();
   glPopMatrix();

   // diffuse_color();

   p++;

   //p++;



   glPushMatrix();   // Mars
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(8 * distance,0,0);
   glScalef(.53,.53,.53);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Jupiter
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(20 * distance,0,0);
   glScalef(11.2,11.2,11.2);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Saturn
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(25 * distance,0,0);
   glScalef(9.45,9.45,9.45);

   glPushMatrix();
   glScalef(1,.01,1);
   glRotatef(90, 1,0,0);
   glutSolidTorus(.175,1,50,50);
   glPopMatrix();

   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Uranus
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(30 * distance,0,0);
   glScalef(4.0,4.0,4.0);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Neptune
   glRotatef(ay * year_data[p], 0,1,0);
   glTranslatef(35 * distance,0,0);
   glScalef(3.88,3.88,3.88);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glFlush();
   //   SDL_Delay ( 500 );
}

void Smooth_Trantitions(float &number)
{
   if (number < 1)
      number += .05;
   else
      number = 1;
}

void KeyUp(unsigned char key, int x, int y)
{
   // keys.keyUp(key);
   if (key == GLUT_KEY_UP)
      std::cout << "I am unclicked\n";
}

void SpecialInput(int key, int x, int y)
{
   switch ( key )
   {
      case GLUT_KEY_UP:
         Smooth_Trantitions(t);
         c += t;
         u = true;
         std::cout << t << std::endl;
         break;
      case GLUT_KEY_DOWN:
         Smooth_Trantitions(t);
         c -= t;
         d = true;
         break;
      case GLUT_KEY_RIGHT:
         Smooth_Trantitions(t);
         a -= t;
         r = true;
         break;
      case GLUT_KEY_LEFT:
         Smooth_Trantitions(t);
         a += t;
         l = true;
         break;
      default:
         std::cout << "no special key\n";
         break;
   }
   glutPostRedisplay();
}

void keyboard ( unsigned char key, int mousex, int mousey )
{
   switch ( key ) {
      case 27:       // escape
         exit ( -1 );
      case 't':
         if ( translate )
            translate = false;
         else
            translate = true;
         break;
      case 'p':
         Smooth_Trantitions(t);
         b -= t;
         break;
      case 'l':
         Smooth_Trantitions(t);
         b += t;
         break;
      case '0':
         light_switch(0);
         break;
      case '1':
         light_switch(1);
         break;
      case '2':
         light_switch(2);
         break;
      case '3':
         light_switch(3);
         break;
      case '4':
         light_switch(4);
         break;
      case '5':
         light_switch(5);
         break;
      case '6':
         light_switch(6);
         break;
      case '7':
         light_switch(7);
         break;
      // case '2':
      //    light_switch2();
      //    break;
      case 'n':
      case 'N':
         CounterN();
         break;
      case 'b':
      case 'B':
         CounterB();
         break;
   }
   glutPostRedisplay();
}

void animate()
{
   if (t > 1)
      t = 1;
   if ( ay > 360 )
      ay = 0;
   else
      ay += .25;
  glutPostRedisplay ();
}

void timerHandle ( int value )
{
   animate();
   glutPostRedisplay();
   glutTimerFunc ( 50, timerHandle, 0 );
}

void visHandle( int visible )
{
   if (visible == GLUT_VISIBLE)
      timerHandle ( 0 );
   else;
}

void ending(){
   //
}
