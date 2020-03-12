//main.cpp
//main loop for graphics
#include <GL/glut.h>

void display( void );
void init( void );
void keyboard ( unsigned char key, int mousex, int mousey );
void SpecialInput(int key, int x, int y);
void KeyUp(unsigned char key, int x, int y);
void visHandle( int visible );
void ending();

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 1600, 800 );

  glutInitWindowPosition( 100, 100 );
  glutCreateWindow("Solar System");
  init();
  
  // glViewport(200,200,300,300);
  glViewport(0,0,10,10);

  glutDisplayFunc(display);
  glutKeyboardFunc ( keyboard );
  glutSpecialFunc (SpecialInput);
  // glutSpecialUpFunc (KeyUp);
  
  glutVisibilityFunc( visHandle );
  glutMainLoop();
  ending();
  return 0;
}

