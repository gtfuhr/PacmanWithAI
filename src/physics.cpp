#include "physics.hpp"

namespace physics
{
void Physics::verify_collision(Player *pacman, Block maze[MAZE_SIDE_LENGHT][MAZE_SIDE_WIDTH])
{
	for(int i = 0; i < MAZE_SIDE_LENGHT; i++){
		for(int j = 0; j < MAZE_SIDE_WIDTH; j++){

			if(maze[i][j].type == BlockTypes::wall){
				Retangulo wall;
			    wall.tam = {MAZE_WALL_WIDTH, MAZE_WALL_WIDTH};
			    wall.pos = {(float)j * MAZE_WALL_WIDTH + MOLDURE, (float)i * MAZE_WALL_LENGHT + MOLDURE};

				if(intercr({{(float)pacman->pos.x * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)pacman->pos.y * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)}}, wall)){
					std::cout << "col" << std::endl;
					if(pacman->move_y != 0){
						if(pacman->move_y > 0)
							pacman->pos.y -= 3 * pacman->move_y;
						else
							pacman->pos.y -= 3 * pacman->move_y + 0.25;
					}
					else if(pacman->move_x != 0){
						if(pacman->move_x > 0)
							pacman->pos.x -= 3 * pacman->move_x;
						else
							pacman->pos.x -= 3 * pacman->move_x + 0.25;
					}

					pacman->move_x = 0;
					pacman->move_y = 0;
				}
			}
		}
	}
}

void Physics::move_ghosts_2(std::list<Ghost> *ghosts)
{
}

void Physics::move_pacman(Player *pacman)
{	
	switch(pacman->key){
		case ALLEGRO_KEY_UP:
			pacman->move_y = -0.25;
			pacman->move_x = 0;
			break;
		case ALLEGRO_KEY_DOWN:
			pacman->move_y = 0.25;
			pacman->move_x = 0;
			break;
		case ALLEGRO_KEY_RIGHT:
			pacman->move_x = 0.25;
			pacman->move_y = 0;
			break;
		case ALLEGRO_KEY_LEFT:
			pacman->move_x = -0.25;
			pacman->move_y = 0;
			break;
	}

	pacman->pos.x += pacman->move_x;
	pacman->pos.y += pacman->move_y;
}
}; // namespace physics 
