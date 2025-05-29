#ifndef COURSEWORK_RECOMMENDATIONENGINE_H
#define COURSEWORK_RECOMMENDATIONENGINE_H

#include <vector>
#include <map>
#include "Recommendation.h"
#include "Report.h"
#include "Category.h"

class RecommendationEngine {
public:
    std::vector<Recommendation> analyze(const Report& report, const std::map<std::string, Category>& categories);
};

#endif //COURSEWORK_RECOMMENDATIONENGINE_H