#include "models.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <map>

using namespace std;

//================= HELPER =================
string areaToString(AreaType a) {
    switch(a) {
        case AreaType::MARKET: return "cho";
        case AreaType::SCHOOL: return "truong hoc";
        case AreaType::HOSPITAL: return "benh vien";
        case AreaType::MAIN_ROAD: return "duong lon";
        case AreaType::RESIDENTIAL: return "khu dan cu";
        case AreaType::PARK: return "cong vien";
    }
    return "";
}

string eventToString(EventType e) {
    switch(e) {
        case EventType::ACCIDENT: return "tai nan";
        case EventType::ROADWORK: return "sua duong";
        case EventType::FLOOD: return "ngap lut";
        case EventType::CONSTRUCTION: return "cong trinh";
        case EventType::FESTIVAL: return "le hoi";
        default: return "";
    }
}

void describeEvents(const Graph& g, const vector<int>& path, stringstream& ss) {
    bool hasEvent = false;

    for (int i = 0; i < (int)path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];

        for (const auto& road : g.adjList[u]) {
            if (road.to == v && road.event != EventType::NONE) {
                ss << "- Xay ra " << eventToString(road.event)
                   << " tai doan ("
                   << g.locations[u].name << " -> "
                   << g.locations[v].name << ").\n";

                hasEvent = true;
                break;
            }
        }
    }

    if (!hasEvent) {
        ss << "- Khong co su kien bat thuong tren tuyen nay.\n";
    }
}

//================= PHAN TICH TUYEN =================
void analyzeRoute(const Graph& g, const vector<int>& path,
                  map<AreaType, int>& areaCount,
                  map<EventType, int>& eventCount) {

    for (int i = 0; i < (int)path.size() - 1; i++) {
        int u = path[i];
        int v = path[i + 1];

        for (const auto& road : g.adjList[u]) {
            if (road.to == v) {
                areaCount[road.areaType]++;
                if (road.event != EventType::NONE)
                    eventCount[road.event]++;
                break;
            }
        }
    }
}

//================= MAIN =================
string evaluateRoutes(const Graph& g, const RouteResult& shortest, const RouteResult& traffic) {

    if (!shortest.found || !traffic.found) {
        return "Khong tim thay duong di hop le.";
    }

    double distA = shortest.totalDistance;
    double costA = shortest.totalCost;

    double distB = traffic.totalDistance;
    double costB = traffic.totalCost;

    double distDiff = ((distB - distA) / distA) * 100.0;
    double costDiff = ((costA - costB) / costA) * 100.0;

    // ===== PHAN TICH =====
    map<AreaType, int> areaA, areaB;
    map<EventType, int> eventA, eventB;

    analyzeRoute(g, shortest.path, areaA, eventA);
    analyzeRoute(g, traffic.path, areaB, eventB);

    stringstream ss;
    ss << fixed << setprecision(2);

    ss << "--- DANH GIA ---\n";

    // ===== KET LUAN CHINH =====
    if (costDiff > 10) {
        ss << "Tuyen co chi phi giao thong thap nhat phu hop hon trong dieu kien hien tai.\n";
        ss << "Tuyen nay dai hon " << distDiff << "% nhung giam " << costDiff << "% chi phi giao thong.\n\n";

        ss << "Ly do:\n";

        // ===== SO SANH AREA =====
        for (auto& it : areaA) {
            AreaType type = it.first;

            int countA = areaA[type];
            int countB = areaB[type];

            if (countA > countB) {
                ss << "- Tuyen ngan nhat di qua nhieu " << areaToString(type)
                   << " hon (" << countA << " lan so voi " << countB << " lan).\n";
            }
        }

        ss << "- Tuyen ngan nhat co cac su kien:\n";
        describeEvents(g, shortest.path, ss);
        ss << "\n- Trong khi do, tuyen thay the:\n";
        describeEvents(g, traffic.path, ss);
        ss << "- Do do, tuyen thay the giup tranh cac khu vuc dong duc va giam rui ro bat thuong.";
    }

    else if (distDiff > 15) {
        ss << "Tuyen ngan nhat phu hop hon.\n";
        ss << "Tuyen thay the tang " << distDiff << "% khoang cach nhung khong giam dang ke chi phi.\n";

        ss << "Ly do:\n";
        ss << "- Hai tuyen co dac diem giao thong tuong tu nhau.\n";
        ss << "- Loi ich tu viec doi tuyen khong du bu dap cho quang duong tang them.";
    }

    else {
        ss << "Hai tuyen co hieu qua tuong duong.\n";
        ss << "Khong co su khac biet dang ke ve giao thong va khoang cach.\n";
    }

    return ss.str();
}