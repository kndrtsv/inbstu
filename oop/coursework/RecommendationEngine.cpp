#include "RecommendationEngine.h"
#include <string>

std::vector<Recommendation> RecommendationEngine::analyze(
        const Report& report,
        const std::map<std::string, Category>& categories) {

    std::vector<Recommendation> recommendations;

    for (const auto& [name, total] : report.totals) {
        auto it = categories.find(name);
        if (it != categories.end()) {
            const Category& category = it->second;
            if (total < -category.limit) {
                recommendations.emplace_back("Limit ["
                                             + std::to_string(category.limit)
                                             + "] exceeded in category: " + name);
            }
        }
    }

    return recommendations;
}