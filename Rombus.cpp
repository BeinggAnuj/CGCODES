#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

class Matrix {
public:
    float mat[3][3];

    // Constructor to initialize the matrix to identity matrix
    Matrix() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = (i == j) ? 1 : 0; // Identity matrix
            }
        }
    }

    // Overloaded multiplication operator to multiply two matrices
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

    // Overloaded function to apply transformation to a point
    void applyTransformation(float &x, float &y) {
        float newX = mat[0][0] * x + mat[0][1] * y + mat[0][2];
        float newY = mat[1][0] * x + mat[1][1] * y + mat[1][2];
        x = newX;
        y = newY;
    }
};

// Function to draw a polygon (equilateral triangle or rhombus)
void drawPolygon(float x1, float y1, float x2, float y2, float x3, float y3, float x4 = -1, float y4 = -1, int color = RED) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    if (x4 != -1 && y4 != -1) {
        line(x3, y3, x4, y4);
        line(x4, y4, x1, y1);
    } else {
        line(x3, y3, x1, y1);
    }
}

// Function to define and draw an equilateral triangle
void drawEquilateralTriangle(float x, float y, float sideLength) {
    float height = (sqrt(3) / 2) * sideLength;  // Height of the equilateral triangle
    float x2 = x + sideLength;
    float y2 = y;
    float x3 = x + sideLength / 2;
    float y3 = y - height;

    drawPolygon(x, y, x2, y2, x3, y3);
}

// Function to define and draw a rhombus based on center and diagonals
void drawRhombus(float cx, float cy, float diag1, float diag2) {
    // Coordinates of the rhombus vertices
    float x1 = cx, y1 = cy - diag2 / 2;  // Top vertex
    float x2 = cx + diag1 / 2, y2 = cy;  // Right vertex
    float x3 = cx, y3 = cy + diag2 / 2;  // Bottom vertex
    float x4 = cx - diag1 / 2, y4 = cy;  // Left vertex

    drawPolygon(x1, y1, x2, y2, x3, y3, x4, y4);
}

int main() {
    int gd=DETECT,gm;
    initgraph(&gd,&gm,NULL);
    // Choosing shape to transform (Triangle or Rhombus)
    int shapeChoice;
    cout << "Choose shape:\n1. Equilateral Triangle\n2. Rhombus\n";
    cin >> shapeChoice;

    Matrix transformation;

    if (shapeChoice == 1) {
        // Input and draw an equilateral triangle
        float x, y, sideLength;
        cout << "Enter the coordinates of the base of the equilateral triangle (x, y): ";
        cin >> x >> y;
        cout << "Enter the side length of the equilateral triangle: ";
        cin >> sideLength;

        drawEquilateralTriangle(x, y, sideLength);

        // Transformation choices
        int choice;
        cout << "Enter transformation:\n1. Translation\n2. Scaling\n3. Rotation\n";
        cin >> choice;

        if (choice == 1) {  // Translation
            float tx, ty;
            cout << "Enter translation factors (tx, ty): ";
            cin >> tx >> ty;
            transformation.mat[0][2] = tx;
            transformation.mat[1][2] = ty;
        }
        else if (choice == 2) {  // Scaling
            float sx, sy;
            cout << "Enter scaling factors (Sx, Sy): ";
            cin >> sx >> sy;
            transformation.mat[0][0] = sx;
            transformation.mat[1][1] = sy;
        }
        else if (choice == 3) {  // Rotation
            float angle;
            cout << "Enter rotation angle (in degrees): ";
            cin >> angle;

            float radian = angle * M_PI / 180.0;
            transformation.mat[0][0] = cos(radian);
            transformation.mat[0][1] = -sin(radian);
            transformation.mat[1][0] = sin(radian);
            transformation.mat[1][1] = cos(radian);
        }
        else {
            cout << "Invalid choice!";
            closegraph();
            return 0;
        }

        // Apply transformation to each vertex of the triangle
        float x1 = x, y1 = y;
        float x2 = x + sideLength, y2 = y;
        float x3 = x + sideLength / 2, y3 = y - (sqrt(3) / 2) * sideLength;

        transformation.applyTransformation(x1, y1);
        transformation.applyTransformation(x2, y2);
        transformation.applyTransformation(x3, y3);

        // Redraw transformed triangle
        drawPolygon(x1, y1, x2, y2, x3, y3);

    }
    else if (shapeChoice == 2) {
        // Input and draw a rhombus
        float cx, cy, diag1, diag2;
        cout << "Enter the center coordinates of the rhombus (cx, cy): ";
        cin >> cx >> cy;
        cout << "Enter the lengths of the diagonals (d1, d2): ";
        cin >> diag1 >> diag2;

        drawRhombus(cx, cy, diag1, diag2);

        // Transformation choices
        int choice;
        cout << "Enter transformation:\n1. Translation\n2. Scaling\n3. Rotation\n";
        cin >> choice;

        if (choice == 1) {  // Translation
            float tx, ty;
            cout << "Enter translation factors (tx, ty): ";
            cin >> tx >> ty;
            transformation.mat[0][2] = tx;
            transformation.mat[1][2] = ty;
        }
        else if (choice == 2) {  // Scaling
            float sx, sy;
            cout << "Enter scaling factors (Sx, Sy): ";
            cin >> sx >> sy;
            transformation.mat[0][0] = sx;
            transformation.mat[1][1] = sy;
        }
        else if (choice == 3) {  // Rotation
            float angle;
            cout << "Enter rotation angle (in degrees): ";
            cin >> angle;

            float radian = angle * M_PI / 180.0;
            transformation.mat[0][0] = cos(radian);
            transformation.mat[0][1] = -sin(radian);
            transformation.mat[1][0] = sin(radian);
            transformation.mat[1][1] = cos(radian);
        }
        else {
            cout << "Invalid choice!";
            closegraph();
            return 0;
        }

        // Apply transformation to each vertex of the rhombus
        float x1 = cx, y1 = cy - diag2 / 2;
        float x2 = cx + diag1 / 2, y2 = cy;
        float x3 = cx, y3 = cy + diag2 / 2;
        float x4 = cx - diag1 / 2, y4 = cy;

        transformation.applyTransformation(x1, y1);
        transformation.applyTransformation(x2, y2);
        transformation.applyTransformation(x3, y3);
        transformation.applyTransformation(x4, y4);

        // Redraw transformed rhombus
        drawPolygon(x1, y1, x2, y2, x3, y3, x4, y4);

    }
    else {
        cout << "Invalid shape choice!";
    }

    delay(5000);  // Wait for 5 seconds before closing
    closegraph();
    return 0;
    }
