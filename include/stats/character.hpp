#ifndef character_hpp
#define character_hpp
#include "attributes.hpp"
#include "statistics.hpp"
#include "calculations.hpp"
#include "ultimate_skill.hpp"
#include <vector>
#include <string>


namespace stats {
    class character
    {
        public:
            // default constructor
            character();

            // load game constructor
            character(const Attributes attr, std::string character_name, int level, int ulti_skill_id,
                      int exp, int attr_points, int exp_needed);

            character(const character&) = default;
            character& operator=(const character&) = default;
            character(character&&) = default; 
            character& operator=(character&&) = default;

            ~character() = default;

            // getters for attributes
            Attributes get_attributes() const;
            int get_strength() const;
            int get_defense() const;
            int get_dexterity() const;
            int get_intelligence() const;

            // getters for statistics
            Statistics get_statistics() const;
            int get_hp() const;
            int get_physical_att() const;
            int get_magic_power() const;
            int get_magic_att() const;
            int get_accuracy() const;
            int get_block_rate() const;
            int get_dodge_rate() const;

            int get_level() const;
            int get_exp() const;
            int get_exp_needed() const;
            int get_attribute_points() const;
            int get_skill_id() const;
            int get_save_slot() const;
            std::string get_character_name() const;

            void set_skill_id(int new_id);
            void set_save_slot(int slot_id);
            void set_character_name(std::string name);
        

            std::vector<Ultimate> get_skill_set() const;
            std::string get_skill_name() const;
            bool get_skill_dmg_type() const;
            float get_skill_dmg_multiplier() const;
            int get_skill_atk_count() const;
            int get_skill_mana_cost() const;

            // add exp to character and check if level-up occurs
            void add_exp(const int exp_aquired);

            // assign attribute point
            void assign_attribute_point(const int attr_id);
            void assign_ultimate_skill(const int skill_id);

            
        private:
            int level_;
            int exp_;
            int exp_needed_;
            int attribute_points_;
            int combat_hp_;
            int combat_mp_;
            int save_slot_;
            std::string character_name_;
            Attributes attributes_;
            Statistics statistics_;
            std::vector<Ultimate> ultimate_skills_;
            int ultimate_skill_id_;


            // level-up character
            void level_up_();

            void collect_ultimate_skills_();

    };
}

#endif