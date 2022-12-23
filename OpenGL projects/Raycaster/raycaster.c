#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#define DegRad 0.0174533 //one degree in radians
#define constPI 3.1415926535
float PI = constPI; //cant do == comparisons with constants -> extra variable
float DEG90 = constPI /2;
float DEG270 = 3*constPI/2;

typedef struct 
{
	int w,a,s,d; //button state on off
}ButtonKeys; 
ButtonKeys Keys;

int All_Textures[]=               //all 32x32 textures
{
 //Checkerboard
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 //Brick
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 //Window
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,    
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,   
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 //Door
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,     

 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  

 0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 
 
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,     
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,         
};

int WIDTH = 1024, HEIGHT = 512;

//PLAYER
float px, py; //"player position"
float pvx, pvy; // "player vector x/y"7
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
	1,0,0,0,0,1,0,1,
	1,0,0,0,0,0,0,1,
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

//RAYCASTING
float dist(float ax, float ay, float bx, float by)
{
	float v1 = bx-ax, v2 = by-ay;
	return ( sqrt(v1*v1 + v2*v2) );
}

void drawRay(float px, float py, float rx, float ry)
{
	glColor3f(1,0,0);
	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2i(px,py);
	glVertex2i(rx,ry);
	glEnd();	
}

void draw3DWall(int ray, float rx, float ry, float distance, float pa, float rayAngle, int isHorizontal, float shade)
{
	float rd = pa - rayAngle; //distance between player angle and ray angle
	if (rd < 0) {rd+=2*PI;}
	if (rd > 2*PI) {rd-=2*PI;}
	distance = distance * cos(rd); //fix fisheye effect (rays further away from player angle are distorted otherwise)
	
	float lineHeight = (mapS*HEIGHT)/distance;
	float texStep = 32.0 / (float) lineHeight;
	float texOffset = 0;
	if (lineHeight > HEIGHT){ texOffset = (lineHeight - HEIGHT)/2.0; lineHeight = HEIGHT;}
	
	float lineOffset = HEIGHT/2 - lineHeight/2;
	
	if (isHorizontal) {glColor3f(0.7,0,0);}
	else {glColor3f(0.9,0,0);}
		
	int y;
	float texY = texOffset*texStep;
	float texX;

	if (shade == 1)
	{
		texX= (int) (ry/2.0)%32;
		if (rayAngle > DEG90 && rayAngle < DEG270) {texX = 31-texX;} //flip textures#
	}
	else
	{	
		texX= (int) (rx/2.0)%32;
		if (rayAngle < PI) {texX = 31-texX;} //flip textures
	}
	
	texY+=32;
	
	
	for (y = 0; y < lineHeight; y++)
	{
		float c=All_Textures[(int) (texY)*32 + (int) (texX)] * shade;
		glColor3f(c,c,c);
		glPointSize(8);
		glBegin(GL_POINTS);
		glVertex2i(ray*8+WIDTH/2+8*2, y+lineOffset);
		glEnd();
		texY+=texStep;
	}
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
		
		float shade = 1;
		int distance = distVer;
		int isHorizontal = 0;
		if (distHor < distVer) {shade = 0.5; rx = horX; ry = horY; distance = distHor; isHorizontal = 1;}
		
		drawRay(px,py,rx,ry);
		
		draw3DWall(ray, rx, ry, distance,  pa, rayAngle, isHorizontal, shade);
		
		rayAngle+=DegRad; //plus one degree
		if (rayAngle <0) {rayAngle+=2*PI;}
		if (rayAngle > 2*PI) {rayAngle -=2*PI;}
	}
}


float frame1, frame2, fps;

//DISPLAY
void display()
{
	//frames per second
	frame2=glutGet(GLUT_ELAPSED_TIME);
	fps=(frame2-frame1);
	frame1=glutGet(GLUT_ELAPSED_TIME);

	//ROTATION
	if(Keys.a==1)	{pa-=0.003*fps; if(pa < 0){pa+=2*PI;} pvx=cos(pa)*5; pvy = sin(pa)*5;}	
	if(Keys.d==1)	{pa+=0.003*fps; if(pa > 2*PI){pa-=2*PI;} pvx=cos(pa)*5; pvy= sin(pa)*5;}

	//MOVEMENT
	int xo = 0; if (pvx<0) {xo=-20;} else {xo=20;}
	int yo = 0; if (pvy<0) {yo=-20;} else {yo=20;}
	int ipx=px/64, ipx_add_xo=(px+xo)/64, ipx_sub_xo=(px-xo)/64; //PLAYER GRID POS
	int ipy=py/64, ipy_add_yo=(py+yo)/64, ipy_sub_yo=(py-yo)/64;
	
	if(Keys.w==1)	
	{
		if(map[ipy*mapX + ipx_add_xo]==0){px+=pvx*0.03*fps;} //COLLISION DETECTION
		
		if(map[ipy_add_yo*mapX + ipx]==0){py+=pvy*0.03*fps;}
	}
	
	if(Keys.s==1)	
	{
		if(map[ipy*mapX + ipx_sub_xo]==0){px-=pvx*0.03*fps;} //COLLISION DETECTION
		
		if(map[ipy_sub_yo*mapX + ipx]==0){py-=pvy*0.03*fps;}
	}
	
	glutPostRedisplay();

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawMap2D();
	drawPlayer();
	raycast();
	glutSwapBuffers();
}

void ButtonDown(unsigned char key, int x, int y)
{
	if(key=='a')	{Keys.a=1;}	
	if(key=='d')	{Keys.d=1;}
	if(key=='w')	{Keys.w=1;}
	if(key=='s')	{Keys.s=1;}	
	
	glutPostRedisplay();
}

void ButtonUp(unsigned char key, int x, int y)
{
	if(key=='a')	{Keys.a=0;}	
	if(key=='d')	{Keys.d=0;}
	if(key=='w')	{Keys.w=0;}
	if(key=='s')	{Keys.s=0;}	
	
	glutPostRedisplay();
}

void init()
{
	glClearColor(0.25, 0.25, 0.35, 0);
	gluOrtho2D(0,1024,512,0);
	px=300; py=300;
	pvx=cos(pa)*5; pvy= sin(pa)*5;
}

void resize(int w, int h)
{
	glutReshapeWindow(1024,512);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(200,200);
	glutCreateWindow("Raycaster");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(ButtonDown);
	glutKeyboardUpFunc(ButtonUp);
	glutMainLoop();
}
