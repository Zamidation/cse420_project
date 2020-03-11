/*
 * render-img0.cpp
 * Demo program showing how to read in a png image file and render it.
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

int window;
int anglex= 0, angley = 0, anglez = 0;		//rotation angles
int screenWidth = 500, screenHeight = 500;
unsigned char *ibuff;				//image buffer pointer

void init(void)
{    
   glClearColor (1, 1, 1, 0.0);
   glShadeModel(GL_FLAT);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   //char *filename = (char *) "house.png";		//image file
   char *filename = (char *)  "mickey20.png";		//image file
 //  char *filename = (char *) "t.png";		//image file
   int iwidth, iheight;	

   ibuff = loadImageRGBA( filename, &iwidth, &iheight);
   glPushMatrix(); 
   glRotatef( anglex, 1.0, 0.0, 0.0);		//rotate object along x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);		//rotate along y-axis	
   glRotatef( anglez, 0.0, 0.0, 1.0);		//rotate along z-axis

   glRasterPos2f ( 1.0, 1.0 );			//position to display image
   glDrawPixels ( iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, ibuff );

   glPopMatrix();
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
    case 'r':	//reset
      anglex = angley = anglez = 0;
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

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(screenWidth, screenHeight);
   glutInitWindowPosition(100, 100);
   window = glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
