#include "subject.h"
#include "observer.h"

void Subject::attach(Observer* observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            return;
        }
    }
}

void Subject::notify() {
    for (auto observer : observers) {
        observer->Notify(*this);
    }
}

void Subject::setSubject(Subject* subject) {
    this->subject = subject;
}

