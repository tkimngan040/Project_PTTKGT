#include "ui_controller.h"
#include <iostream>
#include <limits>

#include "data.h"
#include "traffic.h"
#include "algorithm.h"
#include "ui.h"
#include "graph_ops.h"

using namespace std;

//================= HIEN THI DIA DIEM =================
void showLocations(const Graph& g) {
    cout << "\n===== DANH SACH DIA DIEM =====\n";
    for (int i = 0; i < (int)g.locations.size(); i++) {
        if (g.locations[i].name != "[DELETED]") {
            cout << i << ". " << g.locations[i].name << endl;
        }
    }
}

//================= CHON NGAY =================
Day chooseDay() {
    cout << "\n===== CHON NGAY =====\n";
    cout << "0. Monday\n";
    cout << "1. Tuesday\n";
    cout << "2. Wednesday\n";
    cout << "3. Thursday\n";
    cout << "4. Friday\n";
    cout << "5. Saturday\n";
    cout << "6. Sunday\n";

    int choice;
    cin >> choice;

    return static_cast<Day>(choice);
}

//================= CHON KHUNG GIO =================
TimeSlot chooseTimeSlot() {
    cout << "\n===== CHON KHUNG GIO =====\n";
    cout << "0. Morning (6h - 10h)\n";
    cout << "1. Noon (10h - 14h)\n";
    cout << "2. Afternoon (14h - 18h)\n";
    cout << "3. Evening (18h - 22h)\n";

    int choice;
    cin >> choice;

    return static_cast<TimeSlot>(choice);
}

//================= TIM DUONG =================
void handleFindRoute(Graph& g) {
    int start, end;

    showLocations(g);

    cout << "\nNhap diem bat dau (so): ";
    cin >> start;

    cout << "Nhap diem dich (so): ";
    cin >> end;

    Day day = chooseDay();
    TimeSlot time = chooseTimeSlot();

    TrafficContext ctx{day, time};

    updateTraffic(g, ctx);

    RouteResult shortest = findPath(g, start, end, false);
    RouteResult traffic = findPath(g, start, end, true);

    displayResult(g, start, end, ctx, shortest, traffic);
}

//================= MENU =================
void runApp() {
    Graph g = createSampleGraph();
    int choice;

    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Tim duong\n";
        cout << "2. Them dia diem\n";
        cout << "3. Them duong\n";
        cout << "4. Xoa duong\n";
        cout << "0. Thoat\n";
        cout << "Chon: ";
        cin >> choice;

        if (choice == 1) {
            handleFindRoute(g);
        }

        else if (choice == 2) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string name;
            cout << "Nhap ten dia diem: ";
            getline(cin, name);

            addLocation(g, name);
            cout << "Da them!\n";
        }

        else if (choice == 3) {
            int u, v;
            double d;

            showLocations(g);
            cout << "Nhap diem dau: "; cin >> u;
            cout << "Nhap diem cuoi: "; cin >> v;
            cout << "Nhap khoang cach: "; cin >> d;

            addRoad(g, u, v, d, AreaType::MAIN_ROAD, 1.2);
            cout << "Da them duong!\n";
        }

        else if (choice == 4) {
            int u, v;

            showLocations(g);
            cout << "Nhap diem dau: "; cin >> u;
            cout << "Nhap diem cuoi: "; cin >> v;

            removeRoad(g, u, v);
            cout << "Da xoa duong!\n";
        }

    } while (choice != 0);
}