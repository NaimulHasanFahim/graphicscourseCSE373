#ifndef CLICKCHECK_H_INCLUDED
#define CLICKCHECK_H_INCLUDED

#include<bits/stdc++.h>
#include<windows.h>
#include<graphics.h>

#define INF 10000

using namespace std;

#endif // CLICKCHECK_H_INCLUDED

///To check is my click is in the region or not
struct Point
{
    int x;
    int y;
};




bool onSegment(Point p, Point q, Point r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0)? 1: 2;
}

bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4)
        return true;

    if (o1 == 0 && onSegment(p1, p2, q1)) return true;

    if (o2 == 0 && onSegment(p1, q2, q1)) return true;

    if (o3 == 0 && onSegment(p2, p1, q2)) return true;

    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

bool isInside(Point polygon[], int n)
{
    //cout<<"Yes"<<endl;

    POINT tempPoint;
    GetCursorPos(&tempPoint);
    ScreenToClient(GetForegroundWindow(), &tempPoint);
    PT cp = PT(tempPoint.x, tempPoint.y);
    cp = convertPixel(cp);
    PT mp = {(int)cp.x-WINDOW_W, (int)cp.y};
    Point p = {(int)cp.x-WINDOW_W, (int)cp.y};


    if (n < 3) return false;

    Point extreme = {INF, p.y};

    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;

        if (doIntersect(polygon[i], polygon[next], p, extreme))
        {
            if (orientation(polygon[i], p, polygon[next]) == 0)
                return onSegment(polygon[i], p, polygon[next]);

            count++;
        }
        i = next;
    }
    while (i != 0);

    return count&1; // Same as (count%2 == 1)
}

