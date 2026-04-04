#include <iostream>
#include <iomanip>
#include "models.h"

using namespace std;

string evaluateRoutes(const RouteResult& shortest, const RouteResult& traffic) {

    // ===== KIỂM TRA =====
    if (!shortest.found || !traffic.found) {
        return "Khong tim thay duong di hop le.\n";
    }

    double distShortest = shortest.totalDistance;
    double costShortest = shortest.totalCost;

    double distTraffic = traffic.totalDistance;
    double costTraffic = traffic.totalCost;

    cout << fixed << setprecision(2);

    cout << "\n========== SO SANH TUYEN ==========\n";

    cout << "\n[1] Tuyen ngan nhat:\n";
    cout << "  - Tong khoang cach: " << distShortest << " km\n";
    cout << "  - Tong chi phi giao thong: " << costShortest << "\n";

    cout << "\n[2] Tuyen chi phi giao thong thap nhat:\n";
    cout << "  - Tong khoang cach: " << distTraffic << " km\n";
    cout << "  - Tong chi phi giao thong: " << costTraffic << "\n";

    // ===== TINH % =====
    double distDiffPercent = 0;
    double costDiffPercent = 0;

    if (distShortest > 0)
        distDiffPercent = ((distTraffic - distShortest) / distShortest) * 100.0;

    if (costShortest > 0)
        costDiffPercent = ((costShortest - costTraffic) / costShortest) * 100.0;

    cout << "\n[3] Chenh lech:\n";
    cout << "  - Tang khoang cach: " << distDiffPercent << " %\n";
    cout << "  - Giam chi phi giao thong: " << costDiffPercent << " %\n";

    // ===== DANH GIA =====
    string result = "\n========== DANH GIA ==========\n";

    if (costDiffPercent > 20 && distDiffPercent < 15) {
        result += "Nen chon tuyen chi phi giao thong thap nhat.\n";
        result += "Ly do: Tuyen nay giam dang ke muc do giao thong trong khi chi tang nhe khoang cach.\n";
        result += "Phu hop khi di vao gio cao diem hoac khu vuc dong duc.\n";
    }
    else if (costDiffPercent < 10 && distDiffPercent > 20) {
        result += "Nen chon tuyen ngan nhat.\n";
        result += "Ly do: Loi ich giam giao thong khong dang ke nhung phai di vong xa.\n";
        result += "Phu hop khi giao thong on dinh.\n";
    }
    else {
        result += "Hai tuyen gan nhu tuong duong.\n";
        result += "Chenh lech giua khoang cach va giao thong khong dang ke.\n";
        result += "Co the lua chon tuy theo uu tien ca nhan.\n";
    }

    return result;
}
