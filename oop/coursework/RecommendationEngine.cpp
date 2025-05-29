#include "RecommendationEngine.h"

std::vector<Recommendation> RecommendationEngine::analyze(
        const Report& report,
        const std::map<std::string, Category>& categories) {

    std::vector<Recommendation> recommendations;

    for (const auto& [name, total] : report.totals) {
        auto it = categories.find(name);
        if (it != categories.end()) {
            const Category& category = it->second;
            if (total < -category.limit) {
                recommendations.emplace_back("Limit exceeded in category: " + name);
            }
        }
    }

    return recommendations;
}
