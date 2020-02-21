//icos1.cpp
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <SDL/SDL.h>

#define X .525731112119133606 
#define Z .850650808352039932

static GLfloat vdata[12][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};
static GLuint tindices[20][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

//normalize a vector
void normalize(float v[3]) {    
   GLfloat d = sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]); 
   if (d == 0.0) {
      printf("\nErrot: zero length vector");    
      return;
   }
   v[0] /= d; v[1] /= d; v[2] /= d; 
}

//v1[], v2[] are two vectors
//out[] holds the crossproduct v1 x v2 
void normcrossprod(float v1[3], float v2[3], float out[3]) 
{ 
   GLint i, j; 
   GLfloat length;

   out[0] = v1[1]*v2[2] - v1[2]*v2[1]; 
   out[1] = v1[2]*v2[0] - v1[0]*v2[2]; 
   out[2] = v1[0]*v2[1] - v1[1]*v2[0]; 
   normalize(out); 
}

void init(void)
{
  glClearColor (0.5, 0.5, 0.2, 0.5);

   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100 );
}
  
float colors[20][3];

void display(void)
{
  glMatrixMode(GL_MODELVIEW); // position and aim the camera
  glLoadIdentity();
  gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                             
  glColor3f ( 1, 0, 0 );	//This would have no effect 
  glEnable( GL_CULL_FACE );
  glCullFace ( GL_BACK );

  glEnableClientState ( GL_VERTEX_ARRAY );
//  glEnableClientState(GL_NORMAL_ARRAY); 
  glEnableClientState ( GL_COLOR_ARRAY );
  for ( int i = 0; i < 20; i++ ) 
    for ( int j = 0; j < 3; j++ )
      colors[i][j] = i / (10.0 + 10*j);
 
  glVertexPointer ( 3, GL_FLOAT, 0, vdata );
//  glNormalPointer ( 3, GL_FLOAT, vdata );
  glColorPointer ( 3, GL_FLOAT, 0, colors );

  for (int i = 0; i < 20; i++) 
    glDrawElements (GL_TRIANGLES, 3, GL_UNSIGNED_INT, tindices[i] );
   glDisableClientState ( GL_VERTEX_ARRAY );
 //  glDisableClientState ( GL_NORMAL_ARRAY );
   glDisableClientState ( GL_COLOR_ARRAY );

   glFlush();
}

void keyboard ( unsigned char key, int mousex, int mousey )
{
   switch ( key ) {
     case 27:       // escape
       exit ( -1 );
   }
   glutPostRedisplay();
}


