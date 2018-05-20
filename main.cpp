#include <GL/glut.h>

#include "SweepLines.hpp"

int main(int argc, char **argv) {
    double min = -20000;
    double max = 20000;
    std::size_t n = 2;

    std::vector<SweepLines<double>::Endpoint> endpoints = SweepLines<double>::draw_endpoints(n, min, max);

//    std::vector<SweepLines<double>::Endpoint> endpoints = {SweepLines<double>::Endpoint(-19818.5, -11035.3),
//                                                           SweepLines<double>::Endpoint(-14801.4, 18975.5),
//                                                           SweepLines<double>::Endpoint(17621.1, -3295.51),
//                                                           SweepLines<double>::Endpoint(-12031, -6782.57)};

    SweepLines<double> sl(endpoints);

    bool visualize = true;
    std::vector<SweepLines<double>::Endpoint> xd = endpoints;

    if (visualize) {
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

    }
    std::cout << sl.any_segments_intersect() << std::endl;

    if (visualize) {
        glutMainLoop();
    }


    return 0;
}