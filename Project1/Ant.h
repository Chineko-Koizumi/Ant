#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <utility>

#include "Mesh.h"

struct NextColor
{
	sf::Color color;
	int dirrection;
};

class AntPath
{
	std::vector<std::tuple<sf::Color, std::vector<int>, int, sf::Color>> paths;

	int ** paths_array;
	int paths_array_size;

public:
	AntPath();
	AntPath(int array_size);

	~AntPath();

	void AddColor(sf::Color color, sf::Color changecolor, std::vector<int> directions);
	void AddColor(sf::Color color, sf::Color changecolor, int dirtection, int pos);

	std::pair<sf::Color, int> GetNext(sf::Color color);
	NextColor GetNext(sf::Color color, bool x);

private:

};

class Ant
{
	unsigned int position_x, position_y;
	unsigned int facing;
	int type;

	Mesh* mesh;
	AntPath* antpath;




public:
	unsigned int back_x, back_y;
	bool stop;

	Ant(Mesh* mesh, int x, int y, AntPath* antpath);
	~Ant();

	void SetType(int x);
	void MoveNext();

private:

};
