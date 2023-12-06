#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void randomize(int A[], unsigned char& B) {
    B = 0;
    for (int i = 0; i < 8; ++i) {
        A[i] = -1 * rand() % 2;
        if (A[i] < 0) {
            B += 1 << (8 - i);
        }
        else {
            B += (rand() % 2) << i;
        }
    }
}

bool check(int A[], unsigned char B) {
    bool is_correct = true;
    for (int i = 0; i < 8; ++i) {
        if ((A[i] < 0) != ((B >> (8 - i)) & 1)) {
            is_correct = false;
        }
        cout << A[i] << "\t";
    }
    cout << endl << static_cast<int>(B) << "\t:\t" << is_correct << endl << endl;
    return is_correct;
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    int A[8];
    unsigned char B;
    bool stop = false;
    while (!stop) {
        randomize(A, B);
        stop = check(A, B);
    }
    return 0;
}
