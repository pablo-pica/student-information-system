#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>

struct studentDetails              // Structure to hold student information
{
    int studentID;
    std::string lastName;
    std::string firstName;
    std::string birthday;
    std::string address;
    std::string gender;
    std::string program;
    std::string yearLevel;
};

struct studentNode
{
    studentDetails studentInfo;
    studentNode* next;
};

int colStudentCounter = 5;
int colStudentID = 12; //sets the column size for the table
int colLastName = 15;
int colFirstName = 24;
int colBirthday = 15;
int colAddress = 24;
int colGender = 7;
int colprogram = 10;
int colYearLevel = 10;

void pressToContinue();
void addRecord(studentNode*& head);
// void searchRecord(const std::vector<Student> &students);
void displayAllRecords(studentNode* head, std::fstream& studentRecords);
// void deleteRecord(std::vector<Student> &students);
bool checkIDAvailability(studentNode* head, int studentidattempt);
void saveRecordsToFile(studentNode* head, std::fstream& studentRecords);
void loadRecordsFromFile(studentNode*& head, std::fstream& studentRecords);
void freeMemory (studentNode* head);

int main()
{
    bool inMenu = true;
    studentNode* head = nullptr;
    std::fstream studentRecords;
    system("cls");
        std::cout << " ________________________________________________________________________________________________\n"
                    "|                                                                                                |\n"
                    "|                                    LOADING RECORDS FILE...                                     |\n"
                    "|________________________________________________________________________________________________|\n\n";
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
                << "[1] Add New Record\n"
                << "[2] Search Record\n"
                << "[3] Display All Records\n"
                << "[4] Delete Record\n"
                << "[5] Exit\n\n"
                << "Please type your selection [1-5]: ";

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
    studentRecords.open("student_records.txt", std::ios::in);
    if (!studentRecords.is_open())
    {
        std::cerr << "File not found or unable to open.\n\n";
        return;
    }
    else
    {
        std::cout << "Reading records from file...\n\n";
        while (!studentRecords.eof())
        {
            studentNode* newStudent = new studentNode;
            newStudent->next = nullptr;

            studentRecords >> newStudent->studentInfo.studentID;
            studentRecords.ignore();
            getline(studentRecords, newStudent->studentInfo.lastName, ',');
            getline(studentRecords, newStudent->studentInfo.firstName, ',');
            getline(studentRecords, newStudent->studentInfo.birthday, ',');
            getline(studentRecords, newStudent->studentInfo.address, ',');
            getline(studentRecords, newStudent->studentInfo.gender, ',');
            getline(studentRecords, newStudent->studentInfo.program, ',');
            getline(studentRecords, newStudent->studentInfo.yearLevel);

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
        std::cout<<"File successfully read!\n\n";
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
                    << temp->studentInfo.program << "," << temp->studentInfo.yearLevel;
    studentRecords.close();
}

void addRecord(studentNode*& head)
{
    studentNode* newStudent = new studentNode;
    newStudent -> next = nullptr;

    do
    {
        do
        {
            std::cout << "Enter Student ID Number: ";
            while (!(std::cin>>newStudent->studentInfo.studentID))
            { // only inputs integer
                std::cout << "\nNot a number!\n\n";
                std::cin.clear();
                std::cin.ignore(512, '\n');
                std::cout<<"Enter Student ID Number: ";
            }
            if (newStudent->studentInfo.studentID < 0 || newStudent->studentInfo.studentID > 202499999)
            {
                std::cout<<"\nInvalid student ID! With year 2024 and below only!\n\n";   
            }
        } while (newStudent->studentInfo.studentID < 0 || newStudent->studentInfo.studentID > 202499999);
        std::cout<<newStudent->studentInfo.studentID;
        if (!checkIDAvailability(head, newStudent->studentInfo.studentID))
        {
            std::cout<<"\nThat student ID already exists!\n\n";
        }
    } while (!checkIDAvailability(head, newStudent->studentInfo.studentID));

    std::cin.ignore();
    std::cout << "Enter Last Name: ";
    getline(std::cin, newStudent->studentInfo.lastName);
    std::cout << "Enter First Name: ";
    getline(std::cin, newStudent->studentInfo.firstName);
    std::cout << "Enter Birthday: ";
    getline(std::cin, newStudent->studentInfo.birthday);
    std::cout << "Enter Address: ";
    getline(std::cin, newStudent->studentInfo.address);

    char selectGender;
    do
    {
        std::cout << "Enter Gender [M/F]: ";
        std::cin >> selectGender;
        if (selectGender != 'M' && selectGender != 'm'
            && selectGender != 'F' && selectGender != 'f')
        {
            std::cout<<"\nInvalid gender selection!\n\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (selectGender != 'M' && selectGender != 'm'
            && selectGender != 'F' && selectGender != 'f');

    switch (selectGender)
    {
        case 'm':
        case 'M':
            newStudent->studentInfo.gender = "Male";
            break;
        case 'f':
        case 'F':
            newStudent->studentInfo.gender = "Female";
            break;
    }
    
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Enter Degree Program: ";
    getline(std::cin, newStudent->studentInfo.program);

    int selectYearLevel;
    do
    {
        std::cout << "Enter Year Level [1 - 5]: ";
        std::cin >> selectYearLevel;;
        if (selectYearLevel < 1 || selectYearLevel > 5)
        {
            std::cout<<"\nInvalid year level selection!\n\n";
            std::cin.clear();
        } 

    } while (selectYearLevel < 1 || selectYearLevel > 5);

    switch (selectYearLevel)
    {
        case 1:
            newStudent->studentInfo.yearLevel = "1st Year";
            break;
        case 2:
            newStudent->studentInfo.yearLevel = "2nd Year";
            break;
        case 3:
            newStudent->studentInfo.yearLevel = "3rd Year";
            break;
        case 4:
            newStudent->studentInfo.yearLevel = "4th Year";            
            break;
        case 5:
            newStudent->studentInfo.yearLevel = "5th Year";
            break;
        default:
            break;
    }

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

bool checkIDAvailability(studentNode* head, int studentidattempt)
{
    studentNode* current = head;
    while (current)
    {
        if (current->studentInfo.studentID == studentidattempt)
        {
            return false;
        }
        current = current->next;
    }
    return true;
}

void displayAllRecords(studentNode* head, std::fstream& studentRecords)
{
    system("cls");
    
    std::cout << " ________________________________________________________________________________________________\n"
                "|                                                                                                |\n"
                "|                                      DISPLAY ALL RECORDS                                       |\n"
                "|________________________________________________________________________________________________|\n\n";

    if (head == nullptr)
    {
        std::cout<<"No data to be displayed. Please input at least one data.\n\n";
    }
    else
    {
        std::cout<<" _________________________________________________________________________________________________"
                <<"______________________________________________________________\n";
        std::cout<<"| "<<std::setw(colStudentCounter)<<std::left<<"No."<<"|| "
                        <<std::setw(colStudentID)<<std::left<<"Student ID"<<"|| "
                        <<std::setw(colLastName)<<std::left<<"Last Name"<<"|| "
                        <<std::setw(colFirstName)<<std::left<<"First Name"<<"|| "
                        <<std::setw(colBirthday)<<std::left<<"Birthday"<<"|| "
                        <<std::setw(colAddress)<<std::left<<"Address"<<"|| "
                        <<std::setw(colGender)<<std::left<<"Gender"<<"|| "
                        <<std::setw(colprogram)<<std::left<<"Program"<<"|| "
                        <<std::setw(colYearLevel)<<std::left<<"Year Level"<<"|";

        while (head != nullptr)
        {
            std::cout<<"\n|=============||================||=========================||=========================||========|\n";
            std::cout<<"| "<<std::setw(colStudentCounter)<<std::left<<"No."<<"|| "
                        <<std::setw(colStudentID)<<std::left<<head->studentInfo.studentID<<"|| "
                        <<std::setw(colLastName)<<std::left<<head->studentInfo.lastName<<"|| "
                        <<std::setw(colFirstName)<<std::left<<head->studentInfo.firstName<<"|| "
                        <<std::setw(colBirthday)<<std::left<<head->studentInfo.birthday<<"|| "
                        <<std::setw(colAddress)<<std::left<<head->studentInfo.address<<"|| "
                        <<std::setw(colGender)<<std::left<<head->studentInfo.gender<<"|| "
                        <<std::setw(colprogram)<<std::left<<head->studentInfo.program<<"|| "
                        <<std::setw(colYearLevel)<<std::left<<head->studentInfo.yearLevel<<"|";
            head = head->next;
        }
        std::cout<<"\n _________________________________________________________________________________________________"
                <<"______________________________________________________________\n\n";
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
//                 << "Degree Program: " << student.program << std::endl
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