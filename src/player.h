#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"

using namespace enviro;

class PlayerController : public Process, public AgentInterface {

    public:
    PlayerController() : Process(), AgentInterface(), f(0), LEFT(false), RIGHT(false), firing(false) {}

    void init() {
        prevent_rotation();
        watch("keydown", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "p" && !firing ) {
                firing = true;
            } else if ( k == "w" ) {
                  f = -magnitude;              
            } else if ( k == "s" ) {
                  f = magnitude;  
            } else if ( k == "a" ) {//instead of rotation, the player agent moves laterally
                  LEFT = true;
            } else if ( k == "d" ) {//this movement was refactored from the platformer example
                  RIGHT = true;
            } 
        });        
        watch("keyup", [&](Event &e) {
            auto k = e.value()["key"].get<std::string>();
            if ( k == "p" ) {
                firing = false;
            } else if ( k == "w" || k == "s" ) {
                  f = 0;               
            } else if ( k == "a" ) {
                  LEFT = false;
            } else if ( k == "d" ) {
                  RIGHT = false;
            } 
        });

        zoom(0.75);

        notice_collisions_with("Virus", [&](Event &e) {
            remove_agent(id());
        }); 

    }


    void start() {

    }


    void update() {
        double fx;
        if ( RIGHT ) {
            vx = VEL_X;
        } if ( LEFT ) {
            vx = -VEL_X;
        } else if ( !RIGHT && !LEFT ) {
            vx = 0;
        }
        fx = -K_X*(velocity().x-vx);

        if ( firing ) {//holding the "fire" button to sustain shooting is a lot more desireable than continual pressing
            Agent& bullet = add_agent("Bullet", 
            x() - 17 + 17*cos(angle()), 
            y() - 17 + 17*sin(angle()), 
            angle(), 
            BULLET_STYLE);  
            bullet.apply_force(200,0);
            
            Agent& bullet2 = add_agent("Bullet", //added twin firing capabilities
            x() + 17 + 17*cos(angle()), 
            y() - 17 + 17*sin(angle()),
            angle(), 
            BULLET_STYLE);  
            bullet2.apply_force(200,0);
            
        }
        
        emit(Event("player_position", { 
            { "x", x() }, 
            { "y", y() }    
        }));            

        omni_apply_force(fx,f);
    }
    void stop() {}

    bool LEFT, RIGHT;
    double vx;

    const double VEL_X = 100;
    const double K_X = 15;

    double f;
    double const magnitude = 700;
    bool firing;
    const json BULLET_STYLE = { 
                   {"fill", "green"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               };

};

class Player : public Agent {
    public:
    Player(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    PlayerController c;
};

DECLARE_INTERFACE(Player)

#endif