#ifndef EVALUATION_H
#define EVALUATION_H

#include "models.h"
#include <string>

// Hàm đánh giá và so sánh 2 tuyến đường
std::string evaluateRoutes(
    const Graph& g,
    const RouteResult& shortest,
    const RouteResult& traffic
);

#endif