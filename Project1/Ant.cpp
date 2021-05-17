#pragma once
#include "Ant.h" 

Ant::Ant(Mesh* mesh, int x, int y, AntPath* antpath) :
	mesh(mesh),
	position_x(x),
	position_y(y),
	back_x(x),
	back_y(y),
	facing(0),
	stop(false),
	type(0),
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

	switch (type)
	{

	case 0: 
	{
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
				facing--;
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
	}break;

	case 1: 
	{
		NextColor temp = antpath->GetNext(temp_color_ptr, true);
		mesh->SetSquareColor(position_x, position_y, temp.color);

		switch (facing)
		{
		case 0:
		{
			switch (temp.dirrection)
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
			switch (temp.dirrection)
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
			switch (temp.dirrection)
			{
			case -1:
			{
				position_x++;
				facing--;
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
			switch (temp.dirrection)
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

	}break;

	default:
		break;
	}

	

	if (position_x >= mesh->GetSizeX())
	{
		stop = true;
	}
	else if (position_x <= 0)
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

void Ant::SetType(int x)
{
	type = x;
}

AntPath::AntPath()
{

}

AntPath::AntPath(int array_size):
	paths_array_size(array_size)
{
	paths_array = new int*[array_size];
	for (size_t i = 0; i < array_size; i++)
	{
		paths_array[i] = new int[7];
	}
}

AntPath::~AntPath()
{
	for (size_t i = 0; i < paths_array_size; i++)
	{
		delete[] paths_array[i];
	}
	delete[]paths_array;
}

void AntPath::AddColor(sf::Color color, sf::Color changecolor, std::vector<int> directions)
{
	paths.push_back(std::tuple<sf::Color, std::vector<int>, int, sf::Color>(color, directions, 0, changecolor));
}

void AntPath::AddColor(sf::Color color, sf::Color changecolor, int dirtection, int pos)
{
	paths_array[pos][0] = color.r;
	paths_array[pos][1] = color.g;
	paths_array[pos][2] = color.b;

	paths_array[pos][3] = changecolor.r;
	paths_array[pos][4] = changecolor.g;
	paths_array[pos][5] = changecolor.b;

	paths_array[pos][6] = dirtection;
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

NextColor AntPath::GetNext(sf::Color color, bool x)
{
	NextColor temp;

	for (size_t i = 0; i < paths_array_size; i++)
	{
		if ((paths_array[i][0] == color.r) && (paths_array[i][1] == color.g) && (paths_array[i][2] == color.b)) 
		{
			temp.color = sf::Color(paths_array[i][3], paths_array[i][4], paths_array[i][5]);
			temp.dirrection = paths_array[i][6];
		}
	}
	return temp;
}

