#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

// Function to draw a line using DDA algorithm
void ddaLine(int x1, int y1, int x2, int y2, int color) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), color); // Draw the pixel
        x += xIncrement; // Increment x
        y += yIncrement; // Increment y
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

    // Call DDA line function
    ddaLine(x1, y1, x2, y2, RED);

    delay(5000); // Wait for 5 seconds
    closegraph(); // Close the graphics window

    return 0;
}
