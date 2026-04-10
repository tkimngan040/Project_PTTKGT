#ifndef MODELS_H
#define MODELS_H

#include <string>
#include <vector>

//Loại khu vực
enum class AreaType {
    MARKET,
    SCHOOL,
    HOSPITAL,
    RESIDENTIAL,
    MAIN_ROAD,
    PARK
};

//Sự kiện ngẫu nhiên
enum class EventType {
    NONE,
    ACCIDENT,      // tai nạn
    ROADWORK,      // sửa đường
    FLOOD,         // ngập
    CONSTRUCTION,  // công trình
    FESTIVAL       // lễ hội
};

//Ngày
enum class Day {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};


//Khung giờ
enum class TimeSlot {
    MORNING,
    NOON,
    AFTERNOON,
    EVENING,
    NIGHT
};

//Địa điểm
struct Location {
    int id;
    std::string name;
};


//Tuyến đường
struct Road {
    int from;
    int to;
    double distance;
    AreaType areaType;
    double baseTraffic = 0;
    double trafficCost = 0;
    EventType event = EventType::NONE;
    Road(int f, int t, double d, AreaType a, double b)
        : from(f), to(t), distance(d), areaType(a), baseTraffic(b) {}
};


//Đồ thị
struct Graph {
    std::vector<Location> locations;
    std::vector<std::vector<Road>> adjList;
};


//CONTEXT
struct TrafficContext {
    Day day;
    TimeSlot timeSlot;
};


//RESULT
struct RouteResult {
    std::vector<int> path;
    double totalDistance;
    double totalCost;
    bool found;
};


#endif