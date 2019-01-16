//simples teste da API OpenAL com um parser de arquivo wav
//atualmente está com suporte para apenas uma source
//ainda falta implementar as caracteristicas de audio 3D

#include "audio.hpp"
#include "keyboard.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

ALCcontext *context;
ALCdevice *device;
vector<ALuint> buffers;
ALuint buffer;
vector<ALuint> sources;
ALuint source;

void getAlError(void){
    ALenum error = alGetError();
    switch (error) {
        case AL_NO_ERROR:
            cout << "ERROR: sem erros." << '\n';
            break;
        case AL_INVALID_NAME:
            cout << "ERROR: NOME INVALIDO." << '\n';
            break;
        case AL_INVALID_ENUM:
            cout << "ERROR: ENUM INVALIDO." << '\n';
            break;
        case AL_INVALID_VALUE:
            cout << "ERROR: VALOR INVALIDO." << '\n';
            break;
        case AL_INVALID_OPERATION:
            cout << "ERROR: OPERACAP INVALIDA." << '\n';
            break;
        case AL_OUT_OF_MEMORY:
            cout << "ERROR: SEM MEMORIA." << '\n';
            break;
    }
}

void alInit(void){
// Initialize Open AL
device = alcOpenDevice(NULL); // open default deviceif (device != NULL) {
    context = alcCreateContext(device,NULL); // create context
    if (context != NULL) {
        alcMakeContextCurrent(context); // set active context
    }
    alGetError();
 }


//cria um buffer e se for valido o coloca em um vetor de buffers
void setBuffers(const ALvoid *data, short int format ,ALsizei size, ALsizei frequency){
    alGenBuffers(1, &buffer);
    if(alIsBuffer(buffer)){
        buffers.push_back(buffer);
            if(format == 8){
                alBufferData (buffer, AL_FORMAT_MONO8, data, size, frequency);
            }
            else if(format == 16){
                alBufferData (buffer, AL_FORMAT_MONO16, data, size, frequency);
            }
        alGetError();
    }
    else{
        alGetError();
    }
}

void destroyBuffers(void){
    while (!buffers.empty())
    {
        buffers.pop_back();
        alDeleteBuffers(1, &buffer);
        alGetError();
    }
}

//cria um source e se for valido a coloca em um vetor de sources
void setSources(void){
    alGenSources(1, &source);
    if(alIsSource(source)){
        sources.push_back(source);
    }
    else{
        alGetError();
    }
    
    //setting parameters
    alSource3f(source, AL_POSITION, 100.0, 100.0, 100.0);
    alSourcef(source, AL_GAIN, 0.5f);
    alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
    alSourcef(source, AL_ROLLOFF_FACTOR, 10.0f);
    alSourcef(source, AL_REFERENCE_DISTANCE, 0.0);
    alSourcef(source, AL_MAX_DISTANCE, 200.0);
    alSourcei(source, AL_BUFFER, buffer);
}

void destroySources(void){
    while (!sources.empty())
    {
        sources.pop_back();
        alDeleteSources(1, &source);
        alGetError();
    }
}

ALfloat ORIENTATION[] = { 0.0,0.0,-1.0, 0.0,1.0,0.0};

//cria um objeto listener
void setListener(void){
    alListener3f(AL_POSITION, cameraX, cameraY, cameraZ);
    alListenerfv(AL_ORIENTATION, ORIENTATION);
    cout << "posicao listener: " << cameraX << cameraY <<cameraZ<<endl;
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alListenerf(AL_GAIN, 0.5f);
    alGetError();
}


 //void queueBufferToSource(ALuint source, ALsizei buffer, ALuint *buffers){
// alSourceQueueBuffers(source, buffer, buffers);
 //}
 
 //void unqueueBufferFromSource(ALuint source, ALsizei buffer, ALuint *buffers){
 //stopSource();
 //alSourceUnqueueBuffers(source, buffer, buffers);
 //}

void alCleanUp(void){
  //  unqueueBufferFromSource(source, 1, &buffer);
    destroySources();
    destroyBuffers();
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
    alGetError();
}
//controle de execucao de source

void pauseSource(){
    alSourcePause(source);
}

void stopSource(){
    alSourceStop(source);
}

void playSource(){
    stopSource();
    alSourcePlay(source);
}

void rewindSource(){
    alSourceRewind(source);
}


//wavLoader
typedef struct header_file* header_p;

void wavLoader(){
    char file[] = "/Volumes/HD Mac/Workspaces/C++/xcode/aprendizado/aprendizado/wav/dead 1.wav";
    FILE * wav_file = fopen(file,"rb");        // Open wave file in read mode
    header_p meta = (header_p)malloc(sizeof(header));    // header_p points to a header struct that contains the wave file metadata fields
    
    if (wav_file)
    {
        fread(meta, 1, sizeof(header), wav_file);
       /* cout << " ChunkID is "<< meta->chunk_id << endl;
        cout << " ChunkSize is "<< meta->chunk_size << endl;
        cout << " format of the file is "<< meta->format << endl;
        cout << " Subchunk1ID is "<< meta->subchunk1_id << endl;
        cout << " Subchunk1 Size is "<< meta->subchunk1_size << endl;
        cout << " AudiFormat is "<< meta->audio_format << endl;
        cout << " NumChannels is "<< meta->num_channels << endl;
        cout << " Sampling rate of the input wave file is "<< meta->sample_rate <<" Hz" << endl;
        cout << " ByteRate is "<< meta->byte_rate << endl;
        cout << " BlockAlign is "<< meta->block_align << endl;
        cout << " BitsPerSample is "<< meta->bits_per_sample << endl;
        cout << " Subchunk2ID is "<< meta->subchunk2_id << endl;
        cout << " Subchunk2Size is "<< meta->subchunk2_size << endl;
        
        cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << endl;*/
        
        short *buff16;
        buff16 = new short [meta->subchunk2_size/(meta->bits_per_sample/8)]; // Create an element for every sample
        fread(buff16,meta->bits_per_sample/8,meta->subchunk2_size/(meta->bits_per_sample/8), wav_file);        // Reading data in chunks
        
        fclose(wav_file);
        
        setBuffers(buff16,meta->bits_per_sample,meta->subchunk2_size/(meta->bits_per_sample/8), meta->sample_rate);
       // queueBufferToSource(source, 1, &buffer);
        
        /* for(auto i = 0 ; i < meta->subchunk2_size/(meta->bits_per_sample/8) ; i++){
         cout << "Data: " << buff16[i] << endl;
         }*/
    }
}

