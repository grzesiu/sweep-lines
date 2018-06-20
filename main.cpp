#include <GL/glut.h>
#include <sstream>

#include "sweeplines.hpp"

int main(int argc, char **argv) {



    double min = -20000;
    double max = 20000;
    std::size_t n = 2;
    std::vector<SweepLines<double>::Endpoint> endpoints;
    if (argc == 2) {
        int val;
        std::istringstream iss(argv[1]);
        iss >> val;
        endpoints = SweepLines<double>::draw_endpoints(val, min, max);
    } else {
        endpoints = {SweepLines<double>::Endpoint(0, 3000),
                     SweepLines<double>::Endpoint(4000, 2000),
                     SweepLines<double>::Endpoint(1000, 0),
                     SweepLines<double>::Endpoint(9000, 3000),
                     SweepLines<double>::Endpoint(2000, 1000),
                     SweepLines<double>::Endpoint(5500, 2200),
                     SweepLines<double>::Endpoint(3000, 3000),
                     SweepLines<double>::Endpoint(9000, 1500),
                     SweepLines<double>::Endpoint(5000, 3000),
                     SweepLines<double>::Endpoint(9000, 2000),
                     SweepLines<double>::Endpoint(6500, 1000),
                     SweepLines<double>::Endpoint(8000, 0)};
    }

    SweepLines<double> sl(endpoints);

    std::vector<SweepLines<double>::Endpoint> xd = endpoints;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 640);
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
