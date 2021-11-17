#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED



#endif // CIRCLE_H_INCLUDED
#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;
const int WINDOW_W = getmaxwidth( ), WINDOW_H = getmaxheight( );
int mycolor=0;
int num=0;

struct PT
{
    double x, y;
    PT(){}
    PT(double a, double b)
    {
        x = a;
        y = b;
    }
    bool operator < (const PT &p) const{
        return x < p.x;
    }
};

struct Pointcir
{
    int x;
    int y;
};


PT convertPixel(PT p)
{
    p.x += WINDOW_W/2;
    p.y = -p.y;
    p.y += WINDOW_H/2;

    return p;
}
vector<PT>allCirclePoint;

void drawPixelCir(PT p, int color){
    allCirclePoint.push_back(p);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);

}

void drawPixelCircle(PT p, int color){
    delay(0.5);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);

}

/// Function to put pixels at subsequence points
void drawCircle(int xc, int yc, int x, int y,int color){
    drawPixelCir(PT(xc+x, yc+y), color);
    drawPixelCir(PT(xc-x, yc+y), color);
    drawPixelCir(PT(xc+x, yc-y), color);
    drawPixelCir(PT(xc-x, yc-y), color);
    drawPixelCir(PT(xc+y, yc+x), color);
    drawPixelCir(PT(xc-y, yc+x), color);
    drawPixelCir(PT(xc+y, yc-x), color);
    drawPixelCir(PT(xc-y, yc-x), color);
}

/// Function for circle-generation using Bresenham's algorithm
void circleBres(int xc, int yc, int r,int color){
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(xc, yc, x, y,WHITE);
    while (y >= x)
    {
        x++;
        if(d > 0){
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else{
            d = d + 4 * x + 6;
        }

        drawCircle(xc, yc, x, y,color);
        delay(10);
    }
}

void midPointCircleDraw(int xc, int yc, int r,int color ){

    int x,y,p;
	x=0;
	y=r;
	p=1-r;
	drawCircle(xc,yc,x,y,color);

	while(x<y)
	{
		if(p<0)
		{
			x++;
			p=p+2*x+1;
		}
		else
		{
			x++;
			y--;
			p=p+2*(x-y)+1;
		}
		drawCircle(xc,yc,x,y,color);
		delay(20);
	}


    return;
}


void BoundaryFill(PT currPixel, int boundaryColor, int fillColor)
{
    PT pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.x, pixel.y);
    if(currColor == boundaryColor || currColor == fillColor)
    {
        return;
    }

    drawPixelCir(currPixel, fillColor);

    BoundaryFill(PT(currPixel.x, currPixel.y+1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x, currPixel.y-1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x+1, currPixel.y), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x-1, currPixel.y), boundaryColor, fillColor);
}

bool isInside(int circle_x, int circle_y, int rad, int x, int y){
    if ((x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad)
        return true;
    else
        return false;
}

bool HandleClick( PT p){

    if(num%7==0){
        mycolor=YELLOW;
    }
    else if(num%7==1){
        mycolor=RED;
    }
    else if(num%7==2){
        mycolor=LIGHTBLUE;
    }
    else if(num%7==3){
        mycolor=LIGHTCYAN;
    }
    else if(num%7==4){
        mycolor=MAGENTA;
    }
    else if(num%7==5){
        mycolor=GREEN;
    }
    else if(num%7==6){
        mycolor=CYAN;
    }

    if(isInside(-400,300,40,p.x,p.y)){
       BoundaryFill(p, LIGHTGRAY, mycolor);
       num++;
       return true;
    }
    else if(isInside(-200,300,40,p.x,p.y)){
        BoundaryFill(p, LIGHTGREEN, mycolor);
        num++;
        return true;
    }
    else if(isInside(-0,300,40,p.x,p.y)){
        BoundaryFill(p, LIGHTMAGENTA, mycolor);
        num++;
        return true;
    }
    else if(isInside(200,300,40,p.x,p.y)){
        BoundaryFill(p, LIGHTCYAN, mycolor);
        num++;
        return true;
    }
    else if(isInside(400,300,40,p.x,p.y)){
        BoundaryFill(p, WHITE, mycolor);
        num++;
        return true;
    }

    return false;

}


void CircleMain( ){
    midPointCircleDraw(-400,300,40,LIGHTGRAY);
    midPointCircleDraw(-200,300,40,LIGHTGREEN);
    midPointCircleDraw(-0,300,40,LIGHTMAGENTA);
    midPointCircleDraw(200,300,40,LIGHTCYAN);
    midPointCircleDraw(400,300,40,WHITE);
}
