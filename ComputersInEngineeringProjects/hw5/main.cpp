//hw5
//student Rafael Rangel
//date: 03/29/2021
//project name hw5
//program description: Xonix game edited to have special features
// source code from FamTrinli Published on Apr 26, 2016 edited by Rafael Rangel

#include <SFML/Graphics.hpp> //add the simple and fast multimedia library
#include <time.h> //add the time library to use as a seed for random number and for the game pace
#include "iostream"
#include <SFML/Audio.hpp>
#include <string>

using namespace sf;

//const because these must not be changed in the main function
//Since its for the window grid, this is declared outside the main function
const int M = 25; //height of grid
const int N = 40; //width of grid

int grid[M][N] = {0}; //a value of 0 means a blank square
int ts = 18; //tile size

class Enemy {
    public:
        Enemy() //enemy constructor
        {
            x = y = 300; //starting location of all enemies
            dx = 4 - rand() % 8; //random speed in the x direction
            dy = 4 - rand() % 8; //random speed in the y direction
        }

        //setters for private data members
        void setX(const int inputX){x = inputX;}
        void setY(const int inputY){y = inputY;}
        void setDX(const int inputDX){dx = inputDX;}
        void setDY(const int inputDY){dy = inputDY;}

        //getters for private data members
        int getX() const{return x;}
        int getY() const{return y;}
        int getDX() const{return dx;}
        int getDY() const{return dy;}


    //move method of the enemy class
    void move() {
        x += dx; //move in the x direction according to the dx speed
        if (grid[y / ts][x / ts] == 1) //if it touches the blue squares it bounces off, the 1 means blue tile
        {
            dx = -dx; //change the direction in the x axis to the opposite
            x += dx;  //moves in the x axis by the dx
        }
        y += dy; //move in the y direction according to the dy speed
        if (grid[y / ts][x / ts] == 1) {
            dy = -dy; //changes the direction in the y direction to go in the opposite direction
            y += dy; //moves in the y axis by the dx
        }
    }

    private:
        //private variables
        int x, y; //location of enemy
        int dx, dy; //speed of enemy
};

//function that checks if a square is empty or not, and if it is it fills it with a -1, but if there is an enemy it
// wont fill anything in
//recursive function: means it can be called be called inside a function
void drop(int y, int x) {
    if (grid[y][x] == 0) grid[y][x] = -1; //if the grid is empty fill with a -1
    if (grid[y - 1][x] == 0) drop(y - 1, x); //call itself to continue filling the empty grid squares with -1, above one
    if (grid[y + 1][x] == 0) drop(y + 1, x); //repeat to fill in square below
    if (grid[y][x - 1] == 0) drop(y, x - 1); //now square to the left
    if (grid[y][x + 1] == 0) drop(y, x + 1); //and square to the right
}

int main() {
        srand(time(0)); //seed the random generator with time

        //create window object of the RenderWindow class, a window that can serve as target for 2D drawing
        RenderWindow window(VideoMode(N * ts, M * ts), "Xonix Game!");
        window.setFramerateLimit(60);  //method that limits the framerate to a maximum fixed frequency
        //the frame rate is the frequency at which the frames (consecutive images) appear
        //the input parameter is the frequency in frames per seconds, only to slow down

        Texture t1, t2, t3; //creates 3 object of the Texture class
        if (t1.loadFromFile("images/tiles.png") == false) //loads the "titles.png" image from the images folder
        {
            std::cout << "Error: could not open tiles.png";
            return EXIT_FAILURE;
        }
        if (t2.loadFromFile("images/gameover.png") == false) //loads the "gameover.png" image from the images folder
        {
            std::cout << "Error: could not open gameover.png";
            return EXIT_FAILURE;
        }
        if (t3.loadFromFile("images/enemy.png") == false) //loads the "enemy.png" image from the images file
        {
            std::cout << "Error: could not open enemy.png";
            return EXIT_FAILURE;
        }

        //load the sounds
        sf::SoundBuffer bufferGameOver; //create a sound buffer object to load sound
        //load the gameOverSound.ogg from the sounds directory
        if (!bufferGameOver.loadFromFile("sounds/gameOverSound.ogg")){ //gameOverSound.ogg sound from Zapsplat.com found in https://www.zapsplat.com/?s=lose&post_type=music&sound-effect-category-id= as "Game sound, fun arcade organ tone, short negative fail or lose tone 3". License: Standard License
            std::cout << "Error: could not open gameOverSound.ogg"; //check if sound opens correctly
            return -1;}
        //the sound is already loaded so now we create a sound object
        sf::Sound soundGameOver;
        //assign the according buffer to the sound
        soundGameOver.setBuffer(bufferGameOver);

        sf::SoundBuffer bufferBlockBuilt; //create a sound buffer object to load sound
        //load the gameOverSound.ogg from the sounds directory
        if (!bufferBlockBuilt.loadFromFile("sounds/blockBuilt.ogg")){//blockBuilt.ogg sound from Zapsplat.com found in https://www.zapsplat.com/?s=rock+hit&post_type=music&sound-effect-category-id= as "Brick hit ground 1". License: Standard License
            std::cout << "Error: could not open blockBuilt.ogg"; //check if sound opens correctly
            return -1;
        }
        //the sound is already loaded so now we create a sound object
        sf::Sound soundBlockBuilt;
        //assign the according buffer to the sound
        soundBlockBuilt.setBuffer(bufferBlockBuilt);

        //Create music object and load a sound to it for the background
        Music gameMusic;
        if (!gameMusic.openFromFile("sounds/gameMusic.ogg")) { //gameMusic.ogg sound from Zapsplat.com found in https://www.zapsplat.com/?s=game+music&post_type=music&sound-effect-category-id= as "Game music – action game, fast paced, pumping, high-speed style synth melody, fast electro drums". License: Standard License
            std::cout << "Error: could not open gameMusic.ogg"; //check if sound opens correctly
            return -1; // error
        }

        //Load Airbornegp font into fontCool
        sf::Font fontCool;
        if (!fontCool.loadFromFile("fonts/AIRBORNEGP.ttf"))//AIRBORNE GP.ttf by Gustavo Paz L from https://www.1001freefonts.com/modern-fonts.php License: Free
        {
            std::cout << "Error: could not open AIRBORNEGP.ttf"; //check if sound opens correctly
            return -1; // error
        }

        //Load funegull font into fontMenu
        sf::Font fontMenu;
        if (!fontMenu.loadFromFile("fonts/junegull.ttf"))//junegull.ttf by Tipodermic Fonts from https://www.1001freefonts.com/rounded-fonts.php License: Free
        {
            std::cout << "Error: could not open junegull.ttf"; //check if sound opens correctly
            return -1; // error
        }



        //create a text for the score to have the score on it declared outside window loop to avoid having to reinitialize it over and over again
        Text textScore; //create a text object
        textScore.setFont(fontCool); // select the font
        textScore.setString("score"); // set the string to display
        textScore.setCharacterSize(20); // set the character size in pixels
        textScore.setFillColor(sf::Color::White); //set the text color
        textScore.setStyle(sf::Text::Bold | sf::Text::Underlined); //set the style text
        textScore.setPosition(20,-5); //set the position of the text

        //title text
        Text textTitle;
        textTitle.setFont(fontMenu);
        textTitle.setString("Welcome to Xonix");
        textTitle.setCharacterSize(40);
        textTitle.setFillColor(Color::Blue);
        textTitle.setStyle(sf::Text::Bold | sf::Text::Underlined); //set the style text
        textTitle.setPosition(180,10);

        //text for the home screen buttons
        Text textPlay; //create a text object
        textPlay.setFont(fontMenu); //
        textPlay.setString("INSTRUCTIONS: you are the red square, and your goal is to fill \n"
                                 "as many of the black backgorund as possible, by navigating \n"
                                 "through the space and draving a contour shape that will be \n"
                                 "filled with blue squares once you're tile returns to the edge. \n"
                                 "You can touch your green tile, if you do so you lose. Beware \n"
                                 "the enemies, if they touch you its game over. Use the arrow \n"
                                 "keys to move. While playing you can reset the game with esc \n"
                                 "or go back to the main menu with space \n "); // set the string to display
        textPlay.setCharacterSize(20); // set the character size in pixels
        textPlay.setFillColor(Color::White); //set the text color
        textPlay.setStyle(sf::Text::Bold ); //set the style text
        textPlay.setPosition(40,70); //set the position of the text

        //text enter
        Text textEnter;
        textEnter.setFont(fontMenu);
        textEnter.setString("Press enter to Play");
        textEnter.setCharacterSize(29);
        textEnter.setFillColor(Color::Red);
        textEnter.setStyle(sf::Text::Bold | sf::Text::Underlined); //set the style text
        textEnter.setPosition(200,250);

        //Sprites to be used on the menu screen
        Sprite sMenuEnemy(t3), sMenuTile(t1);
        sMenuEnemy.setPosition(450,200);
        sMenuEnemy.setScale(5,5);

        Sprite sTile(t1), sGameover(t2), sEnemy(
            t3); //create 3 objects of the sprite type, and assign each to a texture from above
        sGameover.setPosition(100, 100); //set the position of the sprite object on the window
        sEnemy.setOrigin(20, 20); //set the origin of the sEnemy sprite object, the default origin is (0,0)

        int enemyCount = 4; //number of enemies
        Enemy a[10]; //declare an array with size 10 of type Enemy object from the Enemy class

        bool Game = true; // bool variable to keep control of the game
        int x = 0, y = 0; //x and y control the current position of the player's tile
        int dx = 0, dy = 0; // dx and dy for the players motion
        float timer = 0, delay = 0.07;  //timer keeps track of the time elapsed, delay is the
        Clock clock; //coordinates the movements of the sprites

        //for loops and if statement to assign a 1 to the outline of the grid
        //the 1 will later indicate to fill the square with a blue tile
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                {
                    grid[i][j] = 1;
                }
            }
        }

        gameMusic.play(); //start playing the background music for all the game stages
        gameMusic.setLoop(true); //loop over the music so the small sized song goes on while the user is playing

        std::string overalScore; //string that will hold the overall score
        int scoreCalc;
        int scoreBlue; //declare score variable to help keep track of the number of blue tile

        //PERSONALIZED MODIFICATION FOR PART 4, used a state machine to give the game a home screen and the game
        enum GameState {
            GS_HOME_SCREEN, GS_GAME, //GS_COMPARISON_DECISION, GS_AUTOMATIC_WIN, GS_AUTOMATIC_LOSE,
        };
        GameState gameStage; //state machine variable
        gameStage = GS_HOME_SCREEN; //start on the home screen

        //display loop
        while (window.isOpen()) {
            //PERSONALIZED added home screen
            if (gameStage == GS_HOME_SCREEN){
                //Event for the home screen with the neccesary commands
                Event a;
                while (window.pollEvent(a)) {
                    if (a.type == Event::Closed) {
                        window.close(); //close window if the closed arrow is pressed
                        return -1; //end the program when the player closes the window
                    }
                    if (a.type == Event::KeyPressed) // when the key is pressed
                        if (a.key.code == Keyboard::Enter) {
                            gameStage = GS_GAME; //change to game stage
                            window.clear();//clear the current window
                            Game = true; //start the game once in the game stage
                            //set up the game to start once in game stage
                                for (int i = 1; i < M - 1; i++) {
                                    for (int j = 1; j < N - 1; j++) {
                                        grid[i][j] = 0;
                                    }}
                            x = 0; // sets the tile to 10 in x
                            y = 0;  // and 0 in y
                        }
                }
                window.clear();

                //assign a 0 to all of the space on the home menu screen except the outline which is one so it gets filled in the menu screen
                for (int i = 1; i < M - 1; i++) {
                    for (int j = 1; j < N - 1; j++) {
                        grid[i][j] = 0;
                    }
                }

                //Draw blue squares on the outline
                for (int i = 0; i < M; i++) {
                    for (int j = 0; j < N; j++) {
                        if (grid[i][j] != 0) {
                            if (grid[i][j] == 1) { sMenuTile.setTextureRect(IntRect(0, 0, ts, ts)); }//blue tile
                            sMenuTile.setPosition(j * ts, i * ts); //fix the location of the tile
                        window.draw(sMenuTile);}
                    }
                }

                //draw on the window for the menu screen
                window.draw(textTitle);
                window.draw(textPlay);
                window.draw(textEnter);
                window.draw(sMenuEnemy);

                //display the window
                window.display();
            }


             else if (gameStage == GS_GAME) {
                //play background music while the user is playing
                if (!Game) {
                    gameMusic.play(); //start playing the sound
                    gameMusic.setLoop(
                            true); //loop over the music so the small sized song goes on while the user is playing
                }

                float time = clock.getElapsedTime().asSeconds(); //get the elapsed time it took to do the last loop
                clock.restart(); //restarts the clock
                timer += time; //add the time of the last loop to the global timer

                //event loop, this type of loop proceces events
                Event e;

                //while loop to run while the event is pending
                while (window.pollEvent(e)) {
                        if (e.type == Event::Closed) {
                            window.close(); //close window if the closed arrow is pressed
                            return -1; //end the program when the player closes the window
                        }
                        if (e.type == Event::KeyPressed) // when the key is pressed
                            if (e.key.code == Keyboard::Escape) {
                                for (int i = 1; i < M - 1; i++) {
                                    for (int j = 1; j < N - 1; j++) {
                                        grid[i][j] = 0;
                                    }
                                }

                                x = 10; // sets the tile to 10 in x
                                y = 0;  // and 0 in y
                                Game = true; //game continues
                            }
                    if (e.type == Event::KeyPressed) //PERSONALIZED CHANGE when the key space key is pressed at any time during the game, it wuits the game and goes to the home Screen
                        if (e.key.code == Keyboard::Space) {
                            Game = false;
                            gameStage = GS_HOME_SCREEN;
                        }
                }


                scoreBlue = 0;//set the number of blue tiles to 0
                //if statements to process keys pressed
                if (Keyboard::isKeyPressed(Keyboard::Left)) {
                    dx = -1; //changes the player tile's motion to the left
                    dy = 0; //does not move in the y direction
                };
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    dx = 1; //changes the player tile's motion to the right
                    dy = 0; //does not move in the y direction
                };
                if (Keyboard::isKeyPressed(Keyboard::Up)) {
                    dx = 0; //does not move in the x direction
                    dy = -1; //changes the player tile's motion up
                };
                if (Keyboard::isKeyPressed(Keyboard::Down)) {
                    dx = 0; //does not move in the x direction
                    dy = 1; //changes the player tile's motion down
                };

                //game goes on while player has not lost
                if (Game) {
                    //if statement to coordinate movement so the player doesn't move very fast
                    if (timer > delay) {
                        x += dx; //move in the x direction according to the motion dx
                        y += dy; //move in the y direction according to the motion dy

                        if (x < 0) x = 0; //keep player inside the grid on the left
                        if (x > N - 1) x = N - 1; //keep player inside the grid on the right
                        if (y < 0) y = 0; //keep player inside the grid from the top
                        if (y > M - 1) y = M - 1; //keep plater inside the gride from the button

                        if (grid[y][x] == 2) {
                            Game = false; //player loses if it touches its current trail, the green tile
                        }
                        if (grid[y][x] == 0) {
                            grid[y][x] = 2; //fill the tiles with a 2, which will later indicate to fill with a green tile
                        }
                        timer = 0; //set timer to 0
                    }

                    for (int i = 0; i < enemyCount; i++) { a[i].move(); }; //move each enemy

                    if (grid[y][x] !=
                        1) { soundBlockBuilt.play(); } //play block build sound when the player returns to the edge

                    if (grid[y][x] ==
                        1) //if the player's red tile touches a blue tile then it occupies the place and the motion is set to 0
                    {
                        dx = dy = 0; //set motion to 0

                        for (int i = 0; i < enemyCount; i++) {
                            drop(a[i].getY() / ts, a[i].getX() / ts);
                        }

                        for (int i = 0; i < M; i++) {
                            for (int j = 0; j < N; j++) {
                                if (grid[i][j] == -1) {
                                    grid[i][j] = 0;
                                } else {
                                    grid[i][j] = 1;
                                    scoreBlue += 1; //add one to the blue tile count for every blue tile found
                                }

                            }
                        }
                    }

                    for (int i = 0; i < enemyCount; i++) {
                        if (grid[a[i].getY() / ts][a[i].getX() / ts] == 2) {
                            Game = false; //player loses if enemy touches its green tile
                        }
                    }

                    /////////draw//////////
                    window.clear();

                    //for loop to go over the squares in the grid
                    for (int i = 0; i < M; i++) {
                        for (int j = 0; j < N; j++) {
                            if (grid[i][j] != 0) {
                                if (grid[i][j] == 1) { sTile.setTextureRect(IntRect(0, 0, ts, ts)); }//blue tile
                                if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts)); //green tile
                                sTile.setPosition(j * ts, i * ts); //fix the location of the tile
                                window.draw(sTile); //draw the tile according to the if statement
                            }
                        }
                    }

                    sTile.setTextureRect(IntRect(36, 0, ts, ts)); //red tile, player tile/position
                    sTile.setPosition(x * ts, y * ts); //set location of tile , player position
                    window.draw(sTile); //draw the tile

                    sEnemy.rotate(10); //rotate the enemy sprite
                    for (int i = 0; i < enemyCount; i++) {
                        sEnemy.setPosition(a[i].getX(), a[i].getY()); //set the location of the enemy object
                        window.draw(sEnemy); //draw the enemy object
                    }

                    //player loses
                    if (!Game) {
                        soundBlockBuilt.stop(); //stop the sound of the block built when the game is over so it is not heard when the player loses
                        window.draw(sGameover); //draw Game over to the screen when the player loses
                        soundGameOver.play(); //play the game over sound when the player has lost
                        gameMusic.stop(); //stop the background music
                    }

                    if (scoreBlue != 0) {
                        scoreCalc = scoreBlue -
                                    126; //this is the score of the player, it is the total number of the filled squares
                        //scoreBlue is the total number of blue squares counted on the loop, when you substract 126 (number of blue squares on the outside, you get the total number of filled squares)

                        overalScore = std::to_string(
                                scoreCalc);// set the overal score string to the value of scoreCalc, this is the score
                    }

                    textScore.setString("score:" +
                                        overalScore); //set the string of the text score to score: and the calculated score
                    window.draw(textScore); //draw the score to the screen
                    window.display(); //display the window

                    //if statement to reset the score to 0 when the game is over
                    if (!Game) {
                        overalScore = "0";
                    }

                }
            }
        }
    return 0;
}
