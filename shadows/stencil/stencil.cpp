
/*
 *  stencil.cpp
 *  This program demonstrates use of the stencil buffer for
 *  masking rectangular regions.  
 *  Whenever the window is redrawn, a value of 1 is drawn 
 *  into a diamond-shaped region in the stencil buffer.  
 *  Elsewhere in the stencil buffer, the value is 0.
 */
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#define YELLOWMAT   1
#define BLUEMAT 2

void init (void) 
{
   glEnable(GL_DEPTH_TEST);
   glClearStencil(0x0);
   glEnable(GL_STENCIL_TEST);
}

//green diamond inside red square
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   glStencilFunc (GL_NOTEQUAL, 0x1, 0x1);	//fail in diamond-region, pass outside
 //  glStencilFunc (GL_EQUAL, 0x1, 0x1);	//pass in diamond-region, fail outside
   glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP);	//no change in stencil buffer values
  
  glColor3f ( 1, 0, 0 );			//red
  glBegin ( GL_POLYGON );
      glVertex3f (-1.0, 1.0, -1);		//z = -1, so red polygon behind green ( below )
      glVertex3f (1.0, 1.0, -1);
      glVertex3f (1.0, -1.0, -1);
      glVertex3f (-1.0, -1.0, -1);
   glEnd();
   glFlush();

   SDL_Delay ( 3000 );
   glFlush();
   glStencilFunc (GL_EQUAL, 0x1, 0x1);		//pass in diamond-region, fail outside
  glColor3f ( 0, 1, 0 );			//green
  glBegin ( GL_POLYGON );

      glVertex3f (-1.0, 1.0, 0);		//z = 0, in front of red polygon
      glVertex3f (1.0, 1.0, 0);
      glVertex3f (1.0, -1.0, 0);
      glVertex3f (-1.0, -1.0, 0);

/*
      glVertex3f (-1.0, 0.0, -1);
      glVertex3f (0.0, 1.0, -1);
      glVertex3f (1.0, 0.0, -1);
      glVertex3f (0.0, -1.0, -1);
*/
   glEnd();
   glFlush();

}

/*  Whenever the window is reshaped, redefine the 
 *  coordinate system and redraw the stencil area.
 */
void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      gluOrtho2D(-3.0, 3.0, -3.0*(GLfloat)h/(GLfloat)w,
                 3.0*(GLfloat)h/(GLfloat)w);
   else
      gluOrtho2D(-3.0*(GLfloat)w/(GLfloat)h,
                 3.0*(GLfloat)w/(GLfloat)h, -3.0, 3.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   //create a diamond shaped stencil area 
   glClear(GL_STENCIL_BUFFER_BIT);	//fill stencil buffer with 0s
   glStencilFunc (GL_ALWAYS, 0x1, 0x1);
   glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE);
   glBegin(GL_QUADS);		//stencil buffer will have diamond-shaped region filled with 1s
      glVertex2f (-1.0, 0.0);
      glVertex2f (0.0, 1.0);
      glVertex2f (1.0, 0.0);
      glVertex2f (0.0, -1.0);
   glEnd();

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, (GLfloat) w/(GLfloat) h, 3.0, 7.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

/* Main Loop
 * Be certain to request stencil bits.
 */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB 
                        | GLUT_DEPTH | GLUT_STENCIL);
   glutInitWindowSize (800, 800);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
