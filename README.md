# EEP520-W20-final-project

Final project using ENVIRO
===


The inspiration for this project is a callback to classical shoot 'em up (or shmup) games that prevailed during the third generation of video game consoles.
While this project is far from complete, and is not nearly as optimized as I would have desired, it is my hope that it may be seen as a humble homage to what
was once a dominant genre in video games.


How to run
===

This project requires Docker to run.

To get started:

    git clone https://github.com/j92cp/EEP520-W20-final-project.git
    cd EEP520-W20-final-project
    docker run -p80:80 -p8765:8765 -v $_local_directory_here_:/source -it klavins/enviro:v1.6 bash
    esm start
    make
    enviro


Then proceed to http://localhost with your web browser to see the ENVIRO client. The game starts as soon as enviro is called, so good luck!


Controls
===

Press the WASD keys to navigate (forward, backward, side-to-side)

Press P for primary fire (hold to sustain)

Press O for secondary fire (This firing mode is limited, and runs on a cooldown. Can be combined with P)



About the project
===

## Overall goal

As mentioned in the introduction, this project is meant to be a small tribute to shoot-em-up games and takes it's vision directly from them. Titles such as 1942 and Gradius come to mind. But the overall ambition came from a desire to create a so-called *danmaku* or bullet hell game, where the screen is
almost completely covered with enemy fire, oftentimes in artistic and intricate patterns. Though this particular attempt falls short of such quality, as a neophyte project, it still, in my opinion, captures the feeling of what it's like to take on such a task.



## Challenges

However, such a lofty goal comes with even loftier challenges. The first challenge came in the form of switching the method of movement. The architecture from where this project is based initially called for rotation about a central axis based on the player's character. Though perfectly fine, for this particular application, lateral movement is best because it allows for constant maneuvering and concentrates fire. To make this happen, the lateral movement described in the `platformer` example within the ENVIRO repository was the perfect choice for implementing lateral motion.


The next challenge was the firing mechanism. One was already built in, but the challenge came when trying to implement twin firing, as well as a second firing mode. Though not so difficult per se, the tedious task of adjusting the spawn point and angle in reference to the player agent took up the most time. With a lot of brute-force and a bit of luck, twin firing was made possible. The next challenge was to convert the incremental fire into a sustained 
stream of bullets, but in time this was also solved through some clever boolean methods.


Secondary firing mode was also tricky to implement. Specifically, how could one limit use of this firing mode by means of a cooldown mechanic? A lot of time was spent trying to make use of `while-if` statements, but after some tinkering, a simple `if-else` statement handles the job well enough. On a side note, an attempt was made to make the secondary fire have the ability to "phase" through enemy agents, while still eliminating them, akin to overpenetrating bullets. But this idea was shelved after proving too cumbersome.


But perhaps, the greatest challenge of all was spawning the enemies. How is one to create enemies *en masse* and spawn them in a round-by-round fashion? It was difficult enough to try and narrow down the field, while making enemy agents proceed in a beeline after spawning. But to try and make dozens, if not hundreds? It seemed almost impossible. That is until I was introduced to an elegant solution: the Coordinator agent. With a coordinator, it was very simple to create dozens of enemies using simple `for` loops, and with some tricks using `if` statements and nesting, the ability to spawn multiple enemy types after clearing a certain number of waves became only as difficult as creating the enemies themselves. After that, it was a simple matter of copying the loop and adding the appropriate agent.


Conclusion/Acknowledgements
===

This project is far from complete. Future goals include:
 - boss agents
 - enemy bullet patterns
 - super attack mechanics
 - alternative primary firing modes
 - multiple lives/checkpoints
 - moving background
 - a GUI (high scores, meter gauges)
 - pause/reset
 - and time willing, multiple stages

I would like to thank Dr. Eric Klavins for his work in the ENVIRO project, as well as his help with understanding features and methods that I would not have been able to grasp on my own. Much of the basic architecture of this project was based heavily from the examples provided in the ENVIRO repository. Also a shoutout to Josef for the very productive discussions in the wee hours of the night.