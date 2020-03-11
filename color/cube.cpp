/*
 * Copyright (c) 1993-2003, Silicon Graphics, Inc.
 * All Rights Reserved
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright
 * notice and this permission notice appear in supporting documentation,
 * and that the name of Silicon Graphics, Inc. not be used in
 * advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.
 *
 * THE MATERIAL EMBODIED ON THIS SOFTWARE IS PROVIDED TO YOU "AS-IS" AND
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OTHERWISE,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL SILICON
 * GRAPHICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
 * OR ANY DAMAGES WHATSOEVER, INCLUDING WITHOUT LIMITATION, LOSS OF
 * PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR THE CLAIMS OF THIRD
 * PARTIES, WHETHER OR NOT SILICON GRAPHICS, INC.  HAS BEEN ADVISED OF
 * THE POSSIBILITY OF SUCH LOSS, HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE POSSESSION, USE
 * OR PERFORMANCE OF THIS SOFTWARE.
 *
 * US Government Users Restricted Rights 
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor clauses
 * in the FAR or the DOD or NASA FAR Supplement.  Unpublished - rights
 * reserved under the copyright laws of the United States.
 *
 * Contractor/manufacturer is:
 *	Silicon Graphics, Inc.
 *	1500 Crittenden Lane
 *	Mountain View, CA  94043
 *	United State of America
 *
 * OpenGL(R) is a registered trademark of Silicon Graphics, Inc.
 */

/*
 *  cube.c
 *  This program demonstrates a single modeling transformation,
 *  glScalef() and a single viewing transformation, gluLookAt().
 *  A wireframe cube is rendered.
 */
#include <GL/glut.h>
#include <stdlib.h>

void init(void) 
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
  // glShadeModel (GL_FLAT);
   glShadeModel (GL_SMOOTH);

   glEnableClientState (GL_VERTEX_ARRAY);
   glEnableClientState (GL_COLOR_ARRAY);

}

void display(void)
{
   glClear (GL_COLOR_BUFFER_BIT);
   glColor3f (1.0, 1.0, 1.0);
   glLoadIdentity ();             /* clear the matrix */
           /* viewing transformation  */
   gluLookAt (3.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//   glScalef (1.0, 2.0, 1.0);      /* modeling transformation */ 
//   glutWireCube (1.0);

static GLint vertices[] = {-1, -1, -1,   //0
                       1, -1, -1,
                       1, 1, -1,
                       -1, 1, -1,        //3
			-1, -1, 1,
			1, -1, 1,
			1, 1, 1,         //6
			-1, 1, 1};       //7
                       
   static GLfloat colors[] = {1.0, 0.2, 0.2,
                       0.2, 0.2, 1.0,
                       0.8, 1.0, 0.2,
                       0.75, 0.75, 0.75,
                       0.35, 0.35, 0.35,
                       0.5, 0.5, 0.5,
			1.0, 0.0, 0.0, 
			0.0, 1.0, 0.0
			};


   glVertexPointer (3, GL_INT, 0, vertices);
   glColorPointer (3, GL_FLOAT, 0, colors);
   glEnable( GL_CULL_FACE );
   glCullFace ( GL_BACK );
   static GLubyte frontIndices[] = {4, 5, 6, 7};
   static GLubyte rightIndices[] = {1, 2, 6, 5};
   static GLubyte bottomIndices[] = {0, 1, 5, 4};
   static GLubyte backIndices[] = {0, 3, 2, 1};
   static GLubyte leftIndices[] = {0, 4, 7, 3};
   static GLubyte topIndices[] = {2, 3, 7, 6};

   glTranslatef ( -1.5, -1.2, 0 );
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, frontIndices);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, rightIndices);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, bottomIndices);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, backIndices);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, leftIndices);
   glDrawElements(GL_QUADS, 4, GL_UNSIGNED_BYTE, topIndices);
   
   glRotatef ( 30, 1, 1, 1 ); 
   glTranslatef ( 3, 2.4, 0 );
   static GLubyte allIndices[] = {4, 5, 6, 7, 1, 2, 6, 5, 
	0, 1, 5, 4, 0, 3, 2, 1, 
	0, 4, 7, 3, 2, 3, 7, 6};

   glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, allIndices);

/*
   glBegin( GL_QUADS );
     glArrayElement ( 4 );    //front face (see notes)
     glArrayElement ( 5 );
     glArrayElement ( 6 );
     glArrayElement ( 7 );

     glArrayElement ( 0 );   //back face
     glArrayElement ( 3 );
     glArrayElement ( 2 );
     glArrayElement ( 1 );
     
     glArrayElement ( 1 );   //back facing (right)
     glArrayElement ( 2 );
     glArrayElement ( 6 );
     glArrayElement ( 5 );

   glEnd();
*/
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMainLoop();
   return 0;
}
