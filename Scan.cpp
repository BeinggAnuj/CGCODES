#include <iostream>
#include <graphics.h>
using namespace std;

struct edge {
    int x1, y1, x2, y2, flag;
};

int main() {
    int gd = DETECT, gm, n, i, j, k;
    edge ed[10], temped;
    float dx, dy, m[10], x_int[10], inter_x[10];
    int x[10], y[10], ymax = 0, ymin = 480, yy, temp;

    initgraph(&gd, &gm, NULL);
    cout << "Enter the number of vertices of the graph: ";
    cin >> n;

    cout << "Enter the vertices:\n";
    for (i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        ymax = max(ymax, y[i]);
        ymin = min(ymin, y[i]);
        ed[i].x1 = x[i];
        ed[i].y1 = y[i];
    }

    cout << "\nEdge Information:\n";
    for (i = 0; i < n - 1; i++) {
        ed[i].x2 = ed[i + 1].x1;
        ed[i].y2 = ed[i + 1].y1;
        ed[i].flag = 0;
        cout << "(" << ed[i].x1 << ", " << ed[i].y1 << ") (" << ed[i].x2 << ", " << ed[i].y2 << ")\n";
    }
    ed[i].x2 = ed[0].x1;
    ed[i].y2 = ed[0].y1;
    ed[i].flag = 0;
    cout << "(" << ed[i].x1 << ", " << ed[i].y1 << ") (" << ed[i].x2 << ", " << ed[i].y2 << ")\n";

    cout << "\nUpdated Edge Information:\n";
    for (i = 0; i < n; i++) {
        if (ed[i].y1 < ed[i].y2) {
            swap(ed[i].x1, ed[i].x2);
            swap(ed[i].y1, ed[i].y2);
        }
        cout << "(" << ed[i].x1 << ", " << ed[i].y1 << ") (" << ed[i].x2 << ", " << ed[i].y2 << ")\n";
    }

    for (i = 0; i < n; i++) {
        line(ed[i].x1, ed[i].y1, ed[i].x2, ed[i].y2);
    }

    for (i = 0; i < n; i++) {
        dx = ed[i].x2 - ed[i].x1;
        dy = ed[i].y2 - ed[i].y1;
        m[i] = (dy == 0) ? 0 : dx / dy;
        inter_x[i] = ed[i].x1;
    }

    yy = ymax;
    while (yy > ymin) {
        for (i = 0; i < n; i++) {
            ed[i].flag = (yy > ed[i].y2 && yy <= ed[i].y1) ? 1 : 0;
        }

        j = 0;
        for (i = 0; i < n; i++) {
            if (ed[i].flag == 1) {
                x_int[j] = (yy == ed[i].y1) ? ed[i].x1 : inter_x[i] + (-m[i]);
                inter_x[i] = x_int[j];
                j++;
            }
        }

        for (i = 0; i < j - 1; i++) {
            for (k = 0; k < j - i - 1; k++) {
                if (x_int[k] > x_int[k + 1]) {
                    swap(x_int[k], x_int[k + 1]);
                }
            }
        }

        for (i = 0; i < j; i += 2) {
            setcolor(GREEN);
            line((int)x_int[i], yy, (int)x_int[i + 1], yy);
        }
        yy--;
        delay(50);
    }

    delay(10000);
    closegraph();
}
