//
//  audio.hpp
//  aprendizado
//
//  Created by User on 15/01/19.
//  Copyright © 2019 mickael. All rights reserved.
//

#ifndef audio_hpp
#define audio_hpp

#include <stdio.h>
#include <OpenAL/OpenAL.h>

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

//interfaces das funções
void alInit(void);
void alCleanUp();
void setListener(void);
void setSources(void);
void wavLoader(void);//setbuffers inside
void playSource(void);
void pauseSource(void);
void stopSource(void);
void rewindSource(void);


void alxSource(ALfloat x);
#endif /* audio_hpp */
