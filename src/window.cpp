#include "window.h"

namespace GameWindow {

    void Init(int width, int height, const char* title) {
        // Allow the user to resize or maximize the window
        SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
        
        // Open the window at the standard size (e.g., 1280x720)
        // It will NOT be maximized by default, but you can click the square icon to do so.
        InitWindow(width, height, title);
        
        SetExitKey(KEY_NULL);
        SetTargetFPS(60);
    }

    void Close() {
        CloseWindow();
    }
}