#include "GL/glut.h"
#include "stdio.h"
#include "math.h"

GLUquadric *q = gluNewQuadric();
GLfloat camY = 0;
GLfloat camX = 0;
GLfloat camZ = 0;
GLfloat dirX = 0;
GLfloat dirY = 0;
GLfloat dirZ = -15;
GLfloat upX = 0;
GLfloat upY = 1;
GLfloat upZ = 0;
GLfloat earth_rev = 0.0f;
GLfloat earth_dir = 0.15f;
GLfloat rotasi_cahaya = 0.0f;
GLfloat moon_rev = 0.0f;
GLfloat moon_dir = 0.9f;
GLfloat ZlookRot = 0.0f;

void initGL(){
    GLfloat sun_direction[] = { 0.0, 2.0, -1.0, 1.0 };
    GLfloat sun_intensity[] = {0.7, 0.7, 0.7, 1.0};
    GLfloat ambient_intensity[] = { 0.3, 0.3, 0.3, 1.0 };

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set clear color to black
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_LIGHTING);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient_intensity);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, sun_direction);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_intensity);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

void drawCone(){
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor4f(1.0, 1.0, 1.0, 0.1);
    gluCylinder(q, 1.5, 0.0f, 5.0f, 60, 60);
    gluDisk(q, 0.0f, 1.5f, 60, 60);
    glDisable(GL_COLOR_MATERIAL);
}

void drawBall(GLfloat radius, GLint slices, GLint stacks){
    gluQuadricTexture(q, true);
    gluSphere(q, radius, slices, stacks);
}

void Sun(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3f(1.0, 1.0, 0.0);
    gluQuadricTexture(q, true);
    gluSphere(q, 1.5, 50, 50);
    glDisable(GL_COLOR_MATERIAL);
}

void Earth(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3f(0.0, 0.5, 1.0);
    gluQuadricTexture(q, true);
    gluSphere(q, 0.4, 50, 50);
    glDisable(GL_COLOR_MATERIAL);
}

void Moon(){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glColor3f(0.75, 0.75, 0.75);
    gluQuadricTexture(q, true);
    gluSphere(q, 0.15, 50, 50);
    glDisable(GL_COLOR_MATERIAL);
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, dirX, dirY, dirZ, upX, upY, upZ);
    glTranslatef(-2, 0, -15);
    glPushMatrix();
    /* Sun */
    Sun();
    glPushMatrix();
    glPopMatrix();
    glRotatef(rotasi_cahaya, 0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0, 0.0, 0.1);
    drawCone();
    glPushMatrix();
    /* Earth */
    glPopMatrix();
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    glRotatef(earth_dir, 0.0f, 0.0f, 1.0f);
    glTranslatef(5, 0, 0);
    Earth();
    glPushMatrix();
    /* Moon */
    glPopMatrix();
    glRotatef(moon_rev, 0.0f, 0.0f, 1.0f);
    glTranslatef(-1.5, 0, 0.0);
    Moon();
    earth_rev += earth_dir;
    rotasi_cahaya += earth_dir;
    moon_rev += moon_dir;
    glutSwapBuffers();
}

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(15, timer, 0);
}

void reshape(GLsizei width, GLsizei height){
    if (height == 0) height = 1;
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void keyControl(int k, int x, int y) {
    switch(k) {
        case GLUT_KEY_UP:
            camZ++;
            break;
        case GLUT_KEY_DOWN:
            camZ--;
            break;
        case GLUT_KEY_LEFT:
            dirX++;
            break;
        case GLUT_KEY_RIGHT:
            dirX--;
            break;
    }
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Solar Eclipse Simulation");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    initGL();
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyControl);
    glutMainLoop();
    return EXIT_SUCCESS;
}
