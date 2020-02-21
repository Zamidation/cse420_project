/*
 * tween.cpp
 * Demo of in-between principle and animation. Press 'ESC' to quit the program.
*/
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

class Point2{
public:
  float x;
  float y;
  Point2()
  { x = y = 0; }
  Point2( float x0, float y0 )
  {
    x = x0;	y = y0;
  }
  Point2 ( const Point2 &p )
  {
    x = p.x;
    y = p.y;
  }
};

Point2 tween( Point2 P1, Point2 P2, float t )
{
  Point2 P;
  P.x = P1.x + ( P2.x - P1.x ) * t;
  P.y = P1.y + ( P2.y - P1.y ) * t;
  return P;
}

void drawTween(Point2 A[], Point2 B[], int n, float t, Point2 c)
{   // draw the tween at time t between polylines A and B
  Point2 P0 = tween(A[0], B[0],t);
//  cvs.moveTo(P0.x+c.x, P0.y+c.y);
  Point2 P1 = Point2( P0.x + c.x, P0.y + c.y );

  for(int i = 1; i <= n; i++)
  {
    Point2 P, P2;
//    cvs.lineTo(P.x+c.x, P.y+c.y);
    if ( i == n )
       P = tween( A[0], B[0],t );
    else 
       P = tween( A[i], B[i],t );
    P2 = Point2( P.x + c.x, P.y + c.y );
    
    glBegin( GL_LINES );
      glVertex2f ( P1.x, P1.y ); 
      glVertex2f ( P2.x, P2.y ); 
    glEnd();
    P1 = P2;
  //  P1 = Point2( P.x + c, P.y + c.y );
   
  }
//  cvs.lineTo(P0.x+c.x, P0.y+c.y);
}

//arbitrarily create two figures for demo use
void makeFigures( Point2 A[], Point2 B[] )
{
  A[0].x = 0;	A[0].y = 0; 	A[1].x = 3;	A[1].y = 3;
  A[2].x = 6;	A[2].y = 0; 	A[3].x = 6;	A[3].y = -6;
  A[4].x = 4;	A[4].y = -6;	A[5].x = 4;	A[5].y = -4;
  A[6].x = 2;	A[6].y = -4;	A[7].x = 2;	A[7].y = -6;
  A[8].x = 0;	A[8].y = -6;
  B[0].x = 0;	B[0].y = 0; 	B[1].x = 3;	B[1].y = 0;
  B[2].x = 6;	B[2].y = 0; 	B[3].x = 6;	B[3].y = -2;
  B[4].x = 4;	B[4].y = -2;	B[5].x = 4;	B[5].y = -6;
  B[6].x = 2;	B[6].y = -6;	B[7].x = 2;	B[7].y = -2;
  B[8].x = 0;	B[8].y = -2;
} 

void setColor( int i )
{
  switch ( i ) {
    case 1:
    	glColor3f( 0, 1, 1 );	
	break;
    case 2:
    	glColor3f( 0, 1, 0 );	//green
	break;
    case 3:
    	glColor3f( 1, 1, 0 );	
	break;
    case 4:
    	glColor3f( 1, 0, 0 );	//red
	break;
    case 5:
    	glColor3f( 0, 0, 1 );	//blue
	break;
    default: 
    	glColor3f( 0, 0, 0 );	//black	
  }
}
  
Point2 A[10], B[10];
Point2 center( -9.5, -4 );
float t = 0, deltat = 0.1;
float deltax = 1.1, deltay = 1.3;

void init ( void )
{
  gluOrtho2D ( -15.0, 15.0, -15.0, 15.0 );
  makeFigures( A, B );		//create figure A and B
  glLineWidth ( 2 );
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
}
void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  int i = (int) (t * 10); 
  setColor( i );
  drawTween( A, B, 9, t, center );
  
  glFlush();
  glutSwapBuffers();
}

void animate()
{
 // SDL_Delay ( 800 );
  t += deltat;
  center.x += deltax;	center.y += deltay;  	//move center for clarity of display
  if ( t > 1 ){
	t = 1.0;
	deltat = -deltat;			//reverse direction
        deltax = -deltax;
        deltay = -deltay;
  } else if ( t < 0 ) {
	t = 0;
	deltat = -deltat;			//reverse direction
        deltax = -deltax;
        deltay = -deltay;
  }
  glutPostRedisplay ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
        exit(0);
        break;
      case 'a':
        animate();	
	break;
  }
}

int main( int argc, char *argv[] )
{

  // Set things (glut) up 
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_ACCUM | GLUT_RGB | GLUT_DEPTH);

   // Create the window and handlers 
   glutCreateWindow("Tweening Demo");
   glutReshapeWindow( 500, 500 );
   glutInitWindowPosition(100, 100);
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   init();
   //perpetual loop
   glutMainLoop();
   return(0);

}

