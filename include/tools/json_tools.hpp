#ifndef json_tools_hpp
#define json_tools_hpp
#include <string>
#include <vector>
#include <utility>
#include "stats/save.hpp"

namespace tools {
    std::vector<std::vector<std::pair<std::string, std::string>>> parse_skills(std::string file_path);
    std::vector<std::vector<std::pair<std::string, std::string>>> parse_saves(std::string file_path);
    std::vector<stats::Save> load_save_data(std::string file_path);
    void save_to_json(std::vector<std::vector<std::pair<std::string, std::string>>> saves, std::string file_path);
    void save_game(std::vector<stats::Save> data, std::string file_path);

}


#endif