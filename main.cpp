#include <GL/glut.h>
#include <cmath>

// Variables globales
int windowWidth = 640;
int windowHeight = 480;
int polygonSides = 6; // n�mero de lados del pol�gono
float polygonRadius = 0.5; // radio del pol�gono
float polygonAngle = 0.0; // �ngulo de rotaci�n del pol�gono
float polygonCenterX = 0.0; // coordenada x del centro del pol�gono
float polygonCenterY = 0.0; // coordenada y del centro del pol�gono
float scale = 1.0; // factor de escala del pol�gono

// Funci�n que dibuja el pol�gono
void drawPolygon() {
    glBegin(GL_POLYGON);
    for (int i = 0; i < polygonSides; i++) {
        float angle = 2.0 * i / polygonSides + polygonAngle;
        float x = polygonCenterX + scale * polygonRadius * cos(angle);
        float y = polygonCenterY + scale * polygonRadius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

// Funci�n que dibuja la escena
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    drawPolygon();
    glutSwapBuffers();
}

// Funci�n que se llama cuando se redimensiona la ventana
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// Funci�n que se llama cuando se mueve el mouse con un bot�n presionado
void motion(int x, int y) {
    float normalizedX = (float)x / windowWidth * 2.0 - 1.0;
    float normalizedY = (float)(windowHeight - y) / windowHeight * 2.0 - 1.0;
    polygonCenterX = normalizedX;
    polygonCenterY = normalizedY;
    glutPostRedisplay();
}

// Funci�n que se llama cuando se gira la rueda del mouse
void mouseWheel(int wheel, int direction, int x, int y) {
    if (direction > 0) {
        scale *= 1.1;
    }
    else {
        scale /= 1.1;
    }
    glutPostRedisplay();
}

// Funci�n que se llama cuando se presiona un bot�n del mouse
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        polygonAngle += 0.1;
        glutPostRedisplay();
    }
}

// Funci�n principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Poligono interactivo");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}