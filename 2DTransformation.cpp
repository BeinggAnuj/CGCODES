#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

class Matrix {
public:
    float mat[3][3];

    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = (i == j) ? 1 : 0; // Identity matrix
            }
        }
    }

    Matrix operator*(const Matrix& other) {
        Matrix result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.mat[i][j] = 0;
                for (int k = 0; k < 3; k++) {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return result;
    }
};

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Matrix vertices;
    cout << "Enter x1, y1: ";
    cin >> vertices.mat[0][0] >> vertices.mat[1][0];
    cout << "Enter x2, y2: ";
    cin >> vertices.mat[0][1] >> vertices.mat[1][1];
    cout << "Enter x3, y3: ";
    cin >> vertices.mat[0][2] >> vertices.mat[1][2];
    vertices.mat[2][0] = vertices.mat[2][1] = vertices.mat[2][2] = 1;

    drawTriangle(vertices.mat[0][0], vertices.mat[1][0], 
                 vertices.mat[0][1], vertices.mat[1][1], 
                 vertices.mat[0][2], vertices.mat[1][2], RED);

    int choice;
    cout << "Enter your choice:\n1. Translation\n2. Scaling\n3. Rotation\n";
    cin >> choice;

    Matrix transformation;
    if (choice == 1) {  // Translation
        float tx, ty;
        cout << "Enter translation factors (tx, ty): ";
        cin >> tx >> ty;

        transformation.mat[0][2] = tx;
        transformation.mat[1][2] = ty;
    } else if (choice == 2) {  // Scaling
        float sx, sy;
        cout << "Enter scaling factors (Sx, Sy): ";
        cin >> sx >> sy;

        transformation.mat[0][0] = sx;
        transformation.mat[1][1] = sy;
    } else if (choice == 3) {  // Rotation
        float angle;
        cout << "Enter rotation angle (in degrees): ";
        cin >> angle;

        float radian = angle * M_PI / 180.0;
        transformation.mat[0][0] = cos(radian);
        transformation.mat[0][1] = -sin(radian);
        transformation.mat[1][0] = sin(radian);
        transformation.mat[1][1] = cos(radian);
    } else {
        cout << "Invalid choice";
        closegraph();
        return 0;
    }

    Matrix transformedVertices = transformation * vertices;

    drawTriangle(transformedVertices.mat[0][0], transformedVertices.mat[1][0],
                 transformedVertices.mat[0][1], transformedVertices.mat[1][1],
                 transformedVertices.mat[0][2], transformedVertices.mat[1][2], BLUE);

    delay(5000);
    closegraph();
    return 0;
}
