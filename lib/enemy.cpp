#include "stats/enemy.hpp"
#include <random>


stats::enemy::enemy() {}

stats::enemy::enemy(const int level) {
    level_ = level;
    exp_ = 8 + (level_ * 2);
    // get attribute values
    attributes_ = architype_builder_();
    stats::calc::calc_statistics(attributes_, statistics_, level_);
}

stats::Attributes stats::enemy::get_attributes() const { return attributes_; }
int stats::enemy::get_strength() const { return attributes_.strength; }
int stats::enemy::get_defense() const { return attributes_.defense; }
int stats::enemy::get_dexterity() const { return attributes_.dexterity; }
int stats::enemy::get_intelligence() const { return attributes_.intelligence; }

stats::Statistics stats::enemy::get_statistics() const { return statistics_; }
int stats::enemy::get_hp() const { return statistics_.hp; }
int stats::enemy::get_physical_att() const { return statistics_.physical_att; }
int stats::enemy::get_magic_power() const { return statistics_.magic_power; }
int stats::enemy::get_magic_att() const { return statistics_.magic_att; }
int stats::enemy::get_accuracy() const { return statistics_.accuracy; }
int stats::enemy::get_block_rate() const { return statistics_.block_rate; }
int stats::enemy::get_dodge_rate() const { return statistics_.dodge_rate; }

int stats::enemy::get_level() const { return level_; }
int stats::enemy::get_exp() const { return exp_; }
int stats::enemy::get_archtype() const { return archtype_; }

stats::Attributes stats::enemy::architype_builder_() {
    // randomly select a integer number between 1 and 3 refering to architype to be built
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 3);
    stats::Attributes attr;
    switch(distr(gen)) {
        case 1:
            // create warrior
            archtype_ = 1;
            build_warrior_(attr);
            ultimate_skill_ = {"warrior skill", true, 1.5, 1, 5};
            break;
        case 2:
            // create rogue
            archtype_ = 2;
            build_rogue_(attr);
            ultimate_skill_ = {"rogue skill", true, 0.125, 10, 5};
            break;
        case 3:
            // create mage
            archtype_ = 3;
            build_mage_(attr);
            ultimate_skill_ = {"mage skill", false, 0.2, 10, 10};
            break;
        default:
            // if here error occurred, throw a exception
            break;
    }

    return attr;
}


void stats::enemy::build_warrior_(Attributes& attr) {
    int attr_points = level_ * 3;
    for(int i = 0; i<attr_points; ++i) {
        if(attr.strength == 30) {
            if(attr.defense == 30) {
                if(attr.dexterity == 30) {
                    attr.intelligence++;
                }
                else {
                    attr.dexterity++;
                }
            }
            else {
                attr.defense++;
            }

        }
        else {
            // 4 points strength, 2 points defense
            switch(i%6) {
                case 0:
                case 2:
                case 3:
                case 5:
                    attr.strength++;
                    break;
                case 1:
                case 4:
                    attr.defense++;
                    break;
                default:
                    // error if enters this case
                    break;       
             }
        }
    }
}

void stats::enemy::build_rogue_(Attributes& attr) {
    int attr_points = level_ * 3;
    for(int i = 0; i<attr_points; ++i) {
        if(attr.dexterity == 30) {
            if(attr.strength == 30) {
                if(attr.defense == 30) {
                    attr.intelligence++;
                }
                else {
                    attr.defense++;
                }
            }
            else {
                attr.strength++;
            }
        }
        else {
            // 4 points dexterity, 2 points strength
            switch(i%6) {
                case 0:
                case 2:
                case 3:
                case 5:
                    attr.dexterity++;
                    break;
                case 1:
                case 4:
                    attr.strength++;
                    break;
                default:
                    // error if enters this case
                    break;       
            }
        }
    }

}

void stats::enemy::build_mage_(Attributes& attr) {
    int attr_points = level_ * 3;
    for(int i = 0; i<attr_points; ++i) {
        if(attr.intelligence == 30) {
            if(attr.dexterity == 30) {
                if(attr.strength == 30) {
                    attr.defense++;
                }
                else {
                    attr.strength++;
                }
            }
            else {
                attr.dexterity++;
            }
        }
        else {
            // 5 points intelligence, 1 points dexterity
            switch(i%6) {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                    attr.intelligence++;
                    break;
                case 5:
                    attr.dexterity++;
                    break;
                default:
                    // error if enters this case
                    break;       
            }
        }
    }

}

bool stats::enemy::get_skill_dmg_type() const { return ultimate_skill_.dmg_type; }
float stats::enemy::get_skill_dmg_multiplier() const { return ultimate_skill_.dmg_multiplier; }
int stats::enemy::get_skill_atk_count() const { return ultimate_skill_.atk_count; }
int stats::enemy::get_skill_mana_cost() const { return ultimate_skill_.mana_cost; }