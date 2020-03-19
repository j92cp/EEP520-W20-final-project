#ifndef __COORDINATOR_AGENT__H
#define __COORDINATOR_AGENT__H 

#include "enviro.h"

using namespace enviro;

class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface(), counter(0), scroll(0), next(0), row(0) {}

    /*
        This coordinator class handles all the enemy spawning. Saves a huge amount of time,
        because rather than having to program in multiple agents at once, Coordinator just renders them in.
    */

    void init() {

    }
    void start() {}
    void update() {

        if ( counter++ == 100 ) {//base enemies

            if ( next <= 2 ) {
                for ( double x = -550; x <= 550; x += 50) {
                    for ( double y = -1000; y <= -800; y += 50 ) {
                        add_agent("Virus", x, y, 0, { {"fill", "blue"}});
                    }
                }
            }

            if ( next > 3 && next <= 7 ) {//same number and density, but they move faster
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

    int counter, scroll;
    int next = 0;
    int row =0;

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