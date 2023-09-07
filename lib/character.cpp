#include "stats/character.hpp"
#include "tools/json_tools.hpp"
#include <utility>

// constructs level 1 character object
stats::character::character() {
    level_ = 1;
    exp_ = 0;
    exp_needed_ = 10;
    attribute_points_ = 5;
    attributes_.strength = 1;
    attributes_.defense = 1;
    attributes_.dexterity = 1;
    attributes_.intelligence = 1;
    ultimate_skill_id_ = 0;
    stats::calc::calc_statistics(attributes_, statistics_, level_);
    collect_ultimate_skills_();
    
}

stats::character::character(const Attributes attr, std::string character_name, int level, int ulti_skill_id,
                            int exp, int attr_points, int exp_needed) {
    level_ = level;
    exp_ = exp;
    exp_needed_ = exp_needed;
    attributes_ = attr;
    ultimate_skill_id_ = ulti_skill_id;
    character_name_ = character_name;
    attribute_points_ = attr_points;
    stats::calc::calc_statistics(attributes_, statistics_, level_);
    collect_ultimate_skills_();
}


stats::Attributes stats::character::get_attributes() const { return attributes_; }
int stats::character::get_strength() const { return attributes_.strength; }
int stats::character::get_defense() const { return attributes_.defense; }
int stats::character::get_dexterity() const { return attributes_.dexterity; }
int stats::character::get_intelligence() const { return attributes_.intelligence; }

stats::Statistics stats::character::get_statistics() const { return statistics_; }
int stats::character::get_hp() const { return statistics_.hp; }
int stats::character::get_physical_att() const { return statistics_.physical_att; }
int stats::character::get_magic_power() const { return statistics_.magic_power; }
int stats::character::get_magic_att() const { return statistics_.magic_att; }
int stats::character::get_accuracy() const { return statistics_.accuracy; }
int stats::character::get_block_rate() const { return statistics_.block_rate; }
int stats::character::get_dodge_rate() const { return statistics_.dodge_rate; }

int stats::character::get_level() const { return level_; }
int stats::character::get_exp() const { return exp_; }
int stats::character::get_exp_needed() const { return exp_needed_; }
int stats::character::get_attribute_points() const { return attribute_points_; }
int stats::character::get_skill_id() const { return ultimate_skill_id_; }
int stats::character::get_save_slot() const { return save_slot_; }
std::string stats::character::get_character_name() const { return character_name_; }

void stats::character::set_skill_id(int new_id) { ultimate_skill_id_ = new_id; }
void stats::character::set_save_slot(int slot_id) { save_slot_ = slot_id; }
void stats::character::set_character_name(std::string name) { character_name_ = name; }


std::vector<stats::Ultimate> stats::character::get_skill_set() const { return ultimate_skills_; }
std::string stats::character::get_skill_name() const { return ultimate_skills_.at(ultimate_skill_id_).name; }
bool stats::character::get_skill_dmg_type() const { return ultimate_skills_.at(ultimate_skill_id_).dmg_type; }
float stats::character::get_skill_dmg_multiplier() const { return ultimate_skills_.at(ultimate_skill_id_).dmg_multiplier; }
int stats::character::get_skill_atk_count() const { return ultimate_skills_.at(ultimate_skill_id_).atk_count; }
int stats::character::get_skill_mana_cost() const { return ultimate_skills_.at(ultimate_skill_id_).mana_cost; }

void stats::character::assign_attribute_point(const int attr_id) {
    if(attribute_points_ > 0) {
        switch(attr_id) {
            case 0:
                if(attributes_.strength < 30) {
                    attributes_.strength++;
                    attribute_points_--;
                }
                break;
            case 1:
                if(attributes_.defense < 30) {
                    attributes_.defense++;
                    attribute_points_--;
                }
                break;
            case 2:
                if(attributes_.dexterity < 30) {
                    attributes_.dexterity++;
                    attribute_points_--;
                }
                break;
            case 3:
                if(attributes_.intelligence < 30) {
                    attributes_.intelligence++;
                    attribute_points_--;
                }
                break;
            default:
                // throw exception, should never enter this case unless error occurred
                break;
        }
        stats::calc::calc_statistics(attributes_, statistics_, level_);
    }
}

void stats::character::assign_ultimate_skill(const int skill_id) { ultimate_skill_id_ = skill_id; }

void stats::character::add_exp(const int exp_aquired) {
    exp_ += exp_aquired;
    while(exp_ >= exp_needed_) {
        level_up_();
    }
}

void stats::character::level_up_() {
    if(level_ < 35) {
        attribute_points_ += 3;
        level_ += 1;
        stats::calc::calc_statistics(attributes_, statistics_, level_);
    }
    exp_ -= exp_needed_;
    exp_needed_ = (int)(exp_needed_ * 1.32);
}


void stats::character::collect_ultimate_skills_() {
    std::string file_path = "data/skills/skills.JSON";
    std::vector<std::vector<std::pair<std::string, std::string>>> skills = tools::parse_skills(file_path);
    
    for(int i = 0; i<skills.size(); ++i) {
        Ultimate temp;
        for(int j =0; j<skills.at(i).size(); ++j) {
            switch(j) {
                case 0:
                    temp.name = skills.at(i).at(j).second;
                    break;
                case 1:
                    if(skills.at(i).at(j).second == "Physical Atk") {
                        temp.dmg_type = true;
                    } 
                    else if(skills.at(i).at(j).second == "Magic Atk") {
                        temp.dmg_type = false;
                    }
                    break;
                case 2:
                    temp.dmg_multiplier = stof(skills.at(i).at(j).second);
                    break;
                case 3:
                    temp.atk_count = stoi(skills.at(i).at(j).second);
                    break;
                case 4:
                    temp.mana_cost = stoi(skills.at(i).at(j).second);
                    break;
            }   
        }
        ultimate_skills_.push_back(temp);
    }

}
