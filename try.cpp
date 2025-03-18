#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Structure to hold student information
struct Student {
    int id;
    string name;
    int age;
    string course;

    // Method to display student information
    void display() const {
        cout << left << setw(10) << id 
             << setw(20) << name 
             << setw(5) << age 
             << course << endl;
    }
};

// Helper function to load all students from file into a vector
vector<Student> loadStudents(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    if (!file) {
        return students; // Return empty vector if file can't be opened
    }

    string line;
    while (getline(file, line)) {
        Student student;
        size_t pos = 0;
        pos = line.find('|');
        student.id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        student.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        student.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        student.course = line;
        students.push_back(student);
    }
    file.close();
    return students;
}

// Updated function to add a new student with duplicate ID check
void addStudent(const string& filename) {
    ofstream file(filename, ios::app); // Append mode
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    Student student;
    cout << "Enter Student ID: ";
    cin >> student.id;
    cin.ignore();

    // Check for duplicate ID
    vector<Student> existingStudents = loadStudents(filename);
    for (const auto& s : existingStudents) {
        if (s.id == student.id) {
            cout << "Error: Student ID " << student.id << " already exists!" << endl;
            file.close();
            return;
        }
    }

    cout << "Enter Student Name: ";
    getline(cin, student.name);

    cout << "Enter Student Age: ";
    cin >> student.age;
    cin.ignore();
    
    cout << "Enter Student Course: ";
    getline(cin, student.course);

    // Write the student data to the file
    file << student.id << "|" << student.name << "|" 
         << student.age << "|" << student.course << endl;

    cout << "Student added successfully!" << endl;
    file.close();
}

// Function to retrieve a student by ID
void getStudentByID(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    int searchID;
    cout << "Enter Student ID to search: ";
    cin >> searchID;

    string line;
    bool found = false;
    while (getline(file, line)) {
        Student student;
        size_t pos = 0;
        pos = line.find('|');
        student.id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        student.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        student.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        student.course = line;

        if (student.id == searchID) {
            cout << "Student Found:" << endl;
            student.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with ID " << searchID << " not found." << endl;
    }

    file.close();
}

// Function to display all students
void displayAllStudents(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }

    cout << left << setw(10) << "ID" 
         << setw(20) << "Name" 
         << setw(5) << "Age" 
         << "Course" << endl;
    cout << string(50, '-') << endl;

    string line;
    while (getline(file, line)) {
        Student student;
        size_t pos = 0;
        pos = line.find('|');
        student.id = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        pos = line.find('|');
        student.name = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find('|');
        student.age = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);

        student.course = line;

        student.display();
    }

    file.close();
}

// Main menu
int main() {
    string filename = "students.txt";
    int choice;

    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add Student\n";
        cout << "2. Search Student by ID\n";
        cout << "3. Display All Students\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(filename);
                break;
            case 2:
                getStudentByID(filename);
                break;
            case 3:
                displayAllStudents(filename);
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Try again!" << endl;
        }
    } while (choice != 4);

    return 0;
}