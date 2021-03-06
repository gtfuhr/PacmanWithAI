#include "physics.hpp"

inline bool operator<(const Ponto_Mapa &a, const Ponto_Mapa &b)
{
	return std::tie(a.x, a.y) < std::tie(b.x, b.y);
}

namespace physics
{
void Physics::initPhy(int x, int y)
{
	localPac = {x, y};
	bloco_antigo = localPac;
	moving = false;
}

Ponto_Mapa Physics::get_local_pac(void)
{
	return localPac;
}

Ponto centroBloco(Ponto_Mapa coordenadas)
{
	Retangulo block_col;
	block_col.tam = {MAZE_WALL_WIDTH, MAZE_WALL_LENGHT};
	block_col.pos = {(float)coordenadas.x * MAZE_WALL_WIDTH + MOLDURE, (float)coordenadas.y * MAZE_WALL_LENGHT + MOLDURE};
	float x1 = block_col.pos.x, y1 = block_col.pos.y;
	float x2 = block_col.pos.x + block_col.tam.larg, y2 = block_col.pos.y + block_col.tam.alt;
	Ponto centro{(x1 + x2) / 2, (y1 + y2) / 2};
	return centro;
}
double Physics::distancia2d(Ponto p1, Ponto p2)
{
	double parte1 = pow((p1.x - p2.x), 2);
	double parte2 = pow((p1.y - p2.y), 2);
	return sqrt(parte1 + parte2);
}

void Physics::defeat_condition(Player *player, std::list<Ghost> *ghosts)
{
	for (auto &ghost : (*ghosts))
	{
		if (distancia2d(ghost.cir.centro, (*player).cir.centro) < PACMAN_RADIUS)
		{
			player->state = State::defeat;
		}
	}
}

int Physics::block_contain_pacman(int x, int y, Player pacman)
{
	Ponto centro_bloco = centroBloco({x, y});
	double dist = distancia2d(centro_bloco, pacman.cir.centro);
	if (dist < PACMAN_RADIUS * 2)
		return 1;
	return 0;
}

int Physics::block_contain_ghost(int x, int y, Ghost *ghost)
{
	Ponto centro_bloco = centroBloco({x, y});
	double dist = distancia2d(centro_bloco, ghost->cir.centro);
	if (dist < PACMAN_RADIUS * 2)
		return 1;
	return 0;
}

int temCaminho(Player pacman, Ponto_Mapa localPac, std::map<Ponto_Mapa, Vertice> grafo)
{
	Ponto_Mapa localDesejado = localPac;
	localDesejado.x += pacman.move_x;
	localDesejado.y += pacman.move_y;
	for (auto it = grafo[localPac].arestas.begin(); it != grafo[localPac].arestas.end(); it++)
	{
		Ponto_Mapa chave_explorada = (**it).chave;
		if (chave_explorada.x == localDesejado.x && chave_explorada.y == localDesejado.y)
			return 1;
	}
	return 0;
}

int Physics::pacmanMudouDeNo(Player *pacman)
{

	if (pacman->move_x < 0)
	{
		if (!block_contain_pacman(localPac.x, localPac.y, *pacman))
		{
			localPac.x += -1;
			pacman->cir.centro = centroBloco(localPac);
			return 1;
		}
	}
	else if (pacman->move_y < 0)
	{
		if (!block_contain_pacman(localPac.x, localPac.y, *pacman))
		{
			localPac.y += -1;
			pacman->cir.centro = centroBloco(localPac);
			return 1;
		}
	}
	else if (pacman->move_x > 0)
	{
		if (!block_contain_pacman(localPac.x, localPac.y, *pacman))
		{
			localPac.x += 1;
			pacman->cir.centro = centroBloco(localPac);
			return 1;
		}
	}
	else if (pacman->move_y > 0)
	{
		if (!block_contain_pacman(localPac.x, localPac.y, *pacman))
		{
			localPac.y += 1;
			pacman->cir.centro = centroBloco(localPac);
			return 1;
		}
	}
	return 0;
}

int trocouDirecao(Player *pacman)
{
	switch (pacman->key)
	{
	case ALLEGRO_KEY_UP:
		if (pacman->move_y == +1)
			return 1;
		else
			return 0;
	case ALLEGRO_KEY_DOWN:
		if (pacman->move_y == -1)
			return 1;
		else
			return 0;
	case ALLEGRO_KEY_RIGHT:
		if (pacman->move_x == -1)
			return 1;
		else
			return 0;
	case ALLEGRO_KEY_LEFT:
		if (pacman->move_x == 1)
			return 1;
		else
			return 0;
	default:
		return 0;
	}
}

int Physics::pacmanIsMoving()
{
	return moving;
}

void Physics::verify_collision(Player *pacman, std::map<Ponto_Mapa, Vertice> grafo, Block maze[][MAZE_SIDE_LENGHT])
{
	if (!moving)
	{
		move_pacman(pacman);
		if (temCaminho(*pacman, localPac, grafo))
			moving = 1;
	}

	if (moving == 1)
	{
		if (pacman->move_x < 0)
		{
			pacman->cir.centro.x -= pacman->speed;
		}
		else if (pacman->move_x > 0)
		{
			pacman->cir.centro.x += pacman->speed;
		}
		else if (pacman->move_y > 0)
		{
			pacman->cir.centro.y += pacman->speed;
		}
		else if (pacman->move_y < 0)
		{
			pacman->cir.centro.y -= pacman->speed;
		}
	}
	if (pacmanMudouDeNo(pacman))
	{
		moving = 0;
		if (maze[localPac.x][localPac.y].type == BlockTypes::intersection)
		{
			pacman->move_x = 0;
			pacman->move_y = 0;
		}
		if (maze[localPac.x][localPac.y].type == BlockTypes::portal)
		{
			if (localPac.x == 28)
				localPac = {1, 17};
			else
				localPac = {27, 17};
		}
	}
	if (trocouDirecao(pacman) && moving == 1)
	{
		moving = 0;
		pacman->move_x *= -1;
		pacman->move_y *= -1;
	}
}

int Physics::pacman_score(Player *pacman, Block maze[][MAZE_SIDE_LENGHT], int score)
{
	if (maze[localPac.x][localPac.y].hasPoint == true)
	{
		score += 10;
		maze[localPac.x][localPac.y].hasPoint = false;
	}

	if (maze[localPac.x][localPac.y].hasBonus == true)
	{
		score += 40;
		maze[localPac.x][localPac.y].hasBonus = false;
	}

	return score;
}

void Physics::win_condition(Player *player, Block maze[][MAZE_SIDE_LENGHT])
{
	for (int i = 0; i < MAZE_SIDE_WIDTH; i++)
	{
		for (int j = 0; j < MAZE_SIDE_LENGHT; j++)
		{
			if (maze[i][j].type != BlockTypes::wall)
			{
				if (maze[i][j].hasPoint == true)
				{
					return;
				}
			}
		}
	}
	player->state = State::win;
}

void detectaDirecaoGhost(Ponto_Mapa ghost, Ponto_Mapa passo, int *move_x, int *move_y)
{
	if (passo.x > ghost.x)
	{
		(*move_x) = 1;
		(*move_y) = 0;
	}
	else if (passo.x < ghost.x)
	{
		(*move_x) = -1;
		(*move_y) = 0;
	}
	else if (passo.y > ghost.y)
	{
		(*move_y) = -1;
		(*move_x) = 0;
	}
	else if (passo.y < ghost.y)
	{
		(*move_y) = 1;
		(*move_x) = 0;
	}
}

void move_ghost(Ghost *ghost, int move_x, int move_y)
{
	if (move_x < 0)
		ghost->cir.centro.x -= ghost->speed;

	else if (move_x > 0)
		ghost->cir.centro.x += ghost->speed;

	else if (move_y > 0)
		ghost->cir.centro.y -= ghost->speed;

	else if (move_y < 0)
		ghost->cir.centro.y += ghost->speed;
}

int Physics::ghostMudouDeNo(Ghost *ghost)
{
	if (ghost->move_x < 0)
	{
		if (!block_contain_ghost(ghost->pos_coord.x, ghost->pos_coord.y, ghost))
		{
			ghost->pos_coord.x += -1;
			ghost->cir.centro = centroBloco(ghost->pos_coord);
			return 1;
		}
	}
	else if (ghost->move_x > 0)
	{
		if (!block_contain_ghost(ghost->pos_coord.x, ghost->pos_coord.y, ghost))
		{
			ghost->pos_coord.x += 1;
			ghost->cir.centro = centroBloco(ghost->pos_coord);
			return 1;
		}
	}
	else if (ghost->move_y < 0)
	{
		if (!block_contain_ghost(ghost->pos_coord.x, ghost->pos_coord.y, ghost))
		{
			ghost->pos_coord.y -= -1;
			ghost->cir.centro = centroBloco(ghost->pos_coord);
			return 1;
		}
	}
	else if (ghost->move_y > 0)
	{
		if (!block_contain_ghost(ghost->pos_coord.x, ghost->pos_coord.y, ghost))
		{
			ghost->pos_coord.y -= 1;
			ghost->cir.centro = centroBloco(ghost->pos_coord);
			return 1;
		}
	}
	return 0;
}

void Physics::move_ghosts_2(std::list<Ghost> *ghosts)
{
	for (auto &ghost : *ghosts)
	{
		if (ghost.moving == 0)
		{
			Ponto_Mapa passo = ghost.caminho.back();
			detectaDirecaoGhost(ghost.pos_coord, passo, &(ghost.move_x), &(ghost.move_y));
			ghost.moving = 1;
		}

		if (ghostMudouDeNo(&ghost))
		{
			ghost.caminho.pop_back();
			ghost.moving = 0;
		}
		else
			move_ghost(&ghost, ghost.move_x, ghost.move_y);
	}
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
}
}; // namespace physics
