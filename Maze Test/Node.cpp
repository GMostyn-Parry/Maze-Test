/*
 * Author: George Mostyn-Parry
 */
#include "Node.hpp"

#include <random> //For random functions.

//Node constructor.
//	coord : The pixel co-ordinate of the node in the maze.
//	mazeSize : The size of the maze this node is a part of.
Node::Node(const sf::Vector2u &coord, const sf::Vector2u &mazeSize)
	:coord(coord)
{
    //Add horizontal paths that are in-bounds of the maze.
    if(coord.x > 1) openPaths.push_back(sf::Vector2i(-2, 0));
    if(coord.x < mazeSize.x - 3) openPaths.push_back(sf::Vector2i(2, 0));

	//Add vertical paths that are in-bounds of the maze.
    if(coord.y > 1) openPaths.push_back(sf::Vector2i(0, -2));
    if(coord.y < mazeSize.y - 3) openPaths.push_back(sf::Vector2i(0, 2));
}

//Returns a path that has yet to be explored at this node, choosing randomly, and removes it from the list of unexplored paths.
sf::Vector2i Node::getRandomOpenPath()
{
	//Randomly choose a path from the list, and store the iterator of the path in the list.
	auto pathIt = openPaths.begin() + rand() % openPaths.size();
	
	//Stores the path that was chosen to be returned.
	sf::Vector2i chosenPath = *pathIt;
	//Erase value from vector after choosing.
	openPaths.erase(pathIt);

	return chosenPath;
}