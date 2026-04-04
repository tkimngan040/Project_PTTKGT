#include "algorithm.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <limits> // Để dùng numeric_limits

using namespace std;

// Cấu trúc hỗ trợ Priority Queue
struct Node {
    int id;
    double weight;
    bool operator>(const Node& other) const { return weight > other.weight; }
};

RouteResult findPath(const Graph& g, int startId, int endId, bool useTrafficMode) {
    int n = g.locations.size();

    // 1. SỬA LỖI QUAN TRỌNG: Kiểm tra input đầu vào
    if (startId < 0 || startId >= n || endId < 0 || endId >= n) {
        return RouteResult{{}, 0.0, 0.0, false};
    }

    // 2. SỬA LỖI TIỀM ẨN: Dùng vô cùng chuẩn xác
    double INF = numeric_limits<double>::infinity();
    vector<double> dist(n, INF);
    vector<int> parent(n, -1);
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[startId] = 0;
    pq.push({startId, 0});

    while (!pq.empty()) {
        int u = pq.top().id;
        double d = pq.top().weight;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == endId) break; // Dijkstra chuẩn: tìm thấy đích thì dừng sớm

        for (const auto& road : g.adjList[u]) {
            int v = road.to;
            // Chọn trọng số dựa trên chế độ: Khoảng cách hoặc Chi phí giao thông 
            double weight = useTrafficMode ? road.trafficCost : road.distance;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    RouteResult result;
    result.found = (dist[endId] != INF);
    
    if (result.found) {
        // Truy vết đường đi từ đích về đầu 
        for (int v = endId; v != -1; v = parent[v]) {
            result.path.push_back(v);
        }
        reverse(result.path.begin(), result.path.end());

        // Tính toán tổng quãng đường và tổng chi phí để bàn giao cho Người 4 
        result.totalDistance = 0;
        result.totalCost = 0;
        for (size_t i = 0; i < result.path.size() - 1; i++) {
            int curr = result.path[i];
            int next = result.path[i+1];
            for (const auto& r : g.adjList[curr]) {
                if (r.to == next) {
                    result.totalDistance += r.distance;
                    result.totalCost += r.trafficCost;
                    break;
                }
            }
        }
    }
    return result;
}