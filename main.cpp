#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include "Optimizer.h"
#include <functional>

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

int get_from_id(const std::vector<CraftOpt::Ingredient>& ings, int id) {
    for (auto i = 0; i < ings.size(); ++i) {
        if (ings[i].id == id) return i;
    }
    return 0;
}

constexpr auto choose(int64_t n, int64_t k) {
    if (k == 0) return static_cast<int64_t>(1);
    return (n * choose(n - 1, k - 1)) / k;
}

template<int SelectCount>
void iteratePosMod(int elements, std::function<void (const std::array<int, SelectCount>&)> callback) {
    std::array<int, SelectCount> index{};
    while (true) {
        if (index[SelectCount - 1] == elements) {
            for (int i = SelectCount - 2; i >= 0; --i) {
                ++index[i];
                if (index[i] < elements) {
                    for (auto j = i + 1; j < SelectCount; ++j) {
                        index[j] = index[i];
                    }
                    break;
                }
            }
            if (index[0] == elements) break;
        }
        callback(index);
        ++index[SelectCount - 1];
    }
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
    /*const auto sets = genSet<3>(0, 10);
    std::cout << sets.size() << std::endl;
    for (const auto& set : sets) {
        for (const auto& v : set) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }*/
    int count = 0;
    constexpr int selectCount = 6;
    iteratePosMod<selectCount>(8, [&count](const auto& index) {
        for (auto i = 0; i < index.size(); ++i) {
            std::cout << index[i] << ", ";
        }
        std::cout << "\n";
        ++count;
    });
    std::cout << "Count: " << count << " Predict: " << choose(selectCount + 8 - 1, selectCount) << "\n";
    CraftOpt::CraftStats craft{};
    craft.add_ingredient(0, ingredients[get_from_id(ingredients, 674)], 45);
    craft.add_ingredient(1, ingredients[get_from_id(ingredients, 596)], 140);
    craft.add_ingredient(2, ingredients[get_from_id(ingredients, 502)], 140);
    craft.add_ingredient(3, ingredients[get_from_id(ingredients, 502)], 125);
    craft.add_ingredient(4, ingredients[get_from_id(ingredients, 502)], 180);
    craft.add_ingredient(5, ingredients[get_from_id(ingredients, 502)], 125);
    return 0;
}
