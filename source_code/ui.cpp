#include <iostream>
#include <iomanip>
#include "models.h"

using namespace std;

//================= DAY TO STRING =================
string dayToString(Day d) {
    switch(d) {
        case Day::MONDAY: return "Monday";
        case Day::TUESDAY: return "Tuesday";
        case Day::WEDNESDAY: return "Wednesday";
        case Day::THURSDAY: return "Thursday";
        case Day::FRIDAY: return "Friday";
        case Day::SATURDAY: return "Saturday";
        case Day::SUNDAY: return "Sunday";
    }
    return "";
}

//================= TIME TO STRING =================
string timeToString(TimeSlot t) {
    switch(t) {
        case TimeSlot::MORNING: return "Morning";
        case TimeSlot::NOON: return "Noon";
        case TimeSlot::AFTERNOON: return "Afternoon";
        case TimeSlot::EVENING: return "Evening";
    }
    return "";
}

//================= PRINT PATH =================
void printPath(const Graph& g, const vector<int>& path) {
    for (int i = 0; i < path.size(); i++) {
        cout << g.locations[path[i]].name;
        if (i != path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
}

//================= MAIN UI OUTPUT =================
void displayResult(
    const Graph& g,
    int start,
    int end,
    const TrafficContext& ctx,
    const RouteResult& shortest,
    const RouteResult& traffic
) {
    cout << fixed << setprecision(2);

    cout << "========== KET QUA TIM DUONG ==========\n";
    cout << "Diem bat dau: " << g.locations[start].name << endl;
    cout << "Diem dich: " << g.locations[end].name << endl;
    cout << "Ngay: " << dayToString(ctx.day) << endl;
    cout << "Khung gio: " << timeToString(ctx.timeSlot) << "\n\n";

    // ===== TUYEN NGAN NHAT =====
    cout << "--- TUYEN DUONG NGAN NHAT ---\n";
    printPath(g, shortest.path);
    cout << "Tong khoang cach: " << shortest.totalDistance << " km\n";
    cout << "Tong chi phi giao thong: " << shortest.totalCost << "\n\n";

    // ===== TUYEN TRAFFIC TOT NHAT =====
    cout << "--- TUYEN CO CHI PHI GIAO THONG THAP NHAT ---\n";
    printPath(g, traffic.path);
    cout << "Tong khoang cach: " << traffic.totalDistance << " km\n";
    cout << "Tong chi phi giao thong: " << traffic.totalCost << "\n\n";

    // ===== DANH GIA =====
    cout << evaluateRoutes(g, shortest, traffic);

    cout << "\n========================================\n";
}