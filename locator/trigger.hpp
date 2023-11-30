#pragma once

#include <string>
#include <list>

#include <iostream>
class AbstractObject;

class AbstractTrigger{
    friend class AbstractObject;
protected:
    AbstractObject *object;
public:
    virtual void update(){};
};

class AbstractObject{
private: 
    std::list<AbstractTrigger *> triggers;
public:
     ~AbstractObject()
    {

        std::list<AbstractTrigger * >::iterator it = triggers.begin();

        while (it != triggers.end())
        {
            delete *it;
            it = triggers.erase(it);
        }
    }

    void addTrigger(AbstractTrigger *  new_trigger)
    { 
        new_trigger->object = this;

        triggers.push_back(new_trigger);
    }

    void removeTrigger(AbstractTrigger * const new_trigger)
    {
        triggers.remove(new_trigger);
        delete new_trigger;
    }

    void notify()
    {
        std::list<AbstractTrigger * >::iterator it = triggers.begin();
        
        while (it != triggers.end())
        {
            (*it++)->update();
            //it++;
        }
    }
};

