#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void dda(int x1, int y1, int x2, int y2) {
    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
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

    int x1, y1, x3, y3;
    cout << "Enter coordinates for x1, y1: ";
    cin >> x1 >> y1;
    cout << "Enter coordinates for x3, y3: ";
    cin >> x3 >> y3;

    int x2 = x3, y2 = y1;
    int x4 = x1, y4 = y3;

    int x5 = (x1 + x2) / 2, y5 = y1;
    int x6 = x2, y6 = (y2 + y3) / 2;
    int x7 = (x3 + x4) / 2, y7 = y3;
    int x8 = x1, y8 = (y1 + y4) / 2;

    int D = x2 - x1;
    int d = y4 - y1;
    int radius = (D * d) / (2 * sqrt((D * D) + (d * d)));

    // Draw outer rectangle
    dda(x1, y1, x2, y2);
    dda(x2, y2, x3, y3);
    dda(x3, y3, x4, y4);
    dda(x4, y4, x1, y1);

    // Draw inner rectangle
    dda(x5, y5, x6, y6);
    dda(x6, y6, x7, y7);
    dda(x7, y7, x8, y8);
    dda(x8, y8, x5, y5);

    // Draw circle
    bresenhamCircle(x5, y6, radius);

    delay(10000);
    closegraph();
    return 0;
}
