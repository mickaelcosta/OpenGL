//
//  keyboard.cpp
//  aprendizado
//
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <iostream>
#include "keyboard.hpp"
#include "robo.hpp"
#include "audio.hpp"

//definição das variáveis
ALfloat cameraX = 3.0, cameraY = 5.0 , cameraZ = 5.0;

GLdouble spin = 0.0;

//implementação das funções
void Specialkey(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            cameraY += 0.25;
            gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            alListener3f(AL_POSITION, cameraX, cameraY, cameraZ);
            std::cout << "posicao listener: " << " " <<cameraX<< " " << cameraY<< " " <<cameraZ << std::endl;
                playSource();
            break;
        case GLUT_KEY_DOWN:
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            cameraY -= 0.25;
            gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case GLUT_KEY_LEFT:
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            cameraX -= 0.25;
            gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case GLUT_KEY_RIGHT:
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            cameraX += 0.25;
            gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
    }
    glutPostRedisplay();
}

GLdouble atualizaPosicaoLuz(void){
    if (spin <= 360)
        return spin += 5.0;
    else
        return 0;
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'l': /* s key rotates light */
            spin = atualizaPosicaoLuz();
            break;
        case 's': /* s key rotates at shoulder */
            if(shoulder <= MAX_SHOLDER_ANGLE)
                shoulder = (shoulder + 5) % 360;
            break;
        case 'S':
            if(shoulder >= MIN_SHOLDER_ANGLE)
                shoulder = (shoulder - 5) % 360;
            break;
        case 'e': /* e key rotates at elbow */
            if(elbow <= MAX_ELBOW_ANGLE)
                elbow = (elbow + 5) % 360;
            break;
        case 'E':
            if(elbow >= MIN_ELBOW_ANGLE)
                elbow = (elbow - 5) % 360;
            break;
        case 'w': /* e key rotates at elbow */
            if (wrist <= MAX_WRIST_ANGLE)
                wrist = (wrist + 5) % 360;
            break;
        case 'W':
            if (wrist >= MIN_WRIST_ANGLE)
                wrist = (wrist - 5) % 360;
            break;
        case 'f': /* e key rotates at elbow */
            if (fingers <= MAX_FINGERS_ANGLE)
                fingers = (fingers + 5) % 360;
            break;
        case 'F':
            if (fingers >= MIN_FINGERS_ANGLE)
                fingers = (fingers - 5) % 360;
            break;
        case 'r': /* e key rotates at elbow */
            if (shoulder_rotate <= 360)
                shoulder_rotate = (shoulder_rotate + 5) % 360;
            break;
        case 'R':
            if (shoulder_rotate >= -360)
                shoulder_rotate = (shoulder_rotate - 5) % 360;
            break;
        case 'z':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            cameraZ += 0.25;
            gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        case 'Z':
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            cameraZ -= 0.25;
            gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
            break;
        default:
            break;
    }
    avisoLimiteArticulacao(shoulder, shoulder_rotate, elbow, fingers);
}
