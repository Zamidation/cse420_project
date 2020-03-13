/*****************
 * Programmers: Mike Cheng-Godinez, Montana Williams
 * Date: March 12, 2020
 * Description:
 *
 * This is a model of the Solar System
 * using Opengl and SDL2. This program needs to be built
 * with 'main.cpp' and 'makefile'. This models the Solar System
 * with the planets Mercury, Venus, Earth, Mars, Jupiter, Saturn,
 * Uranus, and Neptune revolving around the sun. The model is correct
 * in physical scales, except the sun, with the reference radius being Earth.
 *
 * Distances from the sun are not physically correct, but for the sake of the model,
 * they are drawn closer to see the planets.
 *
 * To compile and run this program, simply type 'make solar_system'
 * into your terminal of choice.
 *
 * Controls:
 *    =/-         Increases/Decreases the revolution rate
 *    w/s         Increases/Decreases camera into y-axis
 *    UP/DOWN     Increases/Decreases camera into z-axis
 *    RIGHT/LEFT  Increases/Decreases camera into x-axis
 *    t           Toggles the models to wire cubes. Used to see day rotations
 *    p           Toggles the revolution player
 *    b/n         Moves the selector across different planets
 *    0-9         Toggles lights 0-9
 *
 *****************/

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


float t = 0;
float time_multiplier = .1;
float time_variable = 0;   // rotation angle about y-axis
bool translate = false;

float a = 0;
float b = 0;
float c = 0;

float distance = 5;

void light_switch(int n);
// void light_color(GLfloat lc[4], int light = 10);
// void light_color(float r, float g, float b, float vp, int light = 10);

void diffuse_color(GLfloat d[4], int p = 10)
{
   // GLfloat s[4] = {1.0, 1.0, 1.0, 0.5};
   // glMaterialfv(GL_FRONT, GL_DIFFUSE, d);
   // glMaterialfv(GL_FRONT, GL_SPECULAR, s);
   // glMaterialf(GL_FRONT, GL_SHININESS, 175.0);

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
   GLfloat light2[] = //{ 0.5, 0.5, 0.5};
                     { .25, .25, .25 };
   GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { -1.0, -1.0, -1.0, 0.0 };
   GLfloat light_position2[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat diffuseMaterial[4] = { 1, 1, 0, 0.0 };
   // GLfloat diffuseMaterial[4] = { 1.0, 1.0, 0.0, 0.5 };

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

   glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light1 );
   glLightfv(GL_LIGHT1, GL_AMBIENT, light1 );
   glLightfv(GL_LIGHT1, GL_SPECULAR, light1 );

   glLightfv(GL_LIGHT2, GL_POSITION, light_position2);
   glLightfv(GL_LIGHT2, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT2, GL_AMBIENT, light );
   glLightfv(GL_LIGHT2, GL_SPECULAR, light );

   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

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


float larm = 0, rarm = 0, lleg = -30, rleg = -30,
      udneck = 0, lrneck = 0;
int tweenl = 9, tweenr = -9, tweenll = 9, tweenlr = -9,
    tweennlr = 9, tweennud = 9;

void personModel()
{
  // glTranslatef (1.0, 0.0, 0.0);
  // glRotatef(0, 1, 0, 0);
  // glTranslatef (-1.0, 0.0, 0.0);
  glPushMatrix();//1
  glScalef(.25,.25,.25);
  // glTranslatef (0.0, 0.0, 2.0);//position (center) body
    glPushMatrix();//2head
    glPushMatrix();//3left arm
    glPushMatrix();//4right arm
    glPushMatrix();//5left leg
    glPushMatrix();//6right leg
  glScalef(0.5, 1.5, 1.0);
  glutSolidCube(1);              //body
    glPopMatrix();//6
  glTranslatef(0.0, 0.8, 0.0);//neck
  if(lrneck > 45 || lrneck < -45)
    tweennlr = -tweennlr;
  lrneck += tweennlr;
  glRotatef(lrneck, 0, 1, 0);
    glPushMatrix();
  glScalef(0.4,0.1,0.4);
  glutSolidCube(1);            //neck
    glPopMatrix();
  glTranslatef(-0.05, 0.3, 0.0);
  glTranslatef(0.25, -0.25, 0.0);
  if(udneck > 0 || udneck < -22.5)
    tweennud = -tweennud;
  udneck += tweennud;
  glRotatef(udneck, 0, 0, 1);
  glTranslatef(-0.25, 0.25, 0.0);
  glScalef(0.5,0.5,0.5);
  glutSolidCube(1);              //head

    glPopMatrix();//5
  // glPopMatrix();
                              //left arm 1

  glTranslatef(0.0, 0.75, 0.625);
  if(larm > 60 || larm < -60)
    tweenl = -tweenl;
  larm += tweenl;
  glRotatef(larm, 0, 0, 1);
  glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();//7
  glScalef(0.25, 1.0, 0.25);
  glutSolidCube(1);            //left arm 1
    glPopMatrix();//7
  glTranslatef(-0.4, -0.4, 0.0);//left arm 2
  glScalef(1.0, 0.2, 0.2);
  glutSolidCube(1);           //left arm 2

    glPopMatrix();//4

                              //right arm 1
  glTranslatef(0.0, 0.75, -0.625);
  if(rarm > 60 || rarm < -60)
    tweenr = -tweenr;
  rarm += tweenr;
  glRotatef(rarm, 0, 0, 1);
  glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();//8
  glScalef(0.25, 1.0, 0.25);
  glutSolidCube(1);              //right arm 1
    glPopMatrix();//8
  glTranslatef(-0.4, -0.4, 0.0);//right arm 2
  glScalef(1.0, 0.2, 0.2);
  glutSolidCube(1);             //right arm 2

    glPopMatrix();//3

                              //left leg 1
  glTranslatef(0.0, -0.75, -0.35);
  if(lleg > 30 || lleg < -90)
    tweenll = -tweenll;
//   std::cout << "before:" << lleg << std::endl;
  lleg += tweenll;
//   std::cout << "after:" << lleg << std::endl;
  // glRotatef(-30, 0, 0, 1);
  glRotatef(lleg, 0, 0, 1);
  glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();//9
  glScalef(0.25, 1.0, 0.25);
  glutSolidCube(1);              //left leg 1
    glPopMatrix();//9
  glTranslatef(0.4, -0.4, 0.0);//left leg 2
  glScalef(1.0, 0.2, 0.2);
  glutSolidCube(1);             //left leg 2

    glPopMatrix();//2

                              //right leg 1
  glTranslatef(0.0, -0.75, 0.35);
  if(rleg > 30 || rleg < -90)
    tweenlr = -tweenlr;
//   std::cout << "before:" << lleg << std::endl;
  rleg += tweenlr;
//   std::cout << "after:" << lleg << std::endl;
  // glRotatef(-30, 0, 0, 1);
  glRotatef(rleg, 0, 0, 1);
  glTranslatef(0.0, -0.5, 0.0);
    glPushMatrix();//10
  glScalef(0.25, 1.0, 0.25);
  glutSolidCube(1);              //right leg 1
    glPopMatrix();//10
  glTranslatef(0.4, -0.4, 0.0);//right leg 2
  glScalef(1.0, 0.2, 0.2);
  glutSolidCube(1);             //right leg 2

   //  glPopMatrix();//1

  //CONTINUE HERE
  glPopMatrix();//1
}

float scale_data[10] =  {10, .38      , .95      , 1      , .53       , 11.2      , 9.45      , 4.0       , 3.88     };
float year_data[10] =   {0 , 365/87.97, 365/224.7, 365/365, 1/1.88    , 1/11.86   , 1/29.46   , 1/84.01   , 1/164.79 };
float day_data[10] =    {0 , 58.6     , 243      , 365    , 1.03*365  , 0.41*365  , 0.45* 365 , 0.72 * 365, 0.67*365 };


static int count = 0;
void model(int model_number, int p = 10)
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
         // glBegin(GL_POLYGON);

         //    glVertex2f(0,0);
         //    glVertex2f(1,0);
         //    glVertex2f(1,1);
         //    glVertex2f(0,1);
         // glEnd();

         personModel();

      default:
         break;
   }
   if (p == count){
      // glDisable(GL_LIGHT1);
      glPushMatrix();

      glTranslatef(0, 2.5 + .5*sin(time_variable/time_multiplier) ,0);
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

void planet(int model_number, float day_revolution, int p = 9)
{
   // glPushMatrix();
   glRotatef(time_variable* day_revolution,0,1,0);
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

void light_color(GLfloat lc[4], int light = 10){
   // glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   if(light == 10)
    return;
   GLfloat position[4] = {0, 0, 0, 0};
   glLightfv(lss[light], GL_POSITION, position);
   glLightfv(lss[light], GL_DIFFUSE, lc );
   glLightfv(lss[light], GL_AMBIENT, lc );
   glLightfv(lss[light], GL_SPECULAR, lc );
}
void light_color(float r, float g, float b, float vp, int light = 10){
  GLfloat lightColor[4] = {r, g, b, vp};
  light_color(lightColor, light);
}

static bool onetime = false;

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

   gluPerspective(45,2, .01, 1000);

   // if(u == false || d == false || l == false || r == false){
   //    t = 0.0;
   // }else{
   //    u = false;
   //    d = false;
   //    l = false;
   //    r = false;
   // }

   glTranslatef(a, b,-50+c);

   glRotatef(20,1,0,0);

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



   // glRotatef ( time_variable, 0, 1, 0 ); // spin of sun

   glPushMatrix();

   glScalef(scale_data[p], scale_data[p], scale_data[p]);
   // glScalef(distance * scale_data[p], distance * scale_data[p], distance * scale_data[p]);

   glPushMatrix();   // Neptune Orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01*distance/5,17.5*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Uranus Orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01*distance/5,15*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Saturn Orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01*distance/5,12.5*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Jupiter orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.01*distance/5,10*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Mars orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005*distance/5,4*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Earth orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005*distance/5,3*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Venus orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005*distance/5,2*distance/5,100,100);
   glPopMatrix();

   glPushMatrix();   // Mercury orbit
   glRotatef(90,1,0,0);
   glutSolidTorus(.005*distance/5,distance/5,100,100);
   glPopMatrix();

   // glRotatef ( time_variable, 0, 1, 0 ); // spin of sun

   // glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   diffuse_color(0.0, 0.5, 0.7, 0.5);
   light_switch(2);
   planet(models, day_data[p], p);   // sun
   // diffuse_color(1.0, 0.0, 1.0, 0.5, 0);
   glPopMatrix();
   light_switch(2);
   diffuse_color();

//-------------------------------------
// if(onetime == false){
//   onetime = true;
//   float m[4][4];
//   glGetFloatv(GL_PROJECTION, &m[0][0]);
//   for(int i = 0; i < 4; i++){
//     for(int j = 0; j < 4; j++){
//       std::cout << m[i][j] << "\t";
//     }
//     std::cout << std::endl;
//   }
// }
//-------------------------------------

   glFlush();

   // diffuse_color();

   p++;

   light_color(1.0,0.0,0.0, 0);
   light_color(1.0,0.0,0.0, 1);
   light_color(1.0,0.0,0.0, 2);

   glPushMatrix();   // Mercury
   glRotatef(time_variable * year_data[p]+26, 0,1,0);
   glTranslatef(2 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   planet(models, day_data[p], p);
   glPopMatrix();

   // light_color(1.0,1.0,1.0, 0);
   // light_color(1.0,0.0,0.0, 1);
   // light_color(1.0,0.0,0.0, 2);


   p++;

   glPushMatrix();   // Venus
   glRotatef(time_variable * year_data[p]+70, 0,1,0);
   glTranslatef(4 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;

   glPushMatrix();

   glRotatef(time_variable* year_data[p], 0,1,0);

   glTranslatef ( 6 * distance, 0, 0 );
   // glScalef(.5,.5,.5);

   glPushMatrix();

   glRotatef(10 * time_variable,0,0,1);
   glTranslatef(0, 1 ,0);
   model(2);

   glPopMatrix();

   // diffuse_color(0, 0.7, 0.0, 0.0, 0.5);

   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);

   planet(models, day_data[p], p);    // earth

   glTranslatef (2, 0, 0 );
   // glScalef(.25,.25,.25);
   glScalef(.5,.5,.5);

   planet(models, 1); // moon

   //p++;

   // glTranslatef (2, 0, 0 );
   // glScalef(.5,.5,.5);

   // planet(models, 10);  // moon of moon

   glPopMatrix();
   glPopMatrix();

   // diffuse_color();

   p++;

   //p++;


   glPushMatrix();   // Mars
   glRotatef(time_variable * year_data[p] - 42, 0,1,0);
   glTranslatef(8 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Jupiter
   glRotatef(time_variable * year_data[p] + 153, 0,1,0);
   glTranslatef(20 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Saturn
   glRotatef(time_variable * year_data[p] + 90, 0,1,0);
   glTranslatef(25 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);

   glPushMatrix();
   glScalef(1,.01,1);
   glRotatef(90, 1,0,0);
   glutSolidTorus(.175,1,50,50);
   glPopMatrix();

   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Uranus
   glRotatef(time_variable * year_data[p] - 120, 0,1,0);
   glTranslatef(30 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glPushMatrix();   // Neptune
   glRotatef(time_variable * year_data[p] - 135, 0,1,0);
   glTranslatef(35 * distance,0,0);
   glScalef(distance/5 * scale_data[p], distance/5 * scale_data[p], distance/5 * scale_data[p]);
   glColor3f(123/255, 165/255 , 165/255);
   planet(models, day_data[p], p);
   glPopMatrix();

   p++;


   glFlush();
   //   SDL_Delay ( 500 );
}

void Smooth_Trantitions(float &number)
{
   if (number < 4)
      number += .05;
   else
      number = 4;
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

int temp = 0;
bool paused = false;

void keyboard ( unsigned char key, int mousex, int mousey )
{
   switch ( key ) {
      case 27:       // escape
         exit ( -1 );temp = time_multiplier;
      case 't':
         if ( translate )
            translate = false;
         else
            translate = true;
         break;

      case 'p':

         if (paused == false)
         {
            temp = time_multiplier;
            time_multiplier = 0;
            paused = true;
            // std::cout << paused << "\n";
         }
         else
         {
            time_multiplier = temp;
            paused = false;
            // std::cout << paused << "\n";
         }
         break;
      case 'w':
         Smooth_Trantitions(t);
         b -= t;
         break;
      case 's':
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
      case '=':
         time_multiplier += .1;
         break;
      case '-':
         time_multiplier -= .1;
         break;
   }
   glutPostRedisplay();
}

void animate()
{
   if (t > 4)
      t = 4;
   // if ( time_variable > 360  )
      // time_variable -= 360;
   else
      time_variable += .25 * time_multiplier;
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
