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
  glutInitWindowSize( 800, 800 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow("Icosahedron");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc ( keyboard );

  glViewport ( 0, 0, 500, 500 );
  glutVisibilityFunc( visHandle );
  glutMainLoop();

  return 0;
}

