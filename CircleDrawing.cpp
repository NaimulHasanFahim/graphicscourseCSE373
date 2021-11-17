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


/// Function to put pixels at subsequence points
void drawCircle(int xc, int yc, int x, int y,int color)
{
    drawPixel(PT(xc+x, yc+y), color);
    drawPixel(PT(xc-x, yc+y), color);
    drawPixel(PT(xc+x, yc-y), color);
    drawPixel(PT(xc-x, yc-y), color);
    drawPixel(PT(xc+y, yc+x), color);
    drawPixel(PT(xc-y, yc+x), color);
    drawPixel(PT(xc+y, yc-x), color);
    drawPixel(PT(xc-y, yc-x), color);
}

/// Function for circle-generation using Bresenham's algorithm
void circleBres( )
{
    int xc,yc;
    int r;
    printf("Enter the Circle center point(x & y):");
    scanf("%d %d",&xc,&yc);
    printf("Enter the radius of the circle :");
    scanf("%d",&r);

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

        drawCircle(xc, yc, x, y,WHITE);
        delay(20);
    }
}

void midPointCircleDraw( ){

    int xc,yc,r;
    int x,y,p;
    printf("Enter the Circle center point(x & y):");
	scanf("%d%d",&xc,&yc);
	printf("Enter radius of circle :");
	scanf("%d",&r);

	x=0;
	y=r;
	p=1-r;
	drawCircle(xc,yc,x,y,YELLOW);

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
		drawCircle(xc,yc,x,y,YELLOW);
		delay(20);
	}


    return;
}





int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();


    while(true){
        printf("Press:\n1. For Mid-Point Circle Drawing Algorithm.\n2. For Bresenham’s Circle Drawing Algorithm.\n3.To exit the program.\n");
        int typ;
        scanf("%d",&typ);

        if(typ==1){
            midPointCircleDraw();
        }
        else if(typ==2){
            circleBres();
        }
        else{
            return 0;
        }
        getchar();
    }
    getchar();

    return 0;
}
