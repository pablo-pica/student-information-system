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
    std::string degreeProgram;
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
void searchRecord(studentNode* head, studentDetails search);
void displayFirstRowTable();
void displayRecordDetails(studentNode* current, int studentCounter);
bool isStringEqualNotCaseSensitive(const char string[], const char searchString[]);
void displayAllRecords(studentNode* head, std::fstream& studentRecords);
void deleteRecord(studentNode* head, studentDetails search);
void freeMemory(studentNode* head);
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
                << "[5] Save Current Records to FIle\n"
                << "[6] Exit\n\n"
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
            deleteRecord(head, search);
            pressToContinue();
            break;
        case 5:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                  SAVE CURRENT RECORDS TO FILE                                  |\n"
                        "|________________________________________________________________________________________________|\n\n";
            saveRecordsToFile(head, studentRecords);
            pressToContinue();
            break;
        case 6:
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
            getline(studentRecords, newStudent->studentInfo.degreeProgram, ',');
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
    char confirmSaveToFile;
    std::cout<<"Are you sure you want to save new changes? [y/n] ";
    std::cin>>confirmSaveToFile;                                        // Exiting the program itself,
    if (confirmSaveToFile == 'y' || confirmSaveToFile == 'Y')          // and displaying members
    {
        std::cout << "\nSaving records to file...\n";
        // studentRecords.open("student_records.txt", std::ios::app);
        studentRecords.open("student_records.txt", std::ios::out);
        if (!studentRecords.is_open())
        {
            std::cerr << "Unable to open file for writing.\n";
            return;
        }
        studentNode* temp = head;
        while (temp != nullptr)
        {
            studentRecords << std::endl << temp->studentInfo.studentID << "," << temp->studentInfo.lastName << "," <<
                                            temp->studentInfo.firstName << "," << temp->studentInfo.birthday << "," <<
                                            temp->studentInfo.address << "," << temp->studentInfo.gender << "," <<
                                            temp->studentInfo.degreeProgram << "," << temp->studentInfo.yearLevel;
            temp = temp->next;
        }
        studentRecords.close();
        std::cout << "\nFile succesfully saved!\n";
    }
    else if (confirmSaveToFile == 'n' || confirmSaveToFile == 'N')        
    {    
        std::cout<<"\nRedirecting you back to the menu...\n";
        pressToContinue();
        std::cin.ignore(10000, '\n');   
        return;                          
    }
    else
    {                                  
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout<<"\nInvalid selection! Press any key to try again.";   
        system("pause>0");
    }
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
    getline(std::cin, newStudent->studentInfo.degreeProgram);

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
    int choiceSearch;
    const char* lastNameCStr;
    const char* searchLastNameCStr;
    const char* firstNameCStr;
    const char* searchFirstNameCStr;
    char selectGender;
    const char* genderCStr;
    const char* searchGenderCStr;
    const char* degreeProgramCStr;
    const char* searchDegreeProgramCStr;
    int selectYearLevel;
    const char* yearLevelCStr;
    const char* searchYearLevelCStr;
    do
    {
        bool foundStudent = false;
        int studentCounter = 1;
        studentNode* current = head;
        if (current == nullptr)
        {
            std::cout<<"No data to be displayed. Please input at least one data.\n\n";
        }
        else
        {
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
                        << "Please type your selection [1-7]: ";
            std::cin >> choiceSearch;
            switch (choiceSearch)
            {
                case 1:
                    do
                    {
                        std::cout << "\nSearch records with ID number: ";
                        while (!(std::cin >> search.studentID))
                        { // only inputs integer
                            std::cout << "\nNot a number!\n\n";
                            std::cin.clear();
                            std::cin.ignore(512, '\n');
                            std::cout << "Search records with ID number: ";
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
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                            foundStudent = true;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with id '" << search.studentID << "'!\n";
                    pressToContinue();
                    break;
                case 2:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nSearch records with last name: ";
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
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with last name '" << search.lastName << "'!\n";
                    pressToContinue();
                    break;
                case 3:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nSearch records with fIrst name: ";
                    getline(std::cin, search.firstName);
                    while (current)
                    {
                        firstNameCStr = current->studentInfo.firstName.c_str();
                        searchFirstNameCStr = search.firstName.c_str();
                        if (isStringEqualNotCaseSensitive(firstNameCStr, searchFirstNameCStr) && foundStudent == false)
                        {
                            displayFirstRowTable();
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(firstNameCStr, searchFirstNameCStr))
                        {
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with first name '" << search.firstName << "'!\n";
                    pressToContinue();
                    break;
                case 4:;
                    do
                    {
                        std::cout << "\nSearch records with gender [M/F]: ";
                        std::cin >> selectGender;
                        if (selectGender != 'M' && selectGender != 'm'
                            && selectGender != 'F' && selectGender != 'f')
                        {
                            std::cout<<"\nInvalid gender selection!\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    } while (selectGender != 'M' && selectGender != 'm'
                            && selectGender != 'F' && selectGender != 'f');

                    switch (selectGender)
                    {
                        case 'm':
                        case 'M':
                            search.gender = "Male";
                            break;
                        case 'f':
                        case 'F':
                            search.gender = "Female";
                            break;
                    }
                    while (current)
                    {
                        genderCStr = current->studentInfo.gender.c_str();
                        searchGenderCStr = search.gender.c_str();
                        if (isStringEqualNotCaseSensitive(genderCStr, searchGenderCStr) && foundStudent == false)
                        {
                            displayFirstRowTable();
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(genderCStr, searchGenderCStr))
                        {
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with gender '" << search.gender << "'!\n";
                    pressToContinue();
                    break;
                case 5:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nSearch records with degree program: ";
                    getline(std::cin, search.degreeProgram);
                    while (current)
                    {
                        degreeProgramCStr = current->studentInfo.degreeProgram.c_str();
                        searchDegreeProgramCStr = search.degreeProgram.c_str();
                        if (isStringEqualNotCaseSensitive(degreeProgramCStr, searchDegreeProgramCStr) && foundStudent == false)
                        {
                            displayFirstRowTable();
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(degreeProgramCStr, searchDegreeProgramCStr))
                        {
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with degree program '" << search.degreeProgram << "'!\n";
                    pressToContinue();
                    break;
                case 6:
                    do
                    {
                        std::cout << "\nSearch records with year level: [1 - 5]: ";
                        std::cin >> selectYearLevel;
                        if (selectYearLevel < 1 || selectYearLevel > 5)
                        {
                            std::cout<<"\nInvalid year level selection!\n\n";
                            std::cin.clear();
                        } 
                    } while (selectYearLevel < 1 || selectYearLevel > 5);
                    switch (selectYearLevel)
                    {
                        case 1:
                            search.yearLevel = "1st Year";
                            break;
                        case 2:
                            search.yearLevel = "2nd Year";
                            break;
                        case 3:
                            search.yearLevel = "3rd Year";
                            break;
                        case 4:
                            search.yearLevel = "4th Year";            
                            break;
                        case 5:
                            search.yearLevel = "5th Year";
                            break;
                        default:
                            break;
                    }
                    while (current)
                    {
                        yearLevelCStr = current->studentInfo.yearLevel.c_str();
                        searchYearLevelCStr = search.yearLevel.c_str();
                        if (isStringEqualNotCaseSensitive(yearLevelCStr, searchYearLevelCStr) && foundStudent == false)
                        {
                            displayFirstRowTable();
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(yearLevelCStr, searchYearLevelCStr))
                        {
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                    if (!foundStudent)
                        std::cout << "\nNo student found with year level '" << search.yearLevel << "'!\n";
                    pressToContinue();
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

void displayRecordDetails(studentNode* current, int studentCounter)
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
    std::setw(colprogram-1) << std::left << current->studentInfo.degreeProgram << "| "<<
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
            std::setw(colprogram-1) << std::left << head->studentInfo.degreeProgram << "| "<<
            std::setw(colYearLevel-1) << std::left << head->studentInfo.yearLevel << "|";
            studentCounter++;
            head = head->next;
        }
        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
    }

}


void deleteRecord(studentNode* head, studentDetails search)
{
    do
    {
        std::cout << "\nDelete record with ID number: ";
        while (!(std::cin >> search.studentID))
        { // only inputs integer
            std::cout << "\nNot a number!\n\n";
            std::cin.clear();
            std::cin.ignore(512, '\n');
            std::cout << "Search records with ID number: ";
        }
        if (search.studentID < 0 || search.studentID > 202499999)
        {
            std::cout << "\nInvalid student ID! With year 2024 and below only!\n\n";
        }
    } while (search.studentID < 0 || search.studentID > 202499999);

    studentNode* current = head;
    studentNode* prev = nullptr;

    if (current != nullptr && current->studentInfo.studentID == search.studentID) {
        head = current->next;
        delete current;
        return;
    }
    while (current != nullptr && current->studentInfo.studentID != search.studentID) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        std::cout << "\nNo student found with ID number '" << search.studentID << "'!\n";
        return;
    }
    prev->next = current->next;
    delete current;
}

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