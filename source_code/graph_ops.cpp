#include "graph_ops.h"
#include <algorithm>

//================= VALIDATION =================
bool isValidLocation(const Graph& g, int id) {
    return id >= 0 && id < (int)g.locations.size();
}

//================= LOCATION =================
void addLocation(Graph& g, const std::string& name) {
    int id = g.locations.size();
    g.locations.push_back({id, name});
    g.adjList.push_back({});
}

void updateLocation(Graph& g, int id, const std::string& newName) {
    if (!isValidLocation(g, id)) return;
    g.locations[id].name = newName;
}

void removeLocation(Graph& g, int id) {
    if (!isValidLocation(g, id)) return;

    // Xóa tất cả cạnh liên quan
    for (int i = 0; i < (int)g.adjList.size(); i++) {
        if (i == id) continue;

        auto& adj = g.adjList[i];
        adj.erase(remove_if(adj.begin(), adj.end(),
            [id](const Road& r) { return r.to == id; }), adj.end());
    }

    // Xóa danh sách kề của node này
    g.adjList[id].clear();

    // (Không xóa khỏi vector để tránh lệch ID)
    g.locations[id].name = "[DELETED]";
}

//================= ROAD =================
void addRoad(Graph& g, int from, int to, double dist, AreaType type, double baseTraffic) {
    if (!isValidLocation(g, from) || !isValidLocation(g, to)) return;
    if (from == to) return;

    Road r1(from, to, dist, type, baseTraffic);
    Road r2(to, from, dist, type, baseTraffic);

    g.adjList[from].push_back(r1);
    g.adjList[to].push_back(r2);
}

void removeRoad(Graph& g, int from, int to) {
    if (!isValidLocation(g, from) || !isValidLocation(g, to)) return;

    auto& adj1 = g.adjList[from];
    adj1.erase(remove_if(adj1.begin(), adj1.end(),
        [to](const Road& r) { return r.to == to; }), adj1.end());

    auto& adj2 = g.adjList[to];
    adj2.erase(remove_if(adj2.begin(), adj2.end(),
        [from](const Road& r) { return r.to == from; }), adj2.end());
}

void updateRoad(Graph& g, int from, int to, double newDist) {
    if (!isValidLocation(g, from) || !isValidLocation(g, to)) return;

    for (auto& r : g.adjList[from]) {
        if (r.to == to) {
            r.distance = newDist;
        }
    }

    for (auto& r : g.adjList[to]) {
        if (r.to == from) {
            r.distance = newDist;
        }
    }
}