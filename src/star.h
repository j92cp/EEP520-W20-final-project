#ifndef __STAR_AGENT__H
#define __STAR_AGENT__H 

#include "enviro.h"

using namespace enviro;

class starController : public Process, public AgentInterface {

    public:
    starController() : Process(), AgentInterface(), stream(0) {}

    void init() {
        void prevent_rotation();
        notice_collisions_with("Virus", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
        });

        notice_collisions_with("Virus2", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
        });                 
    }
    void start() {}
    void update() {
        if ( stream++ > 20 ) {
            remove_agent(id());
        }
    }
    void stop() {}

    double stream;


};

class star : public Agent {
    public:
    star(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    starController c;
};

DECLARE_INTERFACE(star)

#endif