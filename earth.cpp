//icos_subdivide.cpp
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "SDL2/SDL.h"
#include <math.h>

#define PI 3.1416926

#define X .525731112119133606 
#define Z .850650808352039932

float ay = 0;   // rotation angle about y-axis
bool translate = false;

float a = 8;
float b = 8;
float c = 8;

void light_switch0();
void light_switch1();

void init(void)
{

   // GLfloat mat_specular[] = {1.0,1.0,1.0,1.0 };

   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.5 };
   GLfloat light[] = { .5, .5, .5};
   GLfloat light1[] = { .25, .25, .25 };
   GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 0.5 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { -1.0, -1.0, -1.0, 0.0 };
   // GLfloat diffuseMaterial[4] = { 1, 1, 1, 1.0 };
   GLfloat diffuseMaterial[4] = { 1, 1, 0, 0.5 };
                                                                         
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

   // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

   glEnable(GL_LIGHTING);

   light_switch0();
   // glEnable(GL_LIGHT0);
   light_switch1();
   // glEnable(GL_LIGHT1);
                                                                                
   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   // glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100 );

   glOrtho(-5.0, 15.0, -5.0, 5.0, .1, 50);
   // glOrtho(5.0, 5.0, 5.0, 5.0, 0.1, 100 );
}

static int count = 0;
void model(int model_number, int p = 10)
{
   switch (model_number)
   {
      case 0:
         glutWireCube(1.0);
         glutSolidCone(1,1,10,10);
         break; 
      case 1:


         glutSolidSphere(0.5,100,50);
         if (p == count){
            glPushMatrix();
            glTranslatef(0, 2.5 + .5*sin(ay) ,0);
            glScalef(.25,.50,.25);
            glRotatef(90,1,0,0);
            glutSolidCone(1,2,10,10);
            glPopMatrix();
         }
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
}

void CounterN()
{
   count = (count + 1) % 9;
}
void CounterB()
{
   if (count == 0)
      count = 8;
   count--;
}



void planet(int model_number, float spin_rate, int p = 10)
{  
   // glPushMatrix();
   glRotatef(ay* spin_rate,0,1,0);
   model(model_number, p);
   glRotatef(ay * spin_rate,0,1,0);
   // glPopMatrix();
}

bool* l0 = new bool(0);
bool* l1 = new bool(0);

void light_switch0()
{
   if(*l0)
   {
      *l0 = false;
      glDisable(GL_LIGHT0);
   }
   else
   {
      *l0 = true;
      glEnable(GL_LIGHT0);
   }
};

void light_switch1()
{
   if(*l1)
   {
      *l1 = false;
      glDisable(GL_LIGHT1);
   }
   else
   {
      *l1 = true;
      glEnable(GL_LIGHT1);
   }
};


void display(void)
{
   // gluPerspective()
   // glMatrixMode(GL_PROJECTION); // position and aim the camera
   glMatrixMode(GL_MODELVIEW);
   
   int p = 0;
   
   // glFrustum ()
   
   // glFrustum (-10.0, 10.0, -10.0, -1.0, 10, 50.0);   
   // glTranslatef(0.0,1.0,-10.0);
   glLoadIdentity();
   
   // gluLookAt(a, b, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   gluLookAt(a, b, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   // glColor3f ( 1, 0, 0 );	//This would have no effect 
   glEnable( GL_CULL_FACE );
   glCullFace ( GL_BACK );
  
   int models = 1;
   if ( translate )
   {
      models = 0;
   }
   

   glRotatef ( ay, 0, 1, 0 ); // spin of sun

   glPushMatrix();
   planet(models, 20, p);   // sun
   glPopMatrix();

   p++;

   glPushMatrix();   // another planet
   glRotatef(ay, 0,1,0);
   glTranslatef(5,0,0);
   glScalef(.25,.25,.25);
   planet(models, 10, p);  
   glPopMatrix();

   p++;

   glTranslatef ( 3, 0, 0 );
   glScalef(.5,.5,.5);

   glPushMatrix();
   glRotatef(10*ay,1,0,0);
   glRotatef(-ay,0,1,0);
   model(2);
   glPopMatrix();

   planet(models, 18, p);    // earth

   p++;
   
   glTranslatef (2, 0, 0 );
   glScalef(.25,.25,.25);
   
   

   planet(models, 10); // moon

   //p++;

   glTranslatef (2, 0, 0 );
   glScalef(.5,.5,.5);

   planet(models, 10);  // moon of moon

   //p++;

   glFlush();
   //   SDL_Delay ( 500 ); 
}

void SpecialInput(int key, int x, int y)
{
   switch ( key )
   {
      case GLUT_KEY_UP:
         a += .1;
         break;
      case GLUT_KEY_DOWN:
         a +- .1;
         break;
      case GLUT_KEY_RIGHT:
         c += .1;
         break;
      case GLUT_KEY_LEFT:
         c -= .1;
         break;
      default:
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
         a += 1;
         break;
      case 'l':
         a -= 1;
         break;
      case '0':
         light_switch0();
         break;
      case '1':
         light_switch1();
         break;
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
   delete l0;
   delete l1;
}