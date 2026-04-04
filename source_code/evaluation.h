#ifndef EVALUATION_H
#define EVALUATION_H

#include "models.h"
#include <string>

std::string evaluateRoutes(const RouteResult& shortest, const RouteResult& traffic);

#endif
