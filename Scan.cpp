#include <iostream>
#include <graphics.h>
#include <vector>
using namespace std;

class Polygon {
protected:
    vector<pair<int, int>> vertices;

public:
    void addVertex(int x, int y) {
        vertices.push_back({x, y});
    }

    void draw() {
        int n = vertices.size();
        for (int i = 0; i < n; i++) {
            line(vertices[i].first, vertices[i].second,
                 vertices[(i + 1) % n].first, vertices[(i + 1) % n].second);
        }
    }
};

class FilledPolygon : public Polygon {
public:
    void scanFill(int color) {
        int ymax = 0, ymin = INT_MAX;
        for (auto &v : vertices) {
            ymax = max(ymax, v.second);
            ymin = min(ymin, v.second);
        }

        for (int y = ymin; y <= ymax; y++) {
            vector<int> intersections;

            for (int i = 0; i < vertices.size(); i++) {
                int x1 = vertices[i].first, y1 = vertices[i].second;
                int x2 = vertices[(i + 1) % vertices.size()].first;
                int y2 = vertices[(i + 1) % vertices.size()].second;

                if (y1 == y2) continue;

                if (y >= min(y1, y2) && y <= max(y1, y2)) {
                    int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                    intersections.push_back(x);
                }
            }

            sort(intersections.begin(), intersections.end());

            for (size_t i = 0; i < intersections.size(); i += 2) {
                line(intersections[i], y, intersections[i + 1], y);
            }
        }

        setcolor(color);
    }
};

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    FilledPolygon poly;
    poly.addVertex(100, 100);
    poly.addVertex(200, 50);
    poly.addVertex(300, 100);
    poly.addVertex(250, 200);
    poly.addVertex(150, 200);

    poly.draw();
    poly.scanFill(YELLOW);

    getch();
    closegraph();
    return 0;
}
