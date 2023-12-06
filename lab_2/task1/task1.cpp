#include <iostream>
using namespace std;

int main() {
    int a, b, c, d;
    cout << "Enter a number for a: ";
    cin >> a;
    cout << "Enter a number for b: ";
    cin >> b;
    cout << "Enter a number for c: ";
    cin >> c;
    cout << "Enter a number for d: ";
    cin >> d;

    int result = (b << 10) + (((d << 4) - d + (a << 3) + a) >> 9) - ((c << 12) + c) + (d << 4);
    cout << "result: " << result;

}