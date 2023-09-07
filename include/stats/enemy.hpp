#ifndef enemy_hpp
#define enemy_hpp
#include "attributes.hpp"
#include "statistics.hpp"
#include "calculations.hpp"
#include "ultimate_skill.hpp"


namespace stats {
    class enemy
    {
        public:
            // no default constructor
            enemy();

            // construct enemy based on character level
            enemy(const int level);

            enemy(const enemy&) = default;
            enemy& operator=(const enemy&) = default;
            enemy(enemy&&) = default; 
            enemy& operator=(enemy&&) = default;

            ~enemy() = default;

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

            bool get_skill_dmg_type() const;
            float get_skill_dmg_multiplier() const;
            int get_skill_atk_count() const;
            int get_skill_mana_cost() const;

            int get_level() const;
            int get_exp() const;
            int get_archtype() const;

        private:
            int level_;
            int archtype_;
            int combat_hp_;
            int combat_mp_;
            int exp_;
            Attributes attributes_;
            Statistics statistics_;
            Ultimate ultimate_skill_;

            Attributes architype_builder_();
            void build_warrior_(Attributes& attr);
            void build_rogue_(Attributes& attr);
            void build_mage_(Attributes& attr);

    };
}

#endif