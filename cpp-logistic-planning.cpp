//// // ISE 105 - Programlamaya Giriş
////// Ödev No: 1 - Lojistik Planlama
////// Geliştirici: Eda GÖRPÜZ

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Sabitler
const int BOYUT = 10;
const int MUSTERI_SAYISI = 5;
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string BLUE = "\033[34m";

// Yapılar
struct Nokta {
    int x, y;
    int* adres;
};

// Fonksiyon Prototipleri
void matrisOlustur(int matris[BOYUT][BOYUT]);
void musteriSec(Nokta musteriler[MUSTERI_SAYISI], int matris[BOYUT][BOYUT]);
void matrisYazdir(int matris[BOYUT][BOYUT], Nokta kurye, Nokta musteriler[MUSTERI_SAYISI], bool ziyaretEdilen[BOYUT][BOYUT]);
int yolPlanla(int matris[BOYUT][BOYUT], Nokta& kurye, Nokta musteriler[MUSTERI_SAYISI], bool ziyaretEdilen[BOYUT][BOYUT]);
void dosyayaYazdir(Nokta musteriler[MUSTERI_SAYISI], int toplamMaliyet);

int main() {
    srand(time(0));

    int matris[BOYUT][BOYUT];
    Nokta musteriler[MUSTERI_SAYISI];
    Nokta kurye = { 0, 0, nullptr };
    bool ziyaretEdilen[BOYUT][BOYUT] = { false };

    matrisOlustur(matris);
    musteriSec(musteriler, matris);

    cout << "Musteri Konumlari:" << endl;
    for (int i = 0; i < MUSTERI_SAYISI; i++) {
        cout << "Musteri " << i + 1 << ": (" << musteriler[i].x << ", " << musteriler[i].y << ") Adres: " << musteriler[i].adres << endl;
    }
    cout << endl;

    cout << "Ilk Durum:" << endl;
    matrisYazdir(matris, kurye, musteriler, ziyaretEdilen);

    int toplamMaliyet = yolPlanla(matris, kurye, musteriler, ziyaretEdilen);

    cout << "Son Durum:" << endl;
    matrisYazdir(matris, kurye, musteriler, ziyaretEdilen);

    dosyayaYazdir(musteriler, toplamMaliyet);

    return 0;
}

void matrisOlustur(int matris[BOYUT][BOYUT]) {
    for (int i = 0; i < BOYUT; i++) {
        for (int j = 0; j < BOYUT; j++) {
            matris[i][j] = rand() % 100 + 1;
        }
    }
}

void musteriSec(Nokta musteriler[MUSTERI_SAYISI], int matris[BOYUT][BOYUT]) {
    for (int i = 0; i < MUSTERI_SAYISI; i++) {
        musteriler[i].x = rand() % BOYUT;
        musteriler[i].y = rand() % BOYUT;
        musteriler[i].adres = &matris[musteriler[i].x][musteriler[i].y];
    }
}

void matrisYazdir(int matris[BOYUT][BOYUT], Nokta kurye, Nokta musteriler[MUSTERI_SAYISI], bool ziyaretEdilen[BOYUT][BOYUT]) {
    for (int i = 0; i < BOYUT; i++) {
        for (int j = 0; j < BOYUT; j++) {
            bool yazildi = false;

            if (kurye.x == i && kurye.y == j) {
                cout << RED << "K\t" << RESET;
                yazildi = true;
            }

            for (int k = 0; k < MUSTERI_SAYISI; k++) {
                if (musteriler[k].x == i && musteriler[k].y == j) {
                    cout << BLUE << "M\t" << RESET;
                    yazildi = true;
                    break;
                }
            }

            if (!yazildi) {
                if (ziyaretEdilen[i][j]) {
                    cout << GREEN << matris[i][j] << "\t" << RESET;
                }
                else {
                    cout << matris[i][j] << "\t";
                }
            }
        }
        cout << endl;
    }
    cout << endl;
}

int yolPlanla(int matris[BOYUT][BOYUT], Nokta& kurye, Nokta musteriler[MUSTERI_SAYISI], bool ziyaretEdilen[BOYUT][BOYUT]) {
    int toplamMaliyet = 0;
    ziyaretEdilen[kurye.x][kurye.y] = true;

    for (int i = 0; i < MUSTERI_SAYISI; i++) {
        int hedefX = musteriler[i].x;
        int hedefY = musteriler[i].y;

        while (kurye.x != hedefX) {
            if (kurye.x < hedefX) kurye.x++;
            else kurye.x--;
            toplamMaliyet += matris[kurye.x][kurye.y];
            ziyaretEdilen[kurye.x][kurye.y] = true;
            matrisYazdir(matris, kurye, musteriler, ziyaretEdilen);
            cout << "Toplam Maliyet: " << toplamMaliyet << endl;
        }

        while (kurye.y != hedefY) {
            if (kurye.y < hedefY) kurye.y++;
            else kurye.y--;
            toplamMaliyet += matris[kurye.x][kurye.y];
            ziyaretEdilen[kurye.x][kurye.y] = true;
            matrisYazdir(matris, kurye, musteriler, ziyaretEdilen);
            cout << "Toplam Maliyet: " << toplamMaliyet << endl;
        }
    }

    while (kurye.x != 0) {
        kurye.x--;
        toplamMaliyet += matris[kurye.x][kurye.y];
        ziyaretEdilen[kurye.x][kurye.y] = true;
        matrisYazdir(matris, kurye, musteriler, ziyaretEdilen);
        cout << "Toplam Maliyet: " << toplamMaliyet << endl;
    }

    while (kurye.y != 0) {
        kurye.y--;
        toplamMaliyet += matris[kurye.x][kurye.y];
        ziyaretEdilen[kurye.x][kurye.y] = true;
        matrisYazdir(matris, kurye, musteriler, ziyaretEdilen);
        cout << "Toplam Maliyet: " << toplamMaliyet << endl;
    }

    return toplamMaliyet;
}

void dosyayaYazdir(Nokta musteriler[MUSTERI_SAYISI], int toplamMaliyet) {
    ofstream dosya("Cost.txt");

    if (dosya.is_open()) {
        dosya << "Musteri Bilgileri:\n";
        for (int i = 0; i < MUSTERI_SAYISI; i++) {
            dosya << "Musteri " << i + 1 << ": (" << musteriler[i].x << ", " << musteriler[i].y << ") Adres: " << musteriler[i].adres << endl;
        }

        dosya << "Toplam Maliyet: " << toplamMaliyet << endl;
        dosya.close();
    }
    else {
        cout << "Dosya yazma hatasi!" << endl;
    }
}

