// IT001.E33.CN2.TTNT - Nhập môn lập trình
// Họ và tên: Vũ Ngọc Huyền
// MSSV: 23210228
// Bài Tập Lý Thuyết

#include <iostream>
using namespace std;

bool LaSoNguyenTo(int n);
bool LaMangDoiXung(int arr[], int n);
int DemXuatHien(int arr[], int n, int x);
int ViTriAmLonNhat(int arr[], int n);
int XoaPhanTu(int arr[], int &n, int k);

int main() {
    int n;
    cout << "Nhap so phan tu cua day: ";
    cin >> n;
    
    while (n <= 0) {
        cout << "So phan tu phai lon hon 0. Nhap lai: ";
        cin >> n;
    }
    
    int arr[100];
    
    // Câu 1: Nhập dãy tăng dần và xuất số nguyên tố
    cout << "\n=== CAU 1: NHAP DAY TANG DAN VA XUAT SO NGUYEN TO ===\n";
    cout << "Nhap day tang dan:\n";
    for (int i = 0; i < n; i++) {
        cout << "Phan tu thu " << i + 1 << ": ";
        cin >> arr[i];
        
        // Kiểm tra dãy tăng dần
        if (i > 0 && arr[i] < arr[i-1]) {
            cout << "Day khong tang dan. Vui long nhap lai tu dau:\n";
            i = -1;
            continue;
        }
    }
    
    // Xuất các số nguyên tố trong mảng
    cout << "Cac so nguyen to trong day: ";
    bool laSoNguyenTo = false;
    for (int i = 0; i < n; i++) {
        if (LaSoNguyenTo(arr[i])) {
            cout << arr[i] << " ";
            laSoNguyenTo = true;
        }
    }
    
    if (!laSoNguyenTo) {
        cout << "Khong co so nguyen to nao trong day.";
    }
    cout << endl;
    
    // Câu 2: Kiểm tra mảng đối xứng
    cout << "\n=== CAU 2: KIEM TRA MANG DOI XUNG ===\n";
    if (LaMangDoiXung(arr, n)) {
        cout << "Mang doi xung";
    } else {
        cout << "Mang khong doi xung";
    }
    cout << endl;
    
    // Câu 3: Liệt kê các giá trị xuất hiện đúng 1 lần
    cout << "\n=== CAU 3: LIET KE CAC GIA TRI XUAT HIEN DUNG 1 LAN ===\n";
    cout << "Cac gia tri xuat hien dung 1 lan: ";
    bool coGiaTri = false;
    for (int i = 0; i < n; i++) {
        if (DemXuatHien(arr, n, arr[i]) == 1) {
            cout << arr[i] << " ";
            coGiaTri = true;
        }
    }
    if (!coGiaTri) {
        cout << "Khong co gia tri nao xuat hien dung 1 lan";
    }
    cout << endl;
    
    // Câu 4: Tìm vị trí phần tử âm lớn nhất
    cout << "\n=== CAU 4: TIM VI TRI PHAN TU AM LON NHAT ===\n";
    int viTri = ViTriAmLonNhat(arr, n);
    if (viTri == -1) {
        cout << "Mang khong co so am";
    } else {
        cout << "Vi tri phan tu am lon nhat: " << viTri << endl;
        cout << "Gia tri: " << arr[viTri];
    }
    cout << endl;
    
    // Câu 5: Xóa phần tử tại vị trí k
    cout << "\n=== CAU 5: XOA PHAN TU TAI VI TRI K ===\n";
    int k;
    cout << "Nhap vi tri can xoa k = ";
    cin >> k;
    
    int ketQua = XoaPhanTu(arr, n, k);
    if (ketQua == 0) {
        cout << "Vi tri khong hop le, khong the xoa";
    } else {
        cout << "Mang sau khi xoa phan tu tai vi tri " << k << ": ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
    }
    cout << endl;
    
    return 0;
}


// Hàm kiểm tra số nguyên tố
bool LaSoNguyenTo(int n)
{
    if(n < 2)
        return false;
    int dem = 0;
    for(int i = 1; i <= n; i++)
        if(n % i == 0)
            dem++;
    if(dem == 2)
        return true;
    return false;
}

// Hàm kiểm tra mảng đối xứng
bool LaMangDoiXung(int arr[], int n) {
    for (int i = 0; i < n/2; i++) {
        if (arr[i] != arr[n-1-i]) {
            return false;
        }
    }
    return true;
}

// Hàm đếm số lần xuất hiện của một phần tử trong mảng
int DemXuatHien(int arr[], int n, int x) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == x) count++;
    }
    return count;
}

// Hàm tìm vị trí phần tử âm lớn nhất
int ViTriAmLonNhat(int arr[], int n) {
    int giaTriAmNhoNhat = -1e9;  // Giá trị âm rất nhỏ
    int viTri = -1;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] < 0 && arr[i] > giaTriAmNhoNhat) {
            giaTriAmNhoNhat = arr[i];
            viTri = i;
        }
    }
    return viTri;
}

// Hàm xóa phần tử tại vị trí k
int XoaPhanTu(int arr[], int &n, int k) {
    if (k < 0 || k >= n) return 0;
    
    for (int i = k; i < n - 1; i++) {
        arr[i] = arr[i + 1];
    }
    n--;
    return 1;
}