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



Ant::Ant(Mesh* mesh, int x, int y, AntPath* antpath):
	mesh(mesh),
	position_x(x),
	position_y(y),
	back_x(x),
	back_y(y),
	antpath(antpath)
{
}

Ant::~Ant()
{
}

void Ant::MoveNext() 
{
	if (stop) return;

	back_x = position_x;
	back_y = position_y;

	sf::Color temp_color_ptr = mesh->GetSquareColorPTR(position_x, position_y);
	std::pair<sf::Color, int> temp = antpath->GetNext(temp_color_ptr);
	mesh->SetSquareColor(position_x, position_y, temp.first);

	switch (facing)
	{
		case 0: 
		{
			switch (temp.second)
			{
				case -1:
				{
					facing = 3;
					position_x--;
				}break;
				case 0:
				{
					position_y++;
				}break;
				case 1:
				{
					position_x++;
					facing++;
				}break;
	
				default:
				break;
			}
		}break;
		case 1:
		{
			switch (temp.second)
			{
			case -1:
			{
				position_y++;
				facing--;
			}break;
			case 0:
			{
				position_x++;
			}break;
			case 1:
			{
				position_y--;
				facing++;
			}break;
	
			default:
				break;
			}
		}break;
		case 2:
		{
			switch (temp.second)
			{
			case -1:
			{
				position_x++;
				facing --;
			}break;
			case 0:
			{
				position_y--;
			}break;
			case 1:
			{
				position_x--;
				facing++;
			}break;
	
			default:
				break;
			}
		}break;
		case 3:
		{
			switch (temp.second)
			{
			case -1:
			{
				position_y--;
				facing--;
			}break;
			case 0:
			{
				position_x--;
			}break;
			case 1:
			{
				position_y++;
				facing = 0;
			}break;
	
			default:
				break;
			}
		}break;
	
			default:
			break;
	}

	if (position_x >= mesh->GetSizeX())
	{
		stop = true;
	}
	else if (position_x <=0)
	{
		stop = true;
	}
	else if (position_y >= mesh->GetSizeY())
	{
		stop = true;
	}
	else if (position_y <= 0)
	{
		stop = true;
	}


	

}

AntPath::AntPath()
{

}

AntPath::~AntPath()
{
}

void AntPath::AddColor(sf::Color color, sf::Color changecolor, std::vector<int> directions)
{
	paths.push_back(std::tuple<sf::Color, std::vector<int>, int, sf::Color>(color, directions, 0, changecolor));
}

std::pair<sf::Color, int> AntPath::GetNext(sf::Color color)
{
	std::pair<sf::Color, int> temp;
	for (size_t i = 0; i < paths.size(); i++)
	{
		if (std::get<0>(paths[i]) == color) 
		{
			temp.first = std::get<3>(paths[i]);
			temp.second = std::get<1>(paths[i])[std::get<2>(paths[i])];

			std::get<2>(paths[i])++;
			if (std::get<2>(paths[i]) >= std::get<1>(paths[i]).size()) 
			{ 
				(std::get<2>(paths[i])) = 0; 
			}
		}
	}

	return temp;
}
