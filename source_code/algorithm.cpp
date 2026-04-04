#include "algorithm.h"
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Cấu trúc hỗ trợ Priority Queue để Dijkstra chạy nhanh hơn
struct Node {
    int id;
    double weight;
    bool operator>(const Node& other) const { return weight > other.weight; }
};

RouteResult findPath(const Graph& g, int startId, int endId, bool useTrafficMode) {
    int n = g.locations.size();
    vector<double> dist(n, 1e9); // Khởi tạo khoảng cách vô cùng
    vector<int> parent(n, -1);   // Mảng lưu vết đường đi
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    dist[startId] = 0;
    pq.push({startId, 0});

    while (!pq.empty()) {
        int u = pq.top().id;
        double d = pq.top().weight;
        pq.pop();

        if (d > dist[u]) continue;
        if (u == endId) break; // Đã tìm thấy đích thì dừng

        for (const auto& road : g.adjList[u]) {
            int v = road.to;
            // Lấy trọng số tùy theo chế độ người dùng chọn 
            double weight = useTrafficMode ? road.trafficCost : road.distance;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({v, dist[v]});
            }
        }
    }

    RouteResult result;
    result.found = (dist[endId] != 1e9);
    
    if (result.found) {
        // 1. Truy vết ngược để lấy danh sách các điểm đi qua 
        for (int v = endId; v != -1; v = parent[v]) {
            result.path.push_back(v);
        }
        reverse(result.path.begin(), result.path.end());

        // 2. Tính toán các chỉ số tổng cộng để Người 4 làm báo cáo 
        result.totalDistance = 0;
        result.totalCost = 0;
        for (size_t i = 0; i < result.path.size() - 1; i++) {
            int u = result.path[i];
            int v = result.path[i+1];
            for (const auto& r : g.adjList[u]) {
                if (r.to == v) {
                    result.totalDistance += r.distance;
                    result.totalCost += r.trafficCost;
                    break;
                }
            }
        }
    }
    return result; // Trả về object kết quả, không in gì ra màn hình 
}