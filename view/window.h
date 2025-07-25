#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s, width, height;
  GC gc;
  unsigned long colours[5];

 public:
  Xwindow(int width=500, int height=500);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Green, Red}; // Black - unknown, Gree - data, Red - virus

  int getWidth() const;
  int getHeight() const;

  void fillRectangle(int x, int y, int width, int height, int colour=White);

  void drawString(int x, int y, std::string msg);

};

#endif
