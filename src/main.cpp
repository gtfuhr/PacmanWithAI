//Comando para compilar:
// make clean
// make
#include "init.hpp"
#include <fstream>

struct Game
{
    Player player;
    Scores scores;
    std::list<Ghost> ghosts;
    draw::Draw draw;
    physics::Physics phy;
    Block maze[MAZE_SIDE_LENGHT][MAZE_SIDE_WIDTH];

    // Init the main structures of the Game
    void init(void)
    {
        draw.t.inicia(SCREEN_WIDTH, SCREEN_LENGTH, "PAC MAN :v");
        draw.t.play_menuMusic();
        draw.load_background();
        draw.scoreboard_bubblesort(&scores);
        load_maze();
        init_player();
    }

    void init_ghost(int i, int j)
    {
        Ghost ghost;
        ghost.pos = {float(j), float(i)};
        ghosts.push_back(ghost);
    }

    void init_player()
    {
        player.state = State::menu;
        player.option = 0;
    }

    void load_maze()
    {
        int numOfBonus = 0;
        std::string line;
        std::ifstream fileStre{MAZE_FILE};
        for (auto i = 0; std::getline(fileStre, line); i++)
            for (auto j = 0; line[j] != '\0'; j++)
            {
                maze[i][j].hasPoint = false;
                maze[i][j].hasBonus = false;
                switch (line[j])
                {
                case '-':
                    maze[i][j].type = BlockTypes::path;
                    maze[i][j].hasPoint = true;
                    break;
                case '+':
                    maze[i][j].type = BlockTypes::crossing;
                    maze[i][j].hasPoint = true;
                    maze[i][j].hasBonus = false;
                    if (numOfBonus < MAX_NUM_OF_BONUS && sin(rand()) > 0.9)
                    {
                        maze[i][j].hasBonus = true;
                        numOfBonus++;
                    }

                    break;
                case '0':
                    maze[i][j].type = BlockTypes::wall;
                    break;
                case '|':
                    maze[i][j].type = BlockTypes::path;
                    maze[i][j].hasPoint = true;
                    break;
                case '*':
                    maze[i][j].type = BlockTypes::pacman_spawn;
                    player.pos = {float(j), float(i)};
                    break;
                case '#':
                    maze[i][j].type = BlockTypes::ghost_spawn;
                    init_ghost(i, j);
                    break;
                case ' ':
                    break;
                }
            }
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
            phy.move_pacman(&player);
            phy.move_ghosts(&ghosts);
            draw.draw_score();
        }
        else if (player.state == State::score)
            draw.draw_scoreboard(&player, &scores);

        // Updates the screen
        draw.t.mostra();
        draw.draw_background();
        draw.t.espera(33.33);
        // Waits 33.33 ms, then updates the screen
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