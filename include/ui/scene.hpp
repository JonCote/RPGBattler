#ifndef scene_hpp
#define scene_hpp
#include <ncurses.h>
#include <string>
#include <vector>
#include <deque>
#include "stats/character.hpp"
#include "stats/enemy.hpp"

namespace ui {
    WINDOW* render_main_menu(std::vector<std::string>& text, int termheight, int termwidt);
    WINDOW* render_character_creation(int termheight, int termwidth);
    WINDOW* render_name_input(int termheight, int termwidth);
    WINDOW* render_new_game(std::vector<std::string>& text, int termheight, int termwidth);
    WINDOW* render_load_game(std::vector<std::string>& text, int termheight, int termwidth);
    WINDOW* render_save(int termheight, int termwidth);
    WINDOW* render_lobby_menu(std::vector<std::string>& text, int termheight, int termwidth);
    WINDOW* render_lobby_attr(std::vector<std::string>& text, stats::character* player, int termheight, int termwidth);
    WINDOW* render_lobby_stats(std::vector<std::string>& text, stats::character* player, int termheight, int termwidth);
    WINDOW* render_lobby_enemy_stats(std::vector<std::string>& text, stats::enemy* next_enemy, int termheight, int termwidth);
    WINDOW* render_lobby_exp_bar(stats::character* player, int termheight, int termwidth);
    WINDOW* render_lobby_skills(std::vector<std::string>& text, stats::character* player, int termheight, int termwidth);
    WINDOW* render_combat_player_stats(std::vector<std::string>& text, std::vector<int> player_resources, stats::character* player, int termheight, int termwidth);
    WINDOW* render_combat_enemy_stats(std::vector<std::string>& text, std::vector<int> enemy_resources, stats::enemy* next_enemy, int termheight, int termwidth);
    WINDOW* render_combat_menu(std::vector<std::string>& text, int termheight, int termwidth);
    WINDOW* render_combat_log(std::deque<std::string> combat_log, int termheight, int termwidth);
    WINDOW* render_combat_defeat(int termheight, int termwidth);
    WINDOW* render_combat_victory(int exp_aquired, int termheight, int termwidth);
    WINDOW* render_background(int termheight, int termwidth);

    void battle();
    void load();

    int create_menu(std::vector<std::string> choices, WINDOW* win, bool enable_back,
                    int x_start=1, int y_start=1, int text_gap=1);
    int skill_select_menu(WINDOW* win, stats::character* player, bool enable_back);
    WINDOW* create_newwin(int height, int width, int start_y, int start_x);
}
#endif