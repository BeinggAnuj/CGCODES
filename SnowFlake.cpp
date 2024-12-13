#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;
void kochCurve(int x1, int y1, int x2, int y2, int depth) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
    } else {
        int dx = x2 - x1;
        int dy = y2 - y1;

        int xA = x1 + dx / 3;
        int yA = y1 + dy / 3;
        int xB = x1 + 2 * dx / 3;
        int yB = y1 + 2 * dy / 3;

        double angle = atan2(dy, dx) - M_PI / 3;
        int xC = (int)(xA + cos(angle) * (sqrt(dx * dx + dy * dy) / 3));
        int yC = (int)(yA + sin(angle) * (sqrt(dx * dx + dy * dy) / 3));
        
        kochCurve(x1, y1, xA, yA, depth - 1);
        kochCurve(xA, yA, xC, yC, depth - 1);
        kochCurve(xC, yC, xB, yB, depth - 1);
        kochCurve(xB, yB, x2, y2, depth - 1);
    }
}

void drawSnowflake(int x, int y, int size, int depth) {
    int x1 = x;
    int y1 = y;
    int x2 = x + size;
    int y2 = y;
    int x3 = x + size / 2;
    int y3 = y - sqrt(3) * size / 2;
    kochCurve(x1, y1, x2, y2, depth);
    kochCurve(x2, y2, x3, y3, depth);
    kochCurve(x3, y3, x1, y1, depth);
}

int main() {
int gd=DETECT,gm;
initgraph(&gd,&gm,NULL);
    int x = 200, y = 400, size = 300, depth;

    cout << "Enter the depth of recursion (e.g., 3 for a simple snowflake): ";
    cin >> depth;
    drawSnowflake(x, y, size, depth);
    getch();
    closegraph();
    return 0;
}
