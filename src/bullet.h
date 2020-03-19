#ifndef __BULLET_AGENT__H
#define __BULLET_AGENT__H 

#include "enviro.h"

using namespace enviro;

class BulletController : public Process, public AgentInterface {

    public:
    BulletController() : Process(), AgentInterface(), counter(0) {}

    void init() {
        void prevent_rotation();
        notice_collisions_with("Virus", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
            emit(Event ("point"));//on collision, this event is watched by the Player agent, and returns a numerical value. This is the point system for this program.
        });

        notice_collisions_with("Virus2", [&](Event &e) {
            remove_agent(e.value()["id"]);
            remove_agent(id());
            emit(Event ("point"));
        });                 
    }
    void start() {}
    void update() {
        if ( counter++ > 20 ) {//automatically despawns bullets should they exceed 20 copies on screen
            remove_agent(id());
        }
    }
    void stop() {}

    double counter;

};

class Bullet : public Agent {
    public:
    Bullet(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    BulletController c;
};

DECLARE_INTERFACE(Bullet)

#endif