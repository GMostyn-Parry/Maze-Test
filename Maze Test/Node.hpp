/*
 * Author: George Mostyn-Parry
 *
 * A class that holds information on a single node during generation of a maze.
 * Nodes are located on odd indices of the maze, and have the possibility to connect to any node surrounding it.
 *
 * This class is necessary for the randomised depth-first search algorithm as we need to keep track of the paths
 * we have already explored for each node in the maze, and we explore from the most recently reached node.
 */
#pragma once

#include <SFML/Graphics.hpp> //For 2D vectors; i.e. sf::Vector2u.

//Holds information on a node in a maze; a node being any point that can have an intersection; i.e. connects to another node.
class Node{
public:
    //Node constructor.
	//	coord : The pixel co-ordinate of the node in the maze.
	//	mazeSize : The size of the maze this node is a part of.
    Node(const sf::Vector2u &coord, const sf::Vector2u &mazeSize);

	//Returns the co-ordinate of the node in the maze.
	const sf::Vector2u& getCoordinate();
	//Returns how many unexplored paths are left at this node.
	size_t getPathsRemaining();
	//Returns a path that has yet to be explored at this node, choosing randomly, and removes it from the list of unexplored paths.
	sf::Vector2i getRandomOpenPath();
private:
	sf::Vector2u coord; //Where the node is in the maze.
	std::vector<sf::Vector2i> openPaths; //All the unexplored paths remaining at this node.
};

//Returns the co-ordinate of the node in the maze.
inline const sf::Vector2u& Node::getCoordinate()
{
	return coord;
}

//Returns how many unexplored paths are left at this node.
inline size_t Node::getPathsRemaining()
{
	return openPaths.size();
}
