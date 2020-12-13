#include <iostream>
#include <Windows.h>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum Specialty { КН, ІТ, ПЗ, ВП, СА };

string specialtyStr[] = { "КН", "ІТ", "ПЗ", "ВП", "СА" };

struct Student
{
	char prizv[64];
	int kurs;
	Specialty specialty;
	int physics;
	int mathematics;
	union
	{
		int programming;
		int NumericalMethods;
		int pedagogy;
	};
};

void EnterSave(char* fname);
void LoadPrint(char* fname);
int fRead(fstream& f, const int i);
char SRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void SortBIN(char* fname);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char fname[61];
	char ch;
	double MinAve = 0.0;
	int countPhysics = 0;
	int countMathematics = 0;
	int countInformatics = 0;
	do
	{
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення та зберігання даних " << endl;
		cout << " [2] - завантаження та виведення даних" << endl;
		cout << " [3] - фізичне впорядкування даних файлу" << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> ch;
		cout << endl << endl << endl;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
			EnterSave(fname);
			break;
		case '2':
			cin.get();
			cin.sync();
			cout << "Введіть ім'я файлу: "; cin.getline(fname, 61);
			LoadPrint(fname);
			break;
		case '3':
			SortBIN(fname);
			cout << "Дані файлу впорядковано!" << endl;
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (ch != '0');

	system("pause");
	return 0;
}

void EnterSave(char* fname)
{
	ofstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка зчитування файлу '" << fname << "'" << endl;
		return;
	}

	Student student;

	int specialty;
	char ch;
	int i = 0;
	do
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		++i;
		cin.sync();
		cout << "Прізвище: "; cin >> student.prizv;
		do
		{
			cout << "Курс: "; cin >> student.kurs;
		} while (!(student.kurs > 0));
		do
		{
			cout << "Спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА): ";
			cin >> specialty;
			student.specialty = (Specialty)specialty;
		} while (!(specialty >= 0 && specialty <= 4));
		do
		{
			cout << "Оцінка з фізики: "; cin >> student.physics;
		} while (!(student.physics >= 0 && student.physics <= 5));
		do
		{
			cout << "Оцінка з математики: "; cin >> student.mathematics;
		} while (!(student.mathematics >= 0 && student.mathematics <= 5));
		do
		{
			switch (student.specialty)
			{
			case КН:
				cout << "Оцінка з програмування: "; cin >> student.programming;
				break;
			case ІТ:
				cout << "Оцінка з чисельних методів: "; cin >> student.NumericalMethods;
				break;
			case ПЗ:
				cout << "Оцінка з педагогіки: "; cin >> student.pedagogy;
				break;
			case ВП:
				cout << "Оцінка з педагогіки: "; cin >> student.pedagogy;
				break;
			case СА:
				cout << "Оцінка з педагогіки: "; cin >> student.pedagogy;
				break;
			}
			cout << endl;
		} while (!((student.programming >= 0 && student.programming <= 5) || (student.NumericalMethods >= 0 && student.NumericalMethods <= 5) || (student.pedagogy >= 0 && student.pedagogy <= 5)));
	
		if (!f.write((char*)&student, sizeof(Student)))
		{
			cerr << "Помилка запису файлу" << endl;
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
}

void LoadPrint(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка зчитування файлу '" << fname << "'" << endl;
		return;
	}

	Student student;
	int i = 0;

	cout << "============================================================================================================"
		 << endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		 << endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		 << endl;
	while (f.read((char*)&student, sizeof(Student)))
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(9) << left << student.prizv
			 << "| " << setw(4) << left << student.kurs << " "
			 << "| " << setw(14) << left << specialtyStr[student.specialty]
			 << "| " << setw(6) << left << student.physics << " "
			 << "| " << setw(10) << left << student.mathematics << " ";
		switch (student.specialty)
		{
		case КН:
			cout << "| " << setw(13) << left
				 << student.programming << " |" << setw(18) << right << "|" << setw(13) << right << "|" << endl;
			break;
		case ІТ:
			cout << "| " << setw(16) << right
				 << "| " << setw(16) << left << student.NumericalMethods << "|" << setw(13) << right << "|" << endl;
			break;
		case ПЗ:
			cout << "| " << setw(15) << right << "|" << setw(19) << right
				 << "| " << setw(12) << left << student.pedagogy << "|" << endl;
			break;
		case ВП:
			cout << "| " << setw(15) << right << "|" << setw(19) << right
				 << "| " << setw(11) << left << student.pedagogy << "|" << endl;
			break;
		case СА:
			cout << "| " << setw(15) << right << "|" << setw(19) << right
				 << "| " << setw(11) << left << student.pedagogy << "|" << endl;
			break;
		}
		cout << "------------------------------------------------------------------------------------------------------------"
			<< endl;
		++i;
	}
}

int fRead(fstream& f, const int i)
{
	Student student;
	f.seekg(i * (long)sizeof(Student)); // встановили вказівник
	f.read((char*)&student, sizeof(Student)); // прочитали значення
	int specialty = student.specialty;
	return specialty;
}

char SRead(fstream& f, const int i)
{
	Student student;
	f.seekg(i * (long)sizeof(Student)); // встановили вказівник
	f.read((char*)&student, sizeof(Student)); // прочитали значення
	char prizv[64];
	strcpy_s(prizv, sizeof(prizv), student.prizv);
	return *prizv;
}

int TRead(fstream& f, const int i)
{
	Student student;
	f.seekg(i * (long)sizeof(Student)); // встановили вказівник
	f.read((char*)&student, sizeof(Student)); // прочитали значення
	int kurs = student.kurs;
	return kurs;
}

void SortBIN(char* fname)
{
	fstream f(fname, ios::binary | ios::in | ios::out);

	f.seekg(0 * (long)sizeof(Student), ios::end);
	int size = f.tellg() / (sizeof(Student));
	f.seekg(0, ios::beg);
	for (int i0 = 1; i0 < size; i0++)
		for (int i1 = 0; i1 < size - i0; i1++)
		{
			int specialty1 = fRead(f, i1);
			int specialty2 = fRead(f, i1 + 1);
			char prizv1 = SRead(f, i1);
			char prizv2 = SRead(f, i1 + 1);
			int kurs1 = TRead(f, i1);
			int kurs2 = TRead(f, i1 + 1);
			if ((specialty1 > specialty2)
				||
				(specialty1 == specialty2 && prizv1 < prizv2)
				||
				(specialty1 == specialty2 && prizv1 == prizv2 && kurs1 > kurs2))
				fChange(f, i1, i1 + 1);
		}
	f.seekp(0, ios::end);
}

void fChange(fstream& f, const int i, const int j)
{
	Student si, sj, temp;
	f.seekg(i * (long)sizeof(Student));
	f.read((char*)&si, sizeof(Student));
	temp = si;
	f.seekg(j * (long)sizeof(Student));
	f.read((char*)&sj, sizeof(Student));
	f.seekp(i * (long)sizeof(Student));
	f.write((char*)&sj, sizeof(Student));
	f.seekp(j * (long)sizeof(Student));
	f.write((char*)&temp, sizeof(Student));
}