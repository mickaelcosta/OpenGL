//
//  robo.cpp
//  aprendizado
//
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.
//

#include "robo.hpp"
#include <GLUT/GLUT.h>

GLfloat mat_specular_esfera[] = { 0.2, 0.2, 0.2, 1.0};
GLfloat mat_specular_braco[] = { 0.5, 0.5, 0.5, 0.4};
GLfloat mat_reflexao[] = { 20.0 };

//posições iniciais
int shoulder = 0,
shoulder_rotate = 0,
elbow = 0, wrist = 0,
fingers = 0;


//implementação das funções
void desenha_esfera(void){
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_esfera);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular_esfera);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_reflexao);
    glutSolidSphere(0.2, 10, 5);
}

void desenha_braco(void){
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular_braco);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_specular_braco);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_reflexao);
    glutSolidCube(1.0);
}

void avisoLimiteArticulacao(int shoulder, int shoulder_rotate, int elbow, int fingers){
    if((shoulder >= MAX_SHOLDER_ANGLE || shoulder <= MIN_SHOLDER_ANGLE) || (shoulder_rotate >= 360 || shoulder_rotate <= -360) || (wrist >= MAX_WRIST_ANGLE || wrist <= MIN_WRIST_ANGLE) || (elbow >= MAX_ELBOW_ANGLE || elbow <= MIN_ELBOW_ANGLE) || (fingers >= MAX_FINGERS_ANGLE || fingers <= MIN_FINGERS_ANGLE)){
        glClearColor(0.6, 0.0, 0.0, 0.0);
        glutPostRedisplay();
    }
    else
        glClearColor(1, 1, 1, 0.0);
    glutPostRedisplay();
}

void gerarRobo(void){
    
    
}
