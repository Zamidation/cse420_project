//project.cpp
//IMPORTANT define the macro var CL_GLEXT_PROTOTYPES below
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/glext.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>

#define  screenHeight  500

using namespace std;

float mydata [] = { 2,3,  1,0,0,  25,5,  0,1,0,  12,20,  0,0,1 };
float mycolor [] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
unsigned int indices []  = { 0, 1, 2, 3, 4 };
unsigned int vbo;    //vertex buffer object
unsigned int ind;

int px = 15, py = 250;

//initialization
void init( void )
{
  glClearColor( 1.0, 1.0, 1.0, 0.0 );	//get white background color
  glColor3f( 0.0f, 0.0f, 0.0f );	//set drawing color
  glPointSize( 1.0 );			//a dot is 4x4
  glMatrixMode( GL_PROJECTION );
  // glLoadIdentity();
  gluOrtho2D( 0.0, 500.0, 0.0, 500.0 );
  // glGenBuffers ( 1,  &vbo );            //handle to vertex buffer object
  // glGenBuffers ( 1,  &ind );
  // glBindBuffer ( GL_ARRAY_BUFFER, vbo );
  // glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, ind );
  // glBufferData ( GL_ARRAY_BUFFER, sizeof ( mydata ), mydata, GL_STATIC_DRAW );
  // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  // glEnableClientState ( GL_VERTEX_ARRAY );
  // glEnableClientState ( GL_COLOR_ARRAY );
  // glVertexPointer ( 2, GL_FLOAT, 5*sizeof(float), 0 );
  // glColorPointer ( 3, GL_FLOAT, 5*sizeof(float), (void*) (2*sizeof(float)));
  cout << "init\n";
} //init

void setPixel(GLint x,GLint y)
{
  glBegin(GL_POINTS);
     glVertex2i(x,y);
  glEnd();
}
void Circle(int xCenter=100, int yCenter=100){
  int r=10;
  int x=0,y=r;
  int d = 3/2 - r;				// = 1 - r
  while(x<=y){
    setPixel(xCenter+x,yCenter+y);
    setPixel(xCenter+y,yCenter+x);		//find other points by symmetry
    setPixel(xCenter-x,yCenter+y);
    setPixel(xCenter+y,yCenter-x);
    setPixel(xCenter-x,yCenter-y);
    setPixel(xCenter-y,yCenter-x);
    setPixel(xCenter+x,yCenter-y);
    setPixel(xCenter-y,yCenter+x);

    if (d<0)
 	d += (2*x)+3;
    else {
	d += (2*(x-y))+5;
	y -= 1;
    }
    x++;
  }

  glFlush();
}
void stickperson(){
  //head
  Circle(px, py+10);
  glBegin(GL_LINES);
    glVertex2i(px, py);
    glVertex2i(px, (py-30));
    //arms
    glVertex2i(px, py);
    glVertex2i(px-10, py-10);
    glVertex2i(px-10, py-10);
    glVertex2i(px-10, py-20);
    glVertex2i(px, py);
    glVertex2i(px+10, py-10);
    glVertex2i(px+10, py-10);
    glVertex2i(px+10, py-20);
    //legs
    glVertex2i(px, (py-30));
    glVertex2i(px-10, (py-60));
    glVertex2i(px, (py-30));
    glVertex2i(px+10, (py-60));
  glEnd();
  glFlush();
}
bool j[] = {0,0};
void jump(){
  cout << "isjump " << *j << ", up: " << py << ", ";
  if(py < 300 && j[1] == 1){
    cout << "jumping up " << j[1] << "\n";
    py += 10;

  }else if(py > 250 && j[1] == 0){
    cout << "jumping up " << j[1] << "\n";
    py -= 10;
  }else{
    cout << "jumping down " << j[1] << "\n";
    if(j[1] == 1)
      j[1] = 0;
    if(py == 250)
      j[0] = 0;
  }
}
void display()
{
  // glViewport(10,10,50,50);
  cout << "display\n";
  glEnable (GL_LINE_STIPPLE);
  glLineWidth(1);
  glLineStipple (2, 0xFFFF);//0x0002
  glClear( GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT );
  //glColor3f(1.0,0.0,0.0);
  cout << "j before " << *j << endl;
  jump();
  cout << "j after " << *j << endl;
  stickperson();
  glDisable(GL_LINE_STIPPLE);
}

void drawDot( float x, float y )
{
  glBegin( GL_POINTS );
    glVertex2f( x, y );		//draw a points
  glEnd();
} //drawDot

void myMouse( int button, int state, int x, int y )
{
// cout << "\tmyMouse" << x/500.0 << " " << y/500.0 << endl;
  if ( button == GLUT_LEFT_BUTTON && state == GLUT_DOWN )
    drawDot( x/1.0, (screenHeight - y)/1.0 );
  glFlush();				//send all output to screen
}

void myMovedMouse(  int mouseX, int mouseY)
{
  // glColor3f(1.0, 0.0, 0.0);
  // cout << "myMovedMouse" << mouseX/500.0 << " " << mouseY/500.0 << endl;
  glRectf ( (float)(mouseX/1.0), (float)((screenHeight-mouseY)/1.0), (float)((mouseX + 6)/500.0), (float)((screenHeight-mouseY + 6)/500.0 ));
  glFlush();
} //myMovedMouse
void myKeyboard ( unsigned char key, int mouseX, int mouseY )
{
  GLint x = mouseX;
  GLint y = screenHeight - mouseY;
  switch( key )
  {
	case 'J':
		printf("jump\n");
    // cout << "j before " << *j << endl;
    if(j[0] == 0){
      j[0] = 1;
      j[1] = 1;
    }
    // cout << "j after " << *j << endl;
	break;
  case 'j':
    printf("run\n");
    px += 8;
    px = px%500;
    glutPostRedisplay();
	break;
	case 's':
		printf("skate\n");
	break;
    case 'e':
	exit ( -1 );
    default :
	break;
  }
}

void ending(){
  glBindBuffer ( GL_ARRAY_BUFFER, 0 );
  glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, 0 );
}
