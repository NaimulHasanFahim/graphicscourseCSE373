#ifndef SCANLINE_H_INCLUDED
#define SCANLINE_H_INCLUDED


#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>


using namespace std;

#endif // SCANLINE_H_INCLUDED

///POLYGON FILLING
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

vector<PT> polypixel;
int lopx=0;
int lopy=0;
bool yes=true;
bool called=false;

void drawPixelPoly(PT p, int color){
    //delay(0.5);
    if(yes){
        polypixel.push_back(p);
    }
    p = convertPixel(p);
    putpixel((int)(p.x+1), (int)(p.y+1), color);
}



void drawLine(PT a, PT b, int color){

    if(a.y == b.y)
    {
        if(a.x > b.x){
            swap(a, b);
        }

        for(int x = a.x; x <= b.x; x++)
        {
            drawPixelPoly(PT(x, a.y), color);
        }
    }
    else if(a.x == b.x)
    {
        if(a.y > b.y){
            swap(a, b);
        }

        for(int y = a.y; y <= b.y; y++)
        {
            drawPixelPoly(PT(a.x, y), color);
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

                drawPixelPoly(a, color);
                a.x +=1;
                a.y +=m;
            }
        }
        else{

            if(a.y > b.y){
                swap(a,b);
            }

            while(a.y <= b.y){

                drawPixelPoly(a, color);
                a.x += m_inv;
                a.y += 1;
            }
        }
    }
}

void drawPolygon(vector<PT> points){
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




int button=0;
int color=RED;
void scanLine(vector<PT> points, int color){

    vector<EDGE> edges;
    button++;
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
            drawLine(int_points[i],int_points[i+1], color);
        }
    }
    yes=false;
}
void scan(){
    called=true;
    vector<PT> polygon;
    polygon.push_back(PT(0-lopx, 100-lopy));
    polygon.push_back(PT(0-lopx, 0-lopy));
    polygon.push_back(PT(100-lopx, 0-lopy));
    polygon.push_back(PT(100-lopx, 100-lopy));

    //drawPolygon(polygon);
    //cout<<button<<endl;
    if(button%7==0){
        color=YELLOW;
    }
    else if(button%7==1){
        color=RED;
    }
    else if(button%7==2){
        color=LIGHTBLUE;
    }
    else if(button%7==3){
        color=LIGHTCYAN;
    }
    else if(button%7==4){
        color=MAGENTA;
    }
    else if(button%7==5){
        color=GREEN;
    }
    else if(button%7==6){
        color=CYAN;
    }


    scanLine(polygon,color);
}
