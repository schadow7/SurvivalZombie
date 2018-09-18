#ifndef __OBSERWOWANY_H__
#define __OBSERWOWANY_H__
#include <list>
#include <vector>
class Entity;
class Observer;
/**
 * @brief Klasa obserwowany
 */
class Subject {
public:
    Subject ();
    virtual ~Subject ();
    /**
     * @brief Rejestracja obserwatora
     * @param Wskaźnik na obiekt do dodania
     * @return
     * + true- zakończona sukcesem,
     * + false-zakończona porażką
     */
    virtual bool registerObserver (Observer *);
    /**
     * @brief Usunięcie obserwatora z listy
     * @param Wskaźnik na obiekt do usunięcia
     * @return
     * + true- zakończona sukcesem,
     * + false-zakończona porażką
     */
    bool unregisterObserver (Observer *);
    /**
     * @brief Powiadomienie obserwatorów
     * @param wartosc
     */
	void notify(Entity *) const;
private:
    std::list<Observer * > m_observers;
};

#endif
