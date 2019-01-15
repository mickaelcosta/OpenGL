//
//  robo.hpp
//  aprendizado
//
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.
//

#ifndef robo_hpp
#define robo_hpp

#include <stdio.h>

//constantes
#define MAX_SHOLDER_ANGLE 95
#define MIN_SHOLDER_ANGLE -135
#define MAX_ELBOW_ANGLE 120
#define MIN_ELBOW_ANGLE -10
#define MAX_WRIST_ANGLE 70
#define MIN_WRIST_ANGLE -70
#define MAX_FINGERS_ANGLE 15
#define MIN_FINGERS_ANGLE -45

//variaveis
extern int shoulder,
shoulder_rotate,
elbow, wrist,
fingers;

//interface funcoes

void desenha_esfera(void);
void desenha_braco(void);
void avisoLimiteArticulacao(int shoulder, int shoulder_rotate, int elbow, int fingers);

#endif /* robo_hpp */
