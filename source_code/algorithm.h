#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "models.h"

// Hàm tìm đường dùng chung cho cả 2 chế độ: Khoảng cách và Chi phí giao thông
// useTrafficMode = false: Tìm tuyến ngắn nhất (km)
// useTrafficMode = true: Tìm tuyến né kẹt xe (Traffic Cost) 
RouteResult findPath(const Graph& g, int startId, int endId, bool useTrafficMode);

#endif