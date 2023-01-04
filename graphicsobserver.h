#ifndef GRAPHICS_OBSERVER_H_
#define GRAPHICS_OBSERVER_H_

#include "window.h"
#include "observer.h"
class Subject;

class GraphicsObserver: public Observer {
    Subject *subj;
    Xwindow *w;
    char **board; // helps with only rendering what's needed
 public:
  GraphicsObserver(Subject *subj);
  void notify() override;
  virtual ~GraphicsObserver();
};

#endif
