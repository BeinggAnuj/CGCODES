#include <GL/glut.h>

void myDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0, 0.0, -5.0);
    glRotatef(20.0, 1.0, 0.0, 0.0);

    glBegin(GL_QUADS);
        // Front face (red)
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);

        // Back face (green)
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, -1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(-1.0, 1.0, -1.0);

        // Right face (blue)
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
        glVertex3f(1.0, 1.0, -1.0);

        // Left face (yellow)
        glColor3f(1.0, 1.0, 0.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(-1.0, 1.0, 1.0);

        // Top face (cyan)
        glColor3f(0.0, 1.0, 1.0);
        glVertex3f(-1.0, 1.0, -1.0);
        glVertex3f(-1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, -1.0);

        // Bottom face (magenta)
        glColor3f(1.0, 0.0, 1.0);
        glVertex3f(-1.0, -1.0, -1.0);
        glVertex3f(-1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, 1.0);
        glVertex3f(1.0, -1.0, -1.0);
    glEnd();
    
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 2.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("3D Transformations");
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
    return 0;
}
