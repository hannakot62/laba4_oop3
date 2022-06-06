//11. Написать программу, управляющую работой библиотеки.Создать
//классы : «Книга», «Отдел», «Библиотека».В классах реализовать следующие
//функции : добавление, удаление книг из отделов, выдача книг на абонемент.
//Классы должны содержать методы доступа и изменения всех полей.


#include <iostream>
#include <iomanip>
#include <windows.h>
#include <string.h>
using namespace std;

int CreateInt();
int CheckInt(char c[]);

class Department;

class Library {
private:
	Department* departments;
	int departmentsQuantity;
	int number;
	string address;
public:
	Library();
	Library(int number, string address, int departmentsQuantity);
	~Library();

	void SetAddress(string newAddress);
	void SetNumber(int newNumber);
	void GetInfo();
	void ShowDepartments();
	void operator=(Library& newLib);
	void AddDep();
	int ChooseADep();
	Department* GetDep(int choise);
};

class Book {
private:
	string title;
	string author;
	bool available;
public:
	Book();
	Book(string title, string author);

	void TakeBook();
	void ReturnBook();
	void GetInfo();
	void operator=(Book& newBook);
	string GetTitle() {
		return title;
	}
	string GetAuthor() {
		return author;
	}
	void SetTitle(string title) {
		this->title = title;
	};
	void SetAuthor(string author) {
		this->author = author;
	};
};

class AudioBook : public Book {
public:
	AudioBook() {
	Book:: Book();
	};
	AudioBook(string title, string author) {
		Book::SetAuthor(author);
		Book::SetTitle(title);
	};

	void GetInfo() {
		cout << "Аудиокнига:" << endl;
		string n;
		n=GetTitle();
		cout << "\"" << n << "\"" << endl;
		cout << "Автор: " << this->GetAuthor() << endl;
	};
};

class Department {
private:
	Book* books;
	AudioBook* audiobooks;
	string name;
	int booksQuantity;
	int audiobooksQuantity;
public:
	Department();
	~Department();
	Department(string name);
	Department(int booksQuantity);
	Department(string name, int booksQuantity, int audiobooksQuantity);

	int getBQuantity();
	int getABQuantity() {
		return audiobooksQuantity;
	};
	void SetName(string newName);
	void ShowAll();
	void ShowB();
	void ShowAB();
	void AddBook();
	void AddAudioBook();
	void DeleteBook();
	void DeleteAudioBook();
	void GetInfo();
	void operator=(Department& newDep);
	int ChooseABook();
	void TB(int choise);
	void RB(int choise);
	Book GetBook(int choise);
};


Library::Library() {
	departmentsQuantity = 1;
	this->departments = new Department[departmentsQuantity];
	Department dep;
	departments[0] = dep;
	number = 1;
	departmentsQuantity = 1;
	address = "ул.Якуба Коласа, д.28";
}

Library::Library(int number, string address, int departmentsQuantity) {
	this->address = address;
	this->number = number;
	this->departmentsQuantity = departmentsQuantity;
	Department* departments = new Department[departmentsQuantity];
	string name;
	int booksQuantity, audiobooksQuantity;
	for (int i = 0; i < departmentsQuantity; i++) {
		cout << "Введите название отдела:" << endl;
		cin >> name;
		cout << "Введите количество книг:" << endl;
		booksQuantity = CreateInt();
		cout << "Введите количество аудиокниг:" << endl;
		audiobooksQuantity = CreateInt();
		Department dep (name, booksQuantity, audiobooksQuantity);
		departments[i] = dep;
	}
}

Library::~Library() {
	//delete departments;
}

void Library::ShowDepartments() {
	for (int i = 0; i < departmentsQuantity; i++) {
		cout << i + 1 << endl;
		departments[i].GetInfo();
		cout << endl;
	}
}

void Library::SetAddress(string newAddress) {
	this->address = newAddress;
}

void Library::SetNumber(int newNumber) {
	this->number = newNumber;
}

void Library::GetInfo() {
	cout << "Информация о библиотеке:" << endl;
	cout << "Адрес: " << address << endl;
	cout << "Номер: " << number << endl;
}

void Library:: operator=(Library& newLib) {
	departmentsQuantity = newLib.departmentsQuantity;
	number = newLib.number;
	address = newLib.address;
	departments = new Department[departmentsQuantity];
	for (int i = 0; i < departmentsQuantity; i++) {
		departments[i] = newLib.departments[i];
	}
}

void Library::AddDep() {
	Department* deps;
	int departmentsQuantity1 = departmentsQuantity + 1;
	deps = new Department[departmentsQuantity1];

	string name1;
	int booksQuantity1, audiobooksQuantity1;

	cout << "Введите название отдела" << endl;
	cin >> name1;
	cout << "Введите количество книг" << endl;
	booksQuantity1 = CreateInt();
	cout << "Введите количество аудиокниг" << endl;
	audiobooksQuantity1 = CreateInt();
	int i = 0;
	for (; i < departmentsQuantity; i++) {
		deps[i] = departments[i];
	}

	Department n(name1, booksQuantity1, audiobooksQuantity1);
	deps[i] = n;

	departmentsQuantity = departmentsQuantity1;
	departments = new Department[departmentsQuantity];
	i = 0;
	for (; i < departmentsQuantity; i++) {
		departments[i] = deps[i];
	}
}

int Library::ChooseADep() {
	cout << "Введите номер отдела:" << endl;
	int num;
	num = CreateInt();
	if (num<1 || num>departmentsQuantity) {
		cout << "Такого отдела нет" << endl;
		return -1;
	}
	else return num - 1;
}

Department* Library::GetDep(int choise) {
	return &departments[choise];
}

Book::Book() {
	title = "Методичка по ООП";
	author = "Петрович Ю.Ю.";
	available = true;
}

Book::Book(string ttitle, string aauthor) {
	this->author = aauthor;
	this->title = ttitle;
	available = true;
}

void Book::TakeBook() {
	if (!available) {
		cout << "Книги нет в наличии" << endl;
	}
	else {
		available = false;
	}
}

void Book::ReturnBook() {
	if (available) {
		cout << "Книга уже присутствует в отделе" << endl;
	}
	else {
		available = true;
	}
}

void Book::GetInfo() {
	cout << "Книга:" << endl;
	string n = this->GetTitle();
	cout << "\"" << n << "\"" << endl;
	cout << "Автор: " << this->GetAuthor() << endl;
	if (this->available) {
		cout << "Есть в наличии" << endl;
	}
	else {
		cout << "Нет в наличии" << endl;
	}
}

void Book:: operator=(Book& newBook) {
	this->title = newBook.title;
	this->author = newBook.author;
	this->available = newBook.available;
}

void Department:: operator=(Department& newDep) {
	this->name = newDep.name;
	this->booksQuantity = newDep.booksQuantity;
	this->books = new Book[booksQuantity];
	for (int i = 0; i < booksQuantity; i++) {
		books[i] = newDep.books[i];
	}

	this->audiobooksQuantity = newDep.audiobooksQuantity;
	this->audiobooks = new AudioBook[audiobooksQuantity];
	for (int i = 0; i < audiobooksQuantity; i++) {
		audiobooks[i] = newDep.audiobooks[i];
	}
}

Department::Department() {
	booksQuantity = 1;
	audiobooksQuantity = 1;
	name = "Программирование";
	books = new Book[booksQuantity];
	Book book1;
	books[0] = book1;
	audiobooks = new AudioBook[audiobooksQuantity];
	AudioBook book2;
	audiobooks[0] = book2;
}

Department::~Department() {
	//delete books;
}

Department::Department(string name) {
	booksQuantity = 1;
	audiobooksQuantity = 0;
	this->name = name;
	books = new Book[booksQuantity];
}

Department::Department(int booksQuantity) {
	this->booksQuantity = booksQuantity;
	audiobooksQuantity = 0;
	name = "Программирование";
	books = new Book[booksQuantity];
	for (int i = 0; i < booksQuantity; i++) {
		this->AddBook();
	}
}

Department::Department(string name, int booksQuantity, int audiobooksQuantity) {
	this->booksQuantity = booksQuantity;
	this->name = name;
	books = new Book[booksQuantity];
	for (int i = 0; i < booksQuantity; i++) {
		string title, author;
		cout << "Введите название книги" << endl;
		cin >> title;
		cout << "Введите автора книги" << endl;
		cin >> author;
		Book n(title, author);
		books[i] = n;
	}

	this->audiobooksQuantity = audiobooksQuantity;
	audiobooks = new AudioBook[audiobooksQuantity];
	for (int i = 0; i < audiobooksQuantity; i++) {
		string title, author;
		cout << "Введите название аудиокниги" << endl;
		cin >> title;
		cout << "Введите автора аудиокниги" << endl;
		cin >> author;
		AudioBook n (title, author);
		audiobooks[i] = n;
	}
}

int Department::getBQuantity() {
	return booksQuantity;
}

void Department::SetName(string newName) {
	this->name = newName;
}

void Department::ShowB() {
	int i = 0;
	cout << endl << "Книги в отделе " << "\"" << name << "\"" << endl;
	for (; i < booksQuantity; i++) {
		cout << i + 1 << ". ";
		books[i].GetInfo();
		cout << endl;
	}
	if (i == 0) {
		cout << "Книги отсутствуют" << endl;
	}
}

void Department::ShowAB() {
	int k = 0;
	cout << endl << "Аудиокниги в отделе " << "\"" << name << "\"" << endl;
	for (; k < audiobooksQuantity; k++) {
		cout << k + 1 << ". ";
		audiobooks[k].GetInfo();
		cout << endl;
	}
	if (k == 0) {
		cout << "Аудиокниги отсутствуют" << endl;
	}
}

void Department::ShowAll() {
	ShowB();
	ShowAB();
}

void Department::AddBook() {
	Book* books1;
	int booksQuantity1 = booksQuantity + 1;
	books1 = new Book[booksQuantity1];

	string title1;
	string author1;

	cout << "Введите название книги" << endl;
	cin >> title1;
	cout << "Введите автора книги" << endl;
	cin >> author1;

	int i = 0;
	for (; i < booksQuantity; i++) {
		books1[i] = books[i];
	}
	Book n(title1, author1);
	books1[i] = n;

	booksQuantity = booksQuantity1;
	books = new Book[booksQuantity];
	i = 0;
	for (; i < booksQuantity; i++) {
		books[i] = books1[i];
	}
}

void Department::AddAudioBook() {
	AudioBook* books1;
	int booksQuantity1 = audiobooksQuantity + 1;
	books1 = new AudioBook[booksQuantity1];

	string title1;
	string author1;

	cout << "Введите название аудиокниги" << endl;
	cin >> title1;
	cout << "Введите автора аудиокниги" << endl;
	cin >> author1;

	int i = 0;
	for (; i < audiobooksQuantity; i++) {
		books1[i] = audiobooks[i];
	}
	AudioBook n(title1, author1);
	books1[i] = n;
	audiobooksQuantity = booksQuantity1;
	audiobooks = new AudioBook[audiobooksQuantity];
	i = 0;
	for (; i < audiobooksQuantity; i++) {
		audiobooks[i] = books1[i];
	}
}

void Department::DeleteBook() {
	ShowB();
	Book* books1 = new Book[booksQuantity - 1];
	cout << "Введите номер книги для удаления:" << endl;
	int num;
	num = CreateInt();
	if (num<1 || num>booksQuantity) {
		cout << "Такой книги нет" << endl;
	}
	else {
		int del = num - 1;
		int i = 0, k = 0;
		for (; i < booksQuantity; i++) {
			if (i != del) {
				books1[k] = books[i];
				k++;
			}
		}
		booksQuantity = booksQuantity - 1;
		books = new Book[booksQuantity];
		i = 0;
		for (; i < booksQuantity; i++) {
			books[i] = books1[i];
		}
	}
}

void Department::DeleteAudioBook() {
	ShowAB();
	AudioBook* books1 = new AudioBook[audiobooksQuantity - 1];
	cout << "Введите номер аудиокниги для удаления:" << endl;
	int num;
	num = CreateInt();
	if (num<1 || num>audiobooksQuantity) {
		cout << "Такой книги нет" << endl;
	}
	else {
		int del = num - 1;
		int i = 0, k = 0;
		for (; i < audiobooksQuantity; i++) {
			if (i != del) {
				books1[k] = audiobooks[i];
				k++;
			}
		}
		audiobooksQuantity = audiobooksQuantity - 1;
		audiobooks = new AudioBook[audiobooksQuantity];
		i = 0;
		for (; i < audiobooksQuantity; i++) {
			audiobooks[i] = books1[i];
		}
	}
}

int Department::ChooseABook() {
	cout << "Введите номер книги:" << endl;
	int num;
	num = CreateInt();
	if (num<1 || num>booksQuantity) {
		cout << "Такой книги нет" << endl;
		return -1;
	}
	else return num - 1;
}

void Department::GetInfo() {
	cout << "Отдел: " << name << endl;
	cout << "Количество книг в отделе: " << booksQuantity+audiobooksQuantity << endl;
}

void Department::TB(int choise) {
	books[choise].TakeBook();
}

void Department::RB(int choise) {
	books[choise].ReturnBook();
}

Book Department::GetBook(int choise) {
	return books[choise];
}

void DepMenu(Department& dep);

void LibMenu(Library& lib) {
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Поменять адрес библиотеки" << endl;
		cout << "2. Поменять номер библиотеки" << endl;
		cout << "3. Просмотреть отделы библиотеки" << endl;
		cout << "4. Просмотреть информацию о библиотеке" << endl;
		cout << "5. Добавить отдел" << endl;
		cout << "6. Работа с выбранным отделом" << endl;
		cout << "7. Выйти" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			string address;
			cout << "Введите новый адрес" << endl;
			cin >> address;
			lib.SetAddress(address);
			break;
		}
		case 2: {
			int num;
			cout << "Введите новый номер" << endl;
			num = CreateInt();
			lib.SetNumber(num);
			lib.GetInfo();
			break;
		}
		case 3: {
			lib.ShowDepartments();
			break;
		}
		case 4: {
			lib.GetInfo();
			break;
		}
		case 5: {
			lib.AddDep();
			break;
		}
		case 6: {
			int num;
			lib.ShowDepartments();
			int choise = lib.ChooseADep();
			if (choise >= 0) {
				DepMenu(*lib.GetDep(choise));
			}
		}
		case 7: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
		}
		}
	}
}

void DepMenu(Department& dep) {
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Вывести количество всех книг в отделе" << endl;
		cout << "2. Поменять название отдела" << endl;
		cout << "3. Вывести список книг" << endl;
		cout << "4. Добавить книгу в отдел" << endl;
		cout << "5. Добавить аудиокнигу в отдел" << endl;
		cout << "6. Удалить книгу из отдела" << endl;
		cout << "7. Удалить аудиокнигу из отдела" << endl;
		cout << "8. Вывести информацию об отделе" << endl;
		cout << "9. Взять книгу" << endl;
		cout << "10. Вернуть книгу" << endl;
		cout << "11. Выйти" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			cout << "Количество книг в отделе: " << dep.getBQuantity() + dep.getABQuantity() << endl;
			break;
		}
		case 2: {
			string name;
			cout << "Введите новое название" << endl;
			cin >> name;
			dep.SetName(name);
			break;
		}
		case 3: {
			dep.ShowAll();
			break;
		}
		case 4: {
			dep.AddBook();
			break;
		}
		case 5: {
			dep.AddAudioBook();
			break;
		}
		case 6: {
			dep.DeleteBook();
			break;
		}
		case 7: {
			dep.DeleteAudioBook();
			break;
		}
		case 8: {
			dep.GetInfo();
			break;
		}
		case 9: {
			dep.ShowB();
			int choise = dep.ChooseABook();
			if (choise >= 0) {
				dep.TB(choise);
			}
			break;
		}
		case 10: {
			dep.ShowB();
			int choise = dep.ChooseABook();
			if (choise >= 0) {
				dep.RB(choise);
			}
			break;
		}
		case 11: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
		}
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	int LibCounter = 1;
	Library libs[5];
	Library lib1;
	libs[0] = lib1;
	int menu = 0;
	int cycle = 1;
	while (cycle) {
		cout << "Выберите необходимое действие:" << endl;
		cout << "1. Создать библиотеку" << endl;
		cout << "2. Вывести список библиотек" << endl;
		cout << "3. Работа с выбранной библиотекой " << endl;
		cout << "4. Выйти" << endl;
		menu = CreateInt();
		switch (menu) {
		case 1: {
			//int number, departmentsQuantity;
			//string address;
			//cout << "Введите адрес библиотеки:" << endl;
			//cin >> address;
			//cout << "Введите номер библиотеки" << endl;
			//number = CreateInt();
			//cout << "Введите количество отделов библиотеки" << endl;
			//departmentsQuantity = CreateInt();
			//Library newlib(number, address, departmentsQuantity);
			//newlib.GetInfo();
			//newlib.ShowDepartments();
			Library newlib;
			libs[LibCounter] = newlib;
			LibCounter++;
			break;
		}
		case 2: {
			for (int i = 0; i < LibCounter; i++) {
				cout << i + 1 << endl;
				libs[i].GetInfo();
				cout << endl;
			}
			break;
		}
		case 3: {
			for (int i = 0; i < LibCounter; i++) {
				cout << i + 1 << endl;
				libs[i].GetInfo();
				cout << endl;
			}
			int li;
			cout << "Введите номер библиотеки:" << endl;
			li = CreateInt();
			if (li<1 || li>LibCounter) {
				cout << "Такой библиотеки нет" << endl;
			}
			else {
				LibMenu(libs[li - 1]);
			}
			break;
		}
		case 4: {
			cycle = 0;
			break;
		}
		default: {
			cout << "Некорректный ввод" << endl;
		}
		}
	}
}

int CreateInt()
{
	char str[70] = "a";//заведомо ложное условие (не целое число)
	while (!CheckInt(str))
	{
		cin >> str;
		if (!CheckInt(str))
		{
			cout << "Некорректный ввод." << endl;
		}
	}
	int n = atoi(str);//перевод в целочисленный формат
	return n;
}

int CheckInt(char c[])
{
	for (int i = 0; i < strlen(c); i++)
	{
		if (c[i] > '9' || c[i] < '0')
		{
			return 0;//это не целое число
		}
	}
	return 1;//это целое число
}