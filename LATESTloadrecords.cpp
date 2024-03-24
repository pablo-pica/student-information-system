#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

struct studentDetails              // Structure to hold student information
{
    int studentID;
    std::string lastName;
    std::string firstName;
    std::string birthday;
    std::string address;
    char gender;
    std::string degreeProgram;
    int yearLevel;
};

struct studentNode
{
    studentDetails studentInfo;
    studentNode* next;
};

void pressToContinue();
void addRecord(studentNode*& head);
// void searchRecord(const std::vector<Student> &students);
void displayAllRecords(studentNode* head, std::fstream& studentRecords);
// void deleteRecord(std::vector<Student> &students);
// bool validateInput(const std::string &input);
void saveRecordsToFile(studentNode* head, std::fstream& studentRecords);
void loadRecordsFromFile(studentNode*& head, std::fstream& studentRecords);
void freeMemory (studentNode* head);

int main()
{
    bool inMenu = true;
    studentNode* head = nullptr;
    std::fstream studentRecords;
    loadRecordsFromFile(head, studentRecords);
    pressToContinue();
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
        switch (choice)
        {
        case 1:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                           ADD RECORD                                           |\n"
                        "|________________________________________________________________________________________________|\n\n";
            addRecord(head);
            // displayAllRecords(head, studentRecords);
            saveRecordsToFile(head, studentRecords);
            pressToContinue();
            break;
        case 2:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         SEARCH RECORD                                          |\n"
                        "|________________________________________________________________________________________________|\n\n";
            // searchRecord(students);
            pressToContinue();
            break;
        case 3:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                      DISPLAY ALL RECORDS                                       |\n"
                        "|________________________________________________________________________________________________|\n\n";
            displayAllRecords(head, studentRecords);
            pressToContinue();
            break;
        case 4:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         DELETE RECORD                                          |\n"
                        "|________________________________________________________________________________________________|\n\n";
            // deleteRecord(students);
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
                        freeMemory(head);
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

void loadRecordsFromFile(studentNode*& head, std::fstream& studentRecords)       // Function to read records from file
{
    std::cout << "Reading records from file...\n\n";
    studentRecords.open("student_records.txt", std::ios::in);
    if (!studentRecords.is_open())
    {
        std::cerr << "Unable to open file.\n";
        return;
    }
    else
    {
        while (studentRecords)
        {
            studentNode* newStudent = new studentNode;
            newStudent->next = nullptr;

            studentRecords >> newStudent->studentInfo.studentID;
            studentRecords.ignore();
            getline(studentRecords, newStudent->studentInfo.lastName, ',');
            getline(studentRecords, newStudent->studentInfo.firstName, ',');
            getline(studentRecords, newStudent->studentInfo.birthday, ',');
            getline(studentRecords, newStudent->studentInfo.address, ',');
            studentRecords >> newStudent->studentInfo.gender;
            studentRecords.ignore();
            getline(studentRecords, newStudent->studentInfo.degreeProgram, ',');
            studentRecords >> newStudent->studentInfo.yearLevel;
            studentRecords.ignore();

            if (head == nullptr)
            {
                head = newStudent;
            }
            else
            {
                studentNode* temp = head;
                while (temp->next != nullptr)
                {
                    temp=temp->next;
                }
                temp->next = newStudent; 
            }
        }
    }
    studentRecords.close();
}

void saveRecordsToFile(studentNode* head, std::fstream& studentRecords)                       // Function to save records to file
{
    std::cout << "Saving records to file...\n";
    studentRecords.open("student_records.txt", std::ios::app);
    if (!studentRecords.is_open())
    {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }
    studentNode* temp = head;
    while (temp->next != nullptr)
    {
        temp=temp->next;
    }
    if (temp->next == nullptr)
    {
        studentRecords << std::endl;
    }
    studentRecords << temp->studentInfo.studentID << "," << temp->studentInfo.lastName << "," << temp->studentInfo.firstName << ","
                    << temp->studentInfo.birthday << "," << temp->studentInfo.address << "," << temp->studentInfo.gender << ","
                    << temp->studentInfo.degreeProgram << "," << temp->studentInfo.yearLevel;
    studentRecords.close();
}

void addRecord(studentNode*& head)
{
    studentNode* newStudent = new studentNode;
    newStudent -> next = nullptr;
    do
    {
        std::cout << "Enter Student ID Number: ";
        while (!(std::cin>>newStudent->studentInfo.studentID)) { // only inputs integer
            std::cout << "\nNot a number!\n\n";
            std::cin.clear();
            std::cin.ignore(512, '\n');
            std::cout<<"Enter Student ID Number: ";
        }
        if (newStudent->studentInfo.studentID < 0 || newStudent->studentInfo.studentID > 202499999)
        {
            std::cout<<"\nInvalid student ID! With year 2024 and below only!\n\n";   
        }
        // std::cin.clear();
        // std::cin.ignore(512, '\n');
    } while (newStudent->studentInfo.studentID < 0 || newStudent->studentInfo.studentID > 202499999);
    
    std::cin.ignore();
    std::cout << "Enter Last Name: ";
    getline(std::cin, newStudent->studentInfo.lastName);
    std::cout << "Enter First Name: ";
    getline(std::cin, newStudent->studentInfo.firstName);
    std::cout << "Enter Birthday: ";
    getline(std::cin, newStudent->studentInfo.birthday);
    std::cout << "Enter Address: ";
    getline(std::cin, newStudent->studentInfo.address);

    do
    {
        std::cout << "Enter Gender (M/F): ";
        std::cin >> newStudent->studentInfo.gender;
        if (newStudent->studentInfo.gender != 'M' && newStudent->studentInfo.gender != 'm'
            && newStudent->studentInfo.gender != 'F' && newStudent->studentInfo.gender != 'f')
        {
            std::cout<<"\nInvalid gender selection!\n\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (newStudent->studentInfo.gender != 'M' && newStudent->studentInfo.gender != 'm'
            && newStudent->studentInfo.gender != 'F' && newStudent->studentInfo.gender != 'f');
    
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Enter Degree Program: ";
    getline(std::cin, newStudent->studentInfo.degreeProgram);

    do
    {
        std::cout << "Enter Year Level (1 - 5): ";
        std::cin >> newStudent->studentInfo.yearLevel;
        if (newStudent->studentInfo.yearLevel < 1 || newStudent->studentInfo.yearLevel > 5)
        {
            std::cout<<"\n\nInvalid year level selection!\n";
            std::cin.clear();
        } 
    } while (newStudent->studentInfo.yearLevel < 1 || newStudent->studentInfo.yearLevel > 5);
    
    std::cout<<std::endl;

    if (head == nullptr)
    {
        head = newStudent;
    }
    else
    {
        studentNode* temp = head;
        while (temp->next != nullptr)
        {
            temp=temp->next;
        }
        temp->next = newStudent;
    }
}

void displayAllRecords(studentNode* head, std::fstream& studentRecords)
{
    std::cout << "Student Records:\n\n";
    while (head != nullptr)
    {
        // cout<<"\n|===============================================================================================|\n";
        // cout<<"| "<<setw(colOne)<<left<<"Student No."<<"|| "<<setw(colTwo)<<left<<"Student ID"
        //     <<"|| "<<setw(colThree)<<left<<"First Name"<<"|| "<<setw(colFour)<<left<<"Last Name"
        //     <<"|| "<<setw(colFive)<<left<<"GPA"<<"|";
        std::cout<< "Student ID: " << head->studentInfo.studentID << std::endl
                << "Last Name: " << head->studentInfo.lastName << std::endl
                << "First Name: " << head->studentInfo.firstName << std::endl
                << "Birthday: " << head->studentInfo.birthday << std::endl
                << "Address: " << head->studentInfo.address << std::endl
                << "Gender: " << head->studentInfo.gender << std::endl
                << "Degree Program: " << head->studentInfo.degreeProgram << std::endl
                << "Year Level: " << head->studentInfo.yearLevel << std::endl << std::endl;
        head = head->next;
    }
}
// Function to search for a record
// void searchRecord(const std::vector<Student> &students)
// {
//     int searchID;
//     std::cout << "Enter Student ID to search: ";
//     std::cin >> searchID;

//     bool found = false;
//     for (const auto &student : students)
//     {
//         if (student.studentID == searchID)
//         {
//             std::cout << "\nStudent found:\n\n"
//                 << "Student ID: " << student.studentID << std::endl
//                 << "Full Name: " << student.fullName << std::endl
//                 << "Birthday: " << student.birthday << std::endl
//                 << "Address: " << student.address << std::endl
//                 << "Gender: " << student.gender << std::endl
//                 << "Degree Program: " << student.degreeProgram << std::endl
//                 << "Year Level: " << student.yearLevel << std::endl
//                 << std::endl;
//             found = true;
//             break;
//         }
//     }
//     if (!found)
//     {
//         std::cout << "Student not found.\n";
//     }
// }



// Function to delete a record
// void deleteRecord(std::vector<Student> &students)
// {
//     int deleteID;
//     std::cout << "Enter Student ID to delete: ";
//     std::cin >> deleteID;

//     auto it = students.begin();
//     while (it != students.end())
//     {
//         if (it->studentID == deleteID)
//         {
//             it = students.erase(it);
//             std::cout << "Record deleted successfully.\n";
//             return;
//         }
//         else
//         {
//             ++it;
//         }
//     }
//     std::cout << "Student not found.\n";
// }

// // Function to validate input
// bool validateInput(const std::string &input)
// {
//     // Implementation of validation
//     return !input.empty();
// }

void freeMemory (studentNode* head)
{
    studentNode* deleter;
    while (head != nullptr)
    {
        deleter = head;
        head = head->next;
        delete deleter;
    }
}

void pressToContinue()
{
    std::cout << "Press any key to continue...";
    system("pause>0");
}