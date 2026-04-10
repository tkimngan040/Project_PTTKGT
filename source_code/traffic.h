#ifndef TRAFFIC_H
#define TRAFFIC_H

#include "models.h"

//================= FACTOR FUNCTIONS =================

// Hệ số theo loại khu vực
double getAreaFactor(AreaType type);

// Hệ số theo ngày trong tuần
double getDayFactor(Day day);

// Hệ số theo khung giờ
double getTimeFactor(TimeSlot time);

// Hệ số theo sự kiện
double getEventFactor(EventType e);

// Hệ số ngẫu nhiên (mô phỏng biến động nhỏ)
double getRandomFactor();

//================= EVENT =================

// Sinh sự kiện ngẫu nhiên trên đường
EventType getRandomEvent();

//================= MAIN LOGIC =================

// Tính chi phí giao thông cho 1 tuyến đường
double calculateTrafficCost(const Road& road, const TrafficContext& ctx);

// Cập nhật toàn bộ graph theo tình trạng giao thông hiện tại
void updateTraffic(Graph& g, const TrafficContext& ctx);

#endif