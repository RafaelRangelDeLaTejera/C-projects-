//hw4
//student Rafael Rangel
//date: 03/19/2021
//project name hw4
//program description: Basic Xonix Game, original code from FamTrinli Published on Apr 26, 2016 edited by Rafael Rangel

#include <SFML/Graphics.hpp> //add the simple and fast multimedia library
#include <time.h> //add the time library to use as a seed for random number and for the game pace
#include "iostream"

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


        //display loop
        while (window.isOpen()) {
            float time = clock.getElapsedTime().asSeconds(); //get the elapsed time it took to do the last loop
            clock.restart(); //restarts the clock
            timer += time; //add the time of the last loop to the global timer

            //event loop, this type of loop proceeces events
            Event e;
            //while loop to run while the event is pending
            while (window.pollEvent(e)) {
                if (e.type == Event::Closed)
                    window.close(); //close window if the closed arrow is pressed

                if (e.type == Event::KeyPressed) // when the key is pressed
                    if (e.key.code == Keyboard::Escape) {
                        for (int i = 1; i < M - 1; i++)
                        {
                            for (int j = 1; j < N - 1; j++)
                            {
                                grid[i][j] = 0;
                            }
                        }

                        x = 10; // sets the tile to 10 in x
                        y = 0;  // and 0 in y
                        Game = true; //game continues
                    }
            }

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

        if (!Game) continue; //TODO for hw 5 substitute continue statement with a while loop
                             //game goes on while player has not lost

            //if statement to coordinate movement so the player doesn't move very fast
            if (timer > delay) {
                x += dx; //move in the x direction according to the motion dx
                y += dy; //move in the y direction according to the motion dy

                if (x < 0) x = 0; //keep player inside the grid on the left
                if (x > N - 1) x = N - 1; //keep player inside the grid on the right
                if (y < 0) y = 0; //keep player inside the grid from the top
                if (y > M - 1) y = M - 1; //keep plater inside the gride from the buttom

                if (grid[y][x] == 2) Game = false; //player loses if it touches its current trail, the green tile
                if (grid[y][x] == 0) grid[y][x] = 2; //fill the tiles with a 2, which will later indicate to fill with a green tile
                timer = 0; //set timer to 0
            }

            for (int i = 0; i < enemyCount; i++){ a[i].move();}; //move each enemy

            if (grid[y][x] == 1) //if the player's red tile touches a blue tile then it ocupies the place and the motion stops moving
            {
                dx = dy = 0; //set motion to 0

                for (int i = 0; i < enemyCount; i++)
                {
                    drop(a[i].getY() / ts, a[i].getX() / ts);
                }

                for (int i = 0; i < M; i++)
                {
                    for (int j = 0; j < N; j++)
                    {
                        if (grid[i][j] == -1) grid[i][j] = 0;
                        else grid[i][j] = 1;
                    }
                }
            }

            for (int i = 0; i < enemyCount; i++)
                if (grid[a[i].getY() / ts][a[i].getX() / ts] == 2) Game = false; //plater loses if enemy touches its green tile

            /////////draw//////////
            window.clear();

            //for loop to go over the squares in the grid
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (grid[i][j] == 0) continue; //if spot is empty then add corresponding tile TODO change for hw5
                    if (grid[i][j] == 1) sTile.setTextureRect(IntRect(0, 0, ts, ts)); //blue tile
                    if (grid[i][j] == 2) sTile.setTextureRect(IntRect(54, 0, ts, ts)); //green tile
                    sTile.setPosition(j * ts, i * ts); //fix the location of the tile
                    window.draw(sTile); //draw the tile according to the if statement
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

            if (!Game) window.draw(sGameover); //draw Game over to the screen when the player loses

            window.display(); //display the window

    }

    return 0;
}
