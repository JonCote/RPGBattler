#ifndef calculations_hpp
#define calculations_hpp
#include "attributes.hpp"
#include "statistics.hpp"

namespace stats {
 namespace calc {
    // calculate statistics based on attributes
    void calc_statistics(const Attributes& attributes, Statistics& statistics, int level);


 }
}


#endif