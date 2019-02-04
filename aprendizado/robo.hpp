//  robo.hpp
//  aprendizado
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.

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

extern int esfera_list, braco_list, blend_enable_list, blend_disable_list, grid_list;

void desenha_esfera(void);
void desenha_braco(void);

class Robo{
private:
    int shoulder,
    shoulder_rotation,
    elbow, wrist,
    fingers;
    
public:
    inline void setShoulder(int valor){
        shoulder = valor;
    };
    inline void setShoulderRotation(int valor){
        shoulder_rotation = valor;
    };
    inline void setElbow(int valor){
           elbow = valor;
    };
    inline void setWrist(int valor){
           wrist = valor;
    };
    inline void setFingers(int valor){
           fingers = valor;
    };
    
    inline int getShoulder(void){
       return shoulder ;
    };
    inline int getShoulderRotation(void){
       return  shoulder_rotation ;
    };
    inline int getElbow(void){
       return elbow;
    };
    inline int getWrist(void){
       return wrist;
    };
    inline int getFingers(void){
        return fingers;
    };
    
    void gerarRobo(void);
    void avisoLimiteArticulacao(void);
    
    Robo():shoulder{0},shoulder_rotation{0},
    elbow{0}, wrist{0},
    fingers{0}{};
    
    ~Robo(){};
};

//interface funcoes




#endif /* robo_hpp */
