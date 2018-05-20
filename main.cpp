#include <GL/glut.h>

#include "SweepLines.hpp"

int main(int argc, char **argv) {
    double min = -20000;
    double max = 20000;
    std::size_t n = 2;

    std::vector<SweepLines<double>::Endpoint> endpoints = SweepLines<double>::draw_endpoints(n, min, max);

    SweepLines<double> sl(endpoints);

    std::vector<SweepLines<double>::Endpoint> xd = endpoints;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("main");
    gluOrtho2D(min, max, min, max);

    for (int i = 0; i < xd.size() / 2; i++) {
        glBegin(GL_LINES);
        glVertex2d(xd[2 * i].x, xd[2 * i].y);
        glVertex2d(xd[2 * i + 1].x, xd[2 * i + 1].y);
        glEnd();
    }

    glutSwapBuffers();

    std::cout << sl.any_segments_intersect() << std::endl;

    glutMainLoop();

    return 0;
}