#pragma once
//
// Created by Simon on 26/01/2023.
//
#include <string>
#include <array>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace CraftOpt {
    using value_t = int16_t;

    enum ProfessionType {
        Scribing = 1,
        Jeweling = 2,
        Alchemism = 4,
        Cooking = 8,
        Weaponsmithing = 16,
        Tailoring = 32,
        Woodworking = 64,
        Armouring = 128
    };

    enum SkillType {
        Strength, Dexterity, Intelligence, Defence, Agility
    };

    enum EffectivenessType {
        Left, Right, Above, Under, Touching, NotTouching
    };

    enum IDType {
        SP_Strength, SP_Dexterity, SP_Intelligence, SP_Defence, SP_Agility,
        Walk_Speed,
        Sprint,
        Sprint_Regen,
        Jump_Height,
        Health_Bonus,
        Health_Regen,
        Health_Regen_Percent,
        Life_Steal,
        Mana_Regen,
        Mana_Steal,
        Poison,
        Exploding,
        Attack_Speed,
        Main_Attack_Damage,
        Main_Attack_Damage_Percent,
        Spell_Damage,
        Spell_Damage_Percent,
        Earth_Damage_Percent,
        Thunder_Damage_Percent,
        Water_Damage_Percent,
        Fire_Damage_Percent,
        Air_Damage_Percent,
        Earth_Defence_Percent,
        Thunder_Defence_Percent,
        Water_Defence_Percent,
        Fire_Defence_Percent,
        Air_Defence_Percent,
        Thorns,
        Reflection,
        Stealing,
        Xp_Bonus,
        Gather_Speed,
        Gather_Xp,
        Loot_Bonus,
        Loot_Quality,
        Soul_Point_Regen,

        ID_Types_Count = Soul_Point_Regen
    };

    struct Ingredient {
        std::string name;
        value_t tier;
        value_t skills;
        value_t level;
        // IDs value range [min, max]
        std::array<std::pair<value_t, value_t>, ID_Types_Count> ids;
        // ItemIDs
        value_t durability;
        std::array<value_t, 5> skill_requirements;
        // ConsumableIDs
        value_t charges;
        value_t length;
        // PosMods
        std::array<value_t, 6> position_modifiers;
    };

    struct CraftStats {
        std::array<size_t, 6> ingredients;
        // IDs value range [min, max]
        std::array<std::pair<value_t, value_t>, ID_Types_Count> ids;
        // ItemIDs
        value_t durability;
        std::array<value_t, 5> skill_requirements;
        // ConsumableIDs
        value_t charges;
        value_t length;
    };

    std::vector<Ingredient> ingredients_from_json(const json&);
}
