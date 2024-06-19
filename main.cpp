#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct bilgi {
    char ad[50];
    int kod;
    int fiyat;
    int stok;
    char tip[20];
    char receterengi[15];
    char etkibolgesi[50];
    bilgi* link;
};

bilgi* ilac = NULL;

bilgi* newnode() {
    bilgi* newilac = new bilgi;
    cout << "\nIlacin adini giriniz: ";
    cin.ignore();
    cin.getline(newilac->ad, 50);
    cout << "Ilacin kodunu giriniz: ";
    cin >> newilac->kod;
    cout << "Ilacin fiyatini giriniz: ";
    cin >> newilac->fiyat;
    cout << "Ilacin stogunu giriniz: ";
    cin >> newilac->stok;
    cout << "Ilacin tipini giriniz (tablet, kapsul, surup, merhem, toz, ampul vs.): ";
    cin >> newilac->tip;
    cout << "Ilacin recete rengini giriniz (kirmizi, yesil, mor, turuncu): ";
    cin >> newilac->receterengi;
    cout << "Ilacin etki bolgesini giriniz (Merkezi sinir sistemi, immun sistem, solunum yollari vs.): ";
    cin.ignore();
    cin.getline(newilac->etkibolgesi, 100);
    newilac->link = NULL;
    return newilac;
}

void addhead(bilgi*& ilac, bilgi* ilac_) {
    ilac_->link = ilac;
    ilac = ilac_;
}

// Bağlı listeyi dosyaya yazar
void yazDosya(bilgi* ilac) {
    ofstream dosyayaz("eczane.dat", ios::binary);
    bilgi* y_ilac = ilac;
    while (y_ilac != NULL) {
        dosyayaz.write(reinterpret_cast<char*>(y_ilac), sizeof(bilgi));
        y_ilac = y_ilac->link;
    }
    dosyayaz.close();
}

// Dosyadan bağlı listeye okur
void okuDosya(bilgi*& ilac) {
    ifstream dosyaoku("eczane.dat", ios::binary);
    if (!dosyaoku) {
        cout << "Dosya acilamadi!";
        return;
    }
    bilgi* onceki = NULL;
    bilgi* yeni = NULL;
    while (true) {
        yeni = new bilgi;
        if (!dosyaoku.read(reinterpret_cast<char*>(yeni), sizeof(bilgi))) {
            delete yeni;
            break;
        }
        yeni->link = NULL;
        if (onceki == NULL) {
            ilac = yeni;
        } else {
            onceki->link = yeni;
        }
        onceki = yeni;
    }
    dosyaoku.close();
}

// KAYIT EKLEME
void kayit_ekleme() {
    bilgi* gecici = NULL;
    okuDosya(gecici); // Dosyadaki mevcut verileri okur
    char secim;
    do {
        bilgi* ilac_ = newnode();
        addhead(gecici, ilac_);
        cout << "\nBaska ilac eklemek istiyor musunuz? (e/h): ";
        cin >> secim;
    } while (secim == 'e' || secim == 'E');
    yazDosya(gecici); // Yeni verileri dosyaya yazar
}

// KAYIT LİSTELEME
void kayit_listele() {
    bilgi* gecici = NULL;
    okuDosya(gecici); // Dosyadaki mevcut verileri okur
    bilgi* y_ilac = gecici;
    while (y_ilac != NULL) {
        cout << endl;
        cout << "Ad: " << y_ilac->ad << endl;
        cout << "Kod: " << y_ilac->kod << endl;
        cout << "Fiyat: " << y_ilac->fiyat << endl;
        cout << "Stok: " << y_ilac->stok << endl;
        cout << "Tip: " << y_ilac->tip << endl;
        cout << "Recete Rengi: " << y_ilac->receterengi << endl;
        cout << "Etki Bolgesi: " << y_ilac->etkibolgesi << endl;
        y_ilac = y_ilac->link;
    }
}

// KAYIT ARAMA
void kayit_ara() {
    bilgi* gecici = NULL;
    okuDosya(gecici); // Dosyadaki mevcut verileri okur
    bilgi* y_ilac = gecici;
    int kod_;
    cout << "\nAramak istediginiz ilacin kodunu giriniz: ";
    cin >> kod_;

    bool bulundu = false;
    while (y_ilac != NULL) {
        if (y_ilac->kod == kod_) {
            cout << "Ad: " << y_ilac->ad << endl;
            cout << "Kod: " << y_ilac->kod << endl;
            cout << "Fiyat: " << y_ilac->fiyat << endl;
            cout << "Stok: " << y_ilac->stok << endl;
            cout << "Tip: " << y_ilac->tip << endl;
            cout << "Recete Rengi: " << y_ilac->receterengi << endl;
            cout << "Etki Bolgesi: " << y_ilac->etkibolgesi << endl;
            cout << endl;
            bulundu = true;
            break;
        }
        y_ilac = y_ilac->link;
    }

    if (!bulundu) {
        cout << "Aranan ilac bulunamadi!" << endl;
    }
}

// KAYIT GÜNCELLEME
void kayit_guncelle() {
    bilgi* gecici = NULL;
    okuDosya(gecici); // Dosyadaki mevcut verileri okur
    bilgi* y_ilac = gecici;
    int g_kod;
    cout << "Guncellemek istediginiz ilacin kodunu giriniz: ";
    cin >> g_kod;

    bool bulundu = false;
    while (y_ilac != NULL) {
        if (y_ilac->kod == g_kod) {
            cout << "Ad: " << y_ilac->ad << endl;
            cout << "Kod: " << y_ilac->kod << endl;
            cout << "Fiyat: " << y_ilac->fiyat << endl;
            cout << "Stok: " << y_ilac->stok << endl;
            cout << "Tip: " << y_ilac->tip << endl;
            cout << "Recete Rengi: " << y_ilac->receterengi << endl;
            cout << "Etki Bolgesi: " << y_ilac->etkibolgesi << endl;
            cout << endl;
            cout << "Guncellemek istediginiz ilac bu mu? (e/h): ";
            char secim_;
            cin >> secim_;
            if (secim_ == 'e' || secim_ == 'E') {
                cout << "Ad: ";
                cin.ignore();
                cin.getline(y_ilac->ad, 50);
                cout << "Kod: ";
                cin >> y_ilac->kod;
                cout << "Fiyat: ";
                cin >> y_ilac->fiyat;
                cout << "Stok: ";
                cin >> y_ilac->stok;
                cout << "Tip: ";
                cin >> y_ilac->tip;
                cout << "Recete Rengi: ";
                cin >> y_ilac->receterengi;
                cout << "Etki Bolgesi: ";
                cin.ignore();
                cin.getline(y_ilac->etkibolgesi, 100);

                bulundu = true;
                break;
            }
        }
        y_ilac = y_ilac->link;
    }

    if (!bulundu) {
        cout << "Aranan ilac bulunamadi!" << endl;
    } else {
        yazDosya(gecici); // Güncellenmiş verileri dosyaya yazar
    }
}

// KAYIT SİLME
void kayit_sil() {
    bilgi* gecici = NULL;
    okuDosya(gecici); // Dosyadaki mevcut verileri okur
    bilgi* y_ilac = gecici;
    bilgi* onceki = NULL;
    int s_kod;
    char secim_s;
    cout << "Silmek istediginiz ilacin kodunu giriniz: ";
    cin >> s_kod;

    bool bulundu = false;
    while (y_ilac != NULL) {
        if (y_ilac->kod == s_kod) {
            cout << "Ad: " << y_ilac->ad << endl;
            cout << "Kod: " << y_ilac->kod << endl;
            cout << "Fiyat: " << y_ilac->fiyat << endl;
            cout << "Stok: " << y_ilac->stok << endl;
            cout << "Tip: " << y_ilac->tip << endl;
            cout << "Recete Rengi: " << y_ilac->receterengi << endl;
            cout << "Etki Bolgesi: " << y_ilac->etkibolgesi << endl;
            cout << endl;
            cout << "Silmek istediginiz ilac bu mu? (e/h): ";
            cin >> secim_s;
            if (secim_s == 'e' || secim_s == 'E') {
                if (onceki == NULL) {
                    gecici = y_ilac->link;
                } else {
                    onceki->link = y_ilac->link;
                }
                delete y_ilac;
                bulundu = true;
                break;
            }
        }
        onceki = y_ilac;
        y_ilac = y_ilac->link;
    }

    if (!bulundu) {
        cout << "Aranan ilac bulunamadi!" << endl;
    } else {
        yazDosya(gecici); // Kalan verileri dosyaya yazar
    }
}

int main() {
    int secim;
            cout << "                 <ECZANE OTOMASYONU>\n";
    do {
        cout << "\n-----------YAPMAK ISTEDIGINIZ ISLEMI SECINIZ-------------";
        cout << "\n| 1 - Ilac ekleme                                       |";
        cout << "\n| 2 - Ilac listeleme                                    |"; 
        cout << "\n| 3 - Ilac arama                                        |";
        cout << "\n| 4 - Ilac Guncelleme                                   |";
        cout << "\n| 5 - Ilac Silme                                        |";
        cout << "\n| 6 - Cikis                                             |";
        cout << "\n---------------------------------------------------------\n";
        cout << "Seciminizi giriniz:";
        cin >> secim;
        switch (secim) {
            case 1:
                kayit_ekleme();
                break;
            case 2:
                kayit_listele();
                break;
            case 3:
                kayit_ara();
                break;
            case 4:
                kayit_guncelle();
                break;
            case 5:
                kayit_sil();
                break;
            case 6:
                cout << "Programdan cikiliyor...\n";
                break;
            default:
                cout << "Gecersiz secim!\n";
        }
    } while (secim != 6);
    return 0;
}


