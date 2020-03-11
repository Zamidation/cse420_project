/*
 * dissolve-aniim.cpp
 * Demo program showing how to read in a png image file and render it
 * and animation.
 * @Author: T.L. Yu, 2008F
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imageio.h"
#include <SDL/SDL.h>

int window;
int anglex= 0, angley = 0, anglez = 0;		//rotation angles
int screenWidth = 500, screenHeight = 500;
unsigned char *ibuff0, *ibuff1;			//image buffer pointers
float tParam = 0.0;

void init(void)
{    
   glClearColor (1, 1, 1, 0.0);
   glShadeModel(GL_FLAT);
}

void blendedImage ( unsigned char *A, unsigned char *B, unsigned char *C, int h, int w, float t )
{
  int size = h * w * 4;

  for ( int i = 0; i < size; ++i ) {
	C[i] = (unsigned char )(  A[i]*(1-t) + B[i]*t );
    }
}

 
void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   char *filename0 = "tom.png";		//image file
   char *filename1 = "maricel.png";		//image file
   int iwidth0, iheight0;	
   int iwidth1, iheight1;	
   unsigned char *img;

   ibuff0 = loadImageRGBA( filename0, &iwidth0, &iheight0);
   ibuff1 = loadImageRGBA( filename1, &iwidth1, &iheight1);
   //printf("%d,%d|%d,%d\n", iwidth0, iheight0, iwidth0, iheight1 );
   img = new unsigned char[iwidth1 * iheight1 * 4];
   
   glPushMatrix(); 
   glRotatef( anglex, 1.0, 0.0, 0.0);		//rotate object along x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);		//rotate along y-axis	
   glRotatef( anglez, 0.0, 0.0, 1.0);		//rotate along z-axis

   float t = 0;
   glRasterPos2f ( -2.0, 1.0 );			//position to display image
   glDrawPixels ( iwidth0, iheight0, GL_RGBA, GL_UNSIGNED_BYTE, ibuff0 );
   glRasterPos2f ( -2.0, -1.0 );			//position to display image
   glDrawPixels ( iwidth1, iheight1, GL_RGBA, GL_UNSIGNED_BYTE, ibuff1 );

   blendedImage ( ibuff0, ibuff1, img, iheight0, iwidth0, tParam );
   glRasterPos2f ( 1.0, 0.5 );			//position to display image
   //glDrawPixels ( iwidth0, iheight0, GL_RGBA, GL_UNSIGNED_BYTE, ibuff0 );
   glDrawPixels ( iwidth0, iheight0, GL_RGBA, GL_UNSIGNED_BYTE, img );

   glPopMatrix();
   glutSwapBuffers();
   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 'x':
      anglex = ( anglex + 3 ) % 360;
      break;
    case 'X':
      anglex = ( anglex - 3 ) % 360;
      break;
    case 'y':
      angley = ( angley + 3 ) % 360;
      break;
    case 'Y':
      angley = ( angley - 3 ) % 360;
      break;
    case 'z':
      anglez = ( anglez + 3 ) % 360;
      break;
    case 'Z':
      anglez = ( anglez - 3 ) % 360;
      break;
    case 't':
      if ( tParam < 1.0 )
       tParam += 0.05;
      break;
    case 'T':
      if ( tParam > 0 )
       tParam -= 0.05;
      break;
    case 'r':	//reset
      anglex = angley = anglez = 0;
      tParam = 0;
      break;
    case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
  glutPostRedisplay();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 30.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt ( 0, 0, 5, 0, 0, 0, 0, 1, 0 );
}

void animate()
{
  static int turn = 0;
  if ( turn == 0 ) {
    if ( tParam < 1.0 )
       tParam += 0.05;
    else 
       turn = 1;
  }
  if ( turn == 1 ) {
    if ( tParam > 0 )
       tParam -= 0.05;
    else
       turn = 0;
  }
  glutPostRedisplay ();
}

void idle ()
{
   static unsigned int prev_time = SDL_GetTicks(),
      current_time = SDL_GetTicks();

   current_time = SDL_GetTicks();          //ms since library starts
   int diff = current_time - prev_time;
   if ( diff < 100 ){    //20 fps ~ 50 ms / frame
      int delay = 100 - ( current_time - prev_time );
       SDL_Delay ( delay );
   }
   prev_time = current_time;
   animate();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(screenWidth, screenHeight);
   glutInitWindowPosition(100, 100);
   window = glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutIdleFunc ( idle );

   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
