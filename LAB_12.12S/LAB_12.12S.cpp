#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Employee {
    string lastName;
    string phoneNumber;
    string roomNumber;
    Employee* next;

    Employee() : lastName(""), phoneNumber(""), roomNumber(""), next(nullptr) {}

    Employee(const string& ln, const string& pn, const string& rn)
        : lastName(ln), phoneNumber(pn), roomNumber(rn), next(nullptr) {}
};

class LinkedList {
private:
    Employee* head;

    void clear(Employee* node) {
        while (node != nullptr) {
            Employee* temp = node;
            node = node->next;
            delete temp;
        }
    }

    Employee* findPrevious(const string& phoneNumber) {
        Employee* prev = nullptr;
        Employee* current = head;
        while (current != nullptr && current->phoneNumber != phoneNumber) {
            prev = current;
            current = current->next;
        }
        return prev;
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() {
        clear(head);
    }

    void addEmployee(const Employee& emp) {
        Employee* newEmp = new Employee(emp);
        if (head == nullptr) {
            head = newEmp;
        }
        else {
            Employee* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newEmp;
        }
    }

    void deleteEmployee(const string& phoneNumber) {
        Employee* prev = findPrevious(phoneNumber);
        Employee* toDelete = nullptr;

        if (prev == nullptr) { // head needs to be deleted
            toDelete = head;
            if (head != nullptr) {
                head = head->next;
            }
        }
        else {
            toDelete = prev->next;
            if (toDelete != nullptr) {
                prev->next = toDelete->next;
            }
        }

        if (toDelete != nullptr) {
            delete toDelete;
            cout << "Employee with phone number " << phoneNumber << " deleted successfully." << endl;
        }
        else {
            cout << "Employee with phone number " << phoneNumber << " not found." << endl;
        }
    }

    Employee* searchByPhoneNumber(const string& phoneNumber) const {
        Employee* current = head;
        while (current != nullptr) {
            if (current->phoneNumber == phoneNumber) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void saveToFile(const string& filename) const {
        ofstream fout(filename);
        if (!fout.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        Employee* current = head;
        while (current != nullptr) {
            fout << current->lastName << " " << current->phoneNumber << " " << current->roomNumber << endl;
            current = current->next;
        }
        fout.close();
    }

    void readFromFile(const string& filename) {
        ifstream fin(filename);
        if (!fin.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }
        clear(head);
        head = nullptr;

        string lastName, phoneNumber, roomNumber;
        while (fin >> lastName >> phoneNumber >> roomNumber) {
            addEmployee(Employee(lastName, phoneNumber, roomNumber));
        }
        fin.close();
    }
};

string filename;

void addEmployee(LinkedList& phoneBook) {
    Employee newEmployee;
    cout << "Enter last name: ";
    cin >> newEmployee.lastName;
    cout << "Enter phone number (two digits): ";
    cin >> newEmployee.phoneNumber;
    cout << "Enter room number: ";
    cin >> newEmployee.roomNumber;

    phoneBook.addEmployee(newEmployee);
}

void deleteEmployee(LinkedList& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number to delete: ";
    cin >> phoneNumber;

    phoneBook.deleteEmployee(phoneNumber);
}

void printEmployeeByPhoneNumber(const LinkedList& phoneBook) {
    string phoneNumber;
    cout << "Enter phone number: ";
    cin >> phoneNumber;

    Employee* employee = phoneBook.searchByPhoneNumber(phoneNumber);
    if (employee != nullptr) {
        cout << "Last name: " << employee->lastName << ", Room number: " << employee->roomNumber << endl;
    }
    else {
        cout << "Employee with phone number " << phoneNumber << " not found." << endl;
    }
}

void savePhoneBookToFile(const LinkedList& phoneBook) {
    phoneBook.saveToFile(filename);
    cout << "Phone book has been saved to file: " << filename << endl;
}

void readPhoneBookFromFile(LinkedList& phoneBook) {
    phoneBook.readFromFile(filename);
    cout << "Phone book has been read from file: " << filename << endl;
}

int main() {
    LinkedList phoneBook;

    cout << "Enter filename: ";
    getline(cin, filename);

    readPhoneBookFromFile(phoneBook);

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Add employee" << endl;
        cout << "2. Delete employee" << endl;
        cout << "3. Print employee by phone number" << endl;
        cout << "4. Save phone book to file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1:
            addEmployee(phoneBook);
            break;
        case 2:
            deleteEmployee(phoneBook);
            break;
        case 3:
            printEmployeeByPhoneNumber(phoneBook);
            break;
        case 4:
            savePhoneBookToFile(phoneBook);
            break;
        case 5:
            cout << "Exiting program." << endl;
            savePhoneBookToFile(phoneBook);
            return 0;
        default:
            cout << "Invalid choice. Please enter a number from 1 to 5." << endl;
        }
    }

    return 0;
}
