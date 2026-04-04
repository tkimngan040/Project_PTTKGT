#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "models.h"

// Tính traffic cost cho 1 tuyến đường
double calculateTrafficCost(const Road& road, const TrafficContext& ctx);

// Cập nhật toàn bộ graph theo tình trạng giao thông
void updateTraffic(Graph& g, const TrafficContext& ctx);

#endif