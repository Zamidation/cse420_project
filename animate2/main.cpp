//main.cpp
//main loop for graphics
#include <GL/glut.h>

void display( void );
void init( void );
void keyboard ( unsigned char key, int mousex, int mousey );

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 500, 500 );
  glutInitWindowPosition( 100, 100 );
  glutCreateWindow("Icosahedron");
  init();
  glutDisplayFunc(display);
  glutKeyboardFunc ( keyboard );

  glViewport ( 0, 0, 500, 500 );

  glutMainLoop();

  return 0;
}

