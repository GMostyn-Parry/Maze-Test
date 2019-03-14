/*
 * Author: George Mostyn-Parry
 * Originally created in November 2016.
 * Annotated and re-factored in January 2019 - February 2019.
 * Compiled with SFML 2.5.1, and Visual Studio 2017 in C++17.
 *
 * A small program to generate a randomly generated maze of a passed size, using a randomised depth-first search algorithm.
 * The mazes do not have entry or exit points.
 * The size must be odd on both axes, but does not have to be uniform.
 */
#include <random> //For random functions.
#include <stack> //Stacks for Randomised Depth-First Search.

#include <SFML/Graphics.hpp> //Import graphics package of SFML.

#include "Node.hpp" //Node class for constructing a maze.

//Creates an image which represents a randomly generated maze.
//	mazeSize : The size of the maze we are generating.
//Returns an image with a randomly drawn maze, of the size passed, drawn onto it.
const sf::Image createImageOfMaze(const sf::Vector2u &mazeSize);

//Creates a new maze, and assigns it to the passed sprite to display.
//	mazeSize : The size of the maze we are generating.
//	sprite : The sprite we will be displaying the maze on.
//	spriteTexture : Texture used by the sprite, and will hold the image of the maze.
void displayNewMaze(const sf::Vector2u &mazeSize, sf::Sprite &sprite, sf::Texture &spriteTexture);

int main(){
	//Maximum size of a generated maze; must be an odd number.
	constexpr unsigned int MAX_SIZE = 199;
	//Minimum size of a generated maze; must be an odd number.
	constexpr unsigned int MIN_SIZE = 5;

    //Seed the random number generator with the current time.
    srand(static_cast<unsigned int>(time(nullptr)));

    //The window we will be rendering to.
    sf::RenderWindow window(sf::VideoMode(MAX_SIZE, MAX_SIZE), "Maze Test");
	//Prevent user from holding down the key, as we don't want to generate mazes too quickly.
	window.setKeyRepeatEnabled(false);
    //The size of the mazes created; includes border.
    sf::Vector2u mazeSize = {MAX_SIZE, MAX_SIZE};

    //Sprite that will display the texture that holds the image of the randomly generated mazes.
    sf::Sprite mazeSprite;
	//Centre the sprite in the middle of the page.
	mazeSprite.setPosition(sf::Vector2f(window.getSize() / 2u));

	//Texture that holds image data of the created maze.
	sf::Texture mazeTex;

	//Create an initial maze on the sprite; comes before setting texture as we need a texture to display before we set the texture.
	displayNewMaze(mazeSize, mazeSprite, mazeTex);

	//Set maze sprite to texture that holds the generated maze image.
	mazeSprite.setTexture(mazeTex);

    //The main loop of the application; it will run until the window closes.
    while(window.isOpen()){
		//Holds information on the most recently polled event.
        sf::Event event;
        //Input handling; handle all inputs performed this frame.
        while(window.pollEvent(event)){
            //Handle every different type of event that is passed.
            switch(event.type){
                //Close the window, if a close event is passed.
                case sf::Event::Closed:
                    window.close();

                    break;
				//Resize the view to the window's new size, when the window is resized.
				case sf::Event::Resized:
				{
					sf::View newView = window.getView();
					newView.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));

					break;
				}
                //Handle when a key is released on the keyboard.
                case sf::Event::KeyReleased:
				{
					//How much to change the size of the maze when a key is released; 20 when shift is held, and 2 when it is not.
					unsigned int sizeChange = event.key.shift ? 20 : 2;

					switch(event.key.code)
					{
						//Close the window when the user presses the escape key.
						case sf::Keyboard::Escape:
							window.close();

							break;
						//Displays a new maze of the same size when the the R key is released.
						case sf::Keyboard::R:
							displayNewMaze(mazeSize, mazeSprite, mazeTex);

							break;
						//Increase the horizontal size when the right arrow key is released.
						case sf::Keyboard::Right:
							//Only increase the size, and generate a new maze, if it will not maze the maze larger than the maximum.
							if(mazeSize.x <= MAX_SIZE - sizeChange)
							{
								mazeSize.x += sizeChange;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}
							//Otherwise, set it to the maximum size, and generate a new maze, if it is not already the maximum size.
							else if(mazeSize.x != MAX_SIZE)
							{
								mazeSize.x = MAX_SIZE;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}

							break;
						//Increase the vertical size when the up arrow key is released.
						case sf::Keyboard::Up:
							//Only increase the size, and generate a new maze, if it will not maze the maze larger than the maximum.
							if(mazeSize.y <= MAX_SIZE - sizeChange)
							{
								mazeSize.y += sizeChange;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}
							//Otherwise, set it to the maximum size, and generate a new maze, if it is not already the maximum size.
							else if(mazeSize.y != MAX_SIZE)
							{
								mazeSize.y = MAX_SIZE;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}

							break;
						//Decrease the horizontal size when the left arrow key is released.
						case sf::Keyboard::Left:
							//Only decrease the size, and generate a new maze, if it will not maze the maze smaller than the minimum.
							if(mazeSize.x >= MIN_SIZE + sizeChange)
							{
								mazeSize.x -= sizeChange;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}
							//Otherwise, set it to the minimum size, and generate a new maze, if it is not already the minimum size.
							else if(mazeSize.x != MIN_SIZE)
							{
								mazeSize.x = MIN_SIZE;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}

							break;
						//Decreases the vertical size when the down arrow key is released.
						case sf::Keyboard::Down:
							//Only decrease the size, and generate a new maze, if it will not maze the maze smaller than the minimum.
							if(mazeSize.y >= MIN_SIZE + sizeChange)
							{
								mazeSize.y -= sizeChange;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}
							//Otherwise, set it to the minimum size, and generate a new maze, if it is not already the minimum size.
							else if(mazeSize.y != MIN_SIZE)
							{
								mazeSize.y = MIN_SIZE;
								displayNewMaze(mazeSize, mazeSprite, mazeTex);
							}

							break;
					}

					break;
				}
            }
        }

		//Clear the window of the last render.
        window.clear();

        //Draw the sprite that shows the maze.
        window.draw(mazeSprite);

        //Display the new render to the user.
        window.display();
    }
}

//Creates an image which represents a randomly generated maze.
//	mazeSize : The size of the maze we are generating.
//Returns an image with a randomly drawn maze, of the size passed, drawn onto it.
const sf::Image createImageOfMaze(const sf::Vector2u &mazeSize){
	///Uses a randomised depth-first search algorithm to procedurally generate the maze.

    //Stores all of the unexplored nodes in the maze being created.
    std::stack<Node> nodeStack;
    //The image that the maze will be drawn onto.
    sf::Image mazeImg;

    //Create an image the same size of the maze, and filled completely black.
    mazeImg.create(mazeSize.x, mazeSize.y, sf::Color::Black);

    //Randomly choose a starting point to start generate the maze from.
    sf::Vector2u start =
            {
				//The operations performed ensure that we get an odd number within the grid.
                static_cast<unsigned int>(rand() % (mazeSize.x - 1) / 2.f) * 2 + 1,
                static_cast<unsigned int>(rand() % (mazeSize.y - 1) / 2.f) * 2 + 1
            };

    //Start stack by creating a node at the chosen starting point.
    nodeStack.emplace(start, mazeSize);

    //Set the starting point's pixel to white; i.e. explored.
    mazeImg.setPixel(start.x, start.y, sf::Color::White);

    //Create the maze while there are still nodes to explore.
    while(nodeStack.size() > 0){
        //Grab the most recently added node from the stack.
        Node &node = nodeStack.top();

		//Choose a random open path from the node.
		sf::Vector2i path = node.getRandomOpenPath();

		//The co-ordinate of the node we get to from following the path from the node at the top of the stack.
		sf::Vector2u newNodeCoord = sf::Vector2u(node.getCoordinate().x + path.x, node.getCoordinate().y + path.y);

        //Remove the node from the stack if it has no more path to explore.
        if(node.getPathsRemaining() == 0){
            nodeStack.pop();
        }        

        //Only open the path if it has not been reached before; i.e. the colour is still black.
        if(mazeImg.getPixel(newNodeCoord.x, newNodeCoord.y) == sf::Color::Black){
            //Add the node to the top of the stack, turning it into the node we will explore next.
            nodeStack.emplace(newNodeCoord, mazeSize);
            //Mark the node as reached.
            mazeImg.setPixel(newNodeCoord.x, newNodeCoord.y, sf::Color::White);

            //Colour the connecting pixel between the node that was at the top of the stack and the new node.
            mazeImg.setPixel(newNodeCoord.x - path.x / 2, newNodeCoord.y - path.y / 2, sf::Color::White);
        }
    }

    //Return the image with the maze drawn onto it.
    return mazeImg;
}

//Creates a new maze, and assigns it to the passed sprite to display.
//	mazeSize : The size of the maze we are generating.
//	sprite : The sprite we will be displaying the maze on.
//	spriteTexture : Texture used by the sprite, and will hold the image of the maze.
void displayNewMaze(const sf::Vector2u &mazeSize, sf::Sprite &sprite, sf::Texture &spriteTexture)
{
	//Create a new maze, and load it into the sprite texture.
	spriteTexture.loadFromImage(createImageOfMaze(mazeSize));

	//Change the sprite texture bounds to hold the new size.
	sprite.setTextureRect({{0, 0}, sf::Vector2i(mazeSize)});
	//Centre the origin of the sprite to the centre of texture the sprite will display.
	sprite.setOrigin(sf::Vector2f(spriteTexture.getSize() / 2u));
}
