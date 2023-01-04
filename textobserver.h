#ifndef TEXT_OBSERVER_H_
#define TEXT_OBSERVER_H_

#include <iostream>
#include "observer.h"
class Subject;

class TextObserver: public Observer {
    Subject *subj;
    std::ostream &out;
 public:
  TextObserver(Subject *subj, std::ostream &out);
  void notify() override;
  virtual ~TextObserver();
};

#endif
