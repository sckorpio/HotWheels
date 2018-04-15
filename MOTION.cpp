#include <stdio.h> 
#include <math.h>
#include <iomanip>
#include <GL/glut.h>
#include <iostream>
#include "MOTION.h"
using namespace std;


MOTION::MOTION()
{
	X=0;  Y=0;  Z=0;
	theta=0;
	ux=0; uz=1;
    Speed=0;
	Acc=30;  Friction=20;  
	t=30;
}

void MOTION::UpdateVector()
{
   ux=cos(theta*(3.14/180));
   uz=sin(theta*(3.14/180));
}

void MOTION::FreeMotion()
{
    X=X+(ux*Speed)*(t/1000);
    Z=Z+(uz*Speed)*(t/1000);

    
    if(Speed>0)
    {  
       if(Speed<Friction*(t/1000))
         Speed=0; 
       
       else
       Speed=Speed-Friction*(t/1000);
    }

    if(Speed<0)
    {  
       if(Speed>-Friction*(t/1000))
         Speed=0; 
       
       else
       Speed=Speed+Friction*(t/1000);
   }
}


void MOTION::DrawVector()
{
    glColor3f(0,1,0);
    glLineWidth(10);

    glBegin(GL_LINES);
    glVertex3f(X,Y+7,Z);
    glVertex3f(X+30*ux,Y+7,Z+30*uz);
    glEnd();

    glLineWidth(1);

}




  


