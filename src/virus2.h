#ifndef __VIRUS_AGENT__H
#define __VIRUS_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

class VirusController2 : public Process, public AgentInterface {

    public:
    VirusController2() : Process(), AgentInterface(){}

    void init() {}

    void start() {}    

    void update() {
        omni_apply_force(0,200);

        if(y() > 1000 ) {
            remove_agent(id());
        }
    }

    void stop() {}

    int speed;

};

class Virus2 : public Agent {
    public:
    Virus2(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    VirusController2 c;
};

DECLARE_INTERFACE(Virus2)

#endif
