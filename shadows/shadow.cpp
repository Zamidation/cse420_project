/* CS 520, CSUSB
 * shadow.cpp
 * Simple shadow of a cube.
 * Data adopted from "Interactive Computer Graphics", by E. Angel
 */
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

//data for the cube
GLfloat vertices[] = {-1.0,-1.0,-1.0,1.0,-1.0,-1.0,
	1.0,1.0,-1.0, -1.0,1.0,-1.0, -1.0,-1.0,1.0, 
	1.0,-1.0,1.0, 1.0,1.0,1.0, -1.0,1.0,1.0};

GLfloat colors[] = {0.0,0.0,0.0,1.0,0.0,0.0,
	1.0,1.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0, 
	1.0,0.0,1.0, 1.0,1.0,1.0, 0.0,1.0,1.0};

GLfloat bcolors[] = {0.0,0.0,0.0,0.0,0.0,0.0,
	0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0, 
	0.0,0.0,0.0, 0.0,0.0,0.0, 0.0,0.0,0.0};

/*
GLfloat bcolors[] = {0.4,0.0,0.0, 0.4,0.0,0.0,
	0.4,0.0,0.0, 0.4,0.0,0.0, 0.4,0.0,0.0, 
	0.4,0.0,0.0, 0.4,0.0,0.0, 0.4,0.0,0.0};
*/
GLfloat greycolors[] = {0.3,0.3,0.3,0.3,0.3,0.3,
	0.3,0.3,0.3, 0.3,0.3,0.3, 0.3,0.3,0.3, 
	0.3,0.3,0.3, 0.3,0.3,0.3, 0.3,0.3,0.3};

GLubyte cubeIndices[]={0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4};

int anglex= 0, angley = 0, anglez = 0;          //rotation angles
int window;

void display(void)
{

  GLfloat light[3]={0.0, 20.0, 0.0};
  GLfloat m[16];			//projection matrix

  int i,j;
  for(i=0;i<16;i++) 
    m[i]=0.0;
  //set projection matrix
  m[0] = m[5] = m[10] = 1.0;
  m[7]=-1.0 / light[1];			//light[1] is y-coordinate of light

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(1.0,1.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);

   glPushMatrix();
   glRotatef( anglex, 1.0, 0.0, 0.0);           //rotate the object about x-axis
   glRotatef( angley, 0.0, 1.0, 0.0);           //rotate about y-axis   
   glRotatef( anglez, 0.0, 0.0, 1.0);           //rotate about z-axis

  glPushMatrix();
  //display the cube
  glTranslatef(0.0, 3.0, 0.0);
  glColorPointer(3,GL_FLOAT, 0, colors); 
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

  glPopMatrix();
  //refer to notes about the transformation, note that matrix operation is in reverse
  //order of instructions
  glTranslatef(light[0], light[1],light[2]);
  glMultMatrixf(m);
  glTranslatef(-light[0], -light[1],-light[2]);
  glColor3f(0.2,0.2,0.2);			//dark

  //The shadow
  //glColorPointer(3,GL_FLOAT, 0, bcolors); 
  glColorPointer(3,GL_FLOAT, 0, greycolors); 
  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

  glPopMatrix();
  glutSwapBuffers(); 
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-4.0, 4.0, -3.0 * (GLfloat) h / (GLfloat) w,
            5.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-4.0 * (GLfloat) w / (GLfloat) h,
            4.0 * (GLfloat) w / (GLfloat) h, -3.0, 5.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
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
    case 'r':                                   //reset
      anglez = angley = anglex = 0;
      glLoadIdentity();
      break;
  case 27: /* escape */
        glutDestroyWindow(window);
        exit(0);
  }
  glutPostRedisplay();
}

int main(int argc, char **argv)
{

/* need both double buffering and z buffer */

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    window = glutCreateWindow( argv[0] );
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST); /* Enable hidden--surface--removal */
    glEnableClientState(GL_COLOR_ARRAY); 
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3,GL_FLOAT, 0, colors); 
    glClearColor(1.0,1.0,1.0,1.0);
    glColor3f(1.0,1.0,1.0);
    glutKeyboardFunc (keyboard);
    glutMainLoop();

    return 0;
}
