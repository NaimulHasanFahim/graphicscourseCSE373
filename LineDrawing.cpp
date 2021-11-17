#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;

struct PT
{
    double x, y;
    PT(){}
    PT(double a, double b)
    {
        x = a;
        y = b;
    }
};

const int WINDOW_W = 800, WINDOW_H = 600;

void drawAxis()
{
    for(int i=0; i<WINDOW_H; i++){
        putpixel(WINDOW_W/2, i, WHITE);
    }
    for(int i=0; i<WINDOW_W; i++){
        putpixel(i, WINDOW_H/2, WHITE);
    }
}

PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}

void drawPixel(PT p, int color)
{
    delay(0.5);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}

void DDA( ){

    double x, y, x1, y1, x2, y2, step, dx, dy;
    cout<<"Enter the value of x1 y1 : ";
    cin>>x1>>y1;
    cout<<"Enter the value of x2 y2 : ";
    cin>>x2>>y2;
    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

    dx = x2-x1;
    dy = y2-y1;

    if(dx>=dy){
        step = dx;
    }
    else{
        step = dy;
    }
    double Xinc = dx/step;
    double Yinc = dy/step;

    x=x1;
    y=y1;

    for(int i=0;i<step;i++){

        drawPixel(PT(x,y),WHITE);
        //cout<<x<<" "<<y<<endl;
        x += Xinc;
        y += Yinc;
        delay(1);
    }

    return;
}

void bresenham()
{
    int x1, y1, x2, y2;
    cout<<"Enter the value of x1 y1 : ";
    cin>>x1>>y1;
    cout<<"Enter the value of x2 y2 : ";
    cin>>x2>>y2;
    cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;

   int m_nw = 2 * (y2 - y1);
   int slp_err_new = m_nw - (x2 - x1);
   for(int x = x1, y = y1; x <= x2; x++){
       drawPixel(PT(x,y),RED);
       //cout << "(" << x << "," << y << ")\n";
       slp_err_new += m_nw;
       if (slp_err_new >= 0){
           y++;
           slp_err_new  -= 2 * (x2 - x1);
      }
   }

   return;
}

int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    while(true){
        int tp;
        printf("Press :\n1. for DDA line generation.\n2. for Bresenham’s Line Generation.\n3. 3 to exit the loop.\n");
        scanf("%d",&tp);

        if(tp==1){
            DDA();
        }
        else if(tp==2){
            bresenham();
        }
        else{
            break;
        }
        getchar();
    }


    return 0;
}
