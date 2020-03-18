#ifndef __BACKGROUND_AGENT__H
#define __BACKGROUND_AGENT__H 

#include "enviro.h"

using namespace enviro;

class backgroundController : public Process, public AgentInterface {

    public:
    backgroundController() : Process(), AgentInterface() {}

    void init() {}
    void start() {}
    void update() {}
    void stop() {}

};

class background : public Agent {
    public:
    background(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    backgroundController c;
};

DECLARE_INTERFACE(background)

#endif