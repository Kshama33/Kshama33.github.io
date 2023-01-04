#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

class Observer;
class Piece;

class Subject {
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers();
  virtual Piece* at(int x, int y) const = 0;
  virtual ~Subject() = default;
};

#endif
