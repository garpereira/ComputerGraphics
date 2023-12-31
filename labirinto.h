#include <GL/glut.h>

#define tamanho 600

typedef struct labirinto3D labirinto3D;

void viraEsquerda(labirinto3D* lab3d);
void viraDireita(labirinto3D* lab3d);

void caminhaPraFrente(labirinto3D* lab3d);
void caminhaPraTras(labirinto3D* lab3d);

void desenha_labirinto3d(labirinto3D* lab3d);
labirinto3D* cria_labirinto3D();
void destroi_labirinto3D(labirinto3D* lab3d);

void troca_textura();
void carregaTexturas();
