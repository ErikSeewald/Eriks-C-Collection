#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define DegRad 0.0174533 //one degree in radians
#define constPI 3.1415926535
float PI = constPI; //cant do == comparisons with constants -> extra variable
float DEG90 = constPI /2;
float DEG270 = 3*constPI/2;

int WIDTH = 1024, HEIGHT = 512;

//PLAYER
float px, py; //"player position"
float pvx, pvy; // "player vector x/y"
float pa = constPI; // "player angle"

void drawPlayer()
{
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
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
};

void drawMap2D()
{
	int x,y,xo,yo; //o - offset
	
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

float dist(float ax, float ay, float bx, float by)
{
	float v1 = bx-ax, v2 = by-ay;
	return ( sqrt(v1*v1 + v2*v2) );
}

//RAYCASTING

void drawRay(float px, float py, float rx, float ry)
{
	glColor3f(1,0,0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2i(px,py);
	glVertex2i(rx,ry);
	glEnd();	
}

void draw3DWall(int ray, float distance, float pa, float rayAngle, int isHorizontal)
{
	float rd = pa - rayAngle; //distance between player angle and ray angle
	if (rd < 0) {rd+=2*PI;}
	if (rd > 2*PI) {rd-=2*PI;}
	distance = distance * cos(rd); //fix fisheye effect (rays further away from player angle are distorted otherwise)
	
	float lineHeight = (mapS*HEIGHT)/distance;
	if (lineHeight > HEIGHT){lineHeight = HEIGHT;}
	
	int lineWidth = WIDTH / 130;
	float lineOffset = HEIGHT/2 - lineHeight/2;
	
	if (isHorizontal) {glColor3f(0.7,0,0);}
	else {glColor3f(0.9,0,0);}
		
	glLineWidth(lineWidth);
	glBegin(GL_LINES);
	glVertex2i(ray*lineWidth+WIDTH/2+lineWidth*2, lineOffset);
	glVertex2i(ray*lineWidth+WIDTH/2+lineWidth*2, lineHeight + lineOffset);
	glEnd();
}

void raycast()
{	
	int mapSize = mapX * mapY;
	int ray, mx, my, mp; //map x/y, map position in array
	int depthOfField;
	float rx, ry, xo, yo; //o - offset
	
	float rayAngle = pa - 30 * DegRad; //minus 30 degrees
	if (rayAngle <0) {rayAngle+=2*PI;}
	if (rayAngle > 2*PI) {rayAngle -=2*PI;}
	
	for(ray=0; ray < 70; ray++)
	{
		//CHECK HORIZONTAL LINES
		depthOfField = 0;
		float distHor = 100000; //set high default value -> check lowest later
		float horX = px, horY = py;
		float aTan=-1/tan(rayAngle);
		
		//looking up
		if(rayAngle > PI) 
		{
			ry = (((int) py / mapS)*mapS)-0.0001; //round to the nearest grid edge -> in this case to the nearest 64th by default
			rx = px + (py-ry)*aTan; // tan = opposite/adjacent -> Tan a * Adjacent = Opposite -> aTan * Opposite = Adjacent -> aTan * ry = rx ("ray check guide.png" in project folder)
			
			yo = -mapS, xo = -yo * aTan; //setting the offsets to the next grid line
		} 
		
		//looking down
		if(rayAngle < PI) 
		{
			ry = (((int) py / mapS)*mapS)+mapS; //round to the nearest grid edge -> in this case to the nearest 64th by default
			rx = px + (py-ry)*aTan; // tan = opposite/adjacent -> Tan a * Adjacent = Opposite -> aTan * Opposite = Adjacent -> aTan * ry = rx ("ray check guide.png" in project folder)
			
			yo = mapS, xo = -yo * aTan; //setting the offsets to the next grid line
		}
		
		//looking straight left or right -> can't hit a horizontal line
		if (rayAngle==0 || rayAngle==PI) 
		{
			rx=px; ry=py; depthOfField = 8;
		}
		
		while (depthOfField < 8)
		{
			mx = (int) rx / mapS; 
			my = (int) ry / mapS;
			mp = my * mapX + mx;
			
			if (mp > 0 && mp < mapSize && map[mp]==1) //hit wall
			{
				depthOfField = 8;
				horX = rx; horY = ry;
				distHor = dist(px,py,horX,horY);
			}
			
			else //check next horizontal line next loop
			{
				rx+=xo;
				ry+=yo;
				++depthOfField;
			}
		}
			
			
		
		//CHECK VERTICAL LINES
		depthOfField = 0;	
		float distVer= 100000; //set high default value -> check lowest later
		float verX = px, verY = py;
		
		float nTan= -tan(rayAngle);
		
		//looking left
		if(rayAngle > DEG90 && rayAngle < DEG270) 
		{
			rx = (((int) px / mapS)*mapS)-0.0001;
			ry = py + (px-rx)*nTan;
			
			xo = -mapS, yo = -xo * nTan; //setting the offsets to the next grid line
		} 
		
		//looking right
		if(rayAngle < DEG90 || rayAngle > DEG270)
		{
			rx = (((int) px / mapS)*mapS)+mapS;
			ry = py + (px-rx)*nTan;
			
			xo = mapS, yo = -xo * nTan; //setting the offsets to the next grid line
		}
			
		//looking straight up or down -> can't hit a vertical line
		if (rayAngle == DEG90 || rayAngle == DEG270) 
		{
			rx=px; ry=py; depthOfField = 8;
		}
		
		while (depthOfField < 8)
		{
			mx = (int) rx / mapS; 
			my = (int) ry / mapS;
			mp = my * mapX + mx;
			
			if (mp > 0 && mp < mapSize && map[mp]==1) //hit wall
			{
				depthOfField = 8;
				distVer = dist(px,py,rx,ry);
			}
			
			else //check next horizontal line next loop
			{
				rx+=xo;
				ry+=yo;
				++depthOfField;
			}
		}
		
		int distance = distVer;
		int isHorizontal = 0;
		if (distHor < distVer) {rx = horX; ry = horY; distance = distHor; isHorizontal = 1;}
		
		drawRay(px,py,rx,ry);
		
		draw3DWall(ray, distance,  pa, rayAngle, isHorizontal);
		
		rayAngle+=DegRad; //plus one degree
		if (rayAngle <0) {rayAngle+=2*PI;}
		if (rayAngle > 2*PI) {rayAngle -=2*PI;}
	}
}


//DISPLAY
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawPlayer();
	raycast();
	glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
	//using radians instead of degrees -> 0 - 2PI
	if(key=='a')	{pa-=0.1; if(pa < 0){pa+=2*PI;} pvx=cos(pa)*5; pvy = sin(pa)*5;}	

	if(key=='d')	{pa+=0.1; if(pa > 2*PI){pa-=2*PI;} pvx=cos(pa)*5; pvy= sin(pa)*5;}
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
