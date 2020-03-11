//icos_subdivide.cpp
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "SDL2/SDL.h"

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
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.5 };
   GLfloat light[] = { 0.5, 0.5, 0.5 };
   GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 0.5 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { 0.0, 0.0, 1.0, 0.0 };
   // GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat diffuseMaterial[4] = { 1, 1, 1, 0.5 };
                                                                         
   // glClearColor (0.5, 0.5, 0.2, 0.0);
   glClearColor(0.0,0.0,0.0,0.0);
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
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT1, GL_AMBIENT, light );
   glLightfv(GL_LIGHT1, GL_SPECULAR, light );
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
   glOrtho(-5.0, 5.0, -5.0, 5.0, 0.1, 100 );
}

void model(int model_number)
{
   switch (model_number)
   {
      case 0:
         glutWireCube(1.0);
         break; 
      case 1:
         glutSolidSphere(1.0,100,50);
         break;
      default:
         break;
   }
}

void planet(int model_number, float spin_rate)
{  
   // glPushMatrix();
   glRotatef(ay* spin_rate,0,1,0);
   model(model_number);
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
   
   glMatrixMode(GL_MODELVIEW); // position and aim the camera
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
      
   glLoadIdentity();
   gluLookAt(a, b, c, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   glColor3f ( 1, 0, 0 );	//This would have no effect 
   glEnable( GL_CULL_FACE );
   glCullFace ( GL_BACK );
  
   int models = 1;
   if ( translate )
   {
      models = 0;
   }

   glRotatef ( ay, 0, 1, 0 ); // spin of sun

   glPushMatrix();
   planet(models, 20);   // sun
   glPopMatrix();


   glPushMatrix();   // another planet
   glRotatef(ay, 0,1,0);
   glTranslatef(5,0,0);
   glScalef(.25,.25,.25);
   planet(models, 10);  
   glPopMatrix();

   glTranslatef ( 3, 0, 0 );
   glScalef(.5,.5,.5);
   
   planet(models, 18);   // earth

   glTranslatef (2, 0, 0 );
   glScalef(.25,.25,.25);

   planet(models, 10); // moon

   glTranslatef (2, 0, 0 );
   glScalef(.5,.5,.5);

   planet(models, 10);  // moon of moon

    glFlush();
   //   SDL_Delay ( 500 ); 
}

void SpecialInput(int key, int x, int y)
{
   switch ( key )
   {
      case GLUT_KEY_UP:
         a += 1;
         break;
      case GLUT_KEY_DOWN:
         a +- 1;
         break;
      case GLUT_KEY_RIGHT:
         c += 1;
         break;
      case GLUT_KEY_LEFT:
         c -= 1;
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
      case '0':
         light_switch0();
         break;
      case '1':
         light_switch1();
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