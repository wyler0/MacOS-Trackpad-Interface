/*
Trackpad Event Interface
Use the following to compile:

g++ -c -Werror -fPIC trackpad.c -o trackpad.o 
g++ -dynamiclib -F/System/Library/PrivateFrameworks -framework MultitouchSupport -framework CoreFoundation -undefined error -o libtrackpad.so trackpad.o

*/
#include "trackpad.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <CoreFoundation/CoreFoundation.h>

Trackpad::Trackpad(){
    MTDeviceRef dev = MTDeviceCreateDefault();
    MTRegisterContactFrameCallback(dev, (Trackpad_callback_wrapper));
    MTDeviceStart(dev, 0);
    f = new Finger*[10];
    numFingers = 0;
}

int Trackpad::callback(int device, Finger *data, int nFingers, double timestamp, int frame){
    for (int i=0; i<nFingers; i++) {
        f[i] = &data[i];
        numFingers = nFingers;
        if(f){
            /*printf("Frame %7d: Angle %6.2f, ellipse %6.3f x%6.3f; "
                "position (%6.3f,%6.3f) vel (%6.3f,%6.3f) "
                "ID %d, state %d [%d %d?] size %6.3f, %6.3f?\n",
            f->frame,
            f->angle * 90 / atan2(1,0),
            f->majorAxis,
            f->minorAxis,
            f->normalized.pos.x,
            f->normalized.pos.y,
            f->normalized.vel.x,
            f->normalized.vel.y,
            f->identifier, f->state, f->foo3, f->foo4,
            f->size, f->unk2);*/
        }
    }
    return 0;
}

float * Trackpad::posx(){
    if(f){
        float * toReturn = new float[numFingers];
        for(int i=0; i<numFingers; i++){
            toReturn[i] = f[i]->normalized.pos.x;
        }
        return toReturn;
    }
    return nullptr;
}

float * Trackpad::posy(){
    if(f){
        float * toReturn = new float[numFingers];
        for(int i=0; i<numFingers; i++){
            toReturn[i] = f[i]->normalized.pos.y;
        }
        return toReturn;
    }
    return nullptr;
}


extern "C" {
    Trackpad* Trackpad_new(){
        main_trackpad_obj = new Trackpad(); 
        return main_trackpad_obj;
    }
    int Trackpad_numFingers(Trackpad* track){
        if(track){return track->numFingers;}
        return -1;
    }
    float * Trackpad_posx(Trackpad* track){
        if(track){return track->posx();}
        return nullptr;
    }
    float * Trackpad_posy(Trackpad* track){
        if(track){return track->posy();}
        return nullptr;
    }
}



/*int main() {
    MTDeviceRef dev = MTDeviceCreateDefault();
    main_trackpad_obj = new Trackpad();
    MTRegisterContactFrameCallback(dev, Trackpad_callback_wrapper);
    MTDeviceStart(dev, 0);
    printf("Ctrl-C to abort\n");
    sleep(-1);
    return 0;
}*/