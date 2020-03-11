/*
 * swap-img.cpp
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
int screenWidth = 500, screenHeight = 500;
int iwidth, iheight;	
unsigned char *ibuff[2];				//image buffer pointers

void init(void)
{    
   glClearColor (0, 0, 0, 0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glShadeModel(GL_FLAT);
   
   //assume both images are of the same size
   char filename[][20] = {"tom.png", "maricel.png"};	//image files
   for ( int i = 0; i < 2; ++i ) 
     ibuff[i] = loadImageRGBA( filename[i], &iwidth, &iheight);
}

void display(void)
{
   glEnable(GL_COLOR_LOGIC_OP);
   glLogicOp ( GL_XOR );
   static bool first = true;
   
   glRasterPos2f ( -2.0, 0.0 );			//position to display image
   glDrawPixels ( iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, ibuff[0] );
   if ( !first )			 
      glDrawPixels ( iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, ibuff[1] );
   
   glRasterPos2f ( 1.0, 0.0 );			//position to display image
   glDrawPixels ( iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, ibuff[1] );
   if ( !first )
     glDrawPixels ( iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, ibuff[0] );
   
   first = false;
   glutSwapBuffers();
   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
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
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
