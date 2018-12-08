#include "physics.hpp"

namespace physics
{
void Physics::initPhy(void)
{
	number_of_rows = 0;
}
int block_contain_pacman(int x, int y, Player pacman)
{
	Retangulo block_col, pacman_col;
	block_col.tam = {MAZE_WALL_WIDTH, MAZE_WALL_LENGHT};
	block_col.pos = {(float)x * MAZE_WALL_WIDTH + MOLDURE, (float)y * MAZE_WALL_LENGHT + MOLDURE};

	Tela tel;
	Cor branca = {255, 255, 255};

	pacman_col.tam = {14.5, 14.5};
	pacman_col.pos = {pacman.cir.centro.x - (float)PACMAN_RADIUS, pacman.cir.centro.y - (float)PACMAN_RADIUS};
	tel.cor(branca);
	if (interrr(pacman_col, block_col))
	{
		tel.retangulo(block_col);
		return 1;
	}
	return 0;
}

int moveToNode(Player *pacman, Block maze[MAZE_SIDE_WIDTH][MAZE_SIDE_LENGHT], int x, int y)
{
	int i = 1;
	if (pacman->move_x > 0)
		while (maze[x + i][y].type != BlockTypes::wall)
		{
			if (maze[x + i][y].type == BlockTypes::intersection)
				return i;
			i++;
		}
	else if (pacman->move_x < 0)
	{
		while (maze[x - i][y].type != BlockTypes::wall)
		{
			if (maze[x - i][y].type == BlockTypes::intersection)
				return i;
			i++;
		}
	}
	else if (pacman->move_y > 0)
	{
		while (maze[x][y + i].type != BlockTypes::wall)
		{
			if (maze[x][y + i].type == BlockTypes::intersection)
				return i;
			i++;
		}
	}
	else if (pacman->move_y < 0)
	{
		while (maze[x][y - i].type != BlockTypes::wall)
		{

			if (maze[x][y - i].type == BlockTypes::intersection)
				return i;
			i++;
		}
	}
	return 0;
}

void keepMoving(Player *pacman)
{
	if (pacman->move_x > 0)
		pacman->cir.centro.x += pacman->speed;
	else if (pacman->move_x < 0)
		pacman->cir.centro.x -= pacman->speed;
	else if (pacman->move_y > 0)
		pacman->cir.centro.y += pacman->speed;
	else if (pacman->move_y < 0)
		pacman->cir.centro.y -= pacman->speed;
}

void Physics::verify_collision(Player *pacman, Block maze[MAZE_SIDE_WIDTH][MAZE_SIDE_LENGHT])
{
	for (int x = 0; x < MAZE_SIDE_WIDTH; x++)
	{
		for (int y = 0; y < MAZE_SIDE_LENGHT; y++)
		{
			if (maze[x][y].type == BlockTypes::wall)
			{
				Retangulo wall;
				wall.tam = {MAZE_WALL_WIDTH, MAZE_WALL_WIDTH};
				wall.pos = {(float)x * MAZE_WALL_WIDTH + MOLDURE, (float)y * MAZE_WALL_LENGHT + MOLDURE};
				if (intercr(pacman->cir, wall))
				{
					std::cout << "col" << std::endl;
					if (pacman->move_y != 0)
					{
						if (pacman->move_y > 0)
							pacman->cir.centro.y -= pacman->speed;
						else
							pacman->cir.centro.y -= pacman->speed;
					}
					else if (pacman->move_x != 0)
					{
						if (pacman->move_x > 0)
							pacman->cir.centro.x -= pacman->speed;
						else
							pacman->cir.centro.x -= pacman->speed;
					}
					pacman->move_x = 0;
					pacman->move_y = 0;
				}
			}
		}
	}
}
int Physics::PacmanMudouCol(int x, int y)
{
	if (bloco_antigo.x != x || bloco_antigo.y != y)
	{
		bloco_antigo.x = x;
		bloco_antigo.y = y;
		return 1;
	}
	return 0;
}

void Physics::move_ghosts_2(std::list<Ghost> *ghosts)
{
}

void Physics::move_pacman(Player *pacman)
{
	switch (pacman->key)
	{
	case ALLEGRO_KEY_UP:
		pacman->move_y = -1;
		pacman->move_x = 0;
		break;
	case ALLEGRO_KEY_DOWN:
		pacman->move_y = 1;
		pacman->move_x = 0;
		break;
	case ALLEGRO_KEY_RIGHT:
		pacman->move_x = 1;
		pacman->move_y = 0;
		break;
	case ALLEGRO_KEY_LEFT:
		pacman->move_x = -1;
		pacman->move_y = 0;
		break;
	}
	keepMoving(pacman);
}
}; // namespace physics
