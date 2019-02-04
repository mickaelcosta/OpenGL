//  robo.cpp
//  aprendizado
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.

#include "robo.hpp"
#include <GLUT/GLUT.h>

GLfloat mat_specular_esfera[] = { 0.2, 0.2, 0.2, 1.0};
GLfloat mat_specular_braco[] = { 0.5, 0.5, 0.5, 0.4};
GLfloat mat_reflexao[] = { 20.0 };

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

void Robo::avisoLimiteArticulacao(void){
    if((shoulder >= MAX_SHOLDER_ANGLE || shoulder <= MIN_SHOLDER_ANGLE) || (shoulder_rotation >= 360 || shoulder_rotation <= -360) || (wrist >= MAX_WRIST_ANGLE || wrist <= MIN_WRIST_ANGLE) || (elbow >= MAX_ELBOW_ANGLE || elbow <= MIN_ELBOW_ANGLE) || (fingers >= MAX_FINGERS_ANGLE || fingers <= MIN_FINGERS_ANGLE)){
        glClearColor(0.6, 0.0, 0.0, 0.0);
        glutPostRedisplay();
    }
    else
        glClearColor(1, 1, 1, 0.0);
    glutPostRedisplay();
}

void Robo::gerarRobo(void){
    //braço
    glTranslatef(-0.75, 0.0, 0.0);
    glCallList(esfera_list);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glRotatef((GLfloat) shoulder_rotation, 0.0, 1.0, 0.0);
    glTranslatef(0.5, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.0, 0.4, 0.5);
    glCallList(blend_enable_list);
    glCallList(braco_list);
    glCallList(blend_disable_list);
    glPopMatrix();
    
    //antebraço
    glTranslatef(0.5, 0.0, 0.0);
    glCallList(esfera_list);
    glRotatef((GLfloat) elbow, 0.0, 0.0, 1.0);
    glTranslatef(0.75, 0.0, 0.0);
    glPushMatrix();
    glScalef(1.5, 0.4, 0.5);
    glCallList(blend_enable_list);
    glCallList(braco_list);
    glCallList(blend_disable_list);
    glPopMatrix();
    
    //Mão
    glTranslatef(0.75, 0.0, 0.0);
    glCallList(esfera_list);
    glRotatef((GLfloat) wrist, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.4, 0.4, 0.4);
    glCallList(blend_enable_list);
    glCallList(braco_list);
    glCallList(blend_disable_list);
    glPopMatrix();
    
    //dedos
    glPushMatrix();//salva coordenadas da ponta da mão
    glTranslatef(0.2, 0.2, 0.0);
    glRotatef((GLfloat) -fingers, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.4, 0.1, 0.1);
    glCallList(blend_enable_list);
    glCallList(braco_list);
    glCallList(blend_disable_list);
    
    glPopMatrix();//restaura coordenadas da ponta da mão para o proximo dedo
    glPopMatrix();
    glTranslatef(0.2, -0.2, 0.0);
    glRotatef((GLfloat) fingers, 0.0, 0.0, 1.0);
    glTranslatef(0.2, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.4, 0.1, 0.1);
    glCallList(blend_enable_list);
    glCallList(braco_list);
    glCallList(blend_disable_list);
    glPopMatrix();
}

