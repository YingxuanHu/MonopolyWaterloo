#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;

class Observer {
public:
    virtual void Notify(Subject&) = 0;
    virtual ~Observer() { };
};

#endif
