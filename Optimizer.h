#pragma once
//
// Created by Simon on 26/01/2023.
//
#include <functional>
#include "Ingredients.h"

namespace CraftOpt {

    void GenerateCrafts(const std::vector<Ingredient>&, ProfessionType, const std::function<bool (CraftStats)>& callback);
};
