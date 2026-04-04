#include "traffic.h"
#include <cstdlib> // rand()
#include <ctime>   // time()

//================= AREA FACTOR =================
double getAreaFactor(AreaType type) {
    switch(type) {
        case AreaType::MARKET: return 1.3;
        case AreaType::SCHOOL: return 1.2;
        case AreaType::HOSPITAL: return 1.25;
        case AreaType::MAIN_ROAD: return 1.4;
        case AreaType::RESIDENTIAL: return 1.0;
        case AreaType::PARK: return 0.9;
    }
    return 1.0;
}

//================= DAY FACTOR =================
double getDayFactor(Day day) {
    switch(day) {
        case Day::MONDAY: return 1.3;
        case Day::TUESDAY:
        case Day::WEDNESDAY:
        case Day::THURSDAY:
        case Day::FRIDAY: return 1.1;
        case Day::SATURDAY: return 0.95;
        case Day::SUNDAY: return 0.8;
    }
    return 1.0;
}

//================= TIME FACTOR =================
double getTimeFactor(TimeSlot time) {
    switch(time) {
        case TimeSlot::MORNING: return 1.4;
        case TimeSlot::NOON: return 1.0;
        case TimeSlot::AFTERNOON: return 1.3;
        case TimeSlot::EVENING: return 1.2;
    }
    return 1.0;
}

//================= RANDOM FACTOR =================
double getRandomFactor() {
    return 0.95 + (rand() % 11) / 100.0; // 0.95 -> 1.05
}

//================= MAIN CALCULATION =================
double calculateTrafficCost(const Road& road, const TrafficContext& ctx) {
    double areaFactor = getAreaFactor(road.areaType);
    double dayFactor = getDayFactor(ctx.day);
    double timeFactor = getTimeFactor(ctx.timeSlot);
    double randomFactor = getRandomFactor();

    return road.distance * road.baseTraffic * areaFactor * dayFactor * timeFactor * randomFactor;
}

//================= UPDATE GRAPH =================
void updateTraffic(Graph& g, const TrafficContext& ctx) {
    // Seed random 1 lần
    srand(time(0));

    for (int i = 0; i < g.adjList.size(); i++) {
        for (auto& road : g.adjList[i]) {
            road.trafficCost = calculateTrafficCost(road, ctx);
        }
    }
}