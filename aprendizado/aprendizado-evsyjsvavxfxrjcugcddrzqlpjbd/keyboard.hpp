//
//  keyboard.hpp
//  aprendizado
//
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.
//

#ifndef keyboard_hpp
#define keyboard_hpp

#include <stdio.h>
#include <GLUT/GLUT.h>
#include <OpenAL/OpenAL.h>

//variáveis
extern ALfloat cameraX, cameraY, cameraZ;
extern GLdouble spin;


//interface das funções
void Specialkey(int key, int x, int y);
GLdouble atualizaPosicaoLuz(void);
void keyboard(unsigned char key, int x, int y);

#endif /* keyboard_hpp */
