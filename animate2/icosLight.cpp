//icos.cpp
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

/* 
GLfloat d1[3], d2[3], norm[3];    
for (j = 0; j < 3; j++) {    
   d1[j] = vdata[tindices[i][0]][j] - vdata[tindices[i][1]][j];    
   d2[j] = vdata[tindices[i][2]][j] - vdata[tindices[i][1]][j];    
}
normcrossprod(d1, d2, norm); 
glNormal3fv(norm);
*/

void init(void)
{
   GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 0.2 };
   GLfloat light[] = { 1.0, 1.0, 1.0 };
   GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 0.2 };
   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { 0.0, 0.0, 1.0, 0.0 };
   //GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };
   GLfloat diffuseMaterial[4] = { 1, 1, 1, 0.2 };
                                                                         
   glClearColor (0.5, 0.5, 0.2, 0.5);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialf(GL_FRONT, GL_SHININESS, 125.0);
   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT0, GL_AMBIENT, light );
   glLightfv(GL_LIGHT0, GL_SPECULAR, light );
   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, light );
   glLightfv(GL_LIGHT1, GL_AMBIENT, light );
   glLightfv(GL_LIGHT1, GL_SPECULAR, light );
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);
                                                                                
   glColorMaterial(GL_FRONT, GL_DIFFUSE);
   glEnable(GL_COLOR_MATERIAL);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100 );
}

void display(void)
{
  glMatrixMode(GL_MODELVIEW); // position and aim the camera
  glLoadIdentity();
  gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                                                             
  glColor3f ( 1, 0, 0 );	//This would have no effect 
  glEnable( GL_CULL_FACE );
  glCullFace ( GL_BACK );

  glBegin(GL_TRIANGLES); 
  for (int i = 0; i < 20; i++) {   
      glColor3f( i/20.0, i/40.0, i/20.0 ); 	//has no effect if Light enabled
      glNormal3fv(&vdata[tindices[i][0]][0]); 
      glVertex3fv(&vdata[tindices[i][0]][0]); 
      glNormal3fv(&vdata[tindices[i][1]][0]); 
      glVertex3fv(&vdata[tindices[i][1]][0]); 
      glNormal3fv(&vdata[tindices[i][2]][0]); 
      glVertex3fv(&vdata[tindices[i][2]][0]);
  }
  glEnd();
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


