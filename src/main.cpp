//Comando para compilar:
// make clean
// make
#include "init.hpp"
#include <fstream>

// bool operator<(const Ponto_Mapa &a, const Ponto_Mapa &b)

struct Game
{
    Player player;
    Scores scores;
    std::list<Ghost> ghosts;
    draw::Draw draw;
    physics::Physics phy;
    Block maze[MAZE_SIDE_WIDTH][MAZE_SIDE_LENGHT];
    ai::Ai ai;
    int score;

    // Init the main structures of the Game
    void init(void)
    {
        score = 0;
        draw.t.inicia(SCREEN_WIDTH, SCREEN_LENGTH, "PAC MAN");
        draw.t.play_menuMusic();
        draw.load_background();
        draw.scoreboard_bubblesort(&scores);
        load_maze();
        ai.init_vertices(maze);
        ai.initContainsPacman(14, 20);
        init_player();
        phy.initPhy(14, 20);
    }

    void init_ghost(int x, int y)
    {
        Ghost ghost;
        ghost.pos = {float(x), float(y)};
        ghosts.push_back(ghost);
    }

    void init_player()
    {
        player.state = State::menu;
        player.option = 0;
        player.move_x = 0;
        player.move_y = 0;
        player.speed = 3;
        player.cir.raio = PACMAN_RADIUS;
    }

    void load_maze()
    {
        int numOfBonus = 0;
        std::string line;
        std::ifstream fileStre{MAZE_FILE};
        for (auto i = 0; std::getline(fileStre, line); i++)
            for (auto l = 0; line[l] != '\0'; l++)
            {
                maze[l][i].hasPoint = false;
                maze[l][i].hasBonus = false;
                switch (line[l])
                {
                case '-':
                    maze[l][i].type = BlockTypes::path;
                    maze[l][i].hasPoint = true;
                    break;
                case '+':
                    maze[l][i].type = BlockTypes::intersection;
                    maze[l][i].hasPoint = true;
                    maze[l][i].hasBonus = false;
                    if (numOfBonus < MAX_NUM_OF_BONUS && sin(rand()) > 0.9)
                    {
                        maze[l][i].hasBonus = true;
                        numOfBonus++;
                    }

                    break;
                case '0':
                    maze[l][i].type = BlockTypes::wall;
                    break;
                case '|':
                    maze[l][i].type = BlockTypes::path;
                    maze[l][i].hasPoint = true;
                    break;
                case '*':
                    maze[l][i].type = BlockTypes::path;
                    player.cir.centro = {(float)l * MAZE_WALL_WIDTH + MOLDURE + (MAZE_WALL_WIDTH / 2), (float)i * MAZE_WALL_LENGHT + MOLDURE + (MAZE_WALL_LENGHT / 2)};
                    break;
                case '#':
                    maze[l][i].type = BlockTypes::path;
                    init_ghost(l, i);
                    break;
                case ' ':
                    maze[l][i].type = BlockTypes::path;
                    break;
                }
            }
    }

    void move_ghosts(void)
    {
        phy.move_ghosts_2(&ghosts);
    }

    // Updates the game
    void update(void)
    {
        // Read last key
        player.key = draw.t.tecla();
        draw.t.limpa();
        // The 'Q' key ends the game
        if (player.state == State::menu)
            draw.draw_main_menu(&player);

        else if (player.state == State::playing)
        {
            draw.draw_map(maze);
            draw.draw_figures(player, ghosts);
            phy.verify_collision(&player, ai.grafo, maze);
            move_ghosts();
            score = phy.pacman_score(&player, maze, score);
            draw.draw_score(score);
        }
        else if (player.state == State::score)
            draw.draw_scoreboard(&player, &scores);

        // Updates the screen
        draw.t.mostra();
        draw.draw_background();
        draw.t.espera(8.33);
    }

    // Verify if the game ended
    bool verifyEnd(void) { return true; }
};

int main(int argc, char **argv)
{
    Game game;
    game.init();
    while (game.player.state != State::end)
        game.update();
    game.draw.finish();
    return 0;
}