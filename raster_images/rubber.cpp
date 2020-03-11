/*
 * rubber.cpp
 * CS 520 demo program showing rubber rectangular drawing.
 * To simplify things, viewport and world window are set to the same.
 * @Author: T.L. Yu, 2009W
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int window;
int screenWidth = 800, screenHeight = 800;
int left, bottom, right, top;			//rectangular area

void init(void)
{    
   glClearColor (1, 1, 1, 0.0);
   glPolygonMode( GL_FRONT, GL_LINE );
   glPolygonMode( GL_BACK, GL_LINE );
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   gluOrtho2D( 0.0, screenWidth, 0.0, screenHeight );	//set to screen values to simplify 
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
   glLineWidth ( 4 );
   glColor3f ( 0, 1, 0 );
   glBegin( GL_TRIANGLES);		//arbitrarily draw something
     glVertex2i ( 100, 100 );
     glVertex2i ( 200, 100 );
     glVertex2i ( 150, 150 );
   glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
}

int mouseDown = 0;

void myMouse( int button, int state, int x, int y )
{
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
    glEnable( GL_COLOR_LOGIC_OP );	//enable logical operations
    glLogicOp ( GL_XOR );		//set it to XOR mode
    left = right = x;			//set the pivot
    top = bottom = screenHeight - y;	 
    mouseDown = 1;
  } else if ( button == GLUT_LEFT_BUTTON && state == GLUT_UP ) {
    mouseDown = 0;
    glDisable( GL_COLOR_LOGIC_OP );	//disable logical operations
    glColor3f ( 1.0, 0.0, 1.0 );
    glRecti ( left, bottom, right, top );//draw the final rectangle	
    glFlush();
  }
}

void mouseMove ( int mx, int my )
{
  if ( mouseDown ) {
    glRecti ( left, bottom, right, top );		//erase old rectangle
    right = mx;					
    bottom = screenHeight - my;			//flip y-coordinates
    //glColor3f ( 0, 0, 1 );
    glRecti ( left, bottom, right, top );		//draw the new rectangle
    glFlush();
  }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
   glutInitWindowSize(screenWidth, screenHeight);
   glutInitWindowPosition(100, 100);
   window = glutCreateWindow(argv[0]);
   init();
   glutDisplayFunc(display);
   glutMouseFunc( myMouse );
   glutMotionFunc( mouseMove );
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0; 
}
