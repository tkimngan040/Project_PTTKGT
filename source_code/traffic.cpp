#include "traffic.h"
#include <random>
#include <ctime>

// Random generator (xịn hơn rand)
static std::mt19937 gen(time(0));

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

//================= EVENT FACTOR =================
double getEventFactor(EventType e) {
    switch(e) {
        case EventType::NONE: return 1.0;
        case EventType::ACCIDENT: return 1.5;
        case EventType::ROADWORK: return 1.4;
        case EventType::FLOOD: return 1.6;
        case EventType::CONSTRUCTION: return 1.3;
        case EventType::FESTIVAL: return 1.35;
    }
    return 1.0;
}

//================= RANDOM FACTOR =================
double getRandomFactor() {
    std::uniform_real_distribution<> dist(0.95, 1.05);
    return dist(gen);
}

//================= RANDOM EVENT ==================
EventType getRandomEvent() {
    std::uniform_int_distribution<> dist(0, 99);
    int r = dist(gen);

    if (r < 55) return EventType::NONE;
    else if (r < 70) return EventType::ACCIDENT;
    else if (r < 80) return EventType::ROADWORK;
    else if (r < 90) return EventType::FLOOD;
    else if (r < 95) return EventType::CONSTRUCTION;
    else return EventType::FESTIVAL;
}

//================= MAIN CALCULATION =================
double calculateTrafficCost(const Road& road, const TrafficContext& ctx) {
    double areaFactor = getAreaFactor(road.areaType);
    double dayFactor = getDayFactor(ctx.day);
    double timeFactor = getTimeFactor(ctx.timeSlot);
    double randomFactor = getRandomFactor();
    double eventFactor = getEventFactor(road.event);

    return road.distance * road.baseTraffic *
           areaFactor * dayFactor *
           timeFactor * randomFactor *
           eventFactor;
}

//================= UPDATE GRAPH =================
void updateTraffic(Graph& g, const TrafficContext& ctx) {

    int n = g.adjList.size();

    for (int u = 0; u < n; u++) {
        for (auto& road : g.adjList[u]) {

            int v = road.to;

            // Chỉ xử lý 1 chiều (u < v) để tránh random 2 lần
            if (u < v) {
                EventType e = getRandomEvent();

                // Gán event cho cả 2 chiều
                road.event = e;

                for (auto& back : g.adjList[v]) {
                    if (back.to == u) {
                        back.event = e;
                        break;
                    }
                }
            }
        }
    }

    // Sau khi có event → tính lại cost
    for (int u = 0; u < n; u++) {
        for (auto& road : g.adjList[u]) {
            road.trafficCost = calculateTrafficCost(road, ctx);
        }
    }
}