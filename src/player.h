#ifndef __PLAYER_AGENT__H
#define __PLAYER_AGENT__H 

#include "enviro.h"
#include <iostream>


using namespace enviro;

class PlayerController : public Process, public AgentInterface {

    public:
    PlayerController() : Process(), AgentInterface(), f(0), LEFT(false), RIGHT(false), firing(false), firing2(false) {}

    void init() {
        
        prevent_rotation();
        watch("keydown", [&](Event &e) {//the keystroke mechanics are refactored from the virus examples
            auto k = e.value()["key"].get<std::string>();
            if ( k == "p" && !firing ) {
                firing = true;
            } else if ( k == "o" && !firing2 ) {
                firing2 = true;            
            } else if ( k == "w" ) {//I was hoping to change the controls to the arrow keys for better handling, but could not due to time constraints.
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
            } else if ( k == "o" ) {
                firing2 = false; 
            } else if ( k == "w" || k == "s" ) {
                  f = 0;              
            } else if ( k == "a" ) {
                  LEFT = false;
            } else if ( k == "d" ) {
                  RIGHT = false;
            } 
        });

        zoom(1);

        notice_collisions_with("Virus", [&](Event &e) {//these are death mechanics for the player
            remove_agent(id());
        }); 

        notice_collisions_with("Virus2", [&](Event &e) {//coming into contact with enemies calls a remove function
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

        if ( firing2 && charge >= 0 ) {//secondary fire with a cooldown mechanism. Sustained fire is only possible with enough "charge"
            Agent& star = add_agent("Star", 
            x() + 17*cos(angle()), 
            y() + 17*sin(angle()), 
            angle(), 
            STAR_STYLE);  
            star.apply_force(400,0);
            charge -= 20;
        } else if (charge <= charge_max) {//charge caps out at 200 units and features a cooldown timer
            charge += 1;
        }

        omni_apply_force(fx,f);

        label("score: " + std::to_string( (int) points ) + //displays points earned
              "charge: " + std::to_string( (int) charge ),20,0); //displays charge level for secondary fire

        watch("point", [&](Event &e) {//watches for point events emitted by collisions between "bullet" and "virus" agents
            points++;         
        });

    }
    void stop() {}

    bool LEFT, RIGHT;
    double vx;
    int points;
    int charge = 199;
    int charge_max = 199;


    const double VEL_X = 100;
    const double K_X = 15;

    double f;
    double const magnitude = 700;
    bool firing, firing2;
    const json BULLET_STYLE = { 
                   {"fill", "white"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.25"}
               };
    const json STAR_STYLE = { 
                   {"fill", "gold"}, 
                   {"stroke", "#888"}, 
                   {"strokeWidth", "5px"},
                   {"strokeOpacity", "0.1"}
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