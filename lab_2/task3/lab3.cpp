#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
using namespace std;
struct Task {
    unsigned short least_significan_bit : 4;
    unsigned short row_number : 2;
    unsigned short position_number : 4;
    unsigned short most_significan_bit : 4;
    unsigned short bitp_49 : 1;
    unsigned short bitp : 1;

};
union Bytes {
    Task task1;
    unsigned short data;

};
void Enter_Text(string text[4]) {
    for (unsigned int i = 0; i < 4; i++) {
        cout << "Enter sentence: " << i + 1 << endl;
        getline(cin, text[i]);
        while (text[i].length() < 16) {
            text[i] += ' ';
        }
        if (text[i].length() > 16) {
            text[i].resize(16);
        }
    }
}

void Encrypt_File(string text[4]) {
    Bytes a;
    unsigned short t = 0, r = 0, b = 0;
    unsigned int y, l;

    ofstream fd("text.txt", ios::binary);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 16; j++) {
            unsigned char c = text[i][j];

            // ������� ������� ���� ASCII � ���� 0-3
            t = c;
            a.task1.least_significan_bit = t & 0x000F;

            // � ���� 4-5 ����������� ����� ����� �����
            a.task1.row_number = i;

            // � ���� 6-9 ������� ����� � ����� (4 ���)
            a.task1.position_number = j;

            // � ���� 10-13 ������ ������� ASCII - ���� �������
            a.task1.most_significan_bit = (c >> 4) & 0x000F;
            
            // �� ������� ���� 4-9
            t = 1;
            b = 0;
            for (l = 4; l < 9; l++) {
                if (a.task1.most_significan_bit & t) {
                    if (b == 0)
                        b = 1;
                    else
                        b = 0;
                }
                t <<= 1;
            }

            a.task1.bitp_49 = b;
            // �� �������
            a.task1.bitp = c & 0x1;

            fd << bitset<16>(a.data);
            fd << endl;
        }
    }
    fd.close();
}
void Decrypt_File() {
    Bytes a;
    unsigned short t = 0, r = 0, b = 0;
    unsigned int y, l, i, j;
    ifstream fd("text.txt", ios::binary);
    ofstream od("decrypt.txt", ios::binary); // ³������� ����� ��� ������ �������������� ������
    if (fd && od) { // �������� �� ������ �����  
        string line;
        while (getline(fd, line)) {
            // ���������� ������ ����� � �������� y
            y = bitset<16>(line).to_ulong();
            a.data = y;
            od << static_cast<char>(a.task1.most_significan_bit << 4 | a.task1.least_significan_bit); // ����� �������������� ������� � ����
        }
        fd.close();
        od.close(); // �������� ���� �����
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

int main() {
    string text[4];
    Enter_Text(text);
    Encrypt_File(text);
    Decrypt_File();
    return 0;
}