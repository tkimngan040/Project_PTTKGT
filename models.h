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
    EVENING
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
    double baseTraffic;
    double trafficCost;
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