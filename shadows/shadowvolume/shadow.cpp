//scene.cpp

using namespace std;

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define M_INFINITY 50.0f
#define NCUBES	4	
#define NSURFACES 2 

//a quad surface
struct surface {
  float vertices[4][3];	//contains 4 3D vectors representing vertices of a quadrilateral surface
};

struct cube {
  struct surface *surfaces[NSURFACES];	//a cube has 6 surfaces
  float position[3];		//position of the cube
};

//dot product of two vectors
static float dot_product(float v1[3], float v2[3])
{
  return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

//normalize a vector
static void normalize(float v[3])
{
  float f = 1.0f / sqrt(dot_product(v, v));

  v[0] *= f;
  v[1] *= f;
  v[2] *= f;
}

//cross product of two vectors
static void cross_product(const float *v1, const float *v2, float *out)
{
  out[0] = v1[1] * v2[2] - v1[2] * v2[1];
  out[1] = v1[2] * v2[0] - v1[0] * v2[2];
  out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

//(3x3 matrix) x (3x1 vector) 
static void multiply_vector_by_matrix(const float m[9], float v[3])
{
  float tmp[3];

  tmp[0] = v[0] * m[0] + v[1] * m[3] + v[2] * m[6];
  tmp[1] = v[0] * m[1] + v[1] * m[4] + v[2] * m[7];
  tmp[2] = v[0] * m[2] + v[1] * m[5] + v[2] * m[8];

  v[0] = tmp[0];
  v[1] = tmp[1];
  v[2] = tmp[2];
}

//creates a new quad surface
static struct surface *new_surface(float vertices[4][3])
{
  int i, j;
  struct surface *surf;

  surf = ( struct surface *) malloc(sizeof(struct surface));
  if(!surf) {
    fprintf(stderr, "Error: Couldn't allocate memory for surface\n");
    return NULL;
  }

  for(i = 0; i < 4; i++) {
    for(j = 0; j < 3; j++)
	surf->vertices[i][j] = vertices[i][j];
  }

  return surf;
}

void render_surface_shadow_volume(
  struct surface *surf, 	//points to a surface
  float *surf_pos, 		//points to a 3D vector representing the surface's position
  float *light_pos		//points to a 3D vecotr representing position of light that's blocked by the surface
)
{
  int i;
  float v[4][3];

  for(i = 0; i < 4; i++) {
    surf->vertices[i][0] += surf_pos[0];		//vertices are now world coordinates
    surf->vertices[i][1] += surf_pos[1];
    surf->vertices[i][2] += surf_pos[2];

    v[i][0] = (surf->vertices[i][0] - light_pos[0]);	//v[] has 'origin' centered at light
    v[i][1] = (surf->vertices[i][1] - light_pos[1]);
    v[i][2] = (surf->vertices[i][2] - light_pos[2]);
    normalize(v[i]);
    v[i][0] *= M_INFINITY;
    v[i][1] *= M_INFINITY;
    v[i][2] *= M_INFINITY;
    v[i][0] += light_pos[0];		//added by Tong to get the correct equation
    v[i][1] += light_pos[1];
    v[i][2] += light_pos[2];
  }

  /* back cap */
  glBegin(GL_QUADS);
    glVertex3fv(v[3]);
    glVertex3fv(v[2]);
    glVertex3fv(v[1]);
    glVertex3fv(v[0]);
  glEnd();


  /* front cap */
  glBegin(GL_QUADS);
    glVertex3fv(surf->vertices[0]);
    glVertex3fv(surf->vertices[1]);
    glVertex3fv(surf->vertices[2]);
    glVertex3fv(surf->vertices[3]);
  glEnd();

  glPushAttrib ( GL_ALL_ATTRIB_BITS );
  glColor3f ( 0, 1, 0 );
  glBegin(GL_QUAD_STRIP);		//The shadow volume
    glVertex3fv(surf->vertices[0]);
    glVertex3fv(v[0]);
    for(i = 1; i <= 4; i++) {
      glVertex3fv(surf->vertices[i % 4]);
      glVertex3fv(v[i % 4]);
    }
  glEnd();
  glPopAttrib();
  
  //restore vertice values ( relative to surface position )
  for(i = 0; i < 4; i++) {
    surf->vertices[i][0] -= surf_pos[0];
    surf->vertices[i][1] -= surf_pos[1];
    surf->vertices[i][2] -= surf_pos[2];
  }
}

static struct cube *new_cube(float size)
{
  int i;
  struct cube *c;
  float v[4][3];
  int error = 0;

  c = (struct cube *) malloc(sizeof(struct cube));
  if(!c)
    return NULL;

  c->position[0] = 0.0f;
  c->position[1] = 0.0f;
  c->position[2] = 0.0f;

  v[0][0] = -size; v[0][1] = size; v[0][2] = size;
  v[1][0] = -size; v[1][1] = -size; v[1][2] = size;
  v[2][0] = size; v[2][1] = -size; v[2][2] = size;
  v[3][0] = size; v[3][1] = size; v[3][2] = size;
  c->surfaces[0] = new_surface(v);
/*
  v[0][0] = size; v[0][1] = size; v[0][2] = -size;
  v[1][0] = size; v[1][1] = -size; v[1][2] = -size;
  v[2][0] = -size; v[2][1] = -size; v[2][2] = -size;
  v[3][0] = -size; v[3][1] = size; v[3][2] = -size;
  c->surfaces[0] = new_surface(v);
 */ 
  v[0][0] = size; v[0][1] = size; v[0][2] = -size;
  v[1][0] = size; v[1][1] = -size; v[1][2] = -size;
  v[2][0] = -size; v[2][1] = -size; v[2][2] = -size;
  v[3][0] = -size; v[3][1] = size; v[3][2] = -size;
  c->surfaces[1] = new_surface(v);

  v[0][0] = -size; v[0][1] = size; v[0][2] = -size;
  v[1][0] = -size; v[1][1] = size; v[1][2] = size;
  v[2][0] = size; v[2][1] = size; v[2][2] = size;
  v[3][0] = size; v[3][1] = size; v[3][2] = -size;
  c->surfaces[2] = new_surface(v);

  v[0][0] = size; v[0][1] = -size; v[0][2] = -size;
  v[1][0] = size; v[1][1] = -size; v[1][2] = size;
  v[2][0] = -size; v[2][1] = -size; v[2][2] = size;
  v[3][0] = -size; v[3][1] = -size; v[3][2] = -size;
  c->surfaces[3] = new_surface(v);

  v[0][0] = -size; v[0][1] = size; v[0][2] = size;
  v[1][0] = -size; v[1][1] = size; v[1][2] = -size;
  v[2][0] = -size; v[2][1] = -size; v[2][2] = -size;
  v[3][0] = -size; v[3][1] = -size; v[3][2] = size;
  c->surfaces[4] = new_surface(v);

  v[0][0] = size; v[0][1] = -size; v[0][2] = size;
  v[1][0] = size; v[1][1] = -size; v[1][2] = -size;
  v[2][0] = size; v[2][1] = size; v[2][2] = -size;
  v[3][0] = size; v[3][1] = size; v[3][2] = size;
  c->surfaces[5] = new_surface(v);

  for(i = 0; i < NSURFACES; i++) {
    if(!c->surfaces[i])
	error = 1;
  }

  if(error != 0) {
    for(i = 0; i < NSURFACES; i++) {
	if(c->surfaces[i])
	  free(c->surfaces[i]);
    }

    free(c);
    return NULL;
  }

  return c;
}

static float light_pos[3] = { 10.0f, 0.0f, 8.0f };
static float light_color[3] = { 0.8f, 0.4f, 0.8f };

static void draw_shadow()
{
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glOrtho(0, 1, 1, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);

  //glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
  glColor4f(0.0f, 0.8f, 0.0f, 0.5f);
  //occupies the whole screen
  glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 1, 0);
    glVertex3i(1, 1, 0);
    glVertex3i(1, 0, 0);
  glEnd();

/*
  glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(0, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, 0);
  glEnd();
*/
  glEnable(GL_DEPTH_TEST);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
}

static void render_surface(struct surface *surf, float *position)
{
  glPushMatrix();
  glTranslatef(position[0], position[1], position[2]);

  glBegin(GL_QUADS);
    glVertex3fv(surf->vertices[0]);
    glVertex3fv(surf->vertices[1]);
    glVertex3fv(surf->vertices[2]);
    glVertex3fv(surf->vertices[3]);
  glEnd();

  glPopMatrix();
}

static void render_cube(struct cube *c)
{
  int i;
  for(i = 0; i < NSURFACES; i++){
    if ( i == 0 ) continue;
    render_surface(c->surfaces[i], c->position);
  }
}

static void render_cuber(struct cube *c)
{
  int i;
  //shadow is projected on the back room wall
  for(i = 0; i < NSURFACES; i++){
    if ( i == 0 ) continue;		//won't work if skip i == 1
    render_surface(c->surfaces[i], c->position);
  }
}


//render a shadow for each surface of a cube
void render_cube_shadow(struct cube *c)
{
  int i;
  //for(i = 0; i < NSURFACES; i++) {
  for(i = 0; i < 1; i++) {
//glEnable(GL_STENCIL_TEST);		//enable stencil testing
//glClearStencil ( 0x1 );
//glClearStencil ( 0x0 );
//glClear ( GL_STENCIL_BUFFER_BIT );
//glStencilFunc ( GL_EQUAL, 0x1, 0x1 );
//glStencilOp ( GL_REPLACE, GL_REPLACE, GL_REPLACE ); 
//goto drawing;
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);//disable writing to color buffer
    glDepthMask(GL_FALSE);		//disable writing to depth buffer (we only care stencil buffer here
    glEnable(GL_STENCIL_TEST);		//enable stencil testing
    glEnable(GL_CULL_FACE);		//will enable both front and back culling ( below )
    glEnable(GL_POLYGON_OFFSET_FILL);	//for working around for some depth buffer precision issues
    glPolygonOffset(0.0f, 100.0f);	//   some depth buffer precision issues

    glCullFace(GL_FRONT);		//cull front faces; only draw back faces	
    glStencilFunc(GL_ALWAYS, 0x0, 0xff);//always passes, ref value = 0, mask = 0xFF

    //keep value when stencil test fails, increment value when passes, keep value if both 
    //  stencil test and depth test pass
    glStencilOp(GL_KEEP, GL_INCR, GL_KEEP);
    render_surface_shadow_volume(c->surfaces[i], c->position, light_pos);
    glCullFace(GL_BACK);		//cull back faces; only draw front faces
    glStencilFunc(GL_ALWAYS, 0x0, 0xff);
    glStencilOp(GL_KEEP, GL_DECR, GL_KEEP);//decrement stencil value when test passes
    render_surface_shadow_volume(c->surfaces[i], c->position, light_pos);

    glDisable(GL_POLYGON_OFFSET_FILL);	//disable polygon offset
    glDisable(GL_CULL_FACE);		//disable front/back culling
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);	//reanble writing to color buffer
    glDepthMask(GL_TRUE);		//renable writing to depth buffer

    glStencilFunc(GL_NOTEQUAL, 0x0, 0xff);		//reset each pixel's stencil value
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);	//  for anything we draw.
drawing:
    draw_shadow();			//draw the shadow ( dark quad )
 //   draw_shadow();			//draw the shadow ( dark quad )
    glDisable(GL_STENCIL_TEST);		//disable stencil testing
  }
}

static float cam_rot[3] = { 22.0f, 0.0f, 0.0f };
static struct cube *cubes[4];
static float sphere_pos[3] = { -10.0f, -5.0f, -10.0f };

void scene_render()
{
  static struct cube *room;
  static unsigned int surface_tex_num;
  static GLUquadricObj *sphere;
  int i;

  if(!cubes[0]) {
    unsigned char *data;
    unsigned int width, height;

 
    /* create objects */
    //room = new_cube(15.0f);
    room = new_cube(5.0f);

    cubes[0] = new_cube(1.0f);
    cubes[0]->position[0] = -2.0f;
    cubes[0]->position[1] = -2.0f;
    cubes[1] = new_cube(1.0f);
    cubes[1]->position[0] = 2.0f;
    cubes[1]->position[1] = -2.0f;
    cubes[2] = new_cube(1.0f);
    cubes[2]->position[0] = 2.0f;
    cubes[2]->position[1] = 2.0f;
    cubes[3] = new_cube(1.0f);
    cubes[3]->position[0] = -2.0f;
    cubes[3]->position[1] = 2.0f;

    sphere = gluNewQuadric();
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glLoadIdentity();
  glTranslatef(0.0f, 0.0f, -15.0f);
  glRotatef(cam_rot[0], 1.0f, 0.0f, 0.0f);
  glRotatef(cam_rot[1], 0.0f, 1.0f, 0.0f);
  glRotatef(cam_rot[2], 0.0f, 0.0f, 1.0f);

  glColor4f(0.75f, 0.0f, 0.0f, 1.0f);
  glPushMatrix();
  glTranslatef(sphere_pos[0], sphere_pos[1], sphere_pos[2]);
  gluSphere(sphere, 2.5f, 30, 30);
  glPopMatrix();

  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  
  /* render each cube */
  glPushAttrib ( GL_ALL_ATTRIB_BITS );
  glColor3f ( 1, 1, 0 );
  for(i = 0; i < NCUBES; i++) {
    if(!cubes[i])
      break;
    render_cube(cubes[i]);
  }
  glPopAttrib();
  glColor3f ( 0,0,1);
  render_cuber(room);
  // render shadows 
  for(i = 0; i < NCUBES; i++)
    render_cube_shadow(cubes[i]);
  //render_cuber(room);
  /* render light */
  glColor3fv(light_color);
  glPointSize ( 8 );
  glBegin ( GL_POINT );
    glVertex3fv ( light_pos );
  glEnd();
  
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
  glFlush();
  glutSwapBuffers();
}

static unsigned int get_ticks()
{
  struct timeval t;

  gettimeofday(&t, NULL);

  return (t.tv_sec * 1000) + (t.tv_usec / 1000);
}

void scene_cycle()
{
  static float light_rot = 0.0f;
  static float sphere_rot = 0.0f;
  static unsigned int prev_ticks = 0;
  unsigned int ticks;
  float time;

  if(!prev_ticks)
  prev_ticks = get_ticks();

  ticks = get_ticks();
  time = (float)(ticks - prev_ticks);
  prev_ticks = ticks;

  light_pos[0] = cosf(light_rot) * 5.0f;
  light_rot += 0.0005f * time;

  sphere_pos[0] = cosf(sphere_rot) * 10.0f;
  sphere_pos[1] = sinf(sphere_rot) * 5.0f;
  sphere_rot += 0.0001f * time;

  scene_render();
}
