#ifndef DDA_H_INCLUDED
#define DDA_H_INCLUDED



#endif // DDA_H_INCLUDED

#include<bits/stdc++.h>

using namespace std;

vector<PT> allp;

bool tk=true;

void drawPixel1(PT p, int color){
    if(tk)
        allp.push_back(p);
    //delay(0.5);
    p = convertPixel(p);
    putpixel((int)(p.x+1), (int)(p.y+1), color);
}



void DDA(double x1, double y1, double x2, double y2 ){

    double x, y, step, dx, dy;

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

        drawPixel1(PT(x,y),WHITE);
        //cout<<x<<" "<<y<<endl;
        x += Xinc;
        y += Yinc;
        delay(0.5);
    }

    return;
}
