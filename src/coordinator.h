#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"

using namespace enviro;

class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface() {}

    void init() {
        for ( double x = -200; x <= 200; x += 50) {
            for ( double y = -1000; y <= -800; y += 50 ) {
                add_agent("Virus", x, y, 0, { {"fill", "blue"}});
            }
        }
    }
    void start() {}
    void update() {}
    void stop() {}

};

class Coordinator : public Agent {
    public:
    Coordinator(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    CoordinatorController c;
};

DECLARE_INTERFACE(Coordinator)

#endif