#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <utility>

class Mesh
{
	sf::RenderWindow* window;
	sf::RenderTexture* Background;
	sf::Sprite sprite;

	unsigned int MeshSize_x, MeshSize_y;
	float SquareSize_x, SquareSize_y;

	sf::RectangleShape** Mesh_Squares;

public:
	Mesh(int x, int y, sf::RenderWindow* window, sf::RenderTexture* Background);
	~Mesh();

	void RedrawMesh();
	void RedrawMesh(int x, int y);
	void SetSquareColor(int x, int y, sf::Color color);

	const sf::Color GetSquareColorPTR(int x, int y);
	const int GetSizeX();
	const int GetSizeY();
	
private:

};

class AntPath
{
	std::vector<std::tuple<sf::Color, std::vector<int>, int, sf::Color>> paths;

public:
	AntPath();
	~AntPath();

	void AddColor(sf::Color color, sf::Color changecolor, std::vector<int> directions);


	std::pair<sf::Color, int> GetNext(sf::Color color);

private:

};

class Ant
{
	unsigned int position_x, position_y;
	unsigned int facing;

	Mesh* mesh;
	AntPath* antpath;


	

public:
	unsigned int back_x, back_y;
	bool stop;

	Ant(Mesh* mesh, int x, int y, AntPath* antpath);
	~Ant();

	void MoveNext();

private:

};

