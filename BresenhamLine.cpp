#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Function to draw a line using Bresenham's algorithm
void bresenhamLine(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int p = 2 * dy - dx;
    int x, y, xEnd;

    // Determine the start and end points
    if (x1 > x2) {
        x = x2;
        y = y2;
        xEnd = x1;
    } else {
        x = x1;
        y = y1;
        xEnd = x2;
    }

    putpixel(x, y, color); // Draw the starting pixel

    // Bresenham's algorithm for line drawing
    while (x < xEnd) {
        x++;
        if (p < 0) {
            p += 2 * dy;
        } else {
            y += (y1 < y2) ? 1 : -1; // Choose the appropriate direction
            p += 2 * (dy - dx);
        }
        putpixel(x, y, color); // Draw the pixel
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int x1, y1, x2, y2;
    cout << "Enter coordinates of the first point (x1, y1): ";
    cin >> x1 >> y1;
    cout << "Enter coordinates of the second point (x2, y2): ";
    cin >> x2 >> y2;

    // Call Bresenham line function
    bresenhamLine(x1, y1, x2, y2, RED);

    delay(5000); // Wait for 5 seconds
    closegraph(); // Close the graphics window

    return 0;
}
