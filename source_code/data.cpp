#include "data.h"

Graph createSampleGraph() {
    Graph g;

    //-----Tạo địa điểm-----
    g.locations = {
        {0, "Cho Trung Tam"},
        {1, "Benh vien Thanh Pho"},
        {2, "Cong vien Hoa Binh"},
        {3, "Truong THPT Nguyen Du"},
        {4, "Sieu thi MegaMart"},
        {5, "Ben xe Trung Tam"},
        {6, "Khu dan cu A"},
        {7, "Khu dan cu B"},
        {8, "Trung tam thuong mai Vincom"},
        {9, "Nha ga Thanh Pho"},
        {10, "Khu cong nghiep TechZone"}
    };

    int n = g.locations.size();
    g.adjList.resize(n);


    //-----Hàm thêm đường 2 chiều-----
    auto addRoad = [&](int from, int to, double dist, AreaType type, double baseTraffic) {
        Road r1(from, to, dist, type, baseTraffic);
        Road r2(to, from, dist, type, baseTraffic);
        g.adjList[from].push_back(r1);
        g.adjList[to].push_back(r2);
    };


    //-----Tạo các tuyến đường-----
    addRoad(0, 1, 2.3, AreaType::MARKET, 1.4);        // Chợ Trung Tâm - Bệnh viện Thành Phố
    addRoad(0, 3, 1.8, AreaType::SCHOOL, 1.5);        // Chợ Trung Tâm - THPT Nguyễn Du
    addRoad(1, 4, 2.0, AreaType::HOSPITAL, 1.3);      // Bệnh viện Thành Phố - MegaMart
    addRoad(2, 4, 1.2, AreaType::PARK, 0.9);          // Công viên HB - MegaMart
    addRoad(2, 6, 2.5, AreaType::RESIDENTIAL, 1.0);   // Công viên HB - Khu dân cư A
    addRoad(3, 5, 3.0, AreaType::MAIN_ROAD, 1.6);     // THPT Nguyễn Du - Bến xe
    addRoad(4, 5, 1.5, AreaType::MAIN_ROAD, 1.7);     // MegaMart - Bến xe
    addRoad(5, 7, 2.8, AreaType::RESIDENTIAL, 1.1);   // Bến xe - Khu dân cư B
    addRoad(6, 7, 1.4, AreaType::RESIDENTIAL, 1.0);   // Khu dân cư A - Khu dân cư B
    addRoad(1, 2, 2.2, AreaType::MAIN_ROAD, 1.5);     // Bệnh viện - Công viên
    addRoad(3, 6, 2.6, AreaType::SCHOOL, 1.4);        // THPT Nguyễn Du - KDC A
    addRoad(4, 7, 2.1, AreaType::MARKET, 1.3);        // MegaMart - KDC B
    addRoad(4, 8, 1.6, AreaType::MAIN_ROAD, 1.6);     // MegaMart - Vincom
    addRoad(5, 9, 2.0, AreaType::MAIN_ROAD, 1.7);     // Bến xe - Nhà ga
    addRoad(7, 10, 2.5, AreaType::RESIDENTIAL, 1.2);  // KDC B - KCN TechZone
    addRoad(8, 9, 1.8, AreaType::MARKET, 1.5);        // Vincom - Nhà ga
    addRoad(9, 10, 2.2, AreaType::MAIN_ROAD, 1.8);    // Nhà ga - KCN TechZone
    addRoad(6, 8, 2.4, AreaType::RESIDENTIAL, 1.1);   // KDC A - Vincom

    return g;
}