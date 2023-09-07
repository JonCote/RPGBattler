#include <iostream>
#include <ncurses.h>
#include <panel.h>
#include <utility>
#include <string>
#include <vector>
#include <deque>
#include <ctime>
#include "ui/scene.hpp"
#include "stats/character.hpp"
#include "stats/enemy.hpp"
#include "stats/combat.hpp"
#include "stats/save.hpp"
#include "tools/json_tools.hpp"

/*****************************
 * Game state scene correlations:
 * -1: Exit game
 * 0: main menu
 * 1: Lobby
 * 2: Combat
 * 3: New game creation
 * 4: Load game data
 * 
 ******************************/
int game_state = 0;
int termwidth;
int termheight;
stats::character player_character;
stats::enemy next_enemy;
std::vector<stats::Save> save_data;
std::string save_file_path;


void assign_name() {
    std::string name;
    int c;
    int i = 0;
    while(1) {
        WINDOW* background = ui::render_background(termheight, termwidth);
        WINDOW* character_creation_win = ui::render_character_creation(termheight, termwidth);
        WINDOW* name_box = ui::render_name_input(termheight, termwidth);
        
        mvwprintw(name_box, 1, 1, name.c_str());
        
        c = wgetch(name_box);
        if((c == 10 || c == KEY_ENTER) && i > 1) {
            // enter key pressed
            game_state = 1;
            break;
        }
        else if(c == 127 || c == '\b' || c == KEY_BACKSPACE) {
            // backspace key pressed
            name.pop_back();
            i--;
        }
        else if(c == 27) {
            game_state = 0;
            break;
        }
        else if((c >= 97 && c <= 122) || (c >= 65 && c <= 90)) {
            // letter pressed
            if(i < 20) {
                name.push_back(char(c));
                i++;
            }
        }
        
        delwin(name_box);
        refresh();
    }

    player_character.set_character_name(name);
}

void new_game() {
    std::string slot1;
    std::string slot2;
    std::string slot3;
    if(!save_data.at(0).name.compare("")) {
        slot1 = "Save Slot 1";
    }
    else {
        slot1 = save_data.at(0).name + ": Level " + std::to_string(save_data.at(0).level) + " [" + save_data.at(0).save_dt + "]";
    }

    if(!save_data.at(1).name.compare("")) {
        slot2 = "Save Slot 2";
    }
    else {
        slot2 = save_data.at(1).name + ": Level " + std::to_string(save_data.at(1).level) + " [" + save_data.at(1).save_dt + "]";
    }

    if(!save_data.at(2).name.compare("")) {
        slot3 = "Save Slot 3";
    }
    else {
        slot3 = save_data.at(2).name + ": Level " + std::to_string(save_data.at(2).level) + " [" + save_data.at(2).save_dt + "]";
    }

    WINDOW* background = ui::render_background(termheight, termwidth);
    std::vector<std::string> save_text = {slot1, slot2, slot3};
    WINDOW* win = ui::render_new_game(save_text, termheight, termwidth);
    
    // render menu and get user selection
    int menu_ind = ui::create_menu(save_text, win, true, 1, 1, 2);

    switch(menu_ind) {
        case 0:
            // add input character name
            player_character = stats::character();
            player_character.set_save_slot(0);
            assign_name();
            break;
        case 1:
            // add input character name
            player_character = stats::character();
            player_character.set_save_slot(1);
            assign_name();
            break;
        case 2:
            // add input character name
            player_character = stats::character();
            player_character.set_save_slot(2);
            assign_name();
            break;
        case 8:
            // backspace hit go back to main_menu
            game_state = 0;
            break;
        default:
          //  printw("ERROR!!! ");
            break;
    }

    delwin(win);
}


void load_game() {
    std::string slot1;
    std::string slot2;
    std::string slot3;
    std::vector<bool> slot_valid {false, false, false};
    if(!save_data.at(0).name.compare("")) {
        slot1 = "Save Slot 1";
    }
    else {
        slot1 = save_data.at(0).name + ": Level " + std::to_string(save_data.at(0).level) + " [" + save_data.at(0).save_dt + "]";
        slot_valid.at(0) = true;
    }

    if(!save_data.at(1).name.compare("")) {
        slot2 = "Save Slot 2";
    }
    else {
        slot2 = save_data.at(1).name + ": Level " + std::to_string(save_data.at(1).level) + " [" + save_data.at(1).save_dt + "]";
        slot_valid.at(1) = true;
    }

    if(!save_data.at(2).name.compare("")) {
        slot3 = "Save Slot 3";
    }
    else {
        slot3 = save_data.at(2).name + ": Level " + std::to_string(save_data.at(2).level) + " [" + save_data.at(2).save_dt + "]";
        slot_valid.at(2) = true;
    }

    WINDOW* background = ui::render_background(termheight, termwidth);
    std::vector<std::string> load_text = {slot1, slot2, slot3};
    WINDOW* win = ui::render_new_game(load_text, termheight, termwidth);
    
    // render menu and get user selection
    int menu_ind = ui::create_menu(load_text, win, true, 1, 1, 2);

    switch(menu_ind) {
        case 0:
            if(slot_valid.at(0)) {
                player_character = stats::character(save_data.at(0).attributes, save_data.at(0).name, save_data.at(0).level,
                                                    save_data.at(0).skill_id, save_data.at(0).exp, save_data.at(0).attr_points,
                                                    save_data.at(0).exp_needed);
                player_character.set_save_slot(0);
                game_state = 1;
            }
            break;
        case 1:
            if(slot_valid.at(1)) {
                player_character = stats::character(save_data.at(1).attributes, save_data.at(1).name, save_data.at(1).level,
                                                    save_data.at(1).skill_id, save_data.at(1).exp, save_data.at(1).attr_points,
                                                    save_data.at(1).exp_needed);
                player_character.set_save_slot(1);
                game_state = 1;
            }
            break;
        case 2:
            if(slot_valid.at(2)) {
                player_character = stats::character(save_data.at(2).attributes, save_data.at(2).name, save_data.at(2).level,
                                                    save_data.at(2).skill_id, save_data.at(2).exp, save_data.at(2).attr_points,
                                                    save_data.at(2).exp_needed);
                player_character.set_save_slot(2);
                game_state = 1;
            }
            break;
        case 8:
            // backspace hit go back to main_menu
            game_state = 0;
            break;
        default:
          //  printw("ERROR!!! ");
            break;
    }

    delwin(win); 

}


void main_menu() {
    std::vector<std::string> choices = {"New Game", "Load Game", "Exit Game"};
    WINDOW* background = ui::render_background(termheight, termwidth);
    WINDOW* win = ui::render_main_menu(choices, termheight, termwidth);
    int menu_ind = ui::create_menu(choices, win, false, 46, 6, 2);

    switch(menu_ind) {
        case 0:
            // make a new game
            game_state = 3;
            break;
        case 1:
            // load game
            game_state = 4;
            break;
        case 2:
            // exit game
            game_state = -1;
            break;
        default:
            // if it gets here a error occurred
            break;
    }

    delwin(win);
}


int lobby_main_menu_selection(int menu_ind) {
    switch(menu_ind) {
        case 0:
          //  printw("Entering Combat ");
            game_state = 2;
            break;
        case 1:
         //   printw("Going to Attribute Assignment ");
            clear();
            refresh();
            return 1;
            break;
        case 2:
           // printw("Going to Ultimate Skill Assignment ");
            clear();
            refresh();
            return 2;
            break;
        case 3:
           // printw("Going to Save Game ");
            clear();
            refresh();
            return 3;
            break;
        case 4:
           // printw("Exiting game! ");
            game_state = -1;
            break;
        default:
           // printw("ERROR!!! ");
            break;
    }
    return 0;
}
void lobby_attr_assignment(int menu_ind) {
    switch(menu_ind) {
        case 0: // Strength
        case 1: // Defense
        case 2: // Dexterity
        case 3: // Intelligence
            player_character.assign_attribute_point(menu_ind);
            break;
        case 8:
            // backspace hit return to lobby main menu
            break;
        default:
           // printw("ERROR!!! ");
            break;
    }

}

void lobby_skill_assignment(int menu_ind){
    if(menu_ind == -1) {
        // backspace hit return to lobby main menu
        return;
    }
    player_character.set_skill_id(menu_ind);
}

void save_game() {
    int c;
    // save game data to json
    int save_slot = player_character.get_save_slot();
    save_data.at(save_slot).name = player_character.get_character_name();
    save_data.at(save_slot).level = player_character.get_level();
    save_data.at(save_slot).exp = player_character.get_exp();
    save_data.at(save_slot).exp_needed = player_character.get_exp_needed();
    save_data.at(save_slot).skill_id = player_character.get_skill_id();
    save_data.at(save_slot).attr_points = player_character.get_attribute_points();
    save_data.at(save_slot).attributes = player_character.get_attributes();

    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    save_data.at(save_slot).save_dt = dt;

    tools::save_game(save_data, save_file_path);

    while(1) {
        WINDOW* background = ui::render_background(termheight, termwidth);
        WINDOW* save_win = ui::render_save(termheight, termwidth);
        c = wgetch(save_win);
        if((c == 10 || c == KEY_ENTER)) {
            // enter key pressed
            delwin(save_win);
            refresh();
            break;
        }
        else if(c == 27) {
            // esc key pressed
            game_state = 0;
            delwin(save_win);
            refresh();
            break;
        }
        
        delwin(save_win);
        refresh();
    }
}


void lobby(int lobby_menu_num) {

    std::vector<std::string> menu_text = {"Enter Combat", "Assign Attribute", "Assign Skill", "Save Game", "Exit Game"};
    std::vector<std::string> stats_text = {"Level", "HP", "Mana", "Physical Atk", "Magic Atk", "Accuracy", "Block Rate", "Dodge Rate"};
    std::vector<std::string> attr_text = {"Strength", "Defense", "Dexterity", "Intelligence"};
    
    WINDOW* background = ui::render_background(termheight, termwidth);
    WINDOW* menu_win = ui::render_lobby_menu(menu_text, termheight, termwidth);
    WINDOW* attr_win = ui::render_lobby_attr(attr_text, &player_character, termheight, termwidth);
    WINDOW* stats_win = ui::render_lobby_stats(stats_text, &player_character, termheight, termwidth);
    WINDOW* enemy_stats_win = ui::render_lobby_enemy_stats(stats_text, &next_enemy, termheight, termwidth);
    WINDOW* skill_win = ui::render_lobby_skills(attr_text, &player_character, termheight, termwidth);
    WINDOW* exp_bar_win = ui::render_lobby_exp_bar(&player_character, termheight, termwidth);

    int menu_ind;
    int to_attr;
    switch(lobby_menu_num) {
        case 0:
            // lobby menu
            menu_ind = ui::create_menu(menu_text, menu_win, false);
            to_attr = lobby_main_menu_selection(menu_ind);
            break;
        case 1:
            // assign attribute points
            menu_ind = ui::create_menu(attr_text, attr_win, true);
            lobby_attr_assignment(menu_ind);
            if(menu_ind != 8 && player_character.get_attribute_points() > 0) {
                // stay in attribute assignment tell backspace is it or out of points to assign
                to_attr = 1;
            }
            break;
        case 2:
            // assign skill
            menu_ind = ui::skill_select_menu(skill_win, &player_character, true);
            lobby_skill_assignment(menu_ind);
            break;
        case 3:
            // save game
            save_game();
            break;
        default:
            break;
    }
    delwin(menu_win);
    delwin(attr_win);
    delwin(stats_win);
    delwin(enemy_stats_win);

    if(to_attr != 0) {
        lobby(to_attr);
    }
}


// combat screen
void combat() {
    std::vector<std::string> combat_actions = {"Attack", "Block", "Dodge", player_character.get_skill_name(), "Flee Combat"}; // replace skill with assigned skill name instead
    std::vector<std::string> stats_text = {"Level", "HP", "Mana", "Physical Atk", "Magic Atk", "Accuracy", "Block Rate", "Dodge Rate"};
    std::vector<int> player_resources {player_character.get_hp(), player_character.get_magic_power()};
    std::vector<int> enemy_resources {next_enemy.get_hp(), next_enemy.get_magic_power()};
    std::deque<std::string> combat_log;
    
    bool in_combat = true;
    while(in_combat) {

        while(combat_log.size() >= 24) {
            combat_log.pop_front();
        }
        // create a new window
        WINDOW* background = ui::render_background(termheight, termwidth);
        WINDOW* menu_win = ui::render_combat_menu(combat_actions, termheight, termwidth);
        WINDOW* player_stats_win = ui::render_combat_player_stats(stats_text, player_resources, &player_character, termheight, termwidth);
        WINDOW* enemy_stats_win = ui::render_combat_enemy_stats(stats_text, enemy_resources, &next_enemy, termheight, termwidth);
        WINDOW* combat_log_win = ui::render_combat_log(combat_log, termheight, termwidth);

        int menu_ind = ui::create_menu(combat_actions, menu_win, false);

        if(menu_ind == 4) {
            // Fleeing combat
            in_combat = false;
            game_state = 1;
        }
        else if(menu_ind == 3 && player_resources.at(1) < player_character.get_skill_mana_cost()) {
            combat_log.push_back("Insufficient mana to cast spell");
        }
        else {
            std::vector<std::string> temp = stats::combat_controller(menu_ind, player_resources, enemy_resources, &player_character, &next_enemy);
            combat_log.insert(combat_log.end(), temp.begin(), temp.end());
        }
        combat_log.push_back("---------------------------------");
        
        if(player_resources.at(0) <= 0) {
            // player lost
            WINDOW* defeat_win = ui::render_combat_defeat(termheight, termwidth);
            getch();
            in_combat = false;
            game_state = 1;
            delwin(defeat_win);
        }
        else if(enemy_resources.at(0) <= 0) {
            // enemy lost
            int exp_aquired = next_enemy.get_exp();
            WINDOW* victory_win = ui::render_combat_victory(exp_aquired, termheight, termwidth);
            getch();
            in_combat = false;
            game_state = 1;
            player_character.add_exp(exp_aquired);
            delwin(victory_win);

        }


        delwin(menu_win);
        delwin(player_stats_win);
        delwin(enemy_stats_win);
        refresh();
    }
}


int main(int argc, char** argv) {

    // pull save data from save file
    if(argc == 1) {
        // use default save file
        save_file_path = "data/save/default_save.JSON";
        save_data = tools::load_save_data(save_file_path);
    }
    else if(argc == 2) {
        // use custome save file passed in
        save_file_path = argv[1];
        save_data = tools::load_save_data(save_file_path);
    }
    else {
        // put usage information then end execution
        std::cout << "Usage: RPGBattle {custom save file path (if desired)}\n";
        return 0;
    }   


    initscr();
    // *** start of ncurses block ***
    start_color();
    cbreak();       // ctrl+c breaks out of ncurses
    noecho();       // user input is not printed to the screen
    curs_set(0);
    termheight = getmaxy(stdscr);
    termwidth = getmaxx(stdscr);

    // game scene controller
    bool exit_game = false;
    while(!exit_game) {
        clear();
        refresh();
        switch(game_state) {
            case -1:
                // exit game
                exit_game = true;
                break;
            case 0:
                // main menu
                main_menu();
                break;
            case 1:
                // lobby
                lobby(0);
                break;
            case 2:
                // combat
                combat();
                next_enemy = stats::enemy(player_character.get_level());
                break;
            case 3:
                // create new game
                new_game();
                next_enemy = stats::enemy(player_character.get_level());
                break;
            case 4:
                // load game
                load_game();
                next_enemy = stats::enemy(player_character.get_level());
                break;
            default:
                break;
        }
    }

    // *** end of ncurses block ***
    endwin();
    return 0;
}