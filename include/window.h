#ifndef WINDOW_H
#define WINDOW_H

#include "raylib.h"

namespace GameWindow {
    // Initializes the window (resizable, but starts at default size)
    void Init(int width, int height, const char* title);
    
    // Closes the window
    void Close();
}

#endif