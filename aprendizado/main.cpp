//
//  main.cpp
//  aprendizado
//
//  Created by User on 26/11/18.
//  Copyright © 2018 mickael. All rights reserved.

#include <iostream>
#include <GLUT/GLUT.h>
#include "robo.hpp"
#include "keyboard.hpp"
#include "grid.hpp"
#include "glLists.hpp"
#include "light.hpp"
#include "audio.hpp"

using namespace std;

static int esfera_list, braco_list, blend_enable_list, blend_disable_list, grid_list;

void display(void){
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //set global matrix
    glPushMatrix();
    glCallList(grid_list);
    glTranslatef(0.0, 2.0, 0.0);
    glPushMatrix();
    //moving light
    glRotated(spin, 1.0, 0.0, 0.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    //reset global matrix
    glPopMatrix(); // para totacionar só a luz
    glPushMatrix();
    
    //braço
    glTranslatef(-0.75, 0.0, 0.0);
    glCallList(esfera_list);
    glRotatef((GLfloat) shoulder, 0.0, 0.0, 1.0);
    glRotatef((GLfloat) shoulder_rotate, 0.0, 1.0, 0.0);
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
    
    glPopMatrix();
    glPopMatrix();//fonte de luz movel
    
    glutSwapBuffers();
}

void init(void){
    GLfloat fogColor[] = { 1.0, 1.0, 1.0, 1 };
    
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
    
    //plano de fundo
    glClearColor(1, 1, 1, 0.0);
    glShadeModel(GL_SMOOTH);

    //light
    lightInit();
    
   // fog
   glEnable(GL_FOG);
   glFogi (GL_FOG_MODE, GL_LINEAR);
   glFogfv (GL_FOG_COLOR, fogColor);
   glFogf (GL_FOG_DENSITY, 0.35);
   glFogf(GL_FOG_START, 10.0);
   glFogf(GL_FOG_END, 50.0);
   glHint (GL_FOG_HINT, GL_DONT_CARE);
   glFogi(GL_FOG_COORD_SRC, GL_FRAGMENT_DEPTH);
    
    
    //audio
    alInit();
    wavLoader();
    setSources();
    setListener();
    
    //esconder partes de entidades não visíveis
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}



void mouse(int button, int state, int x, int y)
{
    GLint viewport[4];
    GLdouble mvmatrix[16], projmatrix[16];
    GLint realy; /* OpenGL y coordinate position */
    GLdouble wx, wy, wz; /* returned world x, y, z coords */
    
    if(state == GLUT_DOWN){
        switch (button) {
            case GLUT_LEFT_BUTTON:
                glGetIntegerv(GL_VIEWPORT, viewport);
                glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
                glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
                /* note viewport[3] is height of window in pixels */
                realy = viewport[3] - (GLint) y - 1;
                cout << "Coordinates at cursor are" << "(" << x << "," << realy << ") \n";
                gluUnProject((GLdouble) x, (GLdouble) realy, 0.0,
                             mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
                printf("World coords at z=0.0 are (%f, %f, %f)\n",
                       wx, wy, wz);
                gluUnProject((GLdouble) x, (GLdouble) realy, cameraZ,
                             mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
                printf("World coords at z= %f are (%f, %f, %f)\n",
                       cameraZ, wx, wy, wz);
            break;
            default:
            break;
            }
    }
     glutPostRedisplay();
}

void selectColor(int item){
    switch (item) {
        case 1:
            glClearColor(0.0, 1.0, 0.0, 0.0);
            break;
        case 2:
             glClearColor(1.0, 0.0, 0.0, 0.0);
            break;
        case 3:
             glClearColor(0.0, 0.0, 1.0, 0.0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void menu(int item){
    if(item == 1)
       alCleanUp();
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
    glutMouseFunc(mouse);
    glutSpecialFunc(Specialkey);
    
    //pop up menu experimental
    int submenu2;
    submenu2 = glutCreateMenu(selectColor);
    glutAddMenuEntry("Green", 1);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Blue", 3);
    glutCreateMenu(menu);
    glutAddMenuEntry("Quit Program", 1);
    glutAddSubMenu("Color", submenu2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    init();
    glutMainLoop();
    
    alCleanUp();
    return 0;
}
