#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>

class Observer;

class Subject {
protected:
    std::vector<Observer*> observers;
    Subject* subject = nullptr;

public:
    virtual ~Subject() {};
    void attach(Observer* observer);
    void detach(Observer* observer);
    void notify();

    void setSubject(Subject* subject);
};

#endif


