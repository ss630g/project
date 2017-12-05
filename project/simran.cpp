#include "project.h"
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif
bool h = false;
void Playsound(ALuint tum) 
{
    alSourcePlay(tum);
}

void csound(const char *a) 
{

#ifdef USE_OPENAL_SOUND
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
        printf(" There is an error  in alutInit()\n");
        return;
    }

    alGetError();

    float termoil[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, termoil);
    alListenerf(AL_GAIN, 1.0);

    ALuint toom;
    toom = alutCreateBufferFromFile(a); 

    ALuint tum;

    alGenSources(1, &tum);
    alSourcei(tum, AL_BUFFER, toom);

    alSourcef(tum, AL_GAIN, 0.20);
    alSourcef(tum, AL_PITCH, 1.0);
    alSourcei(tum, AL_LOOPING, 0);

    if (alGetError() != AL_NO_ERROR) {
        printf("cannot set the source\n");
        return;
    }
    Playsound(tum);
    if(h == true) {
        alDeleteSources(1, &tum);
        alDeleteBuffers(1, &toom);
    }
#endif
}

void dsound()
{ 
#ifdef USE_OPENAL_SOUND
    h = true;

    ALCcontext *stuff = alcGetCurrentContext();
    ALCdevice *yantar = alcGetContextsDevice(stuff);

    alcMakeContextCurrent(NULL);
    alcDestroyContext(stuff);
    alcCloseDevice(yantar);

#endif
}

void vecTrans(int x,int y, int z,Vec v) {
    v[0] = x + v[0];
    v[1] = y + v[1];
    v[2] = z + v[2];

}
void vecScale(int x,int y, int z,Vec v) {
    v[0] = x * v[0];
    v[1] = y * v[1];
    v[2] = z * v[2];
}


void identity(Mat m) {
    m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0;
    m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0;
    m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0;
}
void applyRotation(Mat m, int axis, Flt angle) {
    Flt c = cos(angle);
    Flt s = sin(angle);
    switch (axis) {
        case 0:
            m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0;
            m[1][0] = 0.0; m[1][1] =   c; m[1][2] =  -s;
            m[2][0] = 0.0; m[2][1] =   s; m[2][2] =   c;
            break;
        case 1:
            m[0][0] =   c; m[0][1] = 0.0; m[0][2] =  -s;
            m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0;
            m[2][0] =   s; m[2][1] = 0.0; m[2][2] =   c;
            break;
        case 2:
            m[0][0] =   c; m[0][1] =  -s; m[0][2] = 0.0;
            m[1][0] =   s; m[1][1] =   c; m[1][2] = 0.0;
            m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0;
            break;
    }
}
void transformVec(Mat m, Vec v) {
    Vec t = {
        v[0] * m[0][0] + v[1] * m[0][1] + v[2] * m[0][2],
        v[0] * m[1][0] + v[1] * m[1][1] + v[2] * m[1][2],
        v[0] * m[2][0] + v[1] * m[2][1] + v[2] * m[2][2] };
    v[0] = t[0];
    v[1] = t[1];
    v[2] = t[2];
}

