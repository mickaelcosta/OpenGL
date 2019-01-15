//
//  glLists.cpp
//  aprendizado
//
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.


#include <GLUT/GLUT.h>
#include "glLists.hpp"

void enableBlend(void){
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
}

void disableBlend(void){
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}
