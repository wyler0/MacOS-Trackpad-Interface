# MacOS-Trackpad-Interface
Python and C++ code for interfacing with MacOS MultiTouchSupport data. 

Tested on MacOS Big Sur.

See requirements.txt for required python packages.

Compile Commands for C++ Portion:
g++ -c -fPIC trackpad.c -o trackpad.o 
g++ -dynamiclib -F/System/Library/PrivateFrameworks -framework MultitouchSupport -framework CoreFoundation -undefined error -o libtrackpad.so trackpad.o

See trackpadWrapper for available finger touch data.