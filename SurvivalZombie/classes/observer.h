#ifndef __OBSERWATOR_H__
#define __OBSERWATOR_H__
#include<vector>
class Entity;
/**
 * @brief Klasa obserwatora
 */
class Observer {
public:
    virtual ~Observer () {}
    /**
     * @brief Aktualizuje obserwowane wartości
     */
	virtual void updateObserver(Entity*) = 0;
};

#endif
