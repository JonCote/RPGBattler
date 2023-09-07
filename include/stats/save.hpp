#ifndef save_hpp
#define save_hpp
#include <string>
#include "stats/attributes.hpp"

namespace stats {
    struct Save {
        std::string name;
        int level;
        int exp;
        int exp_needed;
        int skill_id;
        int attr_points;
        Attributes attributes;
        std::string save_dt;
    };
}


#endif