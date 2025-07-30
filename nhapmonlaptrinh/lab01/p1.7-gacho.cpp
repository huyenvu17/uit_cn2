#include <iostream>
using namespace std;

int main()
{
    /*
     * Giải hệ phương trình:
     * 1. so_ga + so_cho = tong_so_con
     * 2. 2 * so_ga + 4 * so_cho = tong_so_chan
     *
     * Từ phương trình (1), ta có: so_ga = tong_so_con - so_cho
     * Thế vào phương trình (2), ta được:
     * 2 * (tong_so_con - so_cho) + 4 * so_cho = tong_so_chan
     * 2*tong_so_con - 2*so_cho + 4*so_cho = tong_so_chan
     * 2*so_cho = tong_so_chan - 2*tong_so_con
     * so_cho = (tong_so_chan - 2 * tong_so_con) / 2
    */
    int tong_so_con, tong_so_chan, so_cho, so_ga ;
    cin >> tong_so_con >> tong_so_chan;
    so_cho = (tong_so_chan - 2 * tong_so_con) / 2;
    so_ga = tong_so_con - so_cho;
    cout << so_ga << " " << so_cho;
    return 0;
}