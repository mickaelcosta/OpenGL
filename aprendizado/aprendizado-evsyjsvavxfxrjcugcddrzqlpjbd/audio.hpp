//  audio.hpp
//  aprendizado
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.

#ifndef audio_hpp
#define audio_hpp

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <OpenAL/OpenAL.h>

using namespace std;

typedef struct header_file
{
    char chunk_id[4];
    int chunk_size;
    char format[4];
    char subchunk1_id[4];
    int subchunk1_size;
    short int audio_format;
    short int num_channels;
    int sample_rate;            // sample_rate denotes the sampling rate.
    int byte_rate;
    short int block_align;
    short int bits_per_sample;
    char subchunk2_id[4];
    int subchunk2_size;            // subchunk2_size denotes the number of samples.
} header;

typedef struct header_file* header_p;

class Audio{
private:
    ALCcontext *context;
    ALCdevice *device;
    ALuint buffer;
    ALuint source;
public:
    //interfaces das funções
    void alInit(void);
    void alCleanUp();
    void setListener(void);
    void setBuffer(const ALvoid *data, short int format ,ALsizei size, ALsizei frequency);
    void destroyBuffer(void);
    void setSource(void);
    void destroySource(void);
    void wavLoader(void);//setbuffers inside
    
    //-------------------------------------
    //--- Controle de execucao de audio ---
    //-------------------------------------
    inline void stopSource(void){
        alSourceStop(source);
    }
    inline void playSource(void){
        stopSource();
        alSourcePlay(source);
    }
    inline void pauseSource(void){
        alSourcePause(source);
    }
    inline void rewindSource(void){
         alSourceRewind(source);
    }
    
    Audio(){};
    ~Audio(){};
};
#endif /* audio_hpp */
