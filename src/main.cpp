//Comando para compilar:
// make clean
// make
#include "init.hpp"
#include <fstream>

struct Game
{
    Player player;
    draw::Draw draw;
    physics::Physics phy;
    Block maze[MAZE_SIDE_LENGHT][MAZE_SIDE_WIDTH];

    // Init the main structures of the game
    void init(void)
    {
        draw.t.inicia(SCREEN_WIDTH, SCREEN_LENGTH, "PACMAN");
        draw.t.play_menuMusic();
        draw.load_background();
        load_maze();
        player.state = State::menu;
        player.option = 0;
    }

    void load_maze()
    {
        std::string line;
        std::ifstream fileStre{MAZE_FILE};
        for (auto i = 0; std::getline(fileStre, line); i++)
            for (auto j = 0; line[j] != '\0'; j++)
                switch (line[j])
                {
                case '-':
                    maze[i][j].type = BlockTypes::horizontal;
                    break;
                case '+':
                    maze[i][j].type = BlockTypes::crossing;
                    break;
                case '0':
                    maze[i][j].type = BlockTypes::wall;
                    break;
                case '|':
                    maze[i][j].type = BlockTypes::vertical;
                    break;
                case '*':
                    maze[i][j].type = BlockTypes::spawn;
                    break;
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

        if (player.state == State::playing)
        {
            draw.draw_map(maze);
            draw.draw_figures();
            phy.move_figures();
        }
        else if (player.state == State::score)
        {
            draw.draw_score();
        }
        // Updates the screen
        draw.t.mostra();
        draw.draw_background();
        draw.t.espera(16.66);
        // Waits 16.66 ms, then updates the screen
    }

    // Verify if the game ended
    bool verifyEnd(void)
    {
        return true;
    }
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