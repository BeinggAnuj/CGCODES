#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

class Matrix {
public:
    float mat[3][4]; // Modified to handle 4 vertices for the rhombus

    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                mat[i][j] = (i == j && j < 3) ? 1 : 0; // Identity matrix
            }
        }
    }

    Matrix operator*(const Matrix& other) {
        Matrix result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                result.mat[i][j] = 0;
                for (int k = 0; k < 3; k++) {
                    result.mat[i][j] += mat[i][k] * other.mat[k][j];
                }
            }
        }
        return result;
    }
};

void drawShape(const Matrix& vertices, int vertexCount, int color) {
    setcolor(color);
    for (int i = 0; i < vertexCount; i++) {
        int next = (i + 1) % vertexCount;
        line(vertices.mat[0][i], vertices.mat[1][i],
             vertices.mat[0][next], vertices.mat[1][next]);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    Matrix vertices;
    int shapeChoice;

    cout << "Select shape to transform:\n1. Equilateral Triangle\n2. Rhombus\n";
    cin >> shapeChoice;

    if (shapeChoice == 1) {
        // Equilateral triangle
        cout << "Enter x1, y1: ";
        cin >> vertices.mat[0][0] >> vertices.mat[1][0];
        cout << "Enter side length: ";
        float side;
        cin >> side;

        vertices.mat[0][1] = vertices.mat[0][0] + side;
        vertices.mat[1][1] = vertices.mat[1][0];

        vertices.mat[0][2] = vertices.mat[0][0] + side / 2;
        vertices.mat[1][2] = vertices.mat[1][0] - sqrt(3) * side / 2;

        vertices.mat[2][0] = vertices.mat[2][1] = vertices.mat[2][2] = 1;

        drawShape(vertices, 3, RED);

    } else if (shapeChoice == 2) {
        // Rhombus
        cout << "Enter bottom-left corner (x1, y1): ";
        cin >> vertices.mat[0][0] >> vertices.mat[1][0];
        cout << "Enter horizontal diagonal length: ";
        float hDiagonal;
        cin >> hDiagonal;
        cout << "Enter vertical diagonal length: ";
        float vDiagonal;
        cin >> vDiagonal;

        vertices.mat[0][1] = vertices.mat[0][0] + hDiagonal / 2;
        vertices.mat[1][1] = vertices.mat[1][0] - vDiagonal / 2;

        vertices.mat[0][2] = vertices.mat[0][0] + hDiagonal;
        vertices.mat[1][2] = vertices.mat[1][0];

        vertices.mat[0][3] = vertices.mat[0][0] + hDiagonal / 2;
        vertices.mat[1][3] = vertices.mat[1][0] + vDiagonal / 2;

        vertices.mat[2][0] = vertices.mat[2][1] = vertices.mat[2][2] = vertices.mat[2][3] = 1;

        drawShape(vertices, 4, RED);

    } else {
        cout << "Invalid shape choice!";
        closegraph();
        return 0;
    }

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
        cout << "Invalid transformation choice!";
        closegraph();
        return 0;
    }

    Matrix transformedVertices = transformation * vertices;

    drawShape(transformedVertices, (shapeChoice == 1) ? 3 : 4, BLUE);

    delay(5000);
    closegraph();
    return 0;
}
