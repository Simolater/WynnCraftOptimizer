#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Optimizer.h"

using json = nlohmann::json;

template<int SelectCount>
std::vector<std::array<int, SelectCount>> genSet(int start, int size) {
    std::vector<std::array<int, SelectCount>> result;
    for (auto i = start; i < size; ++i) {
        for (auto& subset : genSet<SelectCount - 1>(i, size)) {
            std::array<int, SelectCount> set{};
            for (auto j = 0; j < SelectCount - 1; ++j) {
                set[j] = subset[j];
            }
            set[SelectCount - 1] = i;
            result.emplace_back(set);
        }
    }
    return result;
}

template<>
auto genSet<0>(int start, int size) -> std::vector<std::array<int, 0>> {
    return {{}};
}

int main() {
    std::ifstream f("../ingreds_compress.json");
    auto data = json::parse(f);
    auto ingredients = CraftOpt::ingredients_from_json(data);
    constexpr auto x = sizeof(CraftOpt::CraftStats);
    /*CraftOpt::GenerateCrafts(ingredients, CraftOpt::Scribing, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Jeweling, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Alchemism, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Cooking, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Weaponsmithing, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Tailoring, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Woodworking, [](const auto& stats){return true;});
    CraftOpt::GenerateCrafts(ingredients, CraftOpt::Armouring, [](const auto& stats){return true;});*/
    const auto sets = genSet<3>(0, 10);
    std::cout << sets.size() << std::endl;
    for (const auto& set : sets) {
        for (const auto& v : set) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
