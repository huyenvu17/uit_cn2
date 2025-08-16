#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    double diemToan, diemLy, diemHoa;
    cin >> diemToan;
    cin >> diemLy;
    cin >> diemHoa;

    double dtb = (diemToan + diemLy + diemHoa) / 3.0;
    cout << fixed << setprecision(2);
    // Xếp loại dựa trên điểm trung bình
    if (dtb >= 9.0) {
        cout << "DTB = " << dtb << endl << "Loai: XUAT SAC" << endl;
    } else if (dtb >= 8.0) { 
        cout << "DTB =  " << dtb << endl  << "Loai: GIOI" << endl;
    } else if (dtb >= 7.0) {
        cout << "DTB =  " << dtb << endl  << "Loai: KHA" << endl;
    } else if (dtb >= 6.0) { 
        cout << "DTB =  " << dtb << endl  << "Loai: TB KHA" << endl;
    } else if (dtb >= 5.0) {
        cout << "DTB =  " << dtb << endl  << "Loai: TB" << endl;
    } else if (dtb >= 4.0) {
        cout << "DTB =  " << dtb << endl  << "Loai: YEU" << endl;
    } else {
        cout << "DTB = " << dtb << endl  << "Loai: KEM" << endl;
    }

    return 0;
}
