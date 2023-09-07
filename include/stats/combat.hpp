#include <vector>
#include <string>
#include "stats/character.hpp"
#include "stats/enemy.hpp"

namespace stats {
    bool block_check(int rate);
    bool dodge_check(int dodge_rate, int atker_acc);
    std::vector<std::string> player_attack(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy);
    std::vector<std::string> player_block(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy);
    std::vector<std::string> player_dodge(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy);
    std::vector<std::string> player_skill(int enemy_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy);
    int gen_enemy_action(int enemy_archtype);
    int gen_enemy_action_noskill(int enemy_archtype);
    std::vector<std::string> combat_controller(int player_action, std::vector<int>& player_resources, std::vector<int>& enemy_resources, stats::character* player, stats::enemy* enemy);

}