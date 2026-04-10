#include "data.h"

Graph createSampleGraph() {
    Graph g;

    // ====== 50 ĐỊA ĐIỂM (CHIA THEO NHÓM 5) ======
    g.locations = {
        // 0–4: MARKET
        {0, "Cho Trung Tam"},
        {1, "Cho Phuong Dong"},
        {2, "Cho Dem"},
        {3, "Cho Dau Moi"},
        {4, "Cho An Dong"},

        // 5–9: HOSPITAL
        {5, "BV Thanh Pho"},
        {6, "BV Tu Nhan"},
        {7, "BV Nhi Dong"},
        {8, "BV Ung Buou"},
        {9, "BV Cho Ray"},

        // 10–14: PARK
        {10, "CV Hoa Binh"},
        {11, "CV Riverside"},
        {12, "CV Gia Dinh"},
        {13, "CV Tao Dan"},
        {14, "CV Le Van Tam"},

        // 15–19: SCHOOL
        {15, "THPT Nguyen Du"},
        {16, "THCS Le Loi"},
        {17, "DH CNTT"},
        {18, "DH Kinh Te"},
        {19, "DH Bach Khoa"},

        // 20–24: SUPERMARKET
        {20, "MegaMart"},
        {21, "Co.opmart"},
        {22, "BigC"},
        {23, "Emart"},
        {24, "Nguyen Kim"},

        // 25–29: TRANSPORT
        {25, "Ben xe TT"},
        {26, "Ben xe MD"},
        {27, "Ben xe MT"},
        {28, "Nha ga"},
        {29, "San bay"},

        // 30–34: RESIDENTIAL A
        {30, "KDC A1"},
        {31, "KDC A2"},
        {32, "KDC A3"},
        {33, "KDC A4"},
        {34, "KDC A5"},

        // 35–39: RESIDENTIAL B
        {35, "KDC B1"},
        {36, "KDC B2"},
        {37, "KDC B3"},
        {38, "KDC B4"},
        {39, "KDC B5"},

        // 40–44: INDUSTRIAL
        {40, "KCN TechZone"},
        {41, "KCN Song Than"},
        {42, "KCN Tan Thuan"},
        {43, "KCN VSIP"},
        {44, "KCN Hiep Phuoc"},

        // 45–49: MALL
        {45, "Vincom"},
        {46, "Aeon Mall"},
        {47, "Lotte Mart"},
        {48, "Crescent Mall"},
        {49, "SC VivoCity"}
    };

    int n = g.locations.size();
    g.adjList.resize(n);

    // ====== HÀM THÊM ĐƯỜNG ======
    auto addRoad = [&](int from, int to, double dist, AreaType type, double traffic) {
        g.adjList[from].push_back(Road(from, to, dist, type, traffic));
        g.adjList[to].push_back(Road(to, from, dist, type, traffic));
    };

    // ====== 1. KẾT NỐI TRONG CÙNG BLOCK ======
    for (int i = 0; i < 50; i += 5) {
        for (int j = i; j < i + 4; j++) {
            addRoad(j, j + 1, 1.2, AreaType::RESIDENTIAL, 1.0);
        }
    }

    // ====== 2. KẾT NỐI GIỮA CÁC BLOCK LIÊN QUAN ======

    // Market ↔ Transport
    addRoad(0, 25, 2.5, AreaType::MAIN_ROAD, 1.5);
    addRoad(2, 27, 2.7, AreaType::MAIN_ROAD, 1.6);

    // Hospital ↔ Residential
    addRoad(5, 30, 2.0, AreaType::HOSPITAL, 1.3);
    addRoad(7, 35, 2.2, AreaType::HOSPITAL, 1.4);

    // School ↔ Residential
    addRoad(15, 30, 1.8, AreaType::SCHOOL, 1.3);
    addRoad(18, 35, 2.0, AreaType::SCHOOL, 1.4);

    // Park ↔ Residential
    addRoad(10, 31, 1.7, AreaType::PARK, 1.1);
    addRoad(12, 36, 1.9, AreaType::PARK, 1.2);

    // Supermarket ↔ Mall
    addRoad(20, 45, 2.0, AreaType::MARKET, 1.4);
    addRoad(22, 47, 2.1, AreaType::MARKET, 1.5);

    // Mall ↔ Transport
    addRoad(45, 28, 2.3, AreaType::MAIN_ROAD, 1.5);
    addRoad(48, 29, 2.6, AreaType::MAIN_ROAD, 1.6);

    // Industrial ↔ Transport
    addRoad(40, 25, 2.8, AreaType::MAIN_ROAD, 1.7);
    addRoad(42, 28, 2.5, AreaType::MAIN_ROAD, 1.6);

    // ====== 3. KẾT NỐI CHÉO (TẠO NHIỀU ĐƯỜNG KHÁC NHAU) ======
    addRoad(0, 20, 2.2, AreaType::MARKET, 1.4);
    addRoad(5, 10, 2.0, AreaType::MAIN_ROAD, 1.3);
    addRoad(15, 25, 2.3, AreaType::MAIN_ROAD, 1.5);
    addRoad(30, 40, 2.5, AreaType::MAIN_ROAD, 1.6);
    addRoad(35, 45, 2.4, AreaType::MAIN_ROAD, 1.5);

    return g;
}