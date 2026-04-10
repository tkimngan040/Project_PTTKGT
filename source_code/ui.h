#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include "models.h"

using namespace std;

//================= CONVERT ENUM TO STRING =================
string dayToString(Day d);
string timeToString(TimeSlot t);

//================= PRINT PATH =================
void printPath(const Graph& g, const vector<int>& path);

//================= DISPLAY FINAL RESULT =================
void displayResult(
    const Graph& g,
    int start,
    int end,
    const TrafficContext& ctx,
    const RouteResult& shortest,
    const RouteResult& traffic
);

#endif