# include "iGraphics.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dy=1,dx=1;

int arr[3][3]={
  90,90,20,
  80,70,40,
  60,50,80
};


/*
	function iDraw() is called again and again by the system.

	*/


void iDraw() {
	//place your drawing codes here
	iClear();

	iSetColor(255,0,0);
	iFilledRectangle(arr[2][0],arr[2][1],80,20);
	iSetColor(0,255,0);
	iFilledRectangle(arr[1][0],arr[1][1],40,20);
	iSetColor(0,0,255);
	iFilledRectangle(arr[0][0],arr[0][1],20,20);

	iSetColor(255, 0, 0);
	iFilledRectangle(50,46,100,4);
	iSetColor(0, 255, 0);
	iFilledRectangle(200,46,100,4);
	iSetColor(0, 0, 255);
	iFilledRectangle(350,46,100,4);

	iText(80 ,30,"src");
    iText(240,30,"auxi");
    iText(380,30,"des");
    iText(245,280,"hanoi");
}

void FUNC()
{
   if(arr[0][1]<=250 && arr[0][1]>=90 && !(arr[0][0]==390) && !(arr[1][0]==230))
   {
       arr[0][1]+=dy;
       //printf("%d %d ",arr[0][1],dy);
   }
   else if(arr[0][1]>=250 && arr[0][0]<=389 && arr[1][0]==80)
   {
       arr[0][0]+=dx;
       //dy=0;

   }
   else if(arr[0][1]>=50 && arr[0][0] == 390 && arr[1][0]==80)
   {
       //
       //dy =1;
        arr[0][1]-=dy;
        //printf("%d %d ",arr[0][1],dy);
    }
    else if(arr[0][0]==390 && arr[0][1]==49 && arr[1][1]<=250 && arr[1][1]>=70 && !(arr[1][0]==230))
    {
        arr[1][1]+=dy;
    }
    else if(arr[1][1]>=250 && arr[1][0]<=229)
    {
        arr[1][0]+=dx;
    }
    else if(arr[1][1]>=50 && arr[1][0]==230 && !(arr[0][0]==89))
    {
        arr[1][1]-=dy;
    }
    else if(arr[1][0]==230 && arr[0][1]<=250 && !(arr[0][0]==230) && arr[0][1]>=49 && !(arr[0][0]==239) && !(arr[0][0]==89))
    {
        arr[0][1]+=dy;
    }
    else if(arr[0][1]>=250 && arr[0][0]>=240 && arr[1][0]==230)
    {
        arr[0][0]-=dx;
    }
    else if(arr[0][1]>=70 && arr[0][0]==239 && arr[1][0]==230 && !(arr[2][0]==360))
    {
        arr[0][1]-=dy;
    }
    else if(arr[0][0]==239 && arr[1][0]==230 && arr[2][1]>=50 && arr[2][1]<=250 && !(arr[2][0]==360) && !(arr[0][0]==89))
    {
        arr[2][1]+=dy;
    }
    else if(arr[0][0]==239 && arr[1][0]==230 && arr[2][0]<=359 && arr[2][1]>=250)
    {
        arr[2][0]+=dx;
    }
    else if(arr[0][0]==239 && arr[1][0]==230 && arr[2][0]==360 && arr[2][1]>=50)
    {
        arr[2][1]-=dy;
    }
    else if(arr[1][0]==230 && arr[2][0]==360 && arr[0][1]<=250 && !(arr[0][0]==89) && !(arr[0][0]==390))
    {
        arr[0][1]+=dy;
    }
    else if(arr[1][0]==230 && arr[2][0]==360 && arr[0][0]>=90 && arr[0][1]>=250)
    {
        arr[0][0]-=dx;
    }
    else if(arr[1][0]==230 && arr[2][0]==360 && arr[0][1]>=50 && arr[0][0]==89)
    {
        arr[0][1]-=dy;
    }
    else if(arr[0][0]==89 && arr[2][0]==360 && arr[1][1]<=250 && !(arr[1][0]==380))
    {
        arr[1][1]+=dy;
    }
    else if(arr[0][0]==89 && arr[2][0]==360 && arr[1][1]>=250 && arr[1][0]<=379)
    {
        arr[1][0]+=dx;
    }
    else if(arr[0][0]==89 && arr[2][0]==360 && arr[1][1]>=70 && arr[1][0]==380)
    {
        arr[1][1]-=dy;
    }
    else if(arr[2][0]==360 && arr[1][0]==380 && arr[0][1]<=249 && !(arr[0][0]==390))
    {
        arr[0][1]+=dy;
    }
    else if(arr[2][0]==360 && arr[1][0]==380 && arr[0][1]>=250 && arr[0][0]<=389 && arr[0][0]>=89)
    {
        arr[0][0]+=dx;
    }
    else if(arr[2][0]==360 && arr[1][0]==380 && arr[0][0]==390 && arr[0][1]>=90)
    {
        arr[0][1]-=dy;
    }

}

/*
	function iMouseFUNC() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {

}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
    /*
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		r=25;
	}
	*/
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
    /*
	if (key == 'w')
    {
        y+=10;
    }
    else if(key == 'b')
    {

        r=0;
        g=0;
        b=255;
    }
    */
	//place your codes for other keys here
}


void iSpecialKeyboard(unsigned char key) {

}

int main()
{


    iSetTimer(0.000005,FUNC);


	//place your own initialization codes here.
	iInitialize(500, 300, "Towers of Hanoi");
	return 0;
}
