/*
 * tween1.cpp
 * Demo of in-between principle and animation. Press 'ESC' to quit the program.
 * Use glIdelFunc to do anaimation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <SDL/SDL.h>

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

Point2 tween( const Point2 &Q, const Point2 &R, float t )
{
  Point2 P;
  P.x = Q.x + ( R.x - Q.x ) * t;
  P.y = Q.y + ( R.y - Q.y ) * t;
  return P;
}

void drawTween( const Point2 A[], const Point2 B[], int n, float t, const Point2 &c )
{   
  glColor3f (0, 0, 0 );
  glEnable ( GL_POINT_SMOOTH );
  glPointSize ( 8 );
  
  // draw the tween at time t between polylines A and B
  Point2 P0 = tween(A[0], B[0],t);
  Point2 P1 = Point2( P0.x + c.x, P0.y + c.y );
  for(int i = 1; i < n; i++)
  {
    Point2 P, P2;
    if ( i == n )
       P = tween( A[0], B[0],t );
    else 
       P = tween( A[i], B[i],t );
    P2 = Point2( P.x + c.x, P.y + c.y );
    if ( i < n - 1 ) {
      glBegin( GL_POINTS );
        glVertex2f ( P2.x, P2.y ); 
      glEnd();
    } 
    glBegin( GL_LINES );
      glVertex2f ( P1.x, P1.y ); 
      glVertex2f ( P2.x, P2.y ); 
    glEnd();
    P1 = P2;
  }
}

//create two figures for demo use
void makeHand( Point2 A[], Point2 B[] )
{
  A[0].x = 1.2;	A[0].y = 9.8; 	A[1].x = 2;	A[1].y = 8;
  A[2].x = 3;	A[2].y = 7; 	A[3].x = 6;	A[3].y = 7;
  A[4].x = 7;	A[4].y = 5;	A[5].x = 7;	A[5].y = 4;

  B[0].x = 1;	B[0].y = 4; 	B[1].x = 2;	B[1].y = 5;
  B[2].x = 3;	B[2].y = 7; 	B[3].x = 6;	B[3].y = 7;
  B[4].x = 7.5;	B[4].y = 5.5;	B[5].x = 8;	B[5].y = 5;
} 

void makeBody( Point2 A[], Point2 B[] )
{
  A[0].x = 4.5;	A[0].y = 8; 	A[1].x = 4.7;	A[1].y = 5;
  A[2].x = 4.5;	A[2].y = 4; 	

  B[0].x = 4.5;	B[0].y = 8; 	B[1].x = 5;	B[1].y = 5;
  B[2].x = 4.5;	B[2].y = 4; 	
} 

void makeLeg( Point2 A[], Point2 B[] )
{
  A[0].x = 3.5;	A[0].y = 0.2; 	A[1].x = 3;	A[1].y = 2;
  A[2].x = 3.2;	A[2].y = 4; 	A[3].x = 5.8;	A[3].y = 4;
  A[4].x = 6;	A[4].y = 2;	A[5].x = 6.2;	A[5].y = 0.2;

  B[0].x = 3.2;	B[0].y = 0.2; 	B[1].x = 3.5;	B[1].y = 2;
  B[2].x = 3;	B[2].y = 4; 	B[3].x = 5.8;	B[3].y = 4;
  B[4].x = 4.8;	B[4].y = 2;	B[5].x = 7;	B[5].y = 1.8;
} 

Point2 A[10], B[10];
Point2 A1[10], B1[10];
Point2 A2[10], B2[10];
Point2 center( 0, 0 );
float t = 0, deltat = 0.1;
float deltax = 2, deltay = 0;

void init ( void )
{
  gluOrtho2D ( 0.0, 30.0, 0.0, 30.0 );
  makeHand( A, B );	//create figure A and B
  makeBody( A1, B1 );	//create figure A1 and B1
  makeLeg( A2, B2 );	//create figure A2 and B2

  glLineWidth ( 2 );
  glClearColor( 1.0, 1.0, 1.0, 0.0 );
}

void animate();

void idle ()
{
   static unsigned int prev_time = SDL_GetTicks(), 
      current_time = SDL_GetTicks();

   current_time = SDL_GetTicks();          //ms since library starts
   int diff = current_time - prev_time;
 //  if ( current_time - prev_time < 50 ){    //20 fps ~ 50 ms / frame
   if ( diff < 100 ){    //20 fps ~ 50 ms / frame
      int delay = 100 - ( current_time - prev_time );
      printf("Delay=%d\n", delay);
       SDL_Delay ( delay );
      //SDL_Delay ( 50 - ( current_time - prev_time ) ); //do not use
   }
   printf("%u,%u, %d|", current_time, prev_time, current_time - prev_time  );
   prev_time = current_time;
   animate();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  drawTween( A, B, 6, t, center );
  drawTween( A1, B1, 3, t, center );
  drawTween( A2, B2, 6, t, center );
  
  glFlush();
  glutSwapBuffers();
}

void animate()
{
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
      case 'r':
 	deltat = -deltat;       //reverse direction
        deltax = -deltax;
        deltay = -deltay;
	animate();
	break;
  }
}

void timerHandle ( int value )
{
   animate();
   glutPostRedisplay();
   // call timerHandle 100 ms later, 0 is passed to timerHandle (not used here)
   glutTimerFunc ( 100, timerHandle, 0 );
}

void visHandle( int visible )
{
   if (visible == GLUT_VISIBLE)
      timerHandle ( 0 );
   else
      ;
}


int main( int argc, char *argv[] )
{
  // Set things (glut) up 
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );

   // Create the window and handlers 
   glutCreateWindow("Tweening Demo");
   glutReshapeWindow( 500, 500 );
   glutInitWindowPosition(100, 100);
   glutDisplayFunc(display);
  // glutIdleFunc ( idle );
   glutVisibilityFunc( visHandle );

   glutKeyboardFunc(keyboard);
   init();
   //perpetual loop
   glutMainLoop();
   return(0);
}



