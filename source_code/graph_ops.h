#ifndef GRAPH_OPS_H
#define GRAPH_OPS_H

#include "models.h"
#include <string>

//================= LOCATION =================

// Thêm địa điểm mới
void addLocation(Graph& g, const std::string& name);

// Cập nhật tên địa điểm
void updateLocation(Graph& g, int id, const std::string& newName);

// Xóa địa điểm (soft delete)
void removeLocation(Graph& g, int id);

//================= ROAD =================

// Thêm đường (2 chiều)
void addRoad(Graph& g, int from, int to, double dist, AreaType type, double baseTraffic);

// Xóa đường (2 chiều)
void removeRoad(Graph& g, int from, int to);

// Cập nhật thông tin đường
void updateRoad(Graph& g, int from, int to, double newDist);

//================= UTIL =================

// Kiểm tra ID hợp lệ
bool isValidLocation(const Graph& g, int id);

#endif