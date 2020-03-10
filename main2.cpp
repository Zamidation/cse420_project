//main.cpp
//main loop for graphics
#include <GL/glut.h>

void display( void );
void init( void );
void keyboard ( unsigned char key, int mousex, int mousey );
void visHandle( int visible );

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 1600, 800 );
  glutInitWindowPosition( 300, 100 );
  glutCreateWindow("Solar System");
  init();
  
  glutDisplayFunc(display);
  glutKeyboardFunc ( keyboard );
  glViewport(0,0,800,800);
  
  glutVisibilityFunc( visHandle );
  glutMainLoop();

  return 0;
}

