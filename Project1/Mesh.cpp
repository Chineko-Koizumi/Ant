

#include "Mesh.h"

Mesh::Mesh(int x, int y, sf::RenderWindow* window, sf::RenderTexture* Background):
	MeshSize_x(x),
	MeshSize_y(y),
	window(window),
	Background(Background)
{
	SquareSize_x = (float)window->getSize().x / x;
	SquareSize_y = (float)window->getSize().y / y;

	Mesh_Squares = new sf::RectangleShape*[x];
	for (size_t i = 0; i < x; i++)
	{
		Mesh_Squares[i] = new sf::RectangleShape[y];
		for (size_t j = 0; j < y; j++)
		{
			Mesh_Squares[i][j].setFillColor(sf::Color::Black);
			Mesh_Squares[i][j].setSize(sf::Vector2f(SquareSize_x, SquareSize_y));
			Mesh_Squares[i][j].setOrigin(sf::Vector2f(SquareSize_x / 2, SquareSize_y / 2));
			Mesh_Squares[i][j].setPosition(SquareSize_x*i + SquareSize_x/2, SquareSize_y*j + SquareSize_y / 2);
		}
	}

}

Mesh::~Mesh()
{
}



void Mesh::RedrawMesh(int x, int y)
{
	Background->draw(Mesh_Squares[x][y]);
	Background->display();
	sprite.setTexture(Background->getTexture());
	window->draw(sprite);
}

void Mesh::RedrawMesh()
{
	for (size_t i = 0; i < MeshSize_x; i++)
	{
		for (size_t j = 0; j < MeshSize_y; j++)
		{
			Background->draw(Mesh_Squares[i][j]);
		}
	}
}

void Mesh::SetSquareColor(int x, int y, sf::Color color)
{
	Mesh_Squares[x][y].setFillColor(color);
}

const sf::Color Mesh::GetSquareColorPTR(int x, int y)
{
	return Mesh_Squares[x][y].getFillColor();
}

const int Mesh::GetSizeX()
{
	return MeshSize_x;
}

const int Mesh::GetSizeY()
{
	return MeshSize_y;
}


