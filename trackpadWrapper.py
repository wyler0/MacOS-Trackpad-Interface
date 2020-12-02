#!/usr/bin/env python3
from ctypes import cdll
import ctypes as C

lib = cdll.LoadLibrary('libtrackpad.so') # Note: May need to update this path for personal use. 
lib.Trackpad_new.restype  = C.c_void_p
lib.Trackpad_new.argtypes = []
lib.Trackpad_numFingers.restype  = C.c_int
lib.Trackpad_numFingers.argtypes = [C.c_void_p]
lib.Trackpad_posx.restype  = C.POINTER(C.c_float * 10)
lib.Trackpad_posx.argtypes = [C.c_void_p]
lib.Trackpad_posy.restype  = C.POINTER(C.c_float * 10)
lib.Trackpad_posy.argtypes = [C.c_void_p]

class Trackpad(object):
    """Trackpad Finger Position Reading Interface."""
    def __init__(self):
        """Create a C trackpad object."""
        self.obj = lib.Trackpad_new()

    def numFingers(self):
        """Return the y position of finger on trackpad as float."""
        return lib.Trackpad_numFingers(self.obj)

    def posx(self):
        """Return list of x positions of fingers on trackpad as float, or empty list."""
        return [i for i in lib.Trackpad_posx(self.obj).contents if i > 1e-5 and i < 1]

    def posy(self):
        """Return list of y positions of fingers on trackpad as float, or empty list."""
        return [i for i in lib.Trackpad_posy(self.obj).contents if i > 1e-5 and i < 1]