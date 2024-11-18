#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KOMPUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_EKONOMIKA, FIZYKA_INFORMATYKA, TRUDOVE_NAVCHANNIA };
string specStr[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student {
    string prizv;
    int kurs;
    Specialnist spec;
    int fizyka;
    int matematika;
    union {
        int programuvannia;
        int chyselni_metody;
        int pedagogika;
    };
};

void Create(Student* students, const int N);
void Print(const Student* students, const int N);
void PrintAverage(const Student* students, const int N);
double PercentHighPhysics(const Student* students, const int N);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int N;
    cout << "������ ������� ��������: ";
    cin >> N;

    Student* students = new Student[N];
    Create(students, N);
    Print(students, N);
    PrintAverage(students, N);
    cout << "������� ��������, �� �������� ������ '5' ��� '4' � ������: "
        << PercentHighPhysics(students, N) << "%" << endl;

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cin.ignore();
        cout << "  �������: ";
        getline(cin, students[i].prizv);
        cout << "  ����: ";
        cin >> students[i].kurs;
        cout << "  ������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
        cin >> spec;
        students[i].spec = (Specialnist)spec;
        cout << "  ������ � ������: ";
        cin >> students[i].fizyka;
        cout << "  ������ � ����������: ";
        cin >> students[i].matematika;
        if (students[i].spec == KOMPUTERNI_NAUKY) {
            cout << "  ������ � �������������: ";
            cin >> students[i].programuvannia;
        }
        else if (students[i].spec == INFORMATYKA) {
            cout << "  ������ � ��������� ������: ";
            cin >> students[i].chyselni_metody;
        }
        else {
            cout << "  ������ � ���������: ";
            cin >> students[i].pedagogika;
        }
        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "=======================================================================================================================" << endl;
    cout << "| �  | �������  | ���� | ������������           | Գ���� | ���������� | �������������| ������� ������ | ��������� |" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << "| " << setw(3) << left << i + 1 << "";
        cout << "| " << setw(10) << left << students[i].prizv;
        cout << "| " << setw(4) << students[i].kurs << " ";
        cout << "| " << setw(24) << left << specStr[students[i].spec];
        cout << "| " << setw(6) << students[i].fizyka << " ";
        cout << "| " << setw(10) << students[i].matematika << " ";
        if (students[i].spec == KOMPUTERNI_NAUKY) {
            cout << "| " << setw(12) << students[i].programuvannia << " ";
            cout << "| " << setw(16) << " " << "| " << setw(11) << " " << "|" << endl;
        }
        else if (students[i].spec == INFORMATYKA) {
            cout << "| " << setw(12) << " " << "| " << setw(16) << students[i].chyselni_metody << " ";
            cout << "| " << setw(12) << " " << "|" << endl;
        }
        else {
            cout << "| " << setw(13
            ) << " " << "| " << setw(16) << " ";
            cout << "| " << setw(11) << students[i].pedagogika << "|" << endl;
        }
    }
    cout << "=======================================================================================================================" << endl;
}

void PrintAverage(const Student* students, const int N) {
    cout << "������� ��� ������� ��������:" << endl;
    for (int i = 0; i < N; i++) {
        double avg;
        if (students[i].spec == KOMPUTERNI_NAUKY) {
            avg = (students[i].fizyka + students[i].matematika + students[i].programuvannia) / 3.0;
        }
        else if (students[i].spec == INFORMATYKA) {
            avg = (students[i].fizyka + students[i].matematika + students[i].chyselni_metody) / 3.0;
        }
        else {
            avg = (students[i].fizyka + students[i].matematika + students[i].pedagogika) / 3.0;
        }
        cout << "  " << students[i].prizv << ": " << fixed << setprecision(2) << avg << endl;
    }
}

double PercentHighPhysics(const Student* students, const int N) {
    int countHigh = 0, total = 0;
    for (int i = 0; i < N; i++) {
        if (students[i].fizyka == 4 || students[i].fizyka == 5) {
            countHigh++;
        }
        total++;
    }
    return (total > 0) ? (100.0 * countHigh / total) : 0.0;
}
