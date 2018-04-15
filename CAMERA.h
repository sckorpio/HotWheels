#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

class CAMERA
{
	//--------------------------------------------------------------------
   public:

    GLfloat EX;      //EYE coordinates
    GLfloat EY;
    GLfloat EZ;

    GLfloat LX;      //LOOK coordinates
    GLfloat LY;
    GLfloat LZ;

    GLfloat H;

    int VIEW;
    
    //-----------------------------------------------------------------

    
    CAMERA();

    void SetFreeCamera();

    void SetDriveCamera(float cx,float cy,float cz,float ux,float uz);
   
   private:


    void TopView(float cx,float cy,float cz,float ux,float uz);
    void BackView(float cx,float cy,float cz,float ux,float uz);
    void FrontView(float cx,float cy,float cz,float ux,float uz);
    void LeftSideView(float cx,float cy,float cz,float ux,float uz);
    void RightSideView(float cx,float cy,float cz,float ux,float uz);
    void DragonView(float cx,float cy,float cz,float ux,float uz);
    void CornerView(float cx,float cy,float cz,float ux,float uz);
    void WindScreen(float cx,float cy,float cz,float ux,float uz);
    void FixView(float cx,float cy,float cz,float ux,float uz);
};

#endif
