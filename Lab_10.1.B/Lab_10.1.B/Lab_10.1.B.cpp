#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KOMPUTERNI_NAUKY, INFORMATYKA, MATEMATYKA_EKONOMIKA, FIZYKA_INFORMATYKA, TRUDOVE_NAVCHANNIA };
string specStr[] = { "Комп'ютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

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
    cout << "Введіть кількість студентів: ";
    cin >> N;

    Student* students = new Student[N];
    Create(students, N);
    Print(students, N);
    PrintAverage(students, N);
    cout << "Процент студентів, які отримали оцінку '5' або '4' з фізики: "
        << PercentHighPhysics(students, N) << "%" << endl;

    delete[] students;
    return 0;
}

void Create(Student* students, const int N) {
    int spec;
    for (int i = 0; i < N; i++) {
        cout << "Студент № " << i + 1 << ":" << endl;
        cin.ignore();
        cout << "  Прізвище: ";
        getline(cin, students[i].prizv);
        cout << "  Курс: ";
        cin >> students[i].kurs;
        cout << "  Спеціальність (0 - Комп'ютерні науки, 1 - Інформатика, 2 - Математика та економіка, 3 - Фізика та інформатика, 4 - Трудове навчання): ";
        cin >> spec;
        students[i].spec = (Specialnist)spec;
        cout << "  Оцінка з фізики: ";
        cin >> students[i].fizyka;
        cout << "  Оцінка з математики: ";
        cin >> students[i].matematika;
        if (students[i].spec == KOMPUTERNI_NAUKY) {
            cout << "  Оцінка з програмування: ";
            cin >> students[i].programuvannia;
        }
        else if (students[i].spec == INFORMATYKA) {
            cout << "  Оцінка з чисельних методів: ";
            cin >> students[i].chyselni_metody;
        }
        else {
            cout << "  Оцінка з педагогіки: ";
            cin >> students[i].pedagogika;
        }
        cout << endl;
    }
}

void Print(const Student* students, const int N) {
    cout << "=======================================================================================================================" << endl;
    cout << "| №  | Прізвище  | Курс | Спеціальність           | Фізика | Математика | Програмування| Чисельні методи | Педагогіка |" << endl;
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
    cout << "Середній бал кожного студента:" << endl;
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
