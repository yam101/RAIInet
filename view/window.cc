#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include "window.h"

using namespace std;

Xwindow::Xwindow(int width, int height) : width{width}, height{height}
{

  d = XOpenDisplay(NULL);
  if (d == NULL)
  {
    cerr << "Cannot open display" << endl;
    exit(1);
  }
  s = DefaultScreen(d);
  w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                          BlackPixel(d, s), WhitePixel(d, s));
  XSelectInput(d, w, ExposureMask | KeyPressMask);
  XMapRaised(d, w);

  // give window manager time to process the map request
  usleep(10000);

  Pixmap pix = XCreatePixmap(d, w, width,
                             height, DefaultDepth(d, DefaultScreen(d)));
  gc = XCreateGC(d, pix, 0, (XGCValues *)0);

  XFlush(d);
  XFlush(d);

  XColor xcolour = {}; // Initialize to zero
  Colormap cmap;
  char color_vals[7][11] = {"white", "black", "darkred", "darkgreen", "blue", "darkorange", "violet"};

  cmap = DefaultColormap(d, DefaultScreen(d));
  for (int i = 0; i < 7; ++i)
  {
    XParseColor(d, cmap, color_vals[i], &xcolour);
    XAllocColor(d, cmap, &xcolour);
    colours[i] = xcolour.pixel;
  }

  XSetForeground(d, gc, colours[Black]);

  XSizeHints hints;
  hints.flags = (USPosition | PSize | PMinSize | PMaxSize);
  hints.height = hints.base_height = hints.min_height = hints.max_height = height;
  hints.width = hints.base_width = hints.min_width = hints.max_width = width;
  XSetNormalHints(d, w, &hints);

  XSynchronize(d, False); // asynchronous for better performance

  // ensure window is fully mapped and ready before any drawing
  XMapWindow(d, w);
  XFlush(d);
  usleep(50000);
  XSync(d, False);
}

Xwindow::~Xwindow()
{
  XFreeGC(d, gc);
  XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour)
{
  XSetForeground(d, gc, colours[colour]);
  XFillRectangle(d, w, gc, x, y, width, height);
  XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, string msg, int colour)
{
  XSetForeground(d, gc, colours[colour]);
  XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
}

void Xwindow::sync()
{
  XSync(d, False); // ensure all pending operations complete
}

void Xwindow::processEvents()
{
  XEvent event;
  while (XPending(d))
  {
    XNextEvent(d, &event);
  }
}

void Xwindow::flush()
{
  XFlush(d);
}
