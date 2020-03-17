#ifndef __VIRUS_AGENT__H
#define __VIRUS_AGENT__H 

#include "enviro.h"
#include <math.h>

using namespace enviro;

class VirusController : public Process, public AgentInterface {

    public:
    VirusController() : Process(), AgentInterface(), pos_x(0), pos_y(0) {}

    void init() {
        watch("player_position", [&](Event& e) {
            pos_x  = e.value()["x"];
            pos_y  = e.value()["y"];
        });
    }

    void start() {}    

    void update() {
        omni_move_toward(pos_x, pos_y, 0.1);
    }

    void stop() {}

    double pos_x, pos_y;


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
