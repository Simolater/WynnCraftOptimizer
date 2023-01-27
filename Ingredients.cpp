//
// Created by Simon on 26/01/2023.
//
#include "Ingredients.h"
#include <unordered_map>
#include <string_view>

namespace CraftOpt {
    static ProfessionType profession_from_string(const std::string& profession) {
        static std::unordered_map<std::string, ProfessionType> const profs = {
                {"SCRIBING",Scribing}, {"JEWELING",Jeweling},
                {"ALCHEMISM",Alchemism}, {"COOKING",Cooking},
                {"WEAPONSMITHING",Weaponsmithing}, {"TAILORING",Tailoring},
                {"WOODWORKING",Woodworking}, {"ARMOURING",Armouring}};
        if (!profs.contains(profession)) throw std::invalid_argument("Invalid Profession " + profession);
        return profs.at(profession);
    }

    static IDType id_from_string(const std::string& id) {
        static std::unordered_map<std::string, IDType> const idTable = {
                {"str", SP_Strength}, {"dex", SP_Dexterity}, {"int", SP_Intelligence}, {"def", SP_Defence}, {"agi", SP_Agility},
                {"poison", Poison}, {"spd", Walk_Speed}, {"sprint", Sprint}, {"sprintReg", Sprint_Regen}, {"jh", Jump_Height},
                {"hpBonus", Health_Bonus}, {"hprRaw", Health_Regen}, {"hprPct", Health_Regen_Percent}, {"ls", Life_Steal},
                {"sdRaw", Spell_Damage}, {"sdPct", Spell_Damage_Percent},
                {"mdRaw", Main_Attack_Damage}, {"mdPct", Main_Attack_Damage_Percent}, {"atkTier", Attack_Speed},
                {"mr", Mana_Regen}, {"ms", Mana_Steal},
                {"eDefPct", Earth_Defence_Percent}, {"tDefPct", Thunder_Defence_Percent},
                {"wDefPct", Water_Defence_Percent}, {"fDefPct", Fire_Defence_Percent},
                {"aDefPct", Air_Defence_Percent},
                {"eDamPct", Earth_Damage_Percent}, {"tDamPct", Thunder_Damage_Percent},
                {"wDamPct", Water_Damage_Percent}, {"fDamPct", Fire_Damage_Percent},
                {"aDamPct", Air_Damage_Percent},
                {"thorns", Thorns}, {"expd", Exploding}, {"lb", Loot_Bonus}, {"lq", Loot_Quality}, {"ref", Reflection},
                {"xpb", Xp_Bonus}, {"eSteal", Stealing}, {"spRegen", Soul_Point_Regen},
                {"gxp", Gather_Xp}, {"gXp", Gather_Xp}, {"gSpd", Gather_Speed},
        };
        if (!idTable.contains(id)) throw std::invalid_argument("Unknown Id " + id);
        return idTable.at(id);
    }

    Ingredient ingredient_from_json(const json& data) {
        Ingredient result;
        result.name = data["name"];
        result.tier = data["tier"];
        result.level = data["lvl"];

        result.skills = 0;
        for (const auto& prof : data["skills"]) {
            result.skills |= static_cast<value_t>(profession_from_string(prof));
        }

        for (const auto& id : data["ids"].items()) {
            result.ids[id_from_string(id.key())] = std::make_pair(id.value()["minimum"], id.value()["maximum"]);
        }

        const auto& itemIDs = data["itemIDs"];
        result.durability = itemIDs["dura"];
        result.skill_requirements[Strength] = itemIDs["strReq"];
        result.skill_requirements[Dexterity] = itemIDs["dexReq"];
        result.skill_requirements[Intelligence] = itemIDs["intReq"];
        result.skill_requirements[Defence] = itemIDs["defReq"];
        result.skill_requirements[Agility] = itemIDs["agiReq"];

        result.charges = data["consumableIDs"]["charges"];
        result.length = data["consumableIDs"]["dura"];

        const auto& posMods = data["posMods"];
        result.position_modifiers[Left] = posMods["left"];
        result.position_modifiers[Right] = posMods["right"];
        result.position_modifiers[Above] = posMods["above"];
        result.position_modifiers[Under] = posMods["under"];
        result.position_modifiers[Touching] = posMods["touching"];
        result.position_modifiers[NotTouching] = posMods["notTouching"];

        return result;
    }

    std::vector<Ingredient> ingredients_from_json(const json& data) {
        std::vector<CraftOpt::Ingredient> ingredients;
        for (const auto& ingredient_data : data) {
            ingredients.emplace_back(CraftOpt::ingredient_from_json(ingredient_data));
        }
        return ingredients;
    }
}