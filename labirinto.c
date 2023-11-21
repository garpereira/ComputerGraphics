#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#include "labirintoH.h"

//gcc -o labirinto labirinto_v2.c -lGL -lGLU -lglut

int tamanho = 512;
int incr = 0.01f;
double posXY[2] = {0.0f, 0.0f};

// Aqui, o anguloZ é o angulo que o personagem está olhando
// a partir do topo da tela, então a gente limitou um pouco as direções possíveis dele
// na perspectiva, a gente definir esses angulos como sendo a maneira com que ele viraria
// fica meio quadrado, mas foi a melhor maneira que a gente achou de fazer isso

int anguloZTopo[4] = {0, 90, 180, 270};
int anguloZPersp[4] = {180, 270, 0, 90};
int idx_anguloZ = 0;

//==============================================================
//========================= VIEWPORTS ==========================

void viewport_topo() {
    glViewport(3 * tamanho / 4.0 - 20, 5, tamanho / 4.0, tamanho / 4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
    draw_topo();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(posXY[0], posXY[1], 0.0f);
    glRotatef(-anguloZTopo[idx_anguloZ], 0.0f, 0.0f, 1.0f); // rotacional o personagem
    draw_obj();// triangulo vermelho no mapa, representando o personagem
    glPopMatrix();
}

void viewport_perspectiva() {
    glViewport(0, 0, tamanho, tamanho);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0, 1.0, 0.01, 200.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-90, 1.0f, 0.0f, 0.0f); // rotaciona o viewport para ficar de cima, ajustando a visão
    glRotatef(anguloZPersp[idx_anguloZ], 0.0f, 0.0f, 1.0f); // rotaciona o personagem
    glPushMatrix();
    glTranslatef(-posXY[0], -posXY[1], -0.1f); // translada o personagem
    draw_perspectiva(); // renderiza o labirinto
    glPopMatrix();
}

void draw_obj() {
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.05f, 0.05f, -0.05f);
    glVertex3f(-0.05f, 0.05f, -0.05f);
    glVertex3f(0.0f, -2 * 0.05f, -0.05f);
    glEnd();
}

void draw_topo(){
    glLineWidth(2);

    // contorno do viewport
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    // chao do viewport
    glBegin(GL_QUADS);
    glColor3f(0.95f, 0.95f, 0.95f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    //Parede Vermelha
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.75f, 0.75f, -0.05f);
    glVertex3f(0.75f, 0.75f, -0.05f);
    glVertex3f(0.75f, 0.70f, -0.05f);
    glVertex3f(-0.75f, -0.70f, -0.05f);
    glEnd();

    //Parede Azul
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.75f, -0.75f, -0.05f);
    glVertex3f(0.75f, -0.75f, -0.05f);
    glVertex3f(0.75f, -0.70f, -0.05f);
    glVertex3f(-0.75f, -0.70f, -0.05f);
    glEnd();

    //Parede Verde
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.75f, 0.75f, -0.05f);
    glVertex3f(-0.70f, 0.75f, -0.05f);
    glVertex3f(-0.70f, -0.75f, -0.05f);
    glVertex3f(-0.75f, -0.75f, -0.05f);
    glEnd();

    //Parede Amarela
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.75f, 0.75f, -0.05f);
    glVertex3f(0.70f, 0.75f, -0.05f);
    glVertex3f(0.70f, -0.75f, -0.05f);
    glVertex3f(0.75f, -0.75f, -0.05f);
    glEnd();

}

void draw_perspectiva(){
    glLineWidth(2);

    // chao do viewport
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();

    //Parede Vermelha
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-0.75f, 0.75f, -0.05f);
    glVertex3f(0.75f, 0.75f, -0.05f);
    glVertex3f(0.75f, 0.70f, -0.05f);
    glVertex3f(-0.75f, -0.70f, -0.05f);
    glEnd();

    //Parede Azul
    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-0.75f, -0.75f, -0.05f);
    glVertex3f(0.75f, -0.75f, -0.05f);
    glVertex3f(0.75f, -0.70f, -0.05f);
    glVertex3f(-0.75f, -0.70f, -0.05f);
    glEnd();

    //Parede Verde
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.75f, 0.75f, -0.05f);
    glVertex3f(-0.70f, 0.75f, -0.05f);
    glVertex3f(-0.70f, -0.75f, -0.05f);
    glVertex3f(-0.75f, -0.75f, -0.05f);
    glEnd();

    //Parede Amarela
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.75f, 0.75f, -0.05f);
    glVertex3f(0.70f, 0.75f, -0.05f);
    glVertex3f(0.70f, -0.75f, -0.05f);
    glVertex3f(0.75f, -0.75f, -0.05f);
    glEnd();

}

//////////////////////////////////
//       POSICOES DE ANGULO     //
//////////////////////////////////
void caminhaPraFrente() {
    switch (idx_anguloZ) {
        case 0:
            posXY[1] -= incr;
            break;
        case 1:
            posXY[0] -= incr;
            break;
        case 2:
            posXY[1] += incr;
            break;
        case 3:
            posXY[0] += incr;
            break;
    }
}

void caminhaPraTras() {
    switch (idx_anguloZ) {
        case 0:
            posXY[1] += incr;
            break;
        case 1:
            posXY[0] += incr;
            break;
        case 2:
            posXY[1] -= incr;
            break;
        case 3:
            posXY[0] -= incr;
            break;
    }
}

//////////////////////////////////
//       DIRECOES               //
//////////////////////////////////

// Quando a gente ta andando na direção da esquerda, os indices voltam no vetor de anguloZ, sendo que, sempre que for menor que 0, ele volta pra 3
void viraEsquerda() {
    idx_anguloZ--;
    if (idx_anguloZ < 0) {
        idx_anguloZ = 3;
    }
    printf("esquerda -> %d\n", idx_anguloZ);
}

// Quando a gente ta andando na direção da direita, os indices avançam normal no vetor de anguloZ
void viraDireita() {
    idx_anguloZ = (idx_anguloZ + 1) % 4;
    printf("direita -> %d\n", idx_anguloZ);
}

//==============================================================
//========================= FUNCOES GLUT ======================

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewport_perspectiva();
    viewport_topo();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC key
            exit(0);
            break;
        case 'w':
        case 'W':
            caminhaPraFrente();
            break;
        case 's':
        case 'S':
            caminhaPraTras();
            break;
        case 'a':
        case 'A':
            viraEsquerda();
            break;
        case 'd':
        case 'D':
            viraDireita();
            break;
    
    }
}

void idle() {
    glutPostRedisplay(); // redesenha a tela
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(tamanho, tamanho);
    glutCreateWindow("Labirinto");

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
