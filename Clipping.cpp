#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;
static int LEFT = 1, RIGHT = 2, BOTTOM = 4, TOP = 8, xmin, ymin, xmax, ymax;
int getcode(int x, int y) {
    int code = 0;
    if (y > ymax) code |= TOP;
    if (y < ymin) code |= BOTTOM;
    if (x < xmin) code |= LEFT;
    if (x > xmax) code |= RIGHT;
    return code;
}
int main() {
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, (char*) NULL);
    setcolor(WHITE);
    cout << "Enter top left and bottom right coordinates of window: ";
    cin >> xmin >> ymin >> xmax >> ymax;

    int x1, y1, x2, y2;
    cout << "Enter the endpoints of the line: ";
    cin >> x1 >> y1 >> x2 >> y2;

    outtext((char*) "Before clipping");
    rectangle(xmin, ymin, xmax, ymax);
    line(x1, y1, x2, y2);
    delay(5000);

    int outcode1 = getcode(x1, y1);
    int outcode2 = getcode(x2, y2);
    bool accept = false;

    while (true) {
        if (outcode1 == 0 && outcode2 == 0) {
            accept = true;
            break; // both endpoints are inside the window, accept the line
        } else if ((outcode1 & outcode2) != 0) {
            break; // both endpoints share an outside region, reject the line
        } else {
            int x, y;
            int temp = (outcode1 != 0) ? outcode1 : outcode2;
            float m = (x2 - x1) != 0 ? static_cast<float>(y2 - y1) / (x2 - x1) : 0;

            // Handle intersection with window boundaries
            if (temp & TOP) {
                x = x1 + static_cast<int>((ymax - y1) / m);
                y = ymax;
            } else if (temp & BOTTOM) {
                x = x1 + static_cast<int>((ymin - y1) / m);
                y = ymin;
            } else if (temp & LEFT) {
                y = y1 + m * (xmin - x1);
                x = xmin;
            } else if (temp & RIGHT) {
                y = y1 + m * (xmax - x1);
                x = xmax;
            }

            // Update the point based on which code is non-zero
            if (temp == outcode1) {
                x1 = x;
                y1 = y;
                outcode1 = getcode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                outcode2 = getcode(x2, y2);
            }
        }
    }

    cleardevice();
    outtext((char*) "After clipping");
    rectangle(xmin, ymin, xmax, ymax);

    if (accept) {
        setcolor(YELLOW);
        line(x1, y1, x2, y2);
    }

    getch();
    closegraph();
}
