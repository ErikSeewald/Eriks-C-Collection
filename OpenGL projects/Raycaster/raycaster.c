#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define PI 3.1415926535

int WIDTH = 1024, HEIGHT = 512;

//PLAYER
float px, py; //"player position"
float pvx, pvy; // "player vector x/y"
float pa; // "player angle"

void drawPlayer()
{
	//DRAW FACING ANGLE
	glColor3f(1,0,0);
	glLineWidth(3);
	glBegin(GL_LINES);
	glVertex2i(px,py);
	glVertex2i(px+pvx*5, py+pvy*5);
	glEnd();
	
	//PLAYER
	glColor3f(0,1,0);
	glPointSize(8);
	glBegin(GL_POINTS);
	glVertex2i(px,py);
	glEnd();
}

//MAP
int mapX = 8, mapY = 8;
int mapS = 64; //size of grid squares

int map[] =
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,1,0,1,
	1,1,1,1,0,0,0,1,
	1,0,0,1,0,1,0,1,
	1,0,0,1,0,0,0,1,
	1,0,0,0,0,1,0,0,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void drawMap2D()
{
	int x,y,xo,yo;
	
	for(y = 0; y < mapY; y++)
	{
		for(x = 0; x < mapX; x++)
		{
			if(map[y*mapY+x] == 1) 
			{glColor3f(0.85,0.85,0.95);}
			
			else 
			{glColor3f(0.05,0.05,0.1);}
			
			xo = x*mapS; yo = y*mapS;
			glBegin(GL_QUADS);
			glVertex2i(xo	+1	,	yo	+1		);
			glVertex2i(xo+mapS-1,	yo	+1		);
			glVertex2i(xo+mapS-1,	yo+mapS-1	);
			glVertex2i(xo	+1	,	yo+mapS-1	);
			glEnd();
		}
	}
}

//RAYCASTING
void drawRays3D()
{
	int ray, mx, my, mp, dof;
	float rx, ry, xo, yo;
	float rayAngle = pa;
	
	for(ray=0; ray < 1; ray++)
	{
		//CHECK HORIZONTAL LINES
		dof = 0;
		float aTan=-1/tan(rayAngle);
		
		//looking up
		if(rayAngle > PI) 
		{
			ry = ((int) py / mapS)*mapS)-0.0001; //round to the nearest grid edge -> in this case to the nearest 64th by default
			rx = px + (py-ry)*aTan; // tan = opposite/adjacent -> Tan a * Adjacent = Opposite -> aTan * Opposite = Adjacent -> aTan * ry = rx ("ray check guide.png" in project folder)
		} 
		
	}
}

//DISPLAY
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawPlayer();
	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
	//using radians instead of degrees -> 0 - 2PI
	if(key=='a')	{pa-=0.1; if(pa < 0){pa+=2*PI;} pvx=cos(pa)*5; pvy = sin(pa)*5;}	

	if(key=='d')	{pa+=0.1; if(pa > 2*PI){pa+=2*PI;} pvx=cos(pa)*5; pvy= sin(pa)*5;}
	if(key=='w')	{px+=pvx; py+=pvy;}
	if(key=='s')	{px-=pvx; py-=pvy;}	
	
	glutPostRedisplay();
}

void init()
{
	glClearColor(0.25, 0.25, 0.35, 0);
	gluOrtho2D(0,1024,512,0);
	px=300; py=300;
	pvx=cos(pa)*5; pvy= sin(pa)*5;
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("Raycaster");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(buttons);
	glutMainLoop();
}


