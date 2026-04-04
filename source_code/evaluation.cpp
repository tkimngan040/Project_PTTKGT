#include "models.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string evaluateRoutes(const RouteResult& shortest, const RouteResult& traffic) {

    // ===== CHECK =====
    if (!shortest.found || !traffic.found) {
        return "Khong tim thay duong di hop le.";
    }

    double distA = shortest.totalDistance;
    double costA = shortest.totalCost;

    double distB = traffic.totalDistance;
    double costB = traffic.totalCost;

    // ===== % CHENH LECH =====
    double distDiffPercent = 0;
    double costDiffPercent = 0;

    if (distA > 0)
        distDiffPercent = ((distB - distA) / distA) * 100.0;

    if (costA > 0)
        costDiffPercent = ((costA - costB) / costA) * 100.0;

    // ===== FORMAT OUTPUT =====
    stringstream ss;
    ss << fixed << setprecision(2);

    ss << "So sanh hai tuyen:\n";

    ss << "- Tuyen ngan nhat co distance = " << distA;
    ss << ", traffic cost = " << costA << "\n";

    ss << "- Tuyen chi phi giao thong thap nhat co distance = " << distB;
    ss << ", traffic cost = " << costB << "\n";

    ss << "\nChenh lech:\n";
    ss << "- Tang khoang cach: " << distDiffPercent << " %\n";
    ss << "- Giam chi phi giao thong: " << costDiffPercent << " %\n\n";

    // ===== DANH GIA =====
    if (costDiffPercent > 20 && distDiffPercent < 15) {
        ss << "Ket luan: Nen chon tuyen chi phi giao thong thap nhat.\n";
        ss << "Ly do: Giam duoc nhieu ap luc giao thong trong khi chi tang nhe khoang cach.";
    }
    else if (costDiffPercent < 10 && distDiffPercent > 20) {
        ss << "Ket luan: Nen chon tuyen ngan nhat.\n";
        ss << "Ly do: Loi ich giam giao thong khong dang ke nhung phai di vong xa.";
    }
    else {
        ss << "Ket luan: Hai tuyen gan nhu tuong duong.\n";
        ss << "Ly do: Chenh lech giua khoang cach va giao thong khong dang ke.";
    }

    return ss.str();
}
