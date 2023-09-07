#include "stats/calculations.hpp"

void stats::calc::calc_statistics(const Attributes& attributes, Statistics& statistics, int level) {
    // calculates the statistic values based on assigned attributes:

    statistics.hp = 100 + ((level-1) * 10) + (int)(attributes.defense / 2);
    statistics.physical_att = 1 + (int)(attributes.strength) + (int)(attributes.dexterity / 2.5);
    statistics.magic_power = 20 + (int)(attributes.intelligence / 1.5);
    statistics.magic_att = 1 + (int)(attributes.intelligence / 1.5);

    // accuracy is a value between 1 and 100 relating to percentage value (might be worth adding checks and truncating to 100 if over)
    statistics.accuracy = 1 + ((level-1)) + (int)((attributes.dexterity * 2) * 0.5);
    statistics.block_rate = 1 + ((level-1)) + (int)((attributes.defense * 2) * 0.9);
    statistics.dodge_rate = 1 + ((level-1)) + (int)((attributes.dexterity * 2) * 0.9);

}