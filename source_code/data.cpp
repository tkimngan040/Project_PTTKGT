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
        {8, "TTTM Vincom"},
        {9, "Nha ga Thanh Pho"},
        {10, "KCN TechZone"},

        {11, "Cho Phuong Dong"},
        {12, "Benh vien Tu Nhan"},
        {13, "Cong vien Riverside"},
        {14, "Truong Dai hoc CNTT"},
        {15, "Sieu thi Co.opmart"},
        {16, "Ben xe Mien Dong"},
        {17, "Khu dan cu C"},
        {18, "Khu dan cu D"},
        {19, "TTTM Aeon Mall"},
        {20, "San bay Noi dia"},

        {21, "KCN Song Than"},
        {22, "Cho Dem"},
        {23, "Benh vien Nhi Dong"},
        {24, "Cong vien Gia Dinh"},
        {25, "Truong THCS Le Loi"},
        {26, "Sieu thi BigC"},
        {27, "Ben xe Mien Tay"},
        {28, "Khu dan cu E"},
        {29, "Khu dan cu F"},
        {30, "TTTM Lotte Mart"},

        {31, "Nha ga Metro"},
        {32, "KCN Tan Thuan"},
        {33, "Cho Dau Moi"},
        {34, "Benh vien Ung Buou"},
        {35, "Cong vien Tao Dan"},
        {36, "Truong Dai hoc Kinh Te"},
        {37, "Sieu thi Emart"},
        {38, "Khu dan cu G"},
        {39, "Khu dan cu H"},
        {40, "TTTM Crescent Mall"},

        {41, "Ben tau Song"},
        {42, "KCN VSIP"},
        {43, "Cho An Dong"},
        {44, "Benh vien Cho Ray"},
        {45, "Cong vien Le Van Tam"},
        {46, "Truong Dai hoc Bach Khoa"},
        {47, "Sieu thi Nguyen Kim"},
        {48, "Khu dan cu I"},
        {49, "Khu dan cu J"}
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

    // ====== CỤM TRUNG TÂM (0–10) ======
    addRoad(0, 1, 2.3, AreaType::MARKET, 1.4);
    addRoad(0, 3, 1.8, AreaType::SCHOOL, 1.5);
    addRoad(1, 4, 2.0, AreaType::HOSPITAL, 1.3);
    addRoad(2, 4, 1.2, AreaType::PARK, 0.9);
    addRoad(3, 5, 3.0, AreaType::MAIN_ROAD, 1.6);
    addRoad(4, 5, 1.5, AreaType::MAIN_ROAD, 1.7);
    addRoad(5, 9, 2.0, AreaType::MAIN_ROAD, 1.7);
    addRoad(9, 10, 2.2, AreaType::MAIN_ROAD, 1.8);

    // ====== MỞ RỘNG VÒNG 1 ======
    addRoad(4, 8, 1.6, AreaType::MAIN_ROAD, 1.6);
    addRoad(8, 20, 3.5, AreaType::MAIN_ROAD, 1.4);
    addRoad(20, 16, 2.5, AreaType::MAIN_ROAD, 1.5);
    addRoad(16, 5, 2.2, AreaType::MAIN_ROAD, 1.6);

    // ====== CỤM KHU DÂN CƯ ======
    addRoad(6, 7, 1.4, AreaType::RESIDENTIAL, 1.0);
    addRoad(7, 10, 2.5, AreaType::RESIDENTIAL, 1.2);
    addRoad(6, 17, 2.0, AreaType::RESIDENTIAL, 1.1);
    addRoad(17, 18, 1.2, AreaType::RESIDENTIAL, 1.0);
    addRoad(18, 28, 2.3, AreaType::RESIDENTIAL, 1.1);
    addRoad(28, 29, 1.5, AreaType::RESIDENTIAL, 1.0);

    // ====== CỤM TRƯỜNG + CÔNG VIÊN ======
    addRoad(3, 14, 2.5, AreaType::SCHOOL, 1.4);
    addRoad(14, 36, 2.0, AreaType::SCHOOL, 1.3);
    addRoad(36, 46, 2.2, AreaType::SCHOOL, 1.3);
    addRoad(2, 13, 1.7, AreaType::PARK, 1.0);
    addRoad(13, 24, 2.1, AreaType::PARK, 1.1);
    addRoad(24, 35, 2.0, AreaType::PARK, 1.2);

    // ====== CỤM BỆNH VIỆN ======
    addRoad(1, 12, 2.3, AreaType::HOSPITAL, 1.4);
    addRoad(12, 23, 2.1, AreaType::HOSPITAL, 1.3);
    addRoad(23, 34, 2.0, AreaType::HOSPITAL, 1.5);
    addRoad(34, 44, 2.2, AreaType::HOSPITAL, 1.6);

    // ====== CỤM SIÊU THỊ ======
    addRoad(4, 15, 2.0, AreaType::MARKET, 1.4);
    addRoad(15, 26, 2.2, AreaType::MARKET, 1.5);
    addRoad(26, 37, 2.1, AreaType::MARKET, 1.4);
    addRoad(37, 47, 2.0, AreaType::MARKET, 1.3);

    // ====== CỤM KCN ======
    addRoad(10, 21, 2.5, AreaType::MAIN_ROAD, 1.6);
    addRoad(21, 32, 2.3, AreaType::MAIN_ROAD, 1.5);
    addRoad(32, 42, 2.2, AreaType::MAIN_ROAD, 1.4);

    // ====== KẾT NỐI CHÉO (TẠO NHIỀU ĐƯỜNG) ======
    addRoad(0, 11, 2.0, AreaType::MARKET, 1.3);
    addRoad(11, 22, 2.1, AreaType::MARKET, 1.4);
    addRoad(22, 33, 2.3, AreaType::MARKET, 1.5);
    addRoad(33, 43, 2.0, AreaType::MARKET, 1.6);

    addRoad(8, 19, 2.2, AreaType::MAIN_ROAD, 1.4);
    addRoad(19, 30, 2.1, AreaType::MAIN_ROAD, 1.3);
    addRoad(30, 40, 2.0, AreaType::MAIN_ROAD, 1.2);

    addRoad(9, 31, 1.8, AreaType::MAIN_ROAD, 1.5);
    addRoad(31, 41, 2.0, AreaType::MAIN_ROAD, 1.4);

    // ====== KẾT NỐI RANDOM NHẸ (CHO CẠNH TRANH) ======
    addRoad(5, 27, 2.5, AreaType::MAIN_ROAD, 1.5);
    addRoad(27, 16, 2.0, AreaType::MAIN_ROAD, 1.4);
    addRoad(38, 39, 1.2, AreaType::RESIDENTIAL, 1.0);
    addRoad(39, 48, 2.0, AreaType::RESIDENTIAL, 1.1);
    addRoad(48, 49, 1.5, AreaType::RESIDENTIAL, 1.0);

    return g;
}