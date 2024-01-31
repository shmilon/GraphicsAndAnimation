#include <iostream>
#include<GL/gl.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <bits/stdc++.h>
#include<GL/gl.h>
#include<windows.h>
#include<math.h>
#include <cmath>
// for the mouse movement

using namespace std;

const int width = 1000;
const int height = 1000;

GLfloat eyeX = 10;
GLfloat eyeY = 50;
GLfloat eyeZ =50;
GLfloat lookX = 10;
GLfloat lookY = 0;
GLfloat lookZ = 0;

// variable for mouse movement


// end mouse controlling

/// test showing
void renderText(float x, float y, const char* text) {
  glColor3f(1.0f, 1.0f, 1.0f); // white color
  glRasterPos3f(x, y, 0.0f); // position text on screen

  for (int i = 0; i < strlen(text); ++i) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
  }
}

/// functions for creating red circle
void Draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_QUADS);
      glColor3f (1, 0.0, 0.0);

      glVertex3f (0.1, 0.1, 0.0);
      glVertex3f (0.9, 0.1, 0.0);
      glVertex3f (0.9, 0.9, 0.0);
      glVertex3f (0.1, 0.9, 0.0);

    glEnd();

    glFlush();
}

void DrawCircle(float cx, float cy, float r, int num_segments)
{
    Draw();
    glBegin(GL_TRIANGLE_FAN);
    for(int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

/// end creating red circle



// mouse movement function


// end mouse movement function





static GLfloat v_cube[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte c_ind[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(float r,float g,float b)
{

    glBegin(GL_QUADS);
    glColor3d(r,g,b);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[c_ind[i][0]][0], v_cube[c_ind[i][0]][1], v_cube[c_ind[i][0]][2],
                    v_cube[c_ind[i][1]][0], v_cube[c_ind[i][1]][1], v_cube[c_ind[i][1]][2],
                    v_cube[c_ind[i][2]][0], v_cube[c_ind[i][2]][1], v_cube[c_ind[i][2]][2]);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_cube[c_ind[i][j]][0]);
        }
    }
    glEnd();
}

 void flagShow(){


    glPushMatrix();
        glTranslated(-35,5,3);
        glScaled(1,20,1);
        cube(1,1,1);
    glPopMatrix();

     glPushMatrix();
        glTranslated(-35,25,3);
        glScaled(7,5,1);
        cube(0,.5,0);
    glPopMatrix();



   }

static void display(void)
{
    // basic functions for display
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /// show the text

    // Convert float values to strings
  char eyeXStr[16];
  char eyeYStr[16];
  char eyeZStr[16];
  char lookXStr[16];
  char lookYStr[16];
  char lookZStr[16];

  sprintf(eyeXStr, "%.2f", eyeX);
  sprintf(eyeYStr, "%.2f", eyeY);
  sprintf(eyeZStr, "%.2f", eyeZ);
  sprintf(lookXStr, "%.2f", lookX);
  sprintf(lookYStr, "%.2f", lookY);
  sprintf(lookZStr, "%.2f", lookZ);

  // Draw text at specific positions
  renderText(10.0f, 10.0f, "Eye X:");
  renderText(30.0f, 10.0f, eyeXStr);
  renderText(10.0f, 20.0f, "Eye Y:");
  renderText(30.0f, 20.0f, eyeYStr);
  renderText(10.0f, 30.0f, "Eye Z:");
  renderText(30.0f, 30.0f, eyeZStr);
  renderText(10.0f, 40.0f, "Look X:");
  renderText(30.0f, 40.0f, lookXStr);
  renderText(10.0f, 50.0f, "Look Y:");
  renderText(30.0f, 50.0f, lookYStr);
  renderText(10.0f, 60.0f, "Look Z:");
  renderText(30.0f, 60.0f, lookZStr);
    /// end showing text



    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
   gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);

   // Set camera position based on direction



    // end basic functions for display

    DrawCircle(0,15,-5,50);


    // Gound
    glPushMatrix();
        glTranslated(-100,0,-150);
        glScaled(200,1,200);
        cube(0.4,0.6,0.5);
    glPopMatrix();

    // end ground



//main field
    glPushMatrix();
        glTranslated(-50,1,0);
        glScaled(100,1,40);
        cube(.3,0,0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-48,2,0);
        glScaled(97,1,38);
        cube(0.4,0,0.0);
    glPopMatrix();

    glPushMatrix();
        glTranslated(-46,3,0);
        glScaled(93,1,36);
        cube(.5,0,0);
    glPopMatrix();
// field end

    // minar 1

    // main minar

    // minar 1
    glPushMatrix();
        glTranslated(-10,4,1);

        glPushMatrix();
            glTranslated(7,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(10,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(13,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(7,20,0);
            glScaled(7,1,1);
            cube(1,1,1);
        glPopMatrix();

    glPopMatrix();


glPushMatrix();
        glTranslated(-20,2,1);

        glPushMatrix();
            glTranslated(7,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(10,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(13,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(7,20,0);
            glScaled(7,1,1);
            cube(1,1,1);
        glPopMatrix();

    glPopMatrix();


glPushMatrix();
        glTranslated(-30,0,1);

        glPushMatrix();
            glTranslated(7,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(10,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(13,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(7,20,0);
            glScaled(7,1,1);
            cube(1,1,1);
        glPopMatrix();

    glPopMatrix();


glPushMatrix();
        glTranslated(0,2,1);

        glPushMatrix();
            glTranslated(7,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(10,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(13,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(7,20,0);
            glScaled(7,1,1);
            cube(1,1,1);
        glPopMatrix();

    glPopMatrix();


glPushMatrix();
        glTranslated(10,0,1);

        glPushMatrix();
            glTranslated(7,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(10,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(13,0,0);
            glScaled(1,20,1);
            cube(1,1,1);
        glPopMatrix();

        glPushMatrix();
            glTranslated(7,20,0);
            glScaled(7,1,1);
            cube(1,1,1);
        glPopMatrix();

    glPopMatrix();





    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {

    case 'w':
        eyeY=eyeY+0.1;
        break;
    case 's':
        eyeY=eyeY-0.1;
        break;
    case 'd':
        eyeX=eyeX+0.1;
        break;
    case 'a':
        eyeX=eyeX-0.1;
        break;

    case 'i':
        lookY=lookY+0.1;
        break;
    case 'k':
        lookY=lookY-0.1;
        break;
    case 'j':
        lookX=lookX+0.1;
        break;
    case 'l':
        lookX=lookX-0.1;
        break;


    case '+':
        eyeZ=eyeZ+0.1;
        break;
    case '-':
        eyeZ=eyeZ-0.1;
        break;

    }

    glutPostRedisplay();
}


int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(100,100);
    glutInitWindowSize(1000,1000);
    glutCreateWindow("Final Project");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMainLoop();

    return 0;
}
