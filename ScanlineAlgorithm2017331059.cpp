#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>
#include <unordered_map>
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

    bool operator < (const PT &p) const{
        return x < p.x;
    }
};

struct EDGE{
    double y_min, y_max, x_with_y_min, m_inv;
    EDGE(){
    }

    EDGE(double a, double b, double c, double d){
        y_min = a;
        y_max = b;
        x_with_y_min = c;
        m_inv = d;
    }

    bool operator < (const EDGE &p) const{
        return y_min < p.y_min;
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
    delay(0.5);
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

void drawPolygon(vector<PT> points)
{
    int n = points.size();
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
        drawLine(points[i], points[(i+1)%n],color);
    }
}



void scanLine(vector<PT> points, int color){

    vector<EDGE> edges;

    int n=points.size();
    double Start = 1e15;
    double End = -1e15;
    unordered_map<double,int> mp;

    for(int i=0;i<n;i++){
        PT a = points[i];
        PT b = points[(i+1)%n];

        if(a.y == b.y){
            continue;
        }

        EDGE temp;
        temp.y_min = min(a.y, b.y);
        temp.y_max = max(a.y, b.y);
        temp.x_with_y_min = a.y < b.y ? a.x : b.x;
        temp.m_inv = (b.x - a.x)/(b.y - a.y);

        Start = min(Start, temp.y_min);
        End = max(End, temp.y_max);

        mp[temp.y_min] = 1;

        edges.push_back(temp);
    }

    n = edges.size();

    sort(edges.begin(), edges.end());

    for(int i=0;i<n;i++){

        if(mp[edges[i].y_max]){
            edges[i].y_max--;
        }
    }

    for(double y=Start; y<=End; y++){
        vector<PT> int_points;
        for(int i=0;i<n;i++){

            if(y >= edges[i].y_min && y <= edges[i].y_max){

                PT tmp;

                tmp.x = edges[i].x_with_y_min;
                tmp.y = y;

                edges[i].x_with_y_min += edges[i].m_inv;

                int_points.push_back(tmp);
            }
        }

        sort(int_points.begin(),int_points.end());

        for(int i=0;i<int_points.size()-1;i+=2){
                delay(1);
            drawLine(int_points[i],int_points[i+1], RED);
        }
    }
}


int main()
{
    initwindow(WINDOW_W, WINDOW_H);
    drawAxis();

    vector<PT> polygon;

    polygon.push_back(PT(60, 35));
    polygon.push_back(PT(120, 70));
    polygon.push_back(PT(65, 140));
    polygon.push_back(PT(70, 180));
    polygon.push_back(PT(-40, 100));
    polygon.push_back(PT(-50, -100));

    drawPolygon(polygon);

    scanLine(polygon,RED);

    getchar();

    return 0;
}
