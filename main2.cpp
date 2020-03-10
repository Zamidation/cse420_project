//main.cpp
//main loop for graphics
#include <GL/glut.h>

void display( void );
void init( void );
void keyboard ( unsigned char key, int mousex, int mousey );
void visHandle( int visible );
void ending();

int main( int argc, char *argv[] )
{
  glutInit( &argc, argv );
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize( 800, 800 );

  glutInitWindowPosition( 100, 100 );
  glutCreateWindow("Solar System");
  init();
  
  // glViewport(200,200,300,300);
  glViewport(0,0,10,10);

  glutDisplayFunc(display);
  glutKeyboardFunc ( keyboard );
  
  
  glutVisibilityFunc( visHandle );
  glutMainLoop();
  ending();
  return 0;
}

