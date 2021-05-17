#ifndef Mesh_HEADER
#define Mesh_HEADER

#include <SFML/Graphics.hpp>

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



#endif