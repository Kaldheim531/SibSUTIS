#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class ManagementOrganization {
public:
    string typeorg;
    string typesob;

public:
    ManagementOrganization(string typeoforganization, string typeofsobstvennost) {
        typeorg = typeoforganization;
        typesob = typeofsobstvennost;
    }

    void outputTo() {
        cout << "Тип организации: " << typeorg << endl;
        cout << "Тип собственности: " << typesob << endl;
    }

    string get_typeorg() const {
        return typeorg;
    }

    string get_typesob() const {
        return typesob;
    }

    void set_typeorg(string f) {
        typeorg = f;
    }

    // Оператор для сортировки по типу организации
    bool operator<(const ManagementOrganization& other) const {
        return typeorg < other.typeorg;
    }
};

int main() {
    // Создаем исходный вектор объектов ManagementOrganization
    vector<ManagementOrganization> organizations;
    organizations.push_back(ManagementOrganization("Юридическая", "Частная"));
    organizations.push_back(ManagementOrganization("Физическая", "Частная"));
    organizations.push_back(ManagementOrganization("Коллективная", "Частная"));
    organizations.push_back(ManagementOrganization("Некоммерческая", "Государственная"));
    organizations.push_back(ManagementOrganization("Корпоративная", "Частная"));

    // Создаем новый вектор и переписываем в него объекты с типом собственности "Частная"
    vector<ManagementOrganization> newOrganizations;
    for ( int i=0;i<(int)organizations.size();i++) {
        if (organizations[i].typesob== "Частная") {
            newOrganizations.push_back(organizations[i]);
        }
    }

    // Проверяем, не оказался ли новый вектор пустым
    if (newOrganizations.empty()) {
        cout << "Новый вектор пуст." << endl;
    } else {
        // Сортируем объекты в новом векторе по типу организации
        sort(newOrganizations.begin(), newOrganizations.end());

        // Выводим отсортированные объекты
        cout << "Отсортированные объекты:" << endl;
         printf("\n");
        for (int i=0;i<(int)newOrganizations.size();i++) {
            newOrganizations[i].outputTo();
            printf("\n");
        }
    }

    return 0;
}