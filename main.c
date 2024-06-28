#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char* argv[]) 
{
    // Get the pointer to the display (the display being just the general name for your screens and whats on them)
    Display* display = XOpenDisplay(NULL);
    if (display == NULL)
    {
        printf("Failed to open display. Terminating\n");
        return -1;
    }
    // Get which screen to open the window on. This just gets the default which I assume is the primary screen
    unsigned int screenNumber = DefaultScreen(display);

    // Create a simple window on the display at a certain position, size and border width
    // the BlackPixel call in this example is the border colour, the WhitePixel call is the window background
    Window window = XCreateSimpleWindow(display, RootWindow(display, screenNumber), 10, 10, 800, 600, 1, BlackPixel(display, screenNumber), WhitePixel(display, screenNumber));

    // Map the window (actually create it lmao idk how this works leave me alone)
    XMapWindow(display, window);

    char shouldClose = 0;
    XEvent event;
    while (!shouldClose)
    {
        // event loop, pretty standard stuff

        // get the status of all events, e.g. seeing if the window should close, if there's been user input etc.
        XNextEvent(display, &event);

        switch (event.type)
        {
            case ClientMessage: // the window should close
            shouldClose = 1; break;
        }
    }

    // this destroys and closes the window and display believe it or not
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}