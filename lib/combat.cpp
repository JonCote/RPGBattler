#include "stats/combat.hpp"
#include <random>


// block/dodge success, return true
bool stats::block_check(int rate) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    if(distr(gen) <= rate) {
        return true;
    }
    return false;
}

bool stats::dodge_check(int dodge_rate, int atker_acc) {
    int rate = dodge_rate - atker_acc;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    if(rate > 0) {
        if(distr(gen) <= rate) {
            return true;
        }
    }
    return false;
}


std::vector<std::string> stats::player_attack(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy) {
    std::vector<std::string> combat_log;
    int player_dmg = 0;
    if(player->get_magic_att() > player->get_physical_att()) {
        player_dmg = player->get_magic_att();
    }
    else {
        player_dmg = player->get_physical_att();
    }


    if(enemy_action == 0) {
        // atk vs atk
        int enemy_dmg = 0;
        if(enemy->get_magic_att() > enemy->get_physical_att()) {
            enemy_dmg = enemy->get_magic_att();
        }
        else {
            enemy_dmg = enemy->get_physical_att();
        }
        player_resources.at(0) -= enemy_dmg;
        enemy_resources.at(0) -= player_dmg;
        std::string temp = "Player Attack dealt: " + std::to_string(player_dmg) + " damage";
        combat_log.push_back(temp);
        temp = "Enemy Attack dealt: " + std::to_string(enemy_dmg) + " damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 1) {
        // atk vs block
        if(!block_check(enemy->get_block_rate())) {
            enemy_resources.at(0) -= player_dmg;
            std::string temp = "Player Attack dealt: " + std::to_string(player_dmg) + " damage";
            combat_log.push_back(temp);
            temp = "Enemy Blocked: 0 damage";
            combat_log.push_back(temp);
        }
        else {
            std::string temp = "Player Attack dealt: 0 damage";
            combat_log.push_back(temp);
            temp = "Enemy Blocked: " + std::to_string(player_dmg) + " damage";
            combat_log.push_back(temp);
        }
    }
    else if(enemy_action == 2) {
        // atk vs dodge
        if(!dodge_check(enemy->get_dodge_rate(), player->get_accuracy())) {
            enemy_resources.at(0) -= player_dmg;
            std::string temp = "Player Attack dealt: " + std::to_string(player_dmg) + " damage";
            combat_log.push_back(temp);
            temp = "Enemy Dodged: 0 damage";
            combat_log.push_back(temp);
        }
        else {
            std::string temp = "Player Attack dealt: 0 damage";
            combat_log.push_back(temp);
            temp = "Enemy Dodged: " + std::to_string(player_dmg) + " damage";
            combat_log.push_back(temp);
        }
    }
    else if(enemy_action == 3) {
        // atk vs skill
        enemy_resources.at(0) -= player_dmg;

        enemy_resources.at(1) -= enemy->get_skill_mana_cost();
        float dmg_total = 0;
        for(int i = 0; i < enemy->get_skill_atk_count(); ++i) {
            if(enemy->get_skill_dmg_type()) {
                dmg_total += (enemy->get_physical_att() * enemy->get_skill_dmg_multiplier());
            }
            else {
                dmg_total += (enemy->get_magic_att() * enemy->get_skill_dmg_multiplier());
            }
        }
        player_resources.at(0) -= (int)(dmg_total);
        std::string temp = "Player Attack dealt: " + std::to_string(player_dmg) + " damage";
        combat_log.push_back(temp);
        temp = "Enemy Spell dealt: " + std::to_string((int)dmg_total) + " damage";
        combat_log.push_back(temp);
    }

    return combat_log;
}

std::vector<std::string> stats::player_block(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy) {
    std::vector<std::string> combat_log;
    if(enemy_action == 0) {
        // block vs atk
        int enemy_dmg = 0;
        if(enemy->get_magic_att() > enemy->get_physical_att()) {
            enemy_dmg = enemy->get_magic_att();
        }
        else {
            enemy_dmg = enemy->get_physical_att();
        }
        if(!block_check(player->get_block_rate())) {
            player_resources.at(0) -= enemy_dmg;
            std::string temp = "Player Blocked: 0 damage";
            combat_log.push_back(temp);
            temp = "Enemy Attack dealt: " + std::to_string(enemy_dmg) + " damage";
            combat_log.push_back(temp);
        }
        else {
            std::string temp = "Player Blocked: " + std::to_string(enemy_dmg) + " damage";
            combat_log.push_back(temp);
            temp = "Enemy Attack dealt: 0 damage";
            combat_log.push_back(temp);
        }
    }
    else if(enemy_action == 1) {
        // block vs block
        std::string temp = "Player Blocked: 0 damage";
        combat_log.push_back(temp);
        temp = "Enemy Blocked: 0 damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 2) {
        // block vs dodge
        std::string temp = "Player Blocked: 0 damage";
        combat_log.push_back(temp);
        temp = "Enemy Dodged: 0 damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 3) {
        // block vs skill
        enemy_resources.at(1) -= enemy->get_skill_mana_cost();
        float dmg_total = 0;
        float block_total = 0;
        for(int i = 0; i < enemy->get_skill_atk_count(); ++i) {
            if(!block_check(player->get_block_rate())) {
                if(enemy->get_skill_dmg_type()) {
                    dmg_total += (enemy->get_physical_att() * enemy->get_skill_dmg_multiplier());
                }
                else {
                    dmg_total += (enemy->get_magic_att() * enemy->get_skill_dmg_multiplier());
                }
            }
            else {
                if(enemy->get_skill_dmg_type()) {
                    block_total += (enemy->get_physical_att() * enemy->get_skill_dmg_multiplier());
                }
                else {
                    block_total += (enemy->get_magic_att() * enemy->get_skill_dmg_multiplier());
                }
            }
        }
        player_resources.at(0) -= (int)dmg_total;
        std::string temp = "Player Blocked: " + std::to_string((int)block_total) + " Spell damage";
        combat_log.push_back(temp);
        temp = "Enemy Spell dealt: " + std::to_string((int)dmg_total) + " damage";
        combat_log.push_back(temp);
    }
    return combat_log;
}

std::vector<std::string> stats::player_dodge(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy) {
    std::vector<std::string> combat_log;
    if(enemy_action == 0) {
        // dodge vs atk
        int enemy_dmg = 0;
        if(enemy->get_magic_att() > enemy->get_physical_att()) {
            enemy_dmg = enemy->get_magic_att();
        }
        else {
            enemy_dmg = enemy->get_physical_att();
        }
        if(!dodge_check(player->get_dodge_rate(), enemy->get_accuracy())) {
            player_resources.at(0) -= enemy_dmg;
            std::string temp = "Player Dodged: 0 damage";
            combat_log.push_back(temp);
            temp = "Enemy Attack dealt: " + std::to_string(enemy_dmg) + " damage";
            combat_log.push_back(temp);
        }
        else {
            std::string temp = "Player Dodged: " + std::to_string(enemy_dmg) + " damage";
            combat_log.push_back(temp);
            temp = "Enemy Attack dealt: 0 damage";
            combat_log.push_back(temp);
        }
    }
    else if(enemy_action == 1) {
        // dodge vs block
        std::string temp = "Player Dodged: 0 damage";
        combat_log.push_back(temp);
        temp = "Enemy Blocked: 0 damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 2) {
        // dodge vs dodge
        std::string temp = "Player Dodged: 0 damage";
        combat_log.push_back(temp);
        temp = "Enemy Dodged: 0 damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 3) {
        // dodge vs skill
        enemy_resources.at(1) -= enemy->get_skill_mana_cost();
        float dmg_total = 0;
        float dodge_total = 0;
        for(int i = 0; i < enemy->get_skill_atk_count(); ++i) {
            if(!dodge_check(player->get_dodge_rate(), enemy->get_accuracy())) {
                if(enemy->get_skill_dmg_type()) {
                    dmg_total += (enemy->get_physical_att() * enemy->get_skill_dmg_multiplier());
                }
                else {
                    dmg_total += (enemy->get_magic_att() * enemy->get_skill_dmg_multiplier());
                }
            }
            else {
                if(enemy->get_skill_dmg_type()) {
                    dodge_total += (enemy->get_physical_att() * enemy->get_skill_dmg_multiplier());
                }
                else {
                    dodge_total += (enemy->get_magic_att() * enemy->get_skill_dmg_multiplier());
                }
            }
        }
        player_resources.at(0) -= (int)dmg_total;
        std::string temp = "Player Dodged: " + std::to_string((int)dodge_total) + " Spell damage";
        combat_log.push_back(temp);
        temp = "Enemy Spell dealt: " + std::to_string((int)dmg_total) + " damage";
        combat_log.push_back(temp);
    }
    return combat_log;
}

std::vector<std::string> stats::player_skill(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy) {
    std::vector<std::string> combat_log;
    if(enemy_action == 0) {
        // skill vs atk
        int enemy_dmg = 0;
        if(enemy->get_magic_att() > enemy->get_physical_att()) {
            enemy_dmg = enemy->get_magic_att();
        }
        else {
            enemy_dmg = enemy->get_physical_att();
        }
        player_resources.at(0) -= enemy_dmg;
        player_resources.at(1) -= player->get_skill_mana_cost();
        float dmg_total = 0;
        for(int i = 0; i < player->get_skill_atk_count(); ++i) {
            if(player->get_skill_dmg_type()) {
                dmg_total += (player->get_physical_att() * player->get_skill_dmg_multiplier());
            }
            else {
                dmg_total += (player->get_magic_att() * player->get_skill_dmg_multiplier());
            }
        }
        enemy_resources.at(0) -= (int)dmg_total;
        std::string temp = "Player Spell dealt: " + std::to_string((int)dmg_total) + " damage";
        combat_log.push_back(temp);
        temp = "Enemy Attack dealt: " + std::to_string((int)enemy_dmg) + " damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 1) {
        // skill vs block
        player_resources.at(1) -= player->get_skill_mana_cost();
        float dmg_total = 0;
        float block_total = 0;
        for(int i = 0; i < player->get_skill_atk_count(); ++i) {
            if(!block_check(enemy->get_dodge_rate())) {
                if(player->get_skill_dmg_type()) {
                    dmg_total += (player->get_physical_att() * player->get_skill_dmg_multiplier());
                }
                else {
                    dmg_total += (player->get_magic_att() * player->get_skill_dmg_multiplier());
                }
            }
            else {
                if(player->get_skill_dmg_type()) {
                    block_total += (player->get_physical_att() * player->get_skill_dmg_multiplier());
                }
                else {
                    block_total += (player->get_magic_att() * player->get_skill_dmg_multiplier());
                }
            }
        }
        enemy_resources.at(0) -= (int)dmg_total;
        std::string temp = "Player Spell dealt: " + std::to_string((int)dmg_total) + " damage";
        combat_log.push_back(temp);
        temp = "Enemy Blocked: " + std::to_string((int)block_total) + " Spell damage";
        combat_log.push_back(temp);

    }
    else if(enemy_action == 2) {
        // skill vs dodge
        player_resources.at(1) -= player->get_skill_mana_cost();
        float dmg_total = 0;
        float dodge_total = 0;
        for(int i = 0; i < player->get_skill_atk_count(); ++i) {
            if(!dodge_check(enemy->get_dodge_rate(), player->get_accuracy())) {
                if(player->get_skill_dmg_type()) {
                    dmg_total += (player->get_physical_att() * player->get_skill_dmg_multiplier());
                }
                else {
                    dmg_total += (player->get_magic_att() * player->get_skill_dmg_multiplier());
                }
            }
            else {
                if(player->get_skill_dmg_type()) {
                    dodge_total += (player->get_physical_att() * player->get_skill_dmg_multiplier());
                }
                else {
                    dodge_total += (player->get_magic_att() * player->get_skill_dmg_multiplier());
                }
            }
        }
        enemy_resources.at(0) -= (int)dmg_total;
        std::string temp = "Player Spell dealt: " + std::to_string((int)dmg_total) + " damage";
        combat_log.push_back(temp);
        temp = "Enemy Dodged: " + std::to_string((int)dodge_total) + " Spell damage";
        combat_log.push_back(temp);
    }
    else if(enemy_action == 3) {
        // skill vs skill
        player_resources.at(1) -= player->get_skill_mana_cost();
        float player_dmg_total = 0;
        float enemy_dmg_total = 0;
        for(int i = 0; i < player->get_skill_atk_count(); ++i) {
            if(player->get_skill_dmg_type()) {
                player_dmg_total += (player->get_physical_att() * player->get_skill_dmg_multiplier());
            }
            else {
                player_dmg_total += (player->get_magic_att() * player->get_skill_dmg_multiplier());
            }
        }
        enemy_resources.at(1) -= enemy->get_skill_mana_cost();
        for(int i = 0; i < enemy->get_skill_atk_count(); ++i) {
            if(enemy->get_skill_dmg_type()) {
                enemy_dmg_total += (enemy->get_physical_att() * enemy->get_skill_dmg_multiplier());
            }
            else {
                enemy_dmg_total += (enemy->get_magic_att() * enemy->get_skill_dmg_multiplier());
            }
        }
        
        enemy_resources.at(0) -= (int)player_dmg_total;
        player_resources.at(0) -= (int)enemy_dmg_total;
        std::string temp = "Player Spell dealt: " + std::to_string((int)player_dmg_total) + " damage";
        combat_log.push_back(temp);
        temp = "Enemy Spell dealt: " + std::to_string((int)enemy_dmg_total) + " damage";
        combat_log.push_back(temp);
    }

    return combat_log;
}

// return action:
//  1: attack
//  2: block
//  3: dodge
//  4: skill
int stats::gen_enemy_action(int enemy_archtype) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> action_num(1, 3);
    switch(enemy_archtype) {
        case 1: // warrior
            switch(action_num(gen)) {
                case 1:
                    return 0;
                    break;
                case 2:
                    return 1;
                    break;
                case 3:
                    return 3;
                    break;
            }
            break;
        case 2: // rogure
            switch(action_num(gen)) {
                case 1:
                    return 0;
                    break;
                case 2:
                    return 2;
                    break;
                case 3:
                    return 3;
                    break;
            }
            break;
        case 3: // mage
            switch(action_num(gen)) {
                case 1:
                    return 0;
                    break;
                case 2:
                    return 3;
                    break;
                case 3:
                    return 3;
                    break;
            }
            break;
    }
    return -1;
}
int stats::gen_enemy_action_noskill(int enemy_archtype) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> action_num(1, 2);
    switch(enemy_archtype) {
        case 1: // warrior
            switch(action_num(gen)) {
                case 1:
                    return 0;
                    break;
                case 2:
                    return 1;
                    break;
            }
            break;
        case 2: // rogure
            switch(action_num(gen)) {
                case 1:
                    return 0;
                    break;
                case 2:
                    return 2;
                    break;
            }
            break;
        case 3: // mage
            return 0;
            break;
    }
    return -1;
}

std::vector<std::string> stats::combat_controller(int player_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy) {
    // determine enemy combat action based on archtype
    int enemy_archtype = enemy->get_archtype();
    int enemy_action;
    if(enemy_resources.at(1) >= enemy->get_skill_mana_cost()) {
        enemy_action = gen_enemy_action(enemy_archtype);
    }else {
        enemy_action = gen_enemy_action_noskill(enemy_archtype);
    }
    if(enemy_action == -1) {
        // error occurred
    }

    std::vector<std::string> combat_log;
    // calculate combat outcome
    switch(player_action) {
        case 0:
            combat_log = player_attack(enemy_action, player_resources, enemy_resources, player, enemy);
            break;
        case 1:
            combat_log = player_block(enemy_action, player_resources, enemy_resources, player, enemy);
            break;
        case 2:
            combat_log = player_dodge(enemy_action, player_resources, enemy_resources, player, enemy);
            break;
        case 3:
            combat_log = player_skill(enemy_action, player_resources, enemy_resources, player, enemy);
            break;
    }
    
    return combat_log;
}

