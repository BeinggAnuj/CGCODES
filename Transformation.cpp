#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

void applyTransformation(int result[3][3], float transform[3][3], int original[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += transform[i][k] * original[k][j];
            }
        }
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    int vertices[3][3];
    cout << "Enter x1, y1: ";
    cin >> vertices[0][0] >> vertices[1][0];
    cout << "Enter x2, y2: ";
    cin >> vertices[0][1] >> vertices[1][1];
    cout << "Enter x3, y3: ";
    cin >> vertices[0][2] >> vertices[1][2];
    vertices[2][0] = vertices[2][1] = vertices[2][2] = 1;

    drawTriangle(vertices[0][0], vertices[1][0], vertices[0][1], vertices[1][1], vertices[0][2], vertices[1][2], RED);

    int choice;
    cout << "Enter your choice:\n1. Translation\n2. Scaling\n3. Rotation\n";
    cin >> choice;

    int transformedVertices[3][3];
    switch (choice) {
        case 1: {  // Translation
            int tx, ty;
            cout << "Enter translation factors (tx, ty): ";
            cin >> tx >> ty;

            float translationMatrix[3][3] = {
                {1, 0, tx},
                {0, 1, ty},
                {0, 0, 1}
            };
            applyTransformation(transformedVertices, translationMatrix, vertices);
            break;
        }
        case 2: {  // Scaling
            float sx, sy;
            cout << "Enter scaling factors (Sx, Sy): ";
            cin >> sx >> sy;

            float scalingMatrix[3][3] = {
                {sx, 0, 0},
                {0, sy, 0},
                {0, 0, 1}
            };
            applyTransformation(transformedVertices, scalingMatrix, vertices);
            break;
        }
        case 3: {  // Rotation
            float angle;
            cout << "Enter rotation angle (in degrees): ";
            cin >> angle;

            float radian = angle * M_PI / 180.0;
            float rotationMatrix[3][3] = {
                {cos(radian), -sin(radian), 0},
                {sin(radian), cos(radian), 0},
                {0, 0, 1}
            };
            applyTransformation(transformedVertices, rotationMatrix, vertices);
            break;
        }
        default:
            cout << "Invalid choice";
            closegraph();
            return 0;
    }

    drawTriangle(transformedVertices[0][0], transformedVertices[1][0],
                 transformedVertices[0][1], transformedVertices[1][1],
                 transformedVertices[0][2], transformedVertices[1][2], BLUE);

    delay(5000);
    closegraph();
    return 0;
}
