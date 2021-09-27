//hw7
//student Rafael Rangel
//date: 04/18/2021
//project name hw7
//program description: Asteroids game edited to have added features
// source code from FamTrinli Published on Apr 29, 2016 edited by Rafael Rangel
// added game functionality for extra credit
    // added game sounds for explosion , bullet and game over
    // changed the fire rate of the player so it is a more interesting game, did this using the a clock object
    // added a score, now the program keeps track of the score it increments when the player destroys objects
    // added lives that are displayed with a sprite of a heart image from Flaticon so when the player looses lives the sprites disapear
    // when the player runs out of lives the goes to the game over screen where he can restart the game
    // added a game over screen
    // made the game a state machine so it will have a game over screen

#include <SFML/Graphics.hpp> //add the simple and fast multimedia library
#include <time.h> //add the time library to use as a seed for random number and for the game pace
#include <list> //add the list library to use list variable type
#include <cmath> //add cmath library to use advanced mathematic operations
#include <SFML/Audio.hpp> //add the sfml audio library
#include <iostream> //add the input and output library to print error messages to the command line

using namespace sf; //to avoid having to type sf:: when using the sfml library

const int W = 1200; //width of the display
const int H = 800; //height of the display

float DEGTORAD = 0.017453f; //to later convert degrees to radians

//Animation class
class Animation {
    public:
    //data members
        float Frame, speed; //frame float number to be displayed and speed of the frame display
        Sprite sprite; //sprite for the animation
        std::vector<IntRect> frames; //vector that holds interactive rectangles to hold the frames

        //animation default constructor
        Animation() {}

        //animation constructor
        //takes in a texture to assign to the sprite, the speed to assign to speed
        //also int x (left),y(top),w (width)  and h(height) to determine the frame rectangle coordinates rectLeft,rectTop,rectWidth and rectHeight
        Animation(Texture &t, int x, int y, int w, int h, int count, float Speed)
        {
            Frame = 0; //set frame float variable to 0
            speed = Speed; //set speed to the input speed

            for (int i = 0; i < count; i++)
            {
                //add a new IntRect object element at the end of the vector
                frames.push_back(IntRect(x + i * w, y, w,h)); //call the IntRect constructor and pass in coordinates to it to construct the rectangle
            }

            sprite.setTexture(t);//assign the texture to the sprite
            sprite.setOrigin(w / 2, h / 2); //set set the sprite origin to the width w given divided by two on the x axis and on the y axis the height h given divided by two
            sprite.setTextureRect(frames[0]); //Set the texture rectangle to the first IntRect of the frames vector
        }

        //update method, this will create the animation illusion by displaying parts of the animation texture really fast
        void update() {
            Frame += speed; //move the frame according to the speed
            int n = frames.size(); //set n to the size of the frames vector

            //if statement to keep the frame from being greater than the frames.size()
            if (Frame >= n)
            {
                Frame -= n;
            }

            //if statement, when the frames.size() is greater than 0
            if (n > 0)
            {
                sprite.setTextureRect(frames[int(Frame)]); //set the sprite texture to the IntRect from the vector according to the frame variable
            }
        }

        //isEnd method to return true if the Frame + speed is greater or equal to the frames.size(), so it reached the end of the vector
        bool isEnd()
        {
            return Frame + speed >= frames.size();
        }

};

//entity class, this is an abstract base class, cannot be declared as an object in main
class Entity {
    public:
        //private data members
        float x, y;  //x, y location of the entity
        float dx, dy; //dx, dy speed of the entity
        float R; //explosion radius
        float angle; //rotation angle of the entity
        bool life; // draw entity on screen if life is true
        std::string name; //name of the derived class object
        Animation anim; //object of the Animation class (performs the animation)

        //default constructor set life to 1
        Entity() {
            life = 1;
        }

        //settings method to set the anim Animation object, the x, y and radius int variables and the angle float variable
        //input: the desired values for the anim, x , y , angle and Rdata members
        //output: none, its of type void this function just sets the values of the previously listed data members
        virtual void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1) {
            anim = a;
            x = X;
            y = Y;
            angle = Angle;
            R = radius;
        }

        virtual void update() {}; //pure virtual function, if there is an entity lock for a concrete method on the derived classes, this is polymorphism

        //draw method to draw the anim to the window
        //input: pass by reference the RenderWindow object to draw the animation in
        //output: none, its of type void, it just draws the animation on the RenderWindow
        void draw(RenderWindow &app) {
            anim.sprite.setPosition(x, y); //set position of the animation sprite on the window according to the data members x and y, these will be the coordinates
            anim.sprite.setRotation(angle +90); //set rotation of the animation sprite, which will be the angle held in angle data member plus 90
            app.draw(anim.sprite); //draw the animation sprite on the window

            //this circle will not be drawn but will surround the entity to determine when they touch each other
            CircleShape circle(R); //create a circle object named circle of radius R, the radius held on the data member
            circle.setFillColor(Color(255, 0, 0, 170)); //set the fill color to see through red
            circle.setPosition(x, y); //set the position according to the coordinates held in data members x and y
            circle.setOrigin(R, R); //set the origin of the circle according to the radius so that the origin is the center of the animation sprite
            //app.draw(circle); //draw the circle if you want to see it around the entity
        }

        virtual ~Entity() {}; //pure virtual destructor (polymorphism)
};

//derived class that inherits from the Entity class
class asteroid : public Entity {
    public:


    //asteroid constructor
        asteroid() {
            dx = rand() % 8 - 4; //set the speed in the x axis to a random speed from -4 to 4
            dy = rand() % 8 - 4; //set the speed in the y axis to a random speed from -4 to 4
            name = "asteroid"; //set the name to asteroids
            ++asteroidCount; //add one to the static asteroidCount variable to keep count of how many asteroid object have been created
        }

        //concrete update method, it updates the position of the asteroid
        void update() {
            x += dx; //move in the x direction according to the speed dx
            y += dy; //move in the y direction according to the speed dy

            //keep the asteroids on the display, when they leave the display frame, when they leave from one side, they appear on the opposite side and continue their motion
            if (x > W) //if the asteroid leaves the display from the right side when x > W appear on the opposite side at x = 0
            {
                x = 0;
            }
            if (x < 0) //if the asteroid leaves the display from the left side when x < 0 then appear on the other side at x = W
            {
                x = W;
            }
            if (y > H) //if the asteroid leaves the display from the lover side when y > H it appears on the opposite upper side at y = 0
            {
                y = 0;
            }
            if (y < 0) //if the asteroid leaves the display from the upper side when y < 0 it appears on the upper side at y = H
            {
                y = H;
            }
        }

    //static method to get the value of the private static member variable
    static int getAsteroidCount() {
        return asteroidCount;
    }

private:
    //static asteroidCount variable to keep track of the number of asteroids on the game
    static int asteroidCount;

        //destructor for the asteroid class that decreases one in the asteroidCount variable when an asteroid gets destroyed
        ~asteroid() {
         --asteroidCount;
    }

};

//derived bullet class, inherits from the Entity class
class bullet : public Entity {
    public:
        //bullet constructor
        bullet() {
            name = "bullet"; //set the string name to bullet
        }

        //concrete method that updates the position
        void update() {
            //DECTORAD converts the degrees to radians
            dx = cos(angle * DEGTORAD) * 6; //set the speed on the x axis according to cosine of the angle
            dy = sin(angle * DEGTORAD) * 6; //set the speed on the y axis according to sine the angle
            // angle+=rand()%6-3;
            x += dx; //move on the x direction according to the dx speed
            y += dy; //move on the y direction according to the dy speed

            if (x > W || x < 0 || y > H || y < 0)
            {
                life = 0; //when the bullet leaves the frame it disappears, since the life is set to false then the bullet is schedulled for removal from display
            }
        }

};

//derived class inherits from the Entity base class
class player : public Entity {
    public:
        bool thrust; //new bool data member to control the thrust of the ship

        //player constructor
        player() {
            name = "player"; //set the name to player
            //have the player start with no movement
            dy=0;
            dx=0;
        }


        //concrete update method
        void update()
        {
            if (thrust) //if there is thrust
            {
                dx += cos(angle * DEGTORAD) * 0.2; //set the speed in the x axis of the player ship according to the cosine of the angle in radians
                dy += sin(angle * DEGTORAD) * 0.2; //set the speed in the y axis of the player according to the sine of the angle
            }
            else //if there is no thrust
            {
                //the ship doesnt immediately stop, it just loses speed
                dx *= 0.99; //lover the speed in the x axis by multiplying it times 0.99
                dy *= 0.99; //love the speed in the y axis by multiplying the current speed times 0.99
            }

            int maxSpeed = 15; //max magnitude of speed the player's ship can reach
            float speed = sqrt(dx * dx + dy * dy); //
            if (speed > maxSpeed) //if statement to keep the magnitude of the speed components less than or equal to the max speed
            {
                dx *= maxSpeed / speed;
                dy *= maxSpeed / speed;
            }

            //move according to the dx and dy velocities
            x += dx;
            y += dy;

            //keep the player inside the display
            if (x > W)
            {
                x = 0;
            }
            if (x < 0)
            {
                x = W;
            }
            if (y > H)
            {
                y = 0;
            }
            if (y < 0)
            {
                y = H;
            }
        }

};

//ufo derived class inherits from the Entity base class
class UFO : public Entity{
    public:
    //UFO constructor
    UFO() {
        dx = 4; //set the speed in the x axis to 4
        dy = 0; //and to 0 on the y axis so it just moves horizontally
        x = 0; //the initial position of the UFO will be the left edge of the display
        y = rand() % H; //set the starting position of the UFO in the y direction to a random position inside the display
        name = "UFO"; //set the name to UFO
        anim.sprite.scale(0.25,0.25);
    }
    void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1) { //definition of the settings method
        anim = a;
        x = X;
        y = Y;
        angle = Angle;
        R = radius;
        anim.sprite.scale(0.15,0.15); //scale down the UFO sprite that was passed on to the animation object to be used as the UFO
    }

    //concrete update method, it updates the position of the UFO
    void update() {
        x += dx; //move in the x direction according to the speed dx

        //UFO on the display, when they leave the display frame, when they leave from one side, they appear on the opposite side and continue their motion
        if (x > W) //if the UFO leaves the display from the right side when x > W appear on the opposite side at x = 0
        {
            x = 0;
        }
        if (x < 0) //if the UFO leaves the display from the left side when x < 0 then appear on the other side at x = W
        {
            x = W;
        }
    }


};

//isCollide function to be used when two Entity objects collide
//This function checks if to objects collided according to the radius of the circle around them and their position of course
//input two Entity pointers
//output bool, true if the entities collided and false if they didnt
bool isCollide(Entity *a, Entity *b) {
    return (b->x - a->x) * (b->x - a->x) +
           (b->y - a->y) * (b->y - a->y) <
           (a->R + b->R) * (a->R + b->R);
}

//initialize the static asteroid count variable to 0 to count the number on asteroids on the game
int asteroid::asteroidCount = 0;

int main() {
    //seed the random number generator with type
    srand(time(0));

    //create window object of the RenderWindow class, a window that can serve as target for 2D drawing
    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60); //limit the framerate to a maximum fixed frequency of 60 frames per second, this is only to slow down, not speed up

    //load the font to be used (attribution comments on line next to the loaded font, also on the readme file )
    //Load junegull font into fontMenu
    sf::Font fontCool;
    if (!fontCool.loadFromFile("fonts/junegull.ttf"))//junegull.ttf by Tipodermic Fonts from https://www.1001freefonts.com/rounded-fonts.php License: Free
    {
        std::cout << "Error: could not open junegull.ttf"; //check if sound opens correctly
        return -1; // error
    }

    //create a text for the score to have the score on it declared outside window loop to avoid having to reinitialize it over and over again
    Text textScore; //create a text object
    textScore.setFont(fontCool); // select the font
    textScore.setCharacterSize(40); // set the character size in pixels
    textScore.setFillColor(sf::Color::White); //set the text color
    textScore.setStyle(sf::Text::Bold | sf::Text::Underlined); //set the style text
    textScore.setPosition(20,-5); //set the position of the text

    //load all sounds used in the code (attribution codes next to the loaded sounds used, also on the readme file)
    //load UFO sound to be used in the game
    SoundBuffer bufferUFO; //create a sound buffer object to load sound
    //load the ufo.ogg from the sounds directory
    if (!bufferUFO.loadFromFile("sounds/ufo.ogg")){ //ufo.ogg sound from Zapsplat.com by ZapSplat found in https://www.zapsplat.com/?s=ufo&post_type=music&sound-effect-category-id= as "Cartoon UFO hover" License: Standard License
        std::cout << "Error: could not open ufo.ogg"; //check if sound opens correctly
        return -1;}
    //the sound is already loaded so now we create a sound object
    Sound soundUFO;
    //assign the according buffer to the sound
    soundUFO.setBuffer(bufferUFO);

    //load the sound explosion.ogg from the sound directory
    SoundBuffer bufferExplosion; //create a sound buffer object to load sound
    //load the ufo.ogg from the sounds directory
    if (!bufferExplosion.loadFromFile("sounds/explosion.ogg")){ //explosion.ogg sound from Zapsplat.com  by Epic Stock Media found in https://www.zapsplat.com/?s=explosion&post_type=music&sound-effect-category-id= as "8bit explosion, bomb boom or blast, cannon, retro old school, classic cartoon" License: Standard License
        std::cout << "Error: could not open explosion.ogg"; //check if sound opens correctly
        return -1;}
    //the sound is already loaded so now we create a sound object
    Sound soundExplosion;
    //assign the according buffer to the sound
    soundExplosion.setBuffer(bufferExplosion);

    //load the sound explosion.ogg from the sound directory
    SoundBuffer bufferBullet; //create a sound buffer object to load sound
    //load the ufo.ogg from the sounds directory
    if (!bufferBullet.loadFromFile("sounds/bullet.ogg")){  //bullet.ogg sound from Zapsplat.com by Adam A Johnson found in https://www.zapsplat.com/page/2/?s=laser+gun&post_type=music&sound-effect-category-id as "Laser gun, single shot" License: Standard License
        std::cout << "Error: could not open bullet.ogg"; //check if sound opens correctly
        return -1;}
    //the sound is already loaded so now we create a sound object
    Sound soundBullet;
    //assign the according buffer to the sound
    soundBullet.setBuffer(bufferBullet);

    //load the sound gameOver.ogg from the sound directory
    sf::SoundBuffer bufferGameOver; //create a sound buffer object to load sound
    //load the gameOverSound.ogg from the sounds directory
    if (!bufferGameOver.loadFromFile("sounds/gameOver.ogg")){  //gameOver.ogg sound from Zapsplat.com by ZapSplat found in https://www.zapsplat.com/?s=lose+&post_type=music&sound-effect-category-id= as "Game sound, percussive negative, lose, fail tone 1" License: Standard License
        std::cout << "Error: could not open gameOver.ogg"; //check if sound opens correctly
        return -1;}
    //the sound is already loaded so now we create a sound object
    sf::Sound soundGameOver;
    //assign the according buffer to the sound
    soundGameOver.setBuffer(bufferGameOver);


    //create objects of the texture class and load images from the "images" folder onto each texture object
    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10;
    t1.loadFromFile("images/spaceship.png");
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/explosions/type_C.png");
    t4.loadFromFile("images/rock.png");
    t5.loadFromFile("images/fire_blue.png");
    t6.loadFromFile("images/rock_small.png");
    t7.loadFromFile("images/explosions/type_B.png");
    //the next to images were additionally added to the code (attribution next to code when loaded, also on the readme file)
    t8.loadFromFile("images/UFO.png"); //ufo.png Icon made by Icongeek26 from www.flaticon.com License: Flaticon license , Free for personal and commercial purpose with attribution.
    t9.loadFromFile("images/heart.png"); //heart.png Icon made by Kiranshastry from www.flaticon.com License: Flaticon license, Free for personal and commercial purpose with attribution.
    t10.loadFromFile("images/spaceship_go.png");

    //for t1 and t2 enable the smooth filter, this will make the texture appear smoother by making the pixels less noticeable
    t1.setSmooth(true);
    t2.setSmooth(true);

    //create Sprite object named background and assign texture t2 to it
    Sprite background(t2);

    //Create objects of the Animation class and initialize them with the given parameters
    Animation sExplosion(t3, 0, 0, 256, 256, 48, 0.5);
    Animation sRock(t4, 0, 0, 64, 64, 16, 0.2);
    Animation sRock_small(t6, 0, 0, 64, 64, 16, 0.2);
    Animation sBullet(t5, 0, 0, 32, 64, 16, 0.8);
    Animation sPlayer(t1, 0, 0, 512, 512, 1, 0);
    Animation sPlayer_go(t10, 0, 0, 512, 512, 1, 0);
    Animation sExplosion_ship(t7, 0, 0, 192, 192, 64, 0.5);
    Animation sUFO(t8, 0, 0, 512, 512, 1, 0);


    //give the player  4 lives until game over and have score be 0 initially (this will be reset inside main loop when the player looses)
    int playerLife = 4;


    //make that a game state machine to display game over page
    enum GameState {
        GS_GAME, GS_GAMEOVER
    };
    GameState gameStage; //state machine variable
    gameStage = GS_GAME; //start on the game
    bool game = true; //variable that will control when the player has lost inside the main loop

    /////main loop/////
    while (app.isOpen()) //display loop
    {
        if (gameStage == GS_GAME) {
            //create a list of Entity object pointers named entities
            std::list<Entity *> entities;

            //for loop to create 15 asteroid object
            for (int i = 0; i < 15; i++) {
                //create asteroid object pointer and allocate memory for it
                asteroid *a = new asteroid();
                //call the settings method on the current asteroid object and pass these parameters to it and set some of its data members
                a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
                //add the current asteroid object to the entities list at the end of it, thise can be done since the asteroid object is an entity object
                entities.push_back(a);
            }

            //create player object pointer and allocate memory for it, this will be the ship
            player *p = new player();
            //call the settings method for the player object and pass these parameters to set certain data members
            p->settings(sPlayer, W / 2, H / 2, 0, 20);
            //add this player object to the entities list at the end, this can be done because the player object is an entity object
            entities.push_back(p);

            //create clock objects for the UFO sightings and the fireRate of the player
            Clock clock; // create a clock object to control the time it takes for a UFO to appear
            Clock fireRate; //create a clock object to control the bullet fire rate of the player

            int score = 0; //set initial score to 0

            while (game){ //after the game has been initially set up enter this loop and repeat until the player looses
                Event event;//event object to control the game
                //while loop to check for pending events, goes until there are no pending events
                while (app.pollEvent(event)) {
                    if (event.type == Event::Closed) //event::closed triggered when the user wants to close the window
                    {
                        app.close(); //close window
                        return -1;
                    }

                    if (event.type == Event::KeyPressed) //when key is pressed
                    {
                        if (event.key.code == Keyboard::Space) //if the space key is pressed
                        {
                            // change the fire rate of the bullets so it is a more challenging game
                            if (fireRate.getElapsedTime().asSeconds() >= 0.25) { //only allow the player to fire when 0.5 seconds have pased after the last bullet was shot
                                bullet *b = new bullet();
                                b->settings(sBullet, p->x, p->y, p->angle, 10);
                                entities.push_back(b);
                                soundBullet.play(); // play bullet sound
                                fireRate.restart(); //restart the fireRate clock used to control the fire rate
                            }
                        }

                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Right)) //if the right angle is pressed
                {
                    p->angle += 3; //change the angle by adding 3, this will rotate the ship to the right
                }
                if (Keyboard::isKeyPressed(Keyboard::Left)) //if the left angle is pressed
                {
                    p->angle -= 3; //change the angle by subtracting 3, this will rotate the ship to the left
                }
                if (Keyboard::isKeyPressed(Keyboard::Up)) //if the up angle is pressed
                {
                    p->thrust = true; //set thrust to true so that the ship moves forward by impulsing itself
                } else {
                    p->thrust = false; //set thrust to false so the ship stops the impulse, but this doesn't mean it stops, it keeps its momentum until it stops
                }

                //range based for loop to go over all the entities pointer list
                for (auto a:entities) {
                    //range based loop to go over all the entities pointer list again so each possible combination is met
                    for (auto b:entities) {
                        if (a->name == "asteroid" &&
                            b->name == "bullet") //if there is an asteroids entity and a bullet entity
                        {
                            if (isCollide(a, b)) //if the bullet and the asteroid collide
                            {
                                // increment score by 10 when an asteroids is destroyed
                                score += 10;

                                //both their lives are set to 0
                                a->life = false;
                                b->life = false;

                                //the explosion will be displayed when both entities collide
                                Entity *e = new Entity();//create an Entity pointer and allocate memory
                                e->settings(sExplosion, a->x,
                                            a->y); //set the texture for explosion to the entity and the position for the entity
                                e->name = "explosion"; //name it explosion
                                entities.push_back(e);//this is also added to the entities list

                                //play explosion sound when object collide
                                soundExplosion.play();

                                //for loop that gets repeated twice to create two smaller asteroids when the asteroid gets destroyed
                                for (int i = 0; i < 2; i++) {
                                    if (a->R == 15) continue; //if the radius less than 15 create a smaller asteroid
                                    Entity *e = new asteroid(); //create a new entity pointer that allocates memory for an asteroid object
                                    e->settings(sRock_small, a->x, a->y, rand() % 360,
                                                15);//call the settings method to assing the small rock texture, the position of the current big asteroid, the angle and the radius
                                    entities.push_back(e); //add this entity pointer to the entities list
                                }

                            }
                        }

                        //if bullet collides with the UFO
                        if (a->name == "UFO" && b->name == "bullet") {
                            if (isCollide(a, b)) //if the bullet and the asteroid collide
                            {
                                // increment score by 20 when an UFO is destroyed
                                score += 20;

                                //both their lives are set to 0 so they are now scheduled for deletion
                                a->life = false;
                                b->life = false;

                                //the explosion will be displayed when both entities collide
                                Entity *e = new Entity();//create an Entity pointer and allocate memory
                                e->settings(sExplosion, a->x,
                                            a->y); //set the texture for explosion to the entity and the position for the entity
                                e->name = "explosion"; //name it explosion
                                entities.push_back(e);//this is also added to the entities list

                                // play explosion sound when object collide
                                soundExplosion.play();

                                clock.restart(); //restart the clock when the Ufo gets destroyed to time when the next one should appear

                                soundUFO.stop(); //stop playing the UFO sound when it has been destroyed

                            }
                        }

                        //enter if the current looped over entities are a player and an asteroid
                        if (a->name == "player" && b->name == "asteroid") {
                            if (isCollide(a, b)) //enter if they collide
                            {
                                //decrease the player lives by one
                                playerLife--;

                                b->life = false; //set the asteroids life to false

                                //the explosion will be displayed when both entities collide
                                Entity *e = new Entity(); //create an entity object pointer and allocate memory for an entity object
                                e->settings(sExplosion_ship, a->x,
                                            a->y); //assign the explosion for the ship texture and the current position for the entity
                                e->name = "explosion"; //name it explosion
                                entities.push_back(e); //add the entity to the entities list

                                //play explosion sound when object collide
                                soundExplosion.play();

                                //reset the player position to the center to the display and set its speed to 0
                                p->settings(sPlayer, W / 2, H / 2, 0, 20);
                                p->dx = 0;
                                p->dy = 0;
                            }
                        }

                        //enter if the current looped over entites are a player and a UFO
                        if (a->name == "player" && b->name == "UFO") {
                            if (isCollide(a, b)) //enter if they collide
                            {
                                //decrease the player lives by one
                                playerLife--;

                                b->life = false; //set the ufo life to false

                                //the explosion will be displayed when both entities collide
                                Entity *e = new Entity(); //create an entity object pointer and allocate memory for an entity object
                                e->settings(sExplosion_ship, a->x,
                                            a->y); //assign the explosion for the ship texture and the current position for the entity
                                e->name = "explosion"; //name it explosion so the explosion animation shows up
                                entities.push_back(e); //add the entity to the entities list

                                //play explosion sound when object collide
                                soundExplosion.play();

                                //reset the player position to the center to the display and set its speed to 0
                                p->settings(sPlayer, W / 2, H / 2, 0, 20);
                                p->dx = 0;
                                p->dy = 0;

                                clock.restart(); //restart the clock when the Ufo gets destroyed to time when the next one should appear

                                soundUFO.stop(); //stop playing the UFO sound when it has been destroyed
                            }
                        }
                    }
                }


                if (p->thrust) //if the ship has thrust then have the animation be the sPlayer_go sprite
                {
                    p->anim = sPlayer_go;
                    p->anim.sprite.scale(0.15,0.15);
                } else //if it has no thrust have the animation be the sPlayer sprite
                {
                    p->anim = sPlayer;
                    p->anim.sprite.scale(0.15,0.15);
                }

                //loop over the entities
                for (auto e:entities) {
                    if (e->name == "explosion") //if the entity is an explosion
                    {
                        if (e->anim.isEnd()) //if the animation has ended then set life to false
                        {
                            e->life = 0;
                        }
                    }
                }

                //create 15 new asteroids when there are no more on the game using the static asteroidCount variable
                if (asteroid::getAsteroidCount() == 0) //check if there are no more asteroids in the game using using the getter for the static member variable
                {
                    for (int i = 0; i < 15; i++) {
                        //create asteroid object pointer and allocate memory for it
                        asteroid *a = new asteroid();
                        //call the settings method on the current asteroid object and pass these parameters to it and set some of its data members
                        a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
                        //add the current asteroid object to the entities list at the end of it, thise can be done since the asteroid object is an entity object
                        entities.push_back(a);
                    }
                }

                //variable to create the UFO when there is no ufo on the game
                int checkUFO = 0;
                for (auto u:entities) //loop over the entity list to check if there is a UFO
                {
                    if (u->name == "UFO") {
                        checkUFO++; //add one to the checkUFO variable if a UFO was found on the list
                    }

                }
                //create a ufo on the list after approximately 10 seconds have past since the last one was destroyed
                if (clock.getElapsedTime().asSeconds() >= 10 && checkUFO == 0) {
                    UFO *a = new UFO(); //create a UFO object, asteroid is a derived class from entity
                    a->settings(sUFO, 0, rand() % H, -90, 20); //set some of the UFO parameters
                    entities.push_back(a); //add the UFO to the entities list
                    soundUFO.play(); //start playing the UFO sound when the UFO is created
                    soundUFO.setLoop(true); //loop over the sound so it is heard the whole time the UFO is present
                }

                //entities.begin() will return the starting iterator for the entities list
                //entities.end() will return the theoretical iterator of the element after the last element in the list
                // i is an iterator to a entity pointer
                for (auto i = entities.begin(); i != entities.end();) {
                    Entity *e = *i; //*i is an Entity pointer, using * on an iterator returns the element from the list

                    e->update(); //use polymorphism to call the proper update method
                    e->anim.update(); // move to the next frame of the animation

                    // if the entities life is false it gets removed from the entities list using the erase command
                    if (e->life == false) {
                        i = entities.erase(i); // move the iterator to the next element in the list
                        delete e; // declare the object pointed to by e, polymorphism is used to call the proper destructor
                    } else i++; // if life was true, move iterator to the next element in the list
                }

                // set the score text to display the score
                textScore.setString(
                        "score: " +
                        std::to_string(score)); //set the string of the text score to score: and the calculated score


                //////draw//////
                app.draw(background); //draw the background sprite in the window

                //show how many lives the player has left by displaying heart sprites on the screen
                if (playerLife == 1){
                    Sprite live1(t9);
                    live1.scale(0.10,0.10);
                    live1.setPosition(900,10);
                    app.draw(live1);
                }
                else if (playerLife ==2){
                    Sprite live1(t9);
                    live1.scale(0.10,0.10);
                    live1.setPosition(900,10);
                    app.draw(live1);

                    Sprite live2(t9);
                    live2.scale(0.10,0.10);
                    live2.setPosition(960,10);
                    app.draw(live2);
                }
                else if (playerLife ==3){\
                    Sprite live1(t9);
                    live1.scale(0.10,0.10);
                    live1.setPosition(900,10);
                    app.draw(live1);

                    Sprite live2(t9);
                    live2.scale(0.10,0.10);
                    live2.setPosition(960,10);
                    app.draw(live2);

                    Sprite live3(t9);
                    live3.scale(0.10,0.10);
                    live3.setPosition(1020,10);
                    app.draw(live3);

                }
                else if (playerLife ==4){
                    Sprite live1(t9);
                    live1.scale(0.10,0.10);
                    live1.setPosition(900,10);
                    app.draw(live1);

                    Sprite live2(t9);
                    live2.scale(0.10,0.10);
                    live2.setPosition(960,10);
                    app.draw(live2);

                    Sprite live3(t9);
                    live3.scale(0.10,0.10);
                    live3.setPosition(1020,10);
                    app.draw(live3);

                    Sprite live4(t9);
                    live4.scale(0.10,0.10);
                    live4.setPosition(1080,10);
                    app.draw(live4);
                }

                //loop over all the entities to draw them on the display
                for (auto i:entities) {
                    i->draw(app); //draw the entities to the window if life is true
                }

                // draw the score text to the screen to display the score
                app.draw(textScore);

                app.display(); //display the drawn window

                //when the player has no more lives left
                if (playerLife == 0 ){
                    soundGameOver.play(); //play the game over sound
                    game = false; //exit the game loop
                    gameStage = GS_GAMEOVER; //change to the game over stage
                    for (auto i = entities.begin(); i != entities.end();) {
                        Entity *e = *i; //*i is an Entity pointer, using * on an iterator returns the element from the list
                        i = entities.erase(i); // move the iterator to the next element in the list
                        delete e; // declare the object pointed to by e, polymorphism is used to call the proper destructor
                        i++;
                        if (checkUFO!=0){
                            soundUFO.stop(); //stop the ufo sound in case there is a UFO on display
                        }
                    }
                }
            }
        }
            else if (gameStage == GS_GAMEOVER) //when in the game over game stage
            {
            Event event2;//event object to control the game
            //while loop to check for pending events, goes until there are no pending events
            while (app.pollEvent(event2)) {
                if (event2.type == Event::Closed) //event::closed triggered when the user wants to close the window
                {
                    app.close(); //close window
                    return -1; //finish the program when the player closes the window
                }

                if (event2.type == Event::KeyPressed) //when key is pressed
                {
                    if (event2.key.code == Keyboard::Enter) //if the enter key is pressed
                    {
                        playerLife = 4; //set the plater lives back to 4
                     gameStage = GS_GAME; //start the game again
                     game = true; //set this to true to enter the game loop after the initial set up
                     app.clear();
                    }
                    if (event2.key.code == Keyboard::Escape) //if the enter key is pressed
                    {
                        app.close(); //close window
                        return -1; //finish the program when the player closes the window
                    }
                }
            }
            app.clear();

            //create a text for the score to have the score on it declared outside window loop to avoid having to reinitialize it over and over again
            Text textGameOver; //create a text object
            textGameOver.setFont(fontCool); // select the font
            textGameOver.setCharacterSize(100); // set the character size in pixels
            textGameOver.setFillColor(sf::Color::White); //set the text color
            textGameOver.setStyle(sf::Text::Bold | sf::Text::Underlined); //set the style text
            textGameOver.setPosition(370,300); //set the position of the text
            textGameOver.setString("GAME OVER");

            //create a text for the score to have the score on it declared outside window loop to avoid having to reinitialize it over and over again
            Text textPlayAgain; //create a text object
            textPlayAgain.setFont(fontCool); // select the font
            textPlayAgain.setCharacterSize(40); // set the character size in pixels
            textPlayAgain.setFillColor(sf::Color::White); //set the text color
            textPlayAgain.setStyle(sf::Text::Bold ); //set the style text
            textPlayAgain.setPosition(300,500); //set the position of the text
            textPlayAgain.setString("press the enter key to play again");

            app.draw(background); //draw the background
            app.draw(textGameOver); //draw the game over text
            app.draw(textPlayAgain); //draw the instructions to play again
            app.draw(textScore); //draw the score achieved

            app.display();//display the window
        }
    }

    return 0;
}
