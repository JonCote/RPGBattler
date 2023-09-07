#include "ui/scene.hpp"
#include "stats/ultimate_skill.hpp"
#include <sstream>
#include <iomanip>

int ui::create_menu(std::vector<std::string> choices, WINDOW* win, bool enable_back, int x_start, int y_start, int text_gap) {
    // enable interaction with menu
    keypad(win, true);
    
    int inp;
    int highlight = 0;
    int len = choices.size();

    while(1) {
        for(int i = 0; i < len; ++i) {
            if(i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, (i*text_gap)+y_start, x_start, choices.at(i).c_str());
            wattroff(win, A_REVERSE);
        }
        inp = wgetch(win);

        switch(inp) {
            case KEY_UP:
                highlight--;
                if(highlight == -1) {
                    highlight = len-1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == len) {
                    highlight = 0;
                }
                break;
            default:
                break;
        }
        if(inp == 10 || inp == KEY_ENTER || inp == 127 || inp == '\b') {
            break;
        }
        if(enable_back && inp == KEY_BACKSPACE) {
            highlight = 8;
            break;
        }
    }
    return highlight;
}

int ui::skill_select_menu(WINDOW* win, stats::character* player, bool enable_back) {
    // enable interaction with menu
    keypad(win, true);
    
    int inp;
    int highlight = 0;
    std::vector<stats::Ultimate> skill_set = player->get_skill_set();
    int len = skill_set.size();

    while(1) {
        for(int i = 0; i < len; ++i) {
            if(i == highlight) {
                wattron(win, A_REVERSE);
            }
            mvwprintw(win, (i*6)+1, 1, (skill_set.at(i).name).c_str());
            wattroff(win, A_REVERSE);
        }
        inp = wgetch(win);

        switch(inp) {
            case KEY_UP:
                highlight--;
                if(highlight == -1) {
                    highlight = len-1;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == len) {
                    highlight = 0;
                }
                break;
            default:
                break;
        }
        if(inp == 10 || inp == KEY_ENTER) {
            break;
        }
        if(enable_back && inp == KEY_BACKSPACE) {
            highlight = -1;
            break;
        }
    }
    return highlight;
}


WINDOW* ui::create_newwin(int height, int width, int start_y, int start_x) {
    WINDOW* win;
    win = newwin(height, width, start_y, start_x);
    box(win, 0, 0);
    wrefresh(win);
    return win;
}


WINDOW* ui::render_main_menu(std::vector<std::string>& text, int termheight, int termwidth) {
    // create a new window
    WINDOW* win = create_newwin(20, 100, (termheight - 20)/2, (termwidth - 100)/2);
    for(int i = 0; i < text.size(); ++i) {
        mvwprintw(win, (i*2) + 6, 46, text.at(i).c_str());
    }
    wrefresh(win);
    return win;
}

WINDOW* ui::render_character_creation(int termheight, int termwidth) {
    WINDOW* win = create_newwin(20, 100, (termheight - 20)/2, (termwidth - 100)/2);
    mvwprintw(win, 0, 2, "| Character Creation |");
    mvwprintw(win, 15, 25, "Main Menu (ESC)");
    mvwprintw(win, 15, 60, "Continue (Enter)");

    wrefresh(win);
    return win;
}

WINDOW* ui::render_name_input(int termheight, int termwidth) {
    WINDOW* win = create_newwin(3, 30, (termheight - 20)/2 + 5, (termwidth - 100)/2 + 35);
    mvwprintw(win, 0, 2, "| Input Name |");
    wrefresh(win);
    return win;
}

WINDOW* ui::render_new_game(std::vector<std::string>& text, int termheight, int termwidth) {
    // create a new window
    WINDOW* win = create_newwin(7, 70, (termheight - 10)/2, (termwidth - 70)/2);
    for(int i = 0; i < text.size(); ++i) {
        mvwprintw(win, (i*2)+1, 1, text.at(i).c_str());
        if(i != text.size() - 1) {
            mvwprintw(win, (i*2)+2, 1, "--------------------------------");
        }
        
    }
    wrefresh(win);
    return win;
}

WINDOW* ui::render_load_game(std::vector<std::string>& text, int termheight, int termwidth) {
    WINDOW* win = create_newwin(7, 70, (termheight - 10)/2, (termwidth - 70)/2);
    for(int i = 0; i < text.size(); ++i) {
        mvwprintw(win, (i*2)+1, 1, text.at(i).c_str());
        if(i != text.size() - 1) {
            mvwprintw(win, (i*2)+2, 1, "--------------------------------");
        }
    }
    wrefresh(win);
    return win;
}


WINDOW* ui::render_save(int termheight, int termwidth) {
    WINDOW* win = create_newwin(20, 100, (termheight - 20)/2, (termwidth - 100)/2);
    mvwprintw(win, 5, 45, "Game Saved");
    mvwprintw(win, 15, 25, "Main Menu (ESC)");
    mvwprintw(win, 15, 60, "Continue (Enter)");
    
    wrefresh(win);
    return win;
}

WINDOW* ui::render_lobby_menu(std::vector<std::string>& text, int termheight, int termwidth) {
     // main lobby menu window
    WINDOW* menu_win = create_newwin(10, 30, (termheight - 10)/2 + 7, (termwidth-30)/2 - 37);
    for(int i = 0; i < text.size(); ++i) {
        mvwprintw(menu_win, i+1, 1, text.at(i).c_str());
    }
    wrefresh(menu_win);

    return menu_win;
}

WINDOW* ui::render_lobby_attr(std::vector<std::string>& text, stats::character* player, int termheight, int termwidth) {
    WINDOW* attr_win = create_newwin(10, 30, (termheight - 10)/2 - 8, (termwidth-30)/2 + 37);
    mvwprintw(attr_win, 0, 2, "| Attributes |");
    int attr_vals[4] = {player->get_strength(), player->get_defense(), player->get_dexterity(), player->get_intelligence()};
    for(int i = 0; i < text.size(); ++i) {
        std::string temp = text.at(i) + ":  " + std::to_string(attr_vals[i]); 
        mvwprintw(attr_win, i+1, 1, temp.c_str());
    }
    std::string points_avail = "Points Available:  " + std::to_string(player->get_attribute_points());
    mvwprintw(attr_win, 6, 1, points_avail.c_str());
    wrefresh(attr_win);

    return attr_win;
}

WINDOW* ui::render_lobby_stats(std::vector<std::string>& text, stats::character* player, int termheight, int termwidth) {
    WINDOW* stats_win = create_newwin(10, 30, (termheight - 10)/2 + 7, (termwidth-30)/2 + 37);
    mvwprintw(stats_win, 0, 2, "| Stats |");
    int stat_vals[8] = {player->get_level(), player->get_hp(), player->get_magic_power(), player->get_physical_att(),
                        player->get_magic_att(), player->get_accuracy(), player->get_block_rate(), player->get_dodge_rate()}; 
    for(int i = 0; i < text.size(); ++i) {
        std::string temp = text.at(i) + ":  " + std::to_string(stat_vals[i]);
        if(i >= 5) {
            temp += "%";
        }
        mvwprintw(stats_win, i+1, 1, temp.c_str());
    }
    wrefresh(stats_win);

    return stats_win;
}

WINDOW* ui::render_lobby_enemy_stats(std::vector<std::string>& text, stats::enemy* next_enemy, int termheight, int termwidth) {
    WINDOW* enemy_stats_win = create_newwin(10, 30, (termheight - 10)/2 - 8, (termwidth-30)/2 - 37);
    mvwprintw(enemy_stats_win, 0, 2, "| Enemy Stats |");
    int stat_vals[8] = {next_enemy->get_level(), next_enemy->get_hp(), next_enemy->get_magic_power(), next_enemy->get_physical_att(),
                        next_enemy->get_magic_att(), next_enemy->get_accuracy(), next_enemy->get_block_rate(), next_enemy->get_dodge_rate()}; 
    for(int i = 0; i < text.size(); ++i) {
         std::string temp = text.at(i) + ":  " + std::to_string(stat_vals[i]);
        if(i >= 5) {
            temp += "%";
        }
        mvwprintw(enemy_stats_win, i+1, 1, temp.c_str());
    }
    wrefresh(enemy_stats_win);

    return enemy_stats_win;
}

WINDOW* ui::render_lobby_exp_bar(stats::character* player, int termheight, int termwidth) {
    WINDOW* exp_bar = create_newwin(3, 30, (termheight - 3)/2, (termwidth-30)/2 + 37);
    std::string exp_label = "| Exp: " + std::to_string(player->get_exp()) + "/" + std::to_string(player->get_exp_needed()) + " |";
    mvwprintw(exp_bar, 0, 2, exp_label.c_str());
   // mvwprintw(exp_bar, 1, 15 - temp.size()/2, temp.c_str());
    int exp_progress = player->get_exp() * 28 / player->get_exp_needed();
    std::string exp_bar_fill;
    for(int i = 0; i < exp_progress; ++i) {
        exp_bar_fill += "#";
    }
    mvwprintw(exp_bar, 1, 1, exp_bar_fill.c_str());

    wrefresh(exp_bar);
    return exp_bar;
}

WINDOW* ui::render_lobby_skills(std::vector<std::string>& text, stats::character* player, int termheight, int termwidth) {
    WINDOW* skills = create_newwin(25, 35, (termheight - 25)/2, (termwidth-35)/2);
    mvwprintw(skills, 0, 2, "| Skills |");
    std::vector<stats::Ultimate> skill_set = player->get_skill_set();
    for(int i = 0; i < skill_set.size(); ++i) {
        mvwprintw(skills, (i*6)+1, 1, (skill_set.at(i).name).c_str());
        if(player->get_skill_id() == i){
            mvwprintw(skills, (i*6)+1, 24, "[Selected]");
        }
        if(skill_set.at(i).dmg_type) {
            mvwprintw(skills, (i*6)+2, 1, "  Physical Atk");
        }else {
            mvwprintw(skills, (i*6)+2, 1, "  Magic Atk");
        }
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << skill_set.at(i).dmg_multiplier;
        std::string temp = "    Dmg Multiplier:  " + stream.str();
        mvwprintw(skills, (i*6)+3, 1, temp.c_str());
        temp = "    Atk Count:  " + std::to_string(skill_set.at(i).atk_count);
        mvwprintw(skills, (i*6)+4, 1, temp.c_str());
        temp = "    Mana Cost:  " + std::to_string(skill_set.at(i).mana_cost);
        mvwprintw(skills, (i*6)+5, 1, temp.c_str());
        if(i != skill_set.size() - 1) {
            mvwprintw(skills, (i*6)+6, 1, "---------------------------------");
        }
    }

    wrefresh(skills);
    return skills;
}

WINDOW* ui::render_combat_player_stats(std::vector<std::string>& text, std::vector<int> player_resources, stats::character* player, int termheight, int termwidth){
    WINDOW* stats = create_newwin(10, 30, (termheight - 10)/2 - 8, (termwidth-30)/2 - 37);
    mvwprintw(stats, 0, 2, "| My Stats |");
    int stat_vals[8] = {player->get_level(), player_resources.at(0), player_resources.at(1), player->get_physical_att(),
                        player->get_magic_att(), player->get_accuracy(), player->get_block_rate(), player->get_dodge_rate()}; 
    for(int i = 0; i < text.size(); ++i) {
         std::string temp = text.at(i) + ":  " + std::to_string(stat_vals[i]);
        if(i >= 5) {
            temp += "%";
        }
        mvwprintw(stats, i+1, 1, temp.c_str());
    }
    wrefresh(stats);

    return stats;
}


WINDOW* ui::render_combat_enemy_stats(std::vector<std::string>& text, std::vector<int> enemy_resources, stats::enemy* next_enemy, int termheight, int termwidth) {
    WINDOW* enemy_stats_win = create_newwin(10, 30, (termheight - 10)/2 - 8, (termwidth-30)/2 + 37);
    mvwprintw(enemy_stats_win, 0, 2, "| Enemy Stats |");
    int stat_vals[8] = {next_enemy->get_level(), enemy_resources.at(0), enemy_resources.at(1), next_enemy->get_physical_att(),
                        next_enemy->get_magic_att(), next_enemy->get_accuracy(), next_enemy->get_block_rate(), next_enemy->get_dodge_rate()}; 
    for(int i = 0; i < text.size(); ++i) {
         std::string temp = text.at(i) + ":  " + std::to_string(stat_vals[i]);
        if(i >= 5) {
            temp += "%";
        }
        mvwprintw(enemy_stats_win, i+1, 1, temp.c_str());
    }
    wrefresh(enemy_stats_win);

    return enemy_stats_win;
}

WINDOW* ui::render_combat_menu(std::vector<std::string>& text, int termheight, int termwidth) {
    // main lobby menu window
    WINDOW* menu_win = create_newwin(10, 30, (termheight - 10)/2 + 7, (termwidth-30)/2 - 37);
    for(int i = 0; i < text.size(); ++i) {
        mvwprintw(menu_win, i+1, 1, text.at(i).c_str());
    }
    wrefresh(menu_win);

    return menu_win;
}

WINDOW* ui::render_combat_log(std::deque<std::string> combat_log, int termheight, int termwidth) {
    WINDOW* combat_log_win = create_newwin(25, 35, (termheight - 25)/2, (termwidth-35)/2);

    mvwprintw(combat_log_win, 0, 2, "| Combat Log |"); 
    for(int i = 0; i < combat_log.size(); ++i) {
        mvwprintw(combat_log_win, i+1, 1, combat_log.at(i).c_str());
    }
    wrefresh(combat_log_win);

    return combat_log_win;
}

WINDOW* ui::render_combat_defeat(int termheight, int termwidth) {
    WINDOW* defeat_win = create_newwin(20, 120, (termheight - 20)/2, (termwidth-120)/2);
    mvwprintw(defeat_win, 9, 57, "Defeat");

    wrefresh(defeat_win);
    return defeat_win;
}

WINDOW* ui::render_combat_victory(int exp_aquired, int termheight, int termwidth) {
    WINDOW* victory_win = create_newwin(20, 120, (termheight - 20)/2, (termwidth-120)/2);
    mvwprintw(victory_win, 9, 57, "Victory");
    std::string temp = "Exp gained: " + std::to_string(exp_aquired);
    mvwprintw(victory_win, 11, 53, temp.c_str());

    wrefresh(victory_win);
    return victory_win;

}

WINDOW* ui::render_background(int termheight, int termwidth) {
    WINDOW* background = newwin(termheight, termwidth, 0, 0);

    // generate game logo (ascii art aquired from https://www.asciiart.eu/)
    std::vector<std::string> game_logo;
    game_logo.push_back("  _____  _____   _____ ____        _   _   _  ");     
    game_logo.push_back(" |  __ \\|  __ \\ / ____|  _ \\      | | | | | |  ");     
    game_logo.push_back(" | |__) | |__) | |  __| |_) | __ _| |_| |_| | ___ ");
    game_logo.push_back(" |  _  /|  ___/| | |_ |  _ < / _` | __| __| |/ _ \\  ");
    game_logo.push_back(" | | \\ \\| |    | |__| | |_) | (_| | |_| |_| |  __/  ");
    game_logo.push_back(" |_|  \\_\\_|     \\_____|____/ \\__,_|\\__|\\__|_|\\___|  ");

    for(int i = 0; i < game_logo.size(); ++i) {
        mvwprintw(background, 5+i, (termwidth - 50)/2, game_logo.at(i).c_str());
    }

    // generate castle (ascii art aquired from https://www.asciiart.eu/)
    std::vector<std::string> castle_art;
    castle_art.push_back("                                                   !_");
    castle_art.push_back("                                                   |*~=-.,");
    castle_art.push_back("                                                   |_,-'`");
    castle_art.push_back("                                                   |");
    castle_art.push_back("                                                   |");
    castle_art.push_back("                                                  /^\\ ");
    castle_art.push_back("                    !_                           /   \\ ");
    castle_art.push_back("                    |*`~-.,                     /,    \\ ");
    castle_art.push_back("                    |.-~^`                     /#\"     \\ ");
    castle_art.push_back("                    |                        _/##_   _  \\_ ");
    castle_art.push_back("               _   _|  _   _   _            [ ]_[ ]_[ ]_[ ] ");
    castle_art.push_back("              [ ]_[ ]_[ ]_[ ]_[ ]            |_=_-=_ - =_| ");
    castle_art.push_back("            !_ |_=_ =-_-_  = =_|           !_ |=_= -    | ");
    castle_art.push_back("            |*`--,_- _        |            |*`~-.,= []  | ");
    castle_art.push_back("            |.-'|=     []     |   !_       |_.-\"`_-     | ");
    castle_art.push_back("            |   |_=- -        |   |*`~-.,  |  |=_-      | ");
    castle_art.push_back("           /^\\  |=_= -        |   |_,-~`  /^\\ |_ - =[]  | ");
    castle_art.push_back("       _  /   \\_|_=- _   _   _|  _|  _   /   \\|=_-      | ");
    castle_art.push_back("      [ ]/,    \\[ ]_[ ]_[ ]_[ ]_[ ]_[ ]_/,    \\[ ]=-    | ");
    castle_art.push_back("       |/#\"     \\_=-___=__=__- =-_ -=_ /#\"     \\| _ []  | ");
    castle_art.push_back("      _/##_   _  \\_-_ =  _____       _/##_   _  \\_ -    |\\ ");
    castle_art.push_back("     [ ]_[ ]_[ ]_[ ]=_0~{_ _ _}~0   [ ]_[ ]_[ ]_[ ]=-   | \\ ");
    castle_art.push_back("     |_=__-_=-_  =_|-=_ |  ,  |     |_=-___-_ =-__|_    |  \\ ");
    castle_art.push_back("      | _- =-     |-_   | ((* |      |= _=       | -    |___\\ ");
    castle_art.push_back("      |= -_=      |=  _ |  `  |      |_-=_       |=_    |/+\\| ");
    castle_art.push_back("      | =_  -     |_ = _ `-.-`       | =_ = =    |=_-   ||+|| ");
    castle_art.push_back("      |-_=- _     |=_   =            |=_= -_     |  =   ||+|| ");
    castle_art.push_back("      |=_- /+\\    | -=               |_=- /+\\    |=_    |^^^| ");
    castle_art.push_back("      |=_ |+|+|   |= -  -_,--,_      |_= |+|+|   |  -_  |=  | ");
    castle_art.push_back("      |  -|+|+|   |-_=  / |  | \\     |=_ |+|+|   |-=_   |_-/ ");
    castle_art.push_back("      |=_=|+|+|   | =_= | |  | |     |_- |+|+|   |_ =   |=/ ");
    castle_art.push_back("      | _ ^^^^^   |= -  | |  <&>     |=_=^^^^^   |_=-   |/ ");
    castle_art.push_back("      |=_ =       | =_-_| |  | |     |   =_      | -_   | ");
    castle_art.push_back("      |_=-_       |=_=  | |  | |     |=_=        |=-    | ");
    castle_art.push_back("^^^^^^^^^^`^`^^`^`^`^^^""""""""^`^^``^^`^^`^^`^`^``^`^``^``^^");

    for(int i = 0; i < castle_art.size(); ++i) {
        mvwprintw(background, (termheight-36)+i, termwidth - 70, castle_art.at(i).c_str());
    }
    
    // generate land (ascii art aquired from https://www.asciiart.eu/)
    std::vector<std::string> land_art;
    land_art.push_back("              __                            ____   ");
    land_art.push_back("     ____--`~    '--~~__            __ ----~    ~`---,              ___ ");
    land_art.push_back("-~--~                   ~---__ ,--~'                  ~~----_____-~'   `~----~~");

    for(int i = 0; i < land_art.size(); ++i) {
        mvwprintw(background, (termheight-4)+i, termwidth - 149, land_art.at(i).c_str());
    }
    
    wrefresh(background);
    return background;
}

                                                  
