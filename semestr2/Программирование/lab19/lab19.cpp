#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Book {
    int number;
    string FIO;
    string name;
    int year;
    int count;
};

bool compareBooks(const Book a, const Book b) {
    return a.year < b.year;
}

void addBook(vector<Book>& books) {
    Book newBook;
    cout << "Введите номер УДК: ";
    cin >> newBook.number;
    cin.ignore();

    cout << "Введите фамилию и инициалы автора: ";
    getline(cin, newBook.FIO);

    cout << "Введите название: ";
    getline(cin, newBook.name);

    cout << "Введите год издания: ";
    cin >> newBook.year;

    cout << "Введите количество экземпляров данной книги в библиотеке: ";
    cin >> newBook.count;

    books.push_back(newBook);
    sort(books.begin(), books.end(), compareBooks);

}

void removeBook(vector<Book>& books) {
    int number;
    cout << "Введите номер УДК книги, которую нужно удалить: ";
    cin >> number;

    for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        if (it->number == number) {
            books.erase(it);
            break;
        }
    }
}

void checkBookAvailability( vector<Book>& books) {
    int number;
    cout << "Введите номер УДК книги, наличие которой нужно проверить: ";
    cin >> number;

    for (vector<Book>::iterator it = books.begin(); it != books.end(); ++it) {
        if (it->number == number) {
            cout << "Книга есть в библиотеке. Количество экземпляров: " << it->count << endl;
            cout << "Название книги: " << it->name << endl;
            return;
        }
    }

    cout << "Книги с таким номером УДК нет в библиотеке." << endl;
}

int main() {
    vector<Book> books;
    string cont;

    // Ввод книг
    do {
        addBook(books);
        cout << "Хотите продолжить ввод книг? (да/нет): ";
        cin >> cont;
    } while (cont == "да");

    // Удаление книг
    cout << "Хотите удалить книгу? (да/нет): ";
    cin >> cont;
    if (cont == "да") {
        removeBook(books);
    }

    // Проверка наличия книг
    cout << "Хотите проверить наличие книги? (да/нет): ";
    cin >> cont;
    if (cont == "да") {
        checkBookAvailability(books);
    }

    return 0;
}