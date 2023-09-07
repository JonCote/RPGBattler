#ifndef ultimate_skill_hpp
#define ultimate_skill_hpp
#include <string>

namespace stats {
    struct Ultimate {
        std::string name;
        // true = physical damage, false = magic damage
        bool dmg_type;
        float dmg_multiplier;
        int atk_count;
        int mana_cost;
    };
}
#endif