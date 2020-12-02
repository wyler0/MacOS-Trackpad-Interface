#include "MultitouchSupport.h"

#ifndef _trackpad
#define _trackpad
extern "C" {
    class Trackpad {
        public:
            Finger **f;
            int numFingers;

            Trackpad();
            int callback(int device, Finger *data, int nFingers, double timestamp, int frame);
            
            float * posx();

            float * posy();
    };

    Trackpad* main_trackpad_obj;
    int Trackpad_callback_wrapper(int device, Finger *data, int nFingers, double timestamp, int frame){
        if(main_trackpad_obj){
            return main_trackpad_obj->callback(device, data, nFingers, timestamp, frame);
        }
        return 1;
    }
}
#endif
