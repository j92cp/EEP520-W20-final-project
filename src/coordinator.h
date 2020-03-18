#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"

using namespace enviro;

class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface(), counter(0), next(0) {}

    void init() {

    }
    void start() {}
    void update() {
        if ( counter++ == 100 ) {

            if ( next <= 2 ) {
                for ( double x = -550; x <= 550; x += 50) {
                    for ( double y = -1000; y <= -800; y += 50 ) {
                        add_agent("Virus", x, y, 0, { {"fill", "blue"}});
                    }
                }
            }

            if ( next > 3 && next <= 5 ) {
                for ( double x = -550; x <= 550; x += 50) {
                    for ( double y = -1000; y <= -800; y += 50 ) {
                        add_agent("Virus2", x, y, 0, { {"fill", "red"}});
                    }
                }                                     
            }            

            counter = 0;
            next++;
        }


        
    }
    void stop() {}

    int counter;
    int next = 0;

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