#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "tools/json_tools.hpp"
#include <iostream>
#include <fstream>


namespace pt = boost::property_tree;

std::vector<std::vector<std::pair<std::string, std::string>>> tools::parse_skills(std::string file_path) {
    // Create a root
    pt::ptree root;

    // Load the json file to ptree
    pt::read_json(file_path.c_str(), root);

    // parse JSON array of objects named Skills, each object is independent skill object
    std::vector<std::vector<std::pair<std::string, std::string>>> skills;

    auto it = root.get_child("Skills");
    for(auto it2 = it.begin(); it2 != it.end(); ++it2) {
        std::vector<std::pair<std::string, std::string>> skill;
        for(auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
            std::pair<std::string, std::string> temp(it3->first, it3->second.data());
            skill.push_back(temp);
        }
        skills.push_back(skill);
    }

    return skills;
}


std::vector<std::vector<std::pair<std::string, std::string>>> tools::parse_saves(std::string file_path) {
    // Create a root
    pt::ptree root;

    // Load the json file to ptree
    pt::read_json(file_path.c_str(), root);

    // parse JSON array of objects named Skills, each object is independent skill object
    std::vector<std::vector<std::pair<std::string, std::string>>> saves;

    auto it = root.get_child("Saves");
    for(auto it2 = it.begin(); it2 != it.end(); ++it2) {
        std::vector<std::pair<std::string, std::string>> save;
        for(auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
            std::pair<std::string, std::string> temp(it3->first, it3->second.data());
            save.push_back(temp);
        }
        saves.push_back(save);
    }

    return saves;
}


std::vector<stats::Save> tools::load_save_data(std::string file_path) {
    // collect save data from JSON
    std::vector<std::vector<std::pair<std::string, std::string>>> saves = parse_saves(file_path);
    std::vector<stats::Save> save_data;
    // store collected data
    for(int i = 0; i<saves.size(); ++i) {
        stats::Save temp;
        for(int j = 0; j<saves.at(i).size(); ++j) {
            switch(j) {
                case 0:
                    temp.name = saves.at(i).at(j).second;
                    break;
                case 1:
                    temp.level = stoi(saves.at(i).at(j).second);
                    break;
                case 2:
                    temp.exp = stoi(saves.at(i).at(j).second);
                    break;
                case 3:
                    temp.exp_needed = stoi(saves.at(i).at(j).second);
                    break;
                case 4:
                    temp.skill_id = stoi(saves.at(i).at(j).second);
                    break;
                case 5:
                    temp.attr_points = stoi(saves.at(i).at(j).second);
                    break;
                case 6:
                    temp.attributes.strength = stoi(saves.at(i).at(j).second);
                    break;
                case 7:
                    temp.attributes.defense = stoi(saves.at(i).at(j).second);
                    break;
                case 8:
                    temp.attributes.dexterity = stoi(saves.at(i).at(j).second);
                    break;
                case 9:
                    temp.attributes.intelligence = stoi(saves.at(i).at(j).second);
                    break;
                case 10:
                    temp.save_dt = saves.at(i).at(j).second;
                    break;
            }
        }
        if(temp.level > 30) {
            temp.level = 30;
        }
        if(temp.skill_id > 3) {
            temp.skill_id = 0;
        }
        if(temp.attributes.strength > 30) {
            temp.attributes.strength = 30;
        }
        if(temp.attributes.defense > 30) {
            temp.attributes.defense = 30;
        }
        if(temp.attributes.dexterity > 30) {
            temp.attributes.dexterity = 30;
        }
        if(temp.attributes.intelligence > 30) {
            temp.attributes.intelligence = 30;
        }
        save_data.push_back(temp);
    }

    return save_data;
}


void tools::save_to_json(std::vector<std::vector<std::pair<std::string, std::string>>> saves, std::string file_path) {
    pt::ptree root;

    pt::ptree saves_node;
    for(auto &save : saves) {
        pt::ptree save_node;
        for(auto &field : save) {
            save_node.put(field.first, field.second);
        }
        saves_node.push_back(std::make_pair("", save_node));
    }
    root.put_child("Saves", saves_node);

    std::stringstream ss;
    pt::write_json(ss, root);
    std::string out = ss.str();

    std::ofstream out_file;
    out_file.open(file_path);
    out_file << out;
    out_file.close();

}


void tools::save_game(std::vector<stats::Save> data, std::string file_path) {
    std::vector<std::vector<std::pair<std::string, std::string>>> saves;
    for(int i = 0; i < data.size(); ++i) {
        std::pair<std::string, std::string> name("Name", data.at(i).name);
        std::pair<std::string, std::string> level("Level", std::to_string(data.at(i).level));
        std::pair<std::string, std::string> exp("Exp", std::to_string(data.at(i).exp));
        std::pair<std::string, std::string> exp_needed("Exp_needed", std::to_string(data.at(i).exp_needed));
        std::pair<std::string, std::string> skill_id("Skill_id", std::to_string(data.at(i).skill_id));
        std::pair<std::string, std::string> attr_points("Attribute Points", std::to_string(data.at(i).attr_points));
        std::pair<std::string, std::string> strength("Strength", std::to_string(data.at(i).attributes.strength));
        std::pair<std::string, std::string> defense("Defense", std::to_string(data.at(i).attributes.defense));
        std::pair<std::string, std::string> dexterity("Dexterity", std::to_string(data.at(i).attributes.dexterity));
        std::pair<std::string, std::string> intelligence("Intelligence", std::to_string(data.at(i).attributes.intelligence));
        std::pair<std::string, std::string> save_dt("Save_DateTime", data.at(i).save_dt);
        std::vector<std::pair<std::string, std::string>> save {name, level, exp, exp_needed, skill_id, attr_points,
                                                               strength, defense, dexterity, intelligence, save_dt};
        
        saves.push_back(save);
    }

    save_to_json(saves, file_path);
}



