#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unistd.h>
using namespace std;

#define red_color "\x1b[31m"
#define green_color "\x1b[32m"
#define yellow_color "\x1b[33m"
#define cyan_color "\x1b[36m"
#define reset_color "\x1b[0m"
#define orange_color "\x1b[38;5;208m"

class Bicicleta {
private:
    string tip;
    string zona;
    string nr;
public:
    Bicicleta() = default;
    string get_tip() {
        return this -> tip;
    }
    string get_zona() {
        return this -> zona;
    }
    string get_nr() {
        return this -> nr;
    }
    void set_tip(string tip1) {
        this -> tip = move(tip1);
    }
    void set_zona(string zona1) {
        this -> zona = move(zona1);
    }
    void set_nr(string nr1) {
        this -> nr = move(nr1);
    }
};

ostream &operator<<(ostream &out, Bicicleta &bicicleta) {
    out << orange_color "Tip: " << bicicleta.get_tip() << endl;
    out << "Zona: " << bicicleta.get_zona() << endl;
    out << "Nr: " << bicicleta.get_nr() <<reset_color<< endl;
    return out;
}

vector < Bicicleta > citire() {
    vector < Bicicleta > content;
    Bicicleta bicicleta;
    string line, word;
    vector < string > row;
    fstream file("bicicleta.csv", ios:: in );
    if (file.is_open()) {
        while (getline(file, line)) {
            
            row.clear();
            stringstream str(line);
            while (getline(str, word, ',')) {
                row.push_back(word);
            }
            bicicleta.set_tip(row[0]);
            bicicleta.set_zona(row[1]);
            bicicleta.set_nr(row[2]);
            content.push_back(bicicleta);
        }
    } else
        cout <<red_color "Nu se poate\n" reset_color;
    return content;
}

void adaugare_bicicleta(vector < Bicicleta > data, const string& tip, const string& zona) {
    for (auto & i : data) {
        if (i.get_tip()==tip && i.get_zona()==zona) {
            int temp = stoi(i.get_nr());
            temp++;
            i.set_nr(to_string(temp));
        }
        cout << i;
        puts("");
    }
    ofstream fout("bicicleta.csv");
    for (auto & i : data) {
        fout << i.get_tip() << "," << i.get_zona() << "," << i.get_nr() << endl;

    }
}

void inchiriere_bicicleta(vector < Bicicleta > data, const string& tip, const string& zona) {
    int ok=0;
    for (auto & i : data) {
        if (i.get_tip()==tip && i.get_zona()==zona && i.get_nr()!="0") {
            int temp = stoi(i.get_nr());
            temp--;
            i.set_nr(to_string(temp));
            ok++;
        }
        cout << i;
        puts("");
    }
    if(ok==0) {
        cout << red_color "Nu exista biciclete in acea zona!" << reset_color << endl<<endl;
    } else {
        puts(green_color "Felicitari! Tocmai ati inchiriat o bicicleta, aveti 10 ore la dispozitie sa o returnati!" reset_color);
        puts("");
        ofstream fout("bicicleta.csv");
        for (auto & i : data) {
            fout << i.get_tip() << "," << i.get_zona() << "," << i.get_nr() << endl;
        }
    }
}

void cautare_zona(vector < Bicicleta > biciclete, const string& zona) {
    int ok = 0;
    for (auto & i : biciclete) {
        if (i.get_zona()==zona) {
            cout << i;
            ok = 1;
            cout << endl;
        }
    }
    if (ok == 0) {
        puts("");
        cout << red_color "Nu exista bicicleta in aceasta zona!" << reset_color << endl;
        puts("");
    }
}

void cautare_tip(vector < Bicicleta > biciclete, const string& tip) {
    int ok = 0;
    for (auto & i : biciclete) {
        if (i.get_tip()==tip) {
            cout << i;
            ok = 1;
            cout << endl;
        }
    }
    if (ok == 0) {
        puts("");
        cout << red_color "Nu exista bicicleta de acest tip!" << reset_color << endl;
        puts("");
    }
}

void salvare(vector < Bicicleta > biciclete) {
    ofstream fout("bicicleta.csv");
    for (auto & i : biciclete) {
        fout << i.get_tip() << "," << i.get_zona() << "," << i.get_nr() << endl;
    }
}

void timer() {
    int h = 10, m = 0, s = 0;
    system("clear");
    cout << orange_color "Timp ramas: " << h << ":" << m << ":" << s << endl;
    sleep(1);
    system("clear");
    while (h > 0) {
        while (m > 0) {
            while (s > 0) {
                cout << orange_color "Timp ramas: " << h << ":" << m << ":" << s << endl;
                s--;
                sleep(1);
                system("clear");
            }
            m--;
            s = 59;
        }
        h--;
        m = 59;
        s = 59;
    }
}

int main() {
    int x, nr1;
    do {
        puts(green_color "/=================================================================\\" reset_color);
        puts(green_color "               Sistem pentru rezervarea bicicletelor               " reset_color);
        puts(green_color "/=================================================================\\" reset_color);
        puts("");
        puts(yellow_color "Apasa 1 pentru a vedea bicicletele disponibile" reset_color);
        puts(yellow_color "Apasa 2 pentru a adauga bicicleta" reset_color);
        puts(yellow_color "Apasa 3 pentru a inchiria bicicleta" reset_color);
        puts(yellow_color "Apasa 4 pentru a returna bicicleta" reset_color);
        puts(yellow_color "Apasa 5 pentru a cauta bicicleta dupa tip" reset_color);
        puts(yellow_color "Apasa 6 pentru a cauta bicicleta dupa zona" reset_color);
        puts(yellow_color "Apasa 7 pentru a salva bicicletele in fisier" reset_color);
        puts(red_color "Apasa 0 pentru a iesi" reset_color);
        cout << cyan_color "Tasta: " reset_color;
        cin >> x;
        switch (x) {
            case 1: {
                vector < Bicicleta > biciclete = citire();
                cout << green_color "Bicicletele disponibile sunt:" reset_color << endl;
                for (auto & i : biciclete) {
                    cout << i;
                    puts("");
                }
                break;
            }
            case 2: {
                vector < Bicicleta > biciclete = citire();
                string tip, zona;
                cout << green_color "Introduceti tipul bicicletei: " reset_color;
                cin >> tip;
                cout << green_color "Introduceti zona: " reset_color;
                cin >> zona;
                adaugare_bicicleta(biciclete, tip, zona);
                cout<<green_color "Ati adaugat bicicleta cu succes!" reset_color <<endl<<endl;
                break;
            }
            case 3: {
                string tip, zona;
                cout << green_color "Introduceti tipul bicicletei: " reset_color;
                cin >> tip;
                cout << green_color "Introduceti zona: " reset_color;
                cin >> zona;
                inchiriere_bicicleta(citire(), tip, zona);
                puts(green_color "Apasa 1 pentru a continua" reset_color);
                puts(red_color "Apasa 2 pentru a vedea timpul ramas" reset_color);
                cout << cyan_color "Tasta: " reset_color;
                int nr2;
                cin >> nr2;
                switch (nr2) {
                    case 1: {
                        break;
                    }
                    case 2: {
                        timer();
                        break;
                    }
                    default: {
                        cout << red_color "Nu exista optiunea!" << reset_color << endl;
                        break;
                    }
                }
                break;
            }
            case 4: {
                string tip, zona;
                cout << green_color "Introduceti tipul bicicletei: " reset_color;
                cin >> tip;
                cout << green_color "Introduceti zona: " reset_color;
                cin >> zona;
                adaugare_bicicleta(citire(), tip, zona);
                cout<<green_color "Ati returnat bicicleta cu succes!" reset_color <<endl<<endl;
                break;
            }
            case 5: {
                vector < Bicicleta > biciclete = citire();
                string tip;
                cout << green_color "Introduceti tipul bicicletei: " reset_color;
                cin >> tip;
                cautare_tip(biciclete, tip);
                break;
            }
            case 6: {
                vector < Bicicleta > biciclete = citire();
                string zona;
                cout << green_color "Introduceti zona: " reset_color;
                cin >> zona;
                cautare_zona(biciclete, zona);
                break;
            }
            case 7: {
                vector < Bicicleta > biciclete = citire();
                cout<<endl;
                puts(green_color "Datele au fost salvate cu succes!\n" reset_color);
                salvare(biciclete);
                break;
            }
            case 0: {
                exit(0);
            }
            default: {
                cout << red_color "Optiune invalida" reset_color << endl;
            }
        }
        puts(green_color "Apasa 1 pentru a reveni la meniul principal" reset_color);
        puts(red_color "Apasa 0 pentru a iesi" reset_color);
        cout << cyan_color "Tasta: " reset_color;
        cin >> nr1;
        cout << endl;
        if (nr1 == 0)
            exit(0);
    } while (true);
}
