//main.cpp

#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//initialization
void init(void);
void myMouse( int button, int state, int x, int y);
void myMovedMouse(  int mouseX, int mouseY);
void myKeyboard ( unsigned char key, int x, int y );
void display( void );
void ending(void);

/*  Main Loop
 *  Open window with initial window size, title bar,
 *  RGBA display mode, depth buffer.
 */
int main(int argc, char** argv)
{
  glutInit(&argc, argv);	//initialize toolkit
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB );	//set display mode
  glutInitWindowSize(500, 500);		//set window size on screen
  glutInitWindowPosition( 100, 150 ); 	//set window position on screen
  glutCreateWindow("Project");		//open screen widow
  init();
  // glutMouseFunc( myMouse );
  // glutMotionFunc( myMovedMouse );
  glutKeyboardFunc( myKeyboard );
  glutDisplayFunc( display );
  glutMainLoop();			//go into perpetual loop
  return 0;
}
