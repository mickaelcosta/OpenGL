//  main.cpp
//  aprendizado
//  Created by User on 26/11/18.
//  Copyright © 2018 mickael. All rights reserved.

#include <iostream>
#include <GLUT/GLUT.h>
#include "robo.hpp"
#include "keyboard.hpp"
#include "grid.hpp"
#include "light.hpp"
#include "audio.hpp"

using namespace std;

int esfera_list, braco_list, blend_enable_list, blend_disable_list, grid_list;
GLfloat fogColor[] = { 1.0, 1.0, 1.0, 1 };
Robo m_robo1;
Audio m_audio1;


void enableBlend(void){
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
}
void disableBlend(void){
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}
void alCleanAudio(void){
    m_audio1.alCleanUp();
}

void display(void){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //grid
    glPushMatrix(); //set global matrix
    glCallList(grid_list);
    glTranslatef(0.0, 2.0, 0.0);
   
    //moving light
    glPushMatrix();
    glRotated(spin, 1.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix(); // para totacionar só a luz
    
    //braco robotico
    glPushMatrix();
    m_robo1.gerarRobo();
    glPopMatrix();

    glPopMatrix();//restaura matriz global para próximo frame
    glutSwapBuffers();
}

void init(void){
    //plano de fundo
    glClearColor(1, 1, 1, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    
    //listas para performance
    grid_list = glGenLists(1);
    if(grid_list!= 0){
        glNewList(grid_list, GL_COMPILE);
        desenhaGrid(50);
        glEndList();
    }
    braco_list = glGenLists(1);
    if(braco_list != 0){
        glNewList(braco_list, GL_COMPILE);
        desenha_braco();
        glEndList();
    }
    esfera_list = glGenLists(1);
    if(esfera_list != 0){
        glNewList(esfera_list, GL_COMPILE);
        desenha_esfera();
        glEndList();
    }
    blend_enable_list = glGenLists(1);
    if(blend_enable_list != 0){
        glNewList(blend_enable_list, GL_COMPILE);
        enableBlend();
        glEndList();
    }
    blend_disable_list = glGenLists(1);
    if(blend_disable_list != 0){
        glNewList(blend_disable_list, GL_COMPILE);
        disableBlend();
        glEndList();
    }
    //light
    lightInit();
    
   // fog
   glFogi (GL_FOG_MODE, GL_LINEAR);
   glFogfv (GL_FOG_COLOR, fogColor);
   glFogf (GL_FOG_DENSITY, 0.35);
   glFogf(GL_FOG_START, 20.0);
   glFogf(GL_FOG_END, 100.0);
   glHint (GL_FOG_HINT, GL_NICEST);
   glEnable(GL_FOG);

    //audio
    m_audio1.alInit();
    m_audio1.wavLoader();
    m_audio1.setSource();
    m_audio1.setListener();
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void menu(int item){
    if(item == 1)
        exit(0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Braço Robótico");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(Specialkey);
    
    //pop up menu experimental
    glutCreateMenu(menu);
    glutAddMenuEntry("Quit Program", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    init();
    glutMainLoop();
    atexit(alCleanAudio);
    return 0;
}
