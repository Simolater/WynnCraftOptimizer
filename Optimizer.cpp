//
// Created by Simon on 26/01/2023.
//

#include "Optimizer.h"
#include <algorithm>
#include <iostream>

namespace CraftOpt {
    template<int SelectCount, int SetSize>
    constexpr std::vector<std::array<int, SelectCount>> genSet(int start) {
        if constexpr (SelectCount == 0) return {{}};
        std::vector<std::array<int, SelectCount>> result;
        for (auto i = start; i < SetSize; ++i) {
            for (const auto& subset : genSet<SelectCount - 1, SetSize>(i)) {
                result.emplace_back({i, subset});
            }
        }
        return result;
    }

    template<int SelectCount>
    void iteratePosMod(int elements) {
        std::array<int, SelectCount> index{};
        while (true) {
            if (index[SelectCount - 1] == elements) {
                for (int i = SelectCount - 2; i >= 0; --i) {
                    index[i + 1] = 0;
                    ++index[i];
                    if (index[i] < elements) break;
                }
                if (index[0] == elements) break;
            }
            ++index[SelectCount - 1];
        }
    }

    size_t countC(const std::vector<Ingredient>& ingredients, int start, int depth) {
        if (depth == 5) return ingredients.size() - start;
        size_t count = 0;
        for (int i = start; i < ingredients.size(); ++i) {
            count += countC(ingredients, i, depth + 1);
        }
        return count;
    }

    void GenerateCrafts(const std::vector<Ingredient>& ingredients, ProfessionType prof, const std::function<bool (CraftStats)>& callback) {
        std::vector<Ingredient> posMod;
        std::vector<Ingredient> remaining;
        for (const auto& ing : ingredients) {
            if (!(ing.skills & static_cast<value_t>(prof))) continue;
            if (std::any_of(ing.position_modifiers.begin(), ing.position_modifiers.end(), [](value_t val) {return val != 0;}))
                posMod.emplace_back(ing);
            else
                remaining.emplace_back(ing);
        }
        std::cout << "PosMod: " << posMod.size() << " Rem: " << remaining.size() << std::endl;
        std::cout << "Combinations: " << countC(remaining, 0, 0) << std::endl;

    }
}