#include "subject.h"
#include "observer.h"
#include <algorithm>

Subject::Subject () {
}

Subject::~Subject () {
}

bool Subject::registerObserver (Observer * obserwator) {
    if (std::find(m_observers.begin(), m_observers.end(), obserwator) == m_observers.end()) {
        m_observers.push_back(obserwator);
        return true;
    } else
        return false;
}

bool Subject::unregisterObserver (Observer * obserwator) {
    std::list<Observer *>::iterator it;
    it = std::find(m_observers.begin(), m_observers.end(), obserwator);
    if (it != m_observers.end()) {
        m_observers.erase(it);
        return true;
    } else
        return false;
}

void Subject::notify(Entity * ptr) const
{
	std::list<Observer *>::const_iterator it = m_observers.begin();
	for (; it != m_observers.end(); ++it) {
		(*it)->update(ptr);
	}
}
