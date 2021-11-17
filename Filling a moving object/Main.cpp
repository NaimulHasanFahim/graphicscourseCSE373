#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
#include "Circle.h"
#include "ClickCheck.h"
#include "ScanLine.h"
#include "DDA.h"

using namespace std;


void drawPixel(PT p, int color){
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}

void Trans(vector<PT>temp, bool t){
    while(1){

        POINT tempPoint;
        if(GetCursorPos(&tempPoint)){
            ScreenToClient(GetForegroundWindow(), &tempPoint);
            Point polygon1[] = {{0-lopx, 100-lopy}, {100-lopx, 0-lopy}, {100-lopx, 100-lopy}, {0-lopx, 0-lopy}};
            int n = sizeof(polygon1)/sizeof(polygon1[0]);
            PT cp = PT(tempPoint.x, tempPoint.y);
            PT ans= convertPixel(cp);
            Point p = {(int)ans.x-WINDOW_W, (int)ans.y};
            PT mp = {(int)ans.x-WINDOW_W, (int)ans.y};

            if(isInside(polygon1, n) && GetAsyncKeyState(VK_LBUTTON)){
                scan();
                if(t){
                    temp=polypixel;
                    t=false;
                }
            }
            if(GetAsyncKeyState(VK_LBUTTON)&&  HandleClick(mp)){

            }
            else if(GetAsyncKeyState(0x53)){
                return;
            }
            else if (GetAsyncKeyState(VK_ESCAPE)){
                Sleep(1000);
                exit(EXIT_SUCCESS);
			}

        }

        for(int i=0;i<temp.size();i++){
            drawPixel1(temp[i],BLACK);
            temp[i].y-=2;
            drawPixel1(temp[i],color);
        }
        if(t){
            allp=temp;
        }
        else{
            polypixel=temp;
        }

        lopy+=2;
        //delay(10);

    }
}



///MAIN FUNCTION
int main()
{
    int wid1=initwindow(WINDOW_W, WINDOW_H);
    setcurrentwindow(wid1);
    CircleMain( );
    DDA(0,0,100,0);
    DDA(100,0,100,100);
    DDA(0,100,100,100);
    DDA(0,0,0,100);
    tk=false;
    outtextxy(100,200,"Click on the each circle to fill them with color.");
    outtextxy(100,220,"Press Esc to exit the program.");
    outtextxy(100,240,"Click Button \"R\" to move the square.");
    outtextxy(100,260,"Click on the square to change color.");
    outtextxy(100,280,"Click Button \"S\" to stop moving the square.");

    //scan();
    Point polygon1[] = {{0-lopx, 100-lopy}, {100-lopx, 0-lopy}, {100-lopx, 100-lopy}, {0-lopx, 0-lopy}};
    int n = sizeof(polygon1)/sizeof(polygon1[0]);

    while(1){
        POINT tempPoint;
        GetCursorPos(&tempPoint);
        ScreenToClient(GetForegroundWindow(), &tempPoint);
        PT cp = PT(tempPoint.x, tempPoint.y);
        cp = convertPixel(cp);
        PT mp = {(int)cp.x-WINDOW_W, (int)cp.y};
        Point polygon1[] = {{0-lopx, 100-lopy}, {100-lopx, 0-lopy}, {100-lopx, 100-lopy}, {0-lopx, 0-lopy}};
        int n = sizeof(polygon1)/sizeof(polygon1[0]);
        Point tp = {(int)cp.x-WINDOW_W, (int)cp.y};

        if(GetAsyncKeyState(0x52)){

            if(called){
                    Trans(polypixel,false);
            }
            else{
                    Trans(allp,true);
            }
        }
        else if (GetAsyncKeyState(VK_ESCAPE)){
            Sleep(1000);
			exit(EXIT_SUCCESS);
        }
        else if(GetAsyncKeyState(VK_LBUTTON)&&  HandleClick(mp)){
        }
        else if(GetAsyncKeyState(VK_LBUTTON)&&isInside(polygon1, n)){
            scan();
        }
    }
    //Trans();
    getchar();

    return 0;
}
