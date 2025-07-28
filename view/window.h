#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow
{
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[7];

public:
  Xwindow(int width = 500, int height = 500); // Constructor; displays the window.
  ~Xwindow();                                 // Destructor; destroys the window.

  enum
  {
    White = 0,
    Black,
    Red,
    Green,
    Blue,
    Orange,
    Magenta
  }; // Black - unknown, Red - virus, Green - data, Orange - firewall, Blue - server port

  int getWidth() const;
  int getHeight() const;

  void fillRectangle(int x, int y, int width, int height, int colour = White);

  void drawString(int x, int y, std::string msg, int colour = Black);

  void sync();
  void processEvents();
  void flush();
};

#endif
