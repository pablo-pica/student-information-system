#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

struct Student              // Structure to hold student information
{
    int studentID;
    std::string fullName;
    std::string birthday;
    std::string address;
    char gender;
    std::string degreeProgram;
    int yearLevel;
};

void pressToContinue();
void addRecord(std::vector<Student> &students);
void searchRecord(const std::vector<Student> &students);
void displayAllRecords(const std::vector<Student> &students);
void deleteRecord(std::vector<Student> &students);
bool validateInput(const std::string &input);
void saveRecordsToFile(const std::vector<Student> &students);
void loadRecordsFromFile(std::vector<Student> &students);

int main()
{
    std::vector<Student> students;

    // Load records from file
    loadRecordsFromFile(students);
    bool inMenu = true;

    do
    {
        system("cls");
        std::cout << " ________________________________________________________________________________________________\n"
                    "|                                                                                                |\n"
                    "|                         WELCOME TO GROUP 1 STUDENT INFORMATION SYSTEM                          |\n"
                    "|________________________________________________________________________________________________|\n\n"
                << "What do you want to do?\n\n"
                << "1. Add New Record\n"
                << "2. Search Record\n"
                << "3. Display All Records\n"
                << "4. Delete Record\n"
                << "5. Exit\n\n"
                << "Please type your selection: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Clear input buffer

        switch (choice)
        {
        case 1:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                           ADD RECORD                                           |\n"
                        "|________________________________________________________________________________________________|\n\n";
            addRecord(students);
            pressToContinue();
            break;
        case 2:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         SEARCH RECORD                                          |\n"
                        "|________________________________________________________________________________________________|\n\n";
            searchRecord(students);
            pressToContinue();
            break;
        case 3:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                      DISPLAY ALL RECORDS                                       |\n"
                        "|________________________________________________________________________________________________|\n\n";
            displayAllRecords(students);
            pressToContinue();
            break;
        case 4:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         DELETE RECORD                                          |\n"
                        "|________________________________________________________________________________________________|\n\n";
            deleteRecord(students);
            pressToContinue();
            break;
        case 5:
            char confirmExitProgram;
                while (inMenu == true) 
                {
                    system("cls");
                    std::cout << " ________________________________________________________________________________________________\n"
                                "|                                                                                                |\n"
                                "|                                          EXIT PROGRAM                                          |\n"
                                "|________________________________________________________________________________________________|\n\n";
                    std::cout<<"Are you sure you want to exit and terminate the program? [y/n] ";
                    std::cin>>confirmExitProgram;                                        // Exiting the program itself,
                    if (confirmExitProgram == 'y' || confirmExitProgram == 'Y')          // and displaying members
                    {
                        std::cout<<"\nThank you for using the program!\n\n"
                            <<"\tHere are the group members of Group 1 of TN12 in alphabetical order: \n"
                            <<"\t1. Balagao, Aldrin Dave\n"
                            <<"\t2. Bermejo, Christian Jude\n"
                            <<"\t3. Espenilla, Kimberly\n"
                            <<"\t4. Hermogenes, Franc Marcus\n"
                            <<"\t5. Castillo, Francheska\n"
                            <<"\t6. Tibayan, Asher\n"
                            <<"\t7. Valencia, John Rainier\n\n"
                            <<"Press any key to terminate the program.";
                        system("pause>0");
                        return 0;
                    }
                    else if (confirmExitProgram == 'n' || confirmExitProgram == 'N')        // go back to log in menu
                    {    
                        std::cout<<"\nRedirecting you back to the login menu...\n"
                            <<"\nPress any key to continue...";
                        system("pause>0");
                        std::cin.ignore(10000, '\n');   // prevents enter from being inputted to 
                        break;                          // loginMenuOption when it goes back to login menu
                    }
                    else
                    {                                   // for edge cases
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout<<"\nInvalid selection! Press any key to try again.";   
                        system("pause>0");
                    }
                }
                break;
        default:
            std::cin.clear();
            std::cin.ignore(10000, '\n'); // prevents input from looping
            std::cout << "\nInvalid selection! Press any key to try again.";
            system("pause>0");
        }
    } while (inMenu == true);
    return 0;
}

void pressToContinue()
{
    std::cout << "\nPress any key to continue...";
    system("pause>0");
}

// Function to read records from file
void loadRecordsFromFile(std::vector<Student> &students)
{
    std::ifstream inFile("student_records.txt");
    if (!inFile.is_open())
    {
        std::cerr << "Unable to open file.\n";
        return;
    }

    std::cout << "Reading records from file...\n";

    while (!inFile.eof())
    {
        Student newStudent;
        inFile >> newStudent.studentID;
        inFile.ignore();
        getline(inFile, newStudent.fullName, ',');
        getline(inFile, newStudent.birthday, ',');
        getline(inFile, newStudent.address, ',');
        inFile >> newStudent.gender;
        inFile.ignore();
        getline(inFile, newStudent.degreeProgram, ',');
        inFile >> newStudent.yearLevel;
        inFile.ignore();

        students.push_back(newStudent);
    }

    inFile.close();
}

// Function to save records to file
// void saveRecordsToFile(const std::vector<Student> &students)
// {
//     std::ofstream outFile("student_records.txt");
//     if (!outFile.is_open())
//     {
//         std::cerr << "Unable to open file for writing.\n";
//         return;
//     }

//     std::cout << "Saving records to file...\n";

//     for (const auto &student : students)
//     {
//         outFile << student.studentID << "," << student.fullName << "," << student.birthday << ","
//                 << student.address << "," << student.gender << "," << student.degreeProgram << ","
//                 << student.yearLevel << std::endl;
//     }

//     outFile.close();
// }

// Function to add a new record
void addRecord(std::vector<Student> &students)
{
    Student newStudent;
    std::cout << "Enter Student ID Number: ";
    std::cin >> newStudent.studentID;
    std::cin.ignore();
    std::cout << "Enter Full Name: ";
    getline(std::cin, newStudent.fullName);
    std::cout << "Enter Birthday: ";
    getline(std::cin, newStudent.birthday);
    std::cout << "Enter Address: ";
    getline(std::cin, newStudent.address);
    std::cout << "Enter Gender (M/F): ";
    std::cin >> newStudent.gender;
    std::cout << "Enter Degree Program: ";
    getline(std::cin, newStudent.degreeProgram);
    std::cout << "Enter Year Level: ";
    std::cin >> newStudent.yearLevel;

    students.push_back(newStudent);
}

// Function to search for a record
void searchRecord(const std::vector<Student> &students)
{
    int searchID;
    std::cout << "Enter Student ID to search: ";
    std::cin >> searchID;

    bool found = false;
    for (const auto &student : students)
    {
        if (student.studentID == searchID)
        {
            std::cout << "\nStudent found:\n\n"
                << "Student ID: " << student.studentID << std::endl
                << "Full Name: " << student.fullName << std::endl
                << "Birthday: " << student.birthday << std::endl
                << "Address: " << student.address << std::endl
                << "Gender: " << student.gender << std::endl
                << "Degree Program: " << student.degreeProgram << std::endl
                << "Year Level: " << student.yearLevel << std::endl
                << std::endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        std::cout << "Student not found.\n";
    }
}

// Function to display all records
void displayAllRecords(const std::vector<Student> &students)
{
    std::cout << "Student Records:\n\n";
    for (const auto &student : students)
    {
        std::cout<< "Student ID: " << student.studentID << std::endl
                << "Full Name: " << student.fullName << std::endl
                << "Birthday: " << student.birthday << std::endl
                << "Address: " << student.address << std::endl
                << "Gender: " << student.gender << std::endl
                << "Degree Program: " << student.degreeProgram << std::endl
                << "Year Level: " << student.yearLevel << std::endl << std::endl;
    }
}

// Function to delete a record
void deleteRecord(std::vector<Student> &students)
{
    int deleteID;
    std::cout << "Enter Student ID to delete: ";
    std::cin >> deleteID;

    auto it = students.begin();
    while (it != students.end())
    {
        if (it->studentID == deleteID)
        {
            it = students.erase(it);
            std::cout << "Record deleted successfully.\n";
            return;
        }
        else
        {
            ++it;
        }
    }
    std::cout << "Student not found.\n";
}

// Function to validate input
bool validateInput(const std::string &input)
{
    // Implementation of validation
    return !input.empty();
}
