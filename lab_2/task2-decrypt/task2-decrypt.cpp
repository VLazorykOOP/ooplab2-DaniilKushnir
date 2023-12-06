#include <iostream>
#include <string>
#include <fstream>
#include <bitset>
using namespace std;
void Enter_Text(string text[4]) {
    for (unsigned int i = 0; i < 4; i++) {
        cout << "Enter sentence: " << i + 1 << endl;
        getline(cin, text[i]);
        while (text[i].length() <= 16) {
            text[i] += ' ';
        }
        if (text[i].length() > 16) {
            text[i].resize(16);
        }
    }
}

void Encrypt_File(string text[4]) {
    unsigned short t = 0, r = 0, b = 0;
    unsigned int y, l;

    ofstream fd("text.txt", ios::binary);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 16; j++) {
            unsigned char c;
            c = text[i][j];

            // молодша частина коду ASCII у бітах 0-3
            t = c;
            y = t & 0x000F;

                // у бітах 4-5 знаходиться номер рядка букви
                y |= (i << 4);

            // у бітах 6-9 позиція букви у рядку (4 біти)
            y |= (j << 6);

            // у бітах 10-13 старша частина ASCII - коду символу
            t = 0;
            t = c;
            r |= (t >> 4);
            y |= (r << 10);

            // біт парності полів 4-9
            t = 1;
            b = 0;
            for (l = 4; l < 9; l++) {
                if (r & t) {
                    if (b == 0) b = 1; else b = 0;
                }
                t <<= 1;
            }

            y |= b << 14;

            // біт парності коду символу
            y |= (c & 1) << 15;

            fd << bitset<15>(y);
            fd << endl;
        }
    }
    fd.close();
}

void Decrypt_File() {
    char text[4][16];
    unsigned short t = 0, r = 0, b = 0;
    unsigned int y, l, i, j;
    ifstream fd("text.txt", ios::binary);
    ofstream od("decrypt.txt", ios::binary); // Відкриття файлу для запису розшифрованого тексту
    if (fd && od)  { // перевірка чи істинні файли  
        string line;
        while (getline(fd, line)) {
            // конвертуємо бітовий рядок у значення y
            y = bitset<16>(line).to_ulong();
            // молодша частина коду ASCII у бітах 0-3
            t = y & 0x000F;
            // у бітах 4-5 знаходиться номер рядка букви
            i = (y >> 4) & 0x000F;
            // у бітах 6-9 позиція букви у рядку (4 біти)
            j = (y >> 6) & 0x000F;
            // у бітах 10-13 старша частина ASCII - коду символу
            r = (y >> 10) & 0x000F;
            od << static_cast<char>(r << 4 | t); // Запис розшифрованого символу у файл
        }
        fd.close();
        od.close(); // Закриття обох файлів
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
