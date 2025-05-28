#ifndef COURSEWORK_RECOMMENDATION_H
#define COURSEWORK_RECOMMENDATION_H

#include <string>

class Recommendation {
public:
    std::string message;
    Recommendation(const std::string& message) : message(message) {}
};

#endif //COURSEWORK_RECOMMENDATION_H