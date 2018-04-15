#include <stdio.h> 
#include <math.h>
#include <GL/glut.h>
#include <iostream>

#include "CAR.h"
#include "MOTION.h"
#include "CAMERA.h"

using namespace std;


CAR car;
MOTION m;
CAMERA cam;



int ax=-1;
int vx=-1;

float t=30;


void Axes()
{   
    glLineWidth(4);
     
    glColor3f(0,0,1);

    glBegin(GL_LINES);      //Z
    glVertex3f(0,0,5000);
    glVertex3f(0,0,-5000);
    glEnd();



     glColor3f(0,1,1);

    glBegin(GL_LINES);     //Y
    glVertex3f(0,5000,0);
    glVertex3f(0,0,0);
    glEnd();

     glColor3f(0,0,0);

    glBegin(GL_LINES);        //X
    glVertex3f(5000,0,0);
    glVertex3f(-5000,0,0);
    glEnd();

    glLineWidth(1);


    for(int i=-100;i<=100;i+=10)
    {
       glColor3f(0,0,0);
     glBegin(GL_LINES);      //Z
    glVertex3f(i,0,100);
    glVertex3f(i,0,-100);
    glEnd();

    }

    for(int i=-100;i<=100;i+=10)
    {
      glColor3f(0,0,0);
     glBegin(GL_LINES);        //X
    glVertex3f(100,0,i);
    glVertex3f(-100,0,i);
    glEnd();

    }

    
}




void reshape(int w,int h)
{
   glClearColor(1.0, 1.0, 1.0, 0.0);         // black background 
 
   glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

float omega=0;
float wa=0;

void meter()
{
           // black background 
 glMatrixMode(GL_PROJECTION);              // setup viewing projection 
 glLoadIdentity();
 glViewport(0,0,200,200);                           // start with identity matrix 
 glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);   // setup a 10x10x2 viewing world

 
  glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

glTranslatef(0,-50,0);

 glColor3f(0.663, 0.663, 0.663); 
 
  GLUquadricObj *p = gluNewQuadric();
        
  gluDisk(p,0,100,100,100);

  //MARKINGS

  glTranslatef(0,0,0.5);


  
  glColor3f(0,0,0);
  gluDisk(p,92,100,100,100);





  glColor3f(0,0.980,0.604);
  gluPartialDisk(p,70,90,100,100,-120,40);
  glColor3f(0.196,0.804,0.196);
  gluPartialDisk(p,70,90,100,100,-80,40);
  glColor3f(0.604,0.804,0.196);
  gluPartialDisk(p,70,90,100,100,-40,40);
  glColor3f(1,0.843,0);
  gluPartialDisk(p,70,90,100,100,0,40);
  glColor3f(1,0.549,0);
  gluPartialDisk(p,70,90,100,100,40,40);
  glColor3f(1,0.271,0);
  gluPartialDisk(p,70,90,100,100,80,40);
  

  float NT=220;
  float nangle=(200/600.0)*(abs(m.Speed));
  
  if(nangle<220)
  NT=220-nangle;

  else
    NT=340;
  

  cout<<NT<<endl;

 glColor3f(0,0,1);

 glLineWidth(5);

  glBegin(GL_LINES);   //needle
  glVertex3f(1,0,0);
  glVertex3f(80*cos(NT*3.14/180),80*sin(NT*3.14/180),0.5);
  glEnd();



    char text[32];
    sprintf(text, "%.0f", m.Speed/3);
    glColor3f(0, 0, 0);
    glRasterPos3f( -20 , 20 ,0);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);




 

 glFlush(); 
}



void display(void) 
{ 

   glClearColor(1,1,1,0);

   

   glClearDepth(1);
   glClear(GL_COLOR_BUFFER_BIT);
   glClear(GL_DEPTH_BUFFER_BIT);

   glEnable(GL_DEPTH_TEST);
  
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glViewport(0,0,800,800);   
   gluPerspective(45,1,1,10000);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

 
   cam.SetDriveCamera(m.X,m.Y,m.Z,m.ux,m.uz);
  
   if(ax==1)
   Axes();

  // car.SelectModel(1);
  
   car.DrawCar(m.X,m.Y+2,m.Z,m.theta,wa);
   
 //  if(vx==1)
  // drawVector();

   
    glFlush(); 
}



void special(int key,int x,int y)
{
   switch(key)
   {
      case GLUT_KEY_LEFT:{ m.theta=m.theta-4.5; } break;
      case GLUT_KEY_RIGHT: { m.theta=m.theta+4.5;} break;
      case GLUT_KEY_UP:    m.Speed=m.Speed+m.Acc/10; break;
      case GLUT_KEY_DOWN:  m.Speed=m.Speed-m.Acc/10; break; 

      case GLUT_KEY_F1:  car.SelectModel(1);  break;
      case GLUT_KEY_F2:  car.SelectModel(2);  break;
      case GLUT_KEY_F3:  car.SelectModel(3);  break;
      case GLUT_KEY_F4:  car.SelectModel(4);  break;

   }

   m.UpdateVector();

   glutPostRedisplay();
}


void mykey(unsigned char key,int x,int y)
{
   switch(key)
   {
      case 32:{
                 if(m.Speed>0) 
                {  
                    if(m.Speed<10)
                      m.Speed=0;
                    else
                    m.Speed=m.Speed-10;
                }

                if(m.Speed<0) 
                {  
                    if(m.Speed>-10)
                      m.Speed=0;
                    else
                    m.Speed=m.Speed+10;
                }  
              } break;


      case 'A': ax=-ax;  break;
      case 'V': vx=-vx;  break;

     case 'G': cam.H--;  break;
     case 'T': cam.H++;  break;
    
      case '0':  cam.VIEW=0; break;
      case '1':  cam.VIEW=1; break;
      case '2':  cam.VIEW=2; break;
      case '3':  cam.VIEW=3; break;
      case '4':  cam.VIEW=4; break;
      case '5':  cam.VIEW=5; break;
      case '6':  cam.VIEW=6; break;
      case '7':  cam.VIEW=7; break;
      case '8':  cam.VIEW=8; break;
      case '9':  cam.VIEW=9; break;
   

      case 9: ax=-ax;break;   

           
      
   }

   m.UpdateVector();

   glutPostRedisplay();
}





void time(int value)
{  

  cout<<m.X<<" "<<m.Y<<" "<<m.Speed<<endl;
   omega=m.Speed/4;

   wa=wa+omega;

   m.FreeMotion();
  
   meter();
   
   glutPostRedisplay();
   glutTimerFunc(t,time,0);
}





int main(int argc, char **argv) 
{ 
 printf("hello world\n"); 
 glutInit(&argc, argv); 
 glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
 
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
 glutInitWindowPosition(0,0); 
 glutInitWindowSize(800,800); 
 glutCreateWindow ("car");
  
  //init();




  glutReshapeFunc(reshape);

  glutKeyboardFunc(mykey);

   glutSpecialFunc(special);

   glutTimerFunc(t,time,0);
   
 glutDisplayFunc(display); 
 glutMainLoop();

 return 0; 
}

