#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void dda(int x1, int y1, int x2, int y2) {
    float dx = abs(x2 - x1), dy = abs(y2 - y1);
    float len = (dx > dy) ? dx : dy;
    float x_inc = (x2 - x1) / len;
    float y_inc = (y2 - y1) / len;

    float x = x1, y = y1;
    for (int i = 0; i <= len; i++) {
        putpixel(x, y, RED);
        x += x_inc;
        y += y_inc;
    }
}

void bresenhamCircle(int centerX, int centerY, int radius) {
    int x = 0, y = radius;
    int p = 3 - 2 * radius;

    while (x <= y) {
        putpixel(centerX + x, centerY - y, 1);
        putpixel(centerX - x, centerY - y, 2);
        putpixel(centerX - x, centerY + y, 3);
        putpixel(centerX + x, centerY + y, 4);

        putpixel(centerX + y, centerY + x, 5);
        putpixel(centerX + y, centerY - x, 6);
        putpixel(centerX - y, centerY + x, 7);
        putpixel(centerX - y, centerY - x, 8);

        if (p < 0) {
            p += 4 * x + 6;
        } else {
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int centerX, centerY, radius;
    cout << "Enter x-coordinate of center: ";
    cin >> centerX;
    cout << "Enter y-coordinate of center: ";
    cin >> centerY;
    cout << "Enter the radius of the circle: ";
    cin >> radius;

    bresenhamCircle(centerX, centerY, radius);
    bresenhamCircle(centerX, centerY, radius / 2);

    dda(centerX, centerY - radius, centerX - 0.865 * radius, centerY + radius / 2);
    dda(centerX - 0.865 * radius, centerY + radius / 2, centerX + 0.865 * radius, centerY + radius / 2);
    dda(centerX + 0.865 * radius, centerY + radius / 2, centerX, centerY - radius);

    delay(5000);
    closegraph();
    return 0;
}
