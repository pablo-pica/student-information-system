#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <cctype>

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

int colStudentCounter = 6;
int colStudentID = 13; //sets the column size for the table
int colLastName = 16;
int colFirstName = 20;
int colBirthday = 14;
int colAddress = 49;
int colGender = 10;
int colprogram = 10;
int colYearLevel = 12;

// void deleteRecord(std::vector<Student> &students);
void loadRecordsFromFile(studentNode*& head, std::fstream& studentRecords);
void saveRecordsToFile(studentNode* head, std::fstream& studentRecords);
void addRecord(studentNode*& head);
bool checkIDAvailability(studentNode* head, int studentidattempt);
void searchRecord (studentNode* head, studentDetails search);
void displayFirstRowTable();
void displaySpecificRecords (studentNode* current, int studentCounter);
bool isStringEqualNotCaseSensitive(const char string[], const char searchString[]);
void displayAllRecords(studentNode* head, std::fstream& studentRecords);
void freeMemory (studentNode* head);
void pressToContinue();

int main()
{
    studentDetails search;
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
            searchRecord (head, search);
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
        std::cerr << "File not found or unable to open.\n";
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
        std::cout<<"File successfully read!\n";
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
    std::cout << "Enter Birthday [MM/DD/YYYY]: ";
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

void searchRecord (studentNode* head, studentDetails search)
{
    bool inSearchRecord = true;
    do
    {
        studentNode* current = head;
        if (current == nullptr)
        {
            std::cout<<"No data to be displayed. Please input at least one data.\n\n";
        }
        else
        {
            int choiceSearch;
            int studentCounter = 1;
            bool foundStudent = false;
            const char* lastNameCStr;
            const char* searchLastNameCStr;
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         SEARCH RECORD                                          |\n"
                        "|________________________________________________________________________________________________|\n\n";
            std::cout << "How do you want to search?\n\n"
                        << "[1] Search by Student ID\n"
                        << "[2] Search by Last Name\n"
                        << "[3] Search by First Name\n"
                        << "[4] Search by Gender\n"
                        << "[5] Search by Degree Program\n"
                        << "[6] Search by Year Level\n"
                        << "[7] Exit Search Record Menu\n\n"
                        << "Please type your selection [1-5]: ";
            std::cin >> choiceSearch;
            switch (choiceSearch)
            {
                case 1:
                    do
                    {
                        std::cout << "\nEnter Student ID Number: ";
                        while (!(std::cin >> search.studentID))
                        { // only inputs integer
                            std::cout << "\nNot a number!\n\n";
                            std::cin.clear();
                            std::cin.ignore(512, '\n');
                            std::cout << "Enter Student ID Number: ";
                        }
                        if (search.studentID < 0 || search.studentID > 202499999)
                        {
                            std::cout << "\nInvalid student ID! With year 2024 and below only!\n\n";
                        }
                    } while (search.studentID < 0 || search.studentID > 202499999);
                    
                    while (current)
                    {
                        if (search.studentID == current->studentInfo.studentID && foundStudent == false)
                        {
                            displayFirstRowTable();
                            displaySpecificRecords(current, studentCounter);
                            studentCounter++;
                            foundStudent = true;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with id " << search.studentID << "!\n";
                    pressToContinue();
                    break;
                case 2:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nEnter Last Name: ";
                    getline(std::cin, search.lastName);
                    while (current)
                    {
                        lastNameCStr = current->studentInfo.lastName.c_str();
                        searchLastNameCStr = search.lastName.c_str();
                        if (isStringEqualNotCaseSensitive(lastNameCStr, searchLastNameCStr) && foundStudent == false)
                        {
                            displayFirstRowTable();
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(lastNameCStr, searchLastNameCStr))
                        {
                            displaySpecificRecords (current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with last name '" << search.lastName << "'!";
                    pressToContinue();
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    inSearchRecord = false;
                    break;
                default:
                    std::cin.clear();
                    std::cin.ignore(10000, '\n'); // prevents input from looping
                    std::cout << "\nInvalid selection! Press any key to try again.";
                    system("pause>0");
            }
        }
    } while (inSearchRecord == true);
}

void displayFirstRowTable()
{
    std::cout << "\nSet window to fullscreen for better viewing.\n\n";

    std::cout << "|" << std::setfill('-') << std::setw(158) << "" << "|\n";

    std::cout <<"| " << std::setfill(' ') << 
    std::setw(colStudentCounter-1) << std::left << "NO." << "| " << 
    std::setw(colStudentID-1) << std::left << "STUDENT ID" << "| " << 
    std::setw(colLastName-1) << std::left << "LAST NAME" << "| " <<
    std::setw(colFirstName-1) << std::left << "FIRST NAME" << "| " <<
    std::setw(colBirthday-1) << std::left << "BIRTHDAY" << "| " << 
    std::setw(colAddress-1) << std::left << "ADDRESS" << "| " <<
    std::setw(colGender-1) << std::left << "GENDER" << "| " <<
    std::setw(colprogram-1) << std::left << "PROGRAM" << "| " <<
    std::setw(colYearLevel-1) << std::left << "YEAR LEVEL" << "|";
}

void displaySpecificRecords (studentNode* current, int studentCounter)
{
    std::cout << "\n|" << std::setfill('-') <<
    std::setw(colStudentCounter) << "" << "|" <<
    std::setw(colStudentID) << "" << "|" <<
    std::setw(colLastName) << "" << "|" <<
    std::setw(colFirstName) << "" << "|" <<
    std::setw(colBirthday) << "" << "|" <<
    std::setw(colAddress) << "" << "|" <<
    std::setw(colGender) << "" << "|" <<
    std::setw(colprogram) << "" << "|" <<
    std::setw(colYearLevel) << "" << "|\n";

    std::cout << "| " << std::setfill(' ') << 
    std::setw(colStudentCounter-1) << std::left << studentCounter << "| " <<
    std::setw(colStudentID-1) << std::left << current->studentInfo.studentID << "| " << 
    std::setw(colLastName-1) << std::left << current->studentInfo.lastName << "| " <<
    std::setw(colFirstName-1) << std::left << current->studentInfo.firstName << "| " <<
    std::setw(colBirthday-1) << std::left << current->studentInfo.birthday << "| " <<
    std::setw(colAddress-1) << std::left << current->studentInfo.address << "| " <<
    std::setw(colGender-1) << std::left << current->studentInfo.gender << "| " <<
    std::setw(colprogram-1) << std::left << current->studentInfo.program << "| "<<
    std::setw(colYearLevel-1) << std::left << current->studentInfo.yearLevel << "|";
}

bool isStringEqualNotCaseSensitive(const char string[], const char searchString[])
{

    char copyString[50] = "";
    for(int i = 0; i<strlen(string);i++){
        copyString[i] = toupper(string[i]);
    }

    char copySearchString[50] = "";
    for(int i = 0; i<strlen(searchString);i++){
        copySearchString[i] = toupper(searchString[i]);
    }

    bool isStringEqual;
    isStringEqual=strcmp(copyString,copySearchString)==0;

    return isStringEqual;
}

void displayAllRecords(studentNode* head, std::fstream& studentRecords)
{
    system("cls");
    std::cout << " ________________________________________________________________________________________________\n"
                "|                                                                                                |\n"
                "|                                      DISPLAY ALL RECORDS                                       |\n"
                "|________________________________________________________________________________________________|\n\n";
    int studentCounter = 1;
    if (head == nullptr)
    {
        std::cout << "No data to be displayed. Please input at least one data.\n\n";
    }
    else
    {
        std::cout << "Set window to fullscreen for better viewing.\n\n";

        std::cout << "|" << std::setfill('-') << std::setw(158) << "" << "|\n";

        std::cout <<"| " << std::setfill(' ') << 
        std::setw(colStudentCounter-1) << std::left << "NO." << "| " << 
        std::setw(colStudentID-1) << std::left << "STUDENT ID" << "| " << 
        std::setw(colLastName-1) << std::left << "LAST NAME" << "| " <<
        std::setw(colFirstName-1) << std::left << "FIRST NAME" << "| " <<
        std::setw(colBirthday-1) << std::left << "BIRTHDAY" << "| " << 
        std::setw(colAddress-1) << std::left << "ADDRESS" << "| " <<
        std::setw(colGender-1) << std::left << "GENDER" << "| " <<
        std::setw(colprogram-1) << std::left << "PROGRAM" << "| " <<
        std::setw(colYearLevel-1) << std::left << "YEAR LEVEL" << "|";

        while (head != nullptr)
        {   
            std::cout << "\n|" << std::setfill('-') <<
            std::setw(colStudentCounter) << "" << "|" <<
            std::setw(colStudentID) << "" << "|" <<
            std::setw(colLastName) << "" << "|" <<
            std::setw(colFirstName) << "" << "|" <<
            std::setw(colBirthday) << "" << "|" <<
            std::setw(colAddress) << "" << "|" <<
            std::setw(colGender) << "" << "|" <<
            std::setw(colprogram) << "" << "|" <<
            std::setw(colYearLevel) << "" << "|\n";

            std::cout << "| " << std::setfill(' ') << 
            std::setw(colStudentCounter-1) << std::left << studentCounter << "| " <<
            std::setw(colStudentID-1) << std::left << head->studentInfo.studentID << "| " << 
            std::setw(colLastName-1) << std::left << head->studentInfo.lastName << "| " <<
            std::setw(colFirstName-1) << std::left << head->studentInfo.firstName << "| " <<
            std::setw(colBirthday-1) << std::left << head->studentInfo.birthday << "| " <<
            std::setw(colAddress-1) << std::left << head->studentInfo.address << "| " <<
            std::setw(colGender-1) << std::left << head->studentInfo.gender << "| " <<
            std::setw(colprogram-1) << std::left << head->studentInfo.program << "| "<<
            std::setw(colYearLevel-1) << std::left << head->studentInfo.yearLevel << "|";
            studentCounter++;
            head = head->next;
        }
        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
    }

}

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
    std::cout << "\nPress any key to continue...";
    system("pause>0");
}