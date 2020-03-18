#ifndef __VIRUS_AGENT__H
#define __VIRUS_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

class VirusController : public Process, public AgentInterface {

    public:
    VirusController() : Process(), AgentInterface(){}

    void init() {}

    void start() {}    

    void update() {
        omni_apply_force(0,100);

        if(y() > 1000 ) {
            remove_agent(id());
        }
    }

    void stop() {}

    int speed;

};

class Virus : public Agent {
    public:
    Virus(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    VirusController c;
};

DECLARE_INTERFACE(Virus)

#endif
