#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
using namespace std;
/*
---Name : Naimul Hasan
---Reg. No : 2017331059

*/

const int WINDOW_W = 800, WINDOW_H = 600;
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
    delay(0.7);
    p = convertPixel(p);
    putpixel((int)(p.x+0.5), (int)(p.y+0.5), color);
}

void drawLine(PT a, PT b, int color)
{
    if(a.y == b.y)
    {
        if(a.x > b.x){
            swap(a, b);
        }

        for(int x = a.x; x <= b.x; x++)
        {
            drawPixel(PT(x, a.y), color);
        }
    }
    else if(a.x == b.x)
    {
        if(a.y > b.y){
            swap(a, b);
        }

        for(int y = a.y; y <= b.y; y++)
        {
            drawPixel(PT(a.x, y), color);
        }
    }

    else
    {

        double m = (double)(b.y-a.y)/(double)(b.x-a.x);
        double m_inv = 1.0/m;

        if(fabs(m) <= 1.0){

            if(a.x > b.x){
                swap(a,b);
            }

            while(a.x <= b.x){

                drawPixel(a, color);
                a.x +=1;
                a.y +=m;
            }
        }
        else{

            if(a.y > b.y){
                swap(a,b);
            }

            while(a.y <= b.y){

                drawPixel(a, color);
                a.x += m_inv;
                a.y += 1;
            }
        }
    }
}

void drawPolygon1(vector<PT> polypoints)
{
    int n = polypoints.size();
    for(int i=0; i<n; i++)
    {
        int color=YELLOW;
        drawLine(polypoints[i], polypoints[(i+1)%n],color);
    }
}

void drawPolygon2(vector<PT> polypoints)
{
    int n = polypoints.size();
    for(int i=0; i<n; i++)
    {
        int color;
        if(i%3==0){
            color = YELLOW;
        }
        else if(i%3==1){
            color = GREEN;
        }
        else{
            color = BLUE;
        }
        drawLine(polypoints[i], polypoints[(i+1)%n],color);
    }
}



void BoundaryFill(PT currPixel, int boundaryColor, int fillColor)
{
    PT pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.x, pixel.y);
    if(currColor == boundaryColor || currColor == fillColor)
    {
        return;
    }
    //cout<<currPixel.x<<" "<<currPixel.y<<endl;
    drawPixel(currPixel, fillColor);
    BoundaryFill(PT(currPixel.x, currPixel.y+1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x, currPixel.y-1), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x+1, currPixel.y), boundaryColor, fillColor);
    BoundaryFill(PT(currPixel.x-1, currPixel.y), boundaryColor, fillColor);
}

void FloodFill(PT currPixel, int boundaryColor, int fillColor, int oldColor)
{
    PT pixel = convertPixel(currPixel);
    int currColor = getpixel(pixel.x, pixel.y);
    if( currColor != oldColor && currColor != 15 )  ///currColor == boundaryColor ||
    {
        return;
    }

    drawPixel(currPixel, fillColor);

    FloodFill(PT(currPixel.x, currPixel.y+1), boundaryColor, fillColor, oldColor);
    FloodFill(PT(currPixel.x, currPixel.y-1), boundaryColor, fillColor, oldColor);
    FloodFill(PT(currPixel.x+1, currPixel.y), boundaryColor, fillColor, oldColor);
    FloodFill(PT(currPixel.x-1, currPixel.y), boundaryColor, fillColor, oldColor);
}



int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    PT pixel = convertPixel(PT(0,0));
    int currColor = getpixel(pixel.x, pixel.y);
    drawAxis();


    while(true){
        printf("Press:\n1. For Boundary Filling Algorithm.\n2. For Flood Fill Algorithm.\n3.To exit the program.\n");
        int typ;
        scanf("%d",&typ);

        if(typ==1){
            vector<PT> polygon;
            polygon.push_back(PT(-30, 140));
            polygon.push_back(PT(-100, 180));
            polygon.push_back(PT(-160, 140));
            polygon.push_back(PT(-169, 60));
            polygon.push_back(PT(-100, 20));
            polygon.push_back(PT(-30, 60));
            drawPolygon1(polygon);
            BoundaryFill(PT(-90, 100), YELLOW, RED);
        }
        else if(typ==2){
            vector<PT> polygon;
            polygon.push_back(PT(170, 140));
            polygon.push_back(PT(100, 180));
            polygon.push_back(PT(40, 140));
            polygon.push_back(PT(30, 60));
            polygon.push_back(PT(100, 20));
            polygon.push_back(PT(170, 60));
            drawPolygon2(polygon);
            FloodFill(PT(100, 100), YELLOW, RED, currColor);
        }
        else{
            return 0;
        }
        getchar();
    }
    getchar();

    return 0;
}
