#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <array>
#include <unordered_map>

using namespace std;


// Kelas untuk merepresentasikan tiket
class Ticket {
public:
    string movie;
    string seat;
    string day;
    string time;
    double price;

    Ticket(string m, string s, string d, string t, double p) : movie(m), seat(s), day(d), time(t), price(p) {}
};

// Fungsi untuk mengubah string menjadi huruf kecil
string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Fungsi untuk membagi array menjadi dua bagian (divide and conquer)
void merge(vector<Ticket*>& tickets, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<Ticket*> L(n1);
    vector<Ticket*> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = tickets[l + i];
    for (int i = 0; i < n2; i++)
        R[i] = tickets[m + 1 + i];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i]->price <= R[j]->price) {
            tickets[k] = L[i];
            i++;
        } else {
            tickets[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        tickets[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        tickets[k] = R[j];
        j++;
        k++;
    }
}

// Fungsi untuk melakukan merge sort (divide and conquer)
void mergeSort(vector<Ticket*>& tickets, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(tickets, l, m);
        mergeSort(tickets, m + 1, r);
        merge(tickets, l, m, r);
    }
}

// Fungsi untuk menampilkan tiket
void displayTickets(const vector<Ticket*>& tickets) {
    cout << "\n--- Daftar Tiket ---\n";
    for (const auto& ticket : tickets) {
    cout << "Film: " << ticket->movie << ", Kursi: " << ticket->seat 
     << ", Hari: " << ticket->day << ", Jam: " << ticket->time 
     << ", Harga: Rp" << ticket->price << endl;
    }
    cout << "--------------------\n";
}

// Fungsi untuk mendapatkan harga tiket berdasarkan hari dan jenis kursi
double getTicketPrice(const string& seat, const string& day) {
    bool isWeekend = (day == "sabtu" || day == "minggu");
    bool isHotSeat = (seat == "hotseat");

    if (isWeekend) {
        return isHotSeat ? 60000 : 50000;
    } else {
        return isHotSeat ? 40000 : 35000;
    }
}

// Fungsi untuk menampilkan informasi harga
void displayPriceInfo(const list<string>& movies) {
    array<string, 2> seats = {"regular", "hotseat"};

    cout << "\n--- Informasi Harga Tiket ---\n";
    for (const auto& movie : movies) {
        for (const auto& seat : seats) {
            cout << "Film: " << movie << ", Kursi: " << seat << ", Hari: Weekday, Harga: Rp" << getTicketPrice(seat, "senin") << endl;
            cout << "Film: " << movie << ", Kursi: " << seat << ", Hari: Weekend, Harga: Rp" << getTicketPrice(seat, "sabtu") << endl;
        }
    }
    cout << "-----------------------------\n";
}

// Fungsi untuk memesan tiket
bool bookTicket(vector<Ticket*>& tickets, const list<string>& movies) {
    string movie, seat, day, promoCode;
    int numTickets;
    char cancel;
    bool validInput;

    cout << "\nFilm yang tersedia: ";
    for (const auto& m : movies) {
        cout <<"["<< m << "]";
        cout<<" ";
    }
    cout << endl;

    do {
        cout << "Pilih film: ";
        cin >> movie;
        movie = toLowerCase(movie);
        validInput = find(movies.begin(), movies.end(), movie) != movies.end();
        if (!validInput) {
            cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    cout << "Hari yang tersedia: Senin, Selasa, Rabu, Kamis, Jumat, Sabtu, Minggu" << endl;
    do {
        cout << "Pilih hari: ";
        cin >> day;
        day = toLowerCase(day);
        validInput = (day == "senin" || day == "selasa" || day == "rabu" || day == "kamis" || day == "jumat" || day == "sabtu" || day == "minggu");
        if (!validInput) {
            cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    cout << "Kursi yang tersedia: Regular, Hotseat" << endl;
    do {
        cout << "Pilih jenis kursi: ";
        cin >> seat;
        seat = toLowerCase(seat);
        validInput = (seat == "regular" || seat == "hotseat");
        if (!validInput) {
            cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    cout << "Jam yang tersedia: 08:00 sampai 21:00" << endl;
    do {
        cout << "Pilih jam: ";
        cin >> time;
        validInput = (time >= "08:00" && time <= "21:00");
        if (!validInput) {
            cout << "Jam yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    cout << "Berapa tiket yang ingin dipesan: ";
    cin >> numTickets;

    double ticketPrice = getTicketPrice(seat, day);
    double totalPrice = ticketPrice * numTickets;
    double payment;

    // Memasukkan kode promo
    cout << "Masukkan kode promo (opsional, tekan enter jika tidak ada): ";
    cin.ignore();
    getline(cin, promoCode);
    promoCode = toLowerCase(promoCode);

    // Jika kode promo valid, terapkan diskon 2%
    if (promoCode == "nontonyuk") {
        totalPrice *= 0.98;  // Diskon 2%
        cout << "Kode promo diterapkan. Total harga setelah diskon: Rp" << totalPrice << endl;
    }

    cout << "Harga total untuk " << numTickets << " tiket pada kursi " << seat << " di hari " << day << ": Rp" << totalPrice << endl;

    do {
        cout << "Masukkan jumlah pembayaran: ";
        cin >> payment;

        if (payment < totalPrice) {
            cout << "Jumlah uang yang dimasukkan kurang dari harga tiket. Silakan masukkan jumlah yang sesuai.\n";
        }
    } while (payment < totalPrice);

    double change = payment - totalPrice;

    for (int i = 0; i < numTickets; i++) {
        tickets.push_back(new Ticket(movie, seat, day, ticketPrice));
    }

    cout << "Tiket berhasil dipesan!" << endl;
    if (change > 0) {
        cout << "Kembalian: Rp" << change << endl;
    }

    return true;
}

// Fungsi untuk mengembalikan tiket dan refund
void refundTicket(vector<Ticket*>& tickets) {
    if (tickets.empty()) {
        cout << "Tidak ada tiket yang dipesan.\n";
        return;
    }

    string movie, seat, day;
    double refundAmount = 0.0;
    vector<Ticket*>::iterator it = tickets.begin();
    bool validInput;

    cout << "Masukkan detail tiket yang ingin direfund.\n";
    do {
        cout << "Film: ";
        cin >> movie;
        movie = toLowerCase(movie);
        validInput = any_of(tickets.begin(), tickets.end(), [&](Ticket* t) { return t->movie == movie; });
        if (!validInput) {
            cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    do {
        cout << "Kursi: ";
        cin >> seat;
        seat = toLowerCase(seat);
        validInput = any_of(tickets.begin(), tickets.end(), [&](Ticket* t) { return t->seat == seat; });
        if (!validInput) {
            cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    do {
        cout << "Hari: ";
        cin >> day;
        day = toLowerCase(day);
        validInput = any_of(tickets.begin(), tickets.end(), [&](Ticket* t) { return t->day == day; });
        if (!validInput) {
            cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
        }
    } while (!validInput);

    do {
    cout << "Jam: ";
    cin >> time;
    validInput = (time >= "08:00" && time <= "21:00");
    } while (!validInput);

    while (it != tickets.end()) {
        if ((*it)->movie == movie && (*it)->seat == seat && (*it)->day == day) {
            refundAmount += (*it)->price;
            delete *it;
            it = tickets.erase(it);
        } else {
            ++it;
}
    if (refundAmount > 0) {
        cout << "Tiket berhasil direfund. Jumlah refund: Rp" << refundAmount << endl;
    } else {
        cout << "Tiket tidak ditemukan atau tidak valid.\n";
    }
}
}

// Fungsi utama
int main() {
    vector<Ticket*> tickets;
    list<string> movies = {"avengers", "inception", "interstellar"};

    int choice;
    bool exit = false;

    while (!exit) {
        cout << "\n****************************\n";
        cout << "*        TICKET SHOP       *\n";
        cout << "****************************\n";
        cout << "1. Informasi Harga\n";
        cout << "2. Pesan Tiket\n";
        cout << "3. Tampilkan Tiket\n";
        cout << "4. Urutkan Tiket Berdasarkan Harga\n";
        cout << "5. Refund Tiket\n";
        cout << "6. Keluar\n";
        cout << "****************************\n";
        cout << "Masukkan pilihan Anda: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayPriceInfo(movies);
                break;
            case 2:
                if (bookTicket(tickets, movies)) {
                    cout << "Transaksi berhasil.\n";
                }
                break;
            case 3:
                cout << "Tiket:\n";
                displayTickets(tickets);
                break;
            case 4:
                mergeSort(tickets, 0, tickets.size() - 1);
                cout << "Tiket diurutkan berdasarkan harga:\n";
                displayTickets(tickets);
                break;
            case 5:
                refundTicket(tickets);
                break;
            case 6:
                exit = true;
                cout << "Terima kasih telah menggunakan Ticket Shop. Sampai jumpa lagi!\n";
                break;
            default:
                cout << "Input yang anda masukkan salah. Silakan coba lagi.\n";
                break;
        }
    }
// Bersihkan memori yang dialokasikan untuk tiket
    for (Ticket* ticket : tickets) {
        delete ticket;
    }
return 0;

}
