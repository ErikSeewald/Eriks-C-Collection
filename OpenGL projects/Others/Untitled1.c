#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

// Global variables
GLsizei winWidth = 600, winHeight = 600;  // Initial display window size
GLint xRaster = 25, yRaster = 150;        // Initial raster position

// Routine to draw a bitmap character string
void writeBitmapString(void *font, char *string)
{
    char *c;

    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Initialization routine
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

// Routine to draw a square
void drawSquare(void)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);  // Draw square in wireframe mode

    // Set square color to black
    glColor3f(0.0, 0.0, 0.0);

    // Draw square
    glBegin(GL_POLYGON);
    glVertex2i(200, 200);
    glVertex2i(400, 200);
    glVertex2i(400, 400);
    glVertex2i(200, 400);
    glEnd();
}

void drawCube()
{
  // Set the background color to black
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set the view transformation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  // Move the cube to the center of the window
  glTranslatef(150, 150, 0.0);
  

  // Apply a perspective projection
  glMatrixMode(GL_PROJECTION);
  gluPerspective(45.0, 1.0, 1.2, 1.0);

  // Set the drawing color to white
  glColor3f(1.0, 1.0, 1.0);

  // Draw the cube
  glutSolidCube(100.0);

  // Swap the front and back buffers
  glutSwapBuffers();
}


// Window redraw function
void redraw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSquare();
    //drawCube();
    glFlush();
}

// OpenGL window reshape routine
void resize(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 600.0, 0.0, 600.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Keyboard input processing routine
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    // Press escape to exit
    case 27:
        
        break;
    default:
        break;
    }
}

// Main routine
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("drawSquare.c");
    setup();
    glutDisplayFunc(redraw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutMainLoop();

    return 0;
}
