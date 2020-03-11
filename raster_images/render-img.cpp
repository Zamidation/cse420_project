/*
 * render-img.cpp
 * Demo of draggin an image.
 * @Author: T.L. Yu, 2008F
 *
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "imageio.h"

int window;
int screenWidth = 500, screenHeight = 500;
float imgX = -1.0, imgY = 1.0, imgZ = -24.0;	//image display position
unsigned char *ibuff;

void init(void)
{    
   glClearColor (1, 1, 1, 0.0);
   glShadeModel(GL_FLAT);

   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
   //char *filename = (char *) "house.png";
   //char *filename = (char *) "mickey20.png";
   char *filename = (char *) "t.png";
   int   iwidth, iheight;
   
   ibuff = loadImageRGBA( filename, &iwidth, &iheight);

   glRasterPos3f ( imgX, imgY, imgZ );		//position to display image
   glDrawPixels ( iwidth, iheight, GL_RGBA, GL_UNSIGNED_BYTE, ibuff );

   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
  switch(key) {
    case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
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


/* A simplified routine for  converting two-dimensional screen pixel coordinates to three-dimensional
 * World coordinates.
 * Input: (x, y) are screen pixel coordinates; z is set to 0.
 * Output: (*X, *Y, *Z) are world coordinates
 */
void twoD2threeD( int x, int y, double *X, double *Y, double *Z )
{
  int viewport[4];                      //where the viewport values will be stored
  double modelviewMatrix[16];           //where Modelview Matrix will be stored
  double projectionMatrix[16];          //where Projection Matrix will be stored

  glGetIntegerv( GL_VIEWPORT, viewport );//retrieve current viewport: viewport[0] = x-origin, 
                                         //viewport[1]=y-origin, viewport[2]=width, viewport[3]=height
  glGetDoublev( GL_MODELVIEW_MATRIX, modelviewMatrix );  //retrieve Modelview Matrix
  glGetDoublev( GL_PROJECTION_MATRIX, projectionMatrix );//retrieve Projection Matrix

  GLfloat z = 0;
  /*
    In practice, you should actually define the near and far edge z values which are
    clipped to [0, 1].
  */

  gluUnProject ( x, y, z, modelviewMatrix, projectionMatrix, viewport, X, Y, Z );
}

void myMouse( int button, int state, int x, int y )
{
  float xw, yw, zw;
      
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) {
  } 
}

void mouseMove ( int mx, int my )
{
  double xw, yw, zw;				//world coordinates
  twoD2threeD( mx, screenHeight-my, &xw, &yw, &zw );
  
  imgX = xw;
  imgY = yw;
  imgZ = zw;
  glutPostRedisplay();
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
   glutMouseFunc( myMouse );
   glutMotionFunc( mouseMove );
   glutMainLoop();
   return 0; 
}
