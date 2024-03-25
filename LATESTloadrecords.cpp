#include <iostream>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <cctype>

struct studentDetails  // Structure to hold student information
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

int colStudentCounter = 6;  //sets the column size for the table
int colStudentID = 13; 
int colLastName = 16;
int colFirstName = 20;
int colBirthday = 14;
int colAddress = 49;
int colGender = 10;
int colprogram = 10;
int colYearLevel = 12;

bool loadRecordsFromFile(studentNode*& head, std::fstream& studentRecords); // declare function prototypes
bool isFileEmpty(const std::string& filename);
void saveRecordsToFile(studentNode* head, std::fstream& studentRecords);
void addRecord(studentNode*& head);
bool checkIDMatch(studentNode* head, int studentidattempt);
void searchRecord(studentNode* head, studentDetails search);
void displayFirstRowTable();
void displayRecordDetails(studentNode* current, int studentCounter);
void displaySpecificRecord(studentNode* head, int searchID);
bool isStringEqualNotCaseSensitive(const char string[], const char searchString[]);
void displayAllRecords(studentNode* head, std::fstream& studentRecords);
bool deleteRecord(studentNode*& head, studentDetails search);
void freeMemory(studentNode* head);
void pressToContinue();

int main()
{
    studentDetails search;  // initialize values
    bool inMenu = true;
    studentNode* head = nullptr;
    char confirmSaveToFile;
    char confirmExitProgram;
    std::fstream studentRecords;
    system("cls");
        std::cout << " ________________________________________________________________________________________________\n"
                    "|                                                                                                |\n"
                    "|                                    LOADING RECORDS FILE...                                     |\n"
                    "|________________________________________________________________________________________________|\n\n";
    bool savedFile = loadRecordsFromFile(head, studentRecords);         // tries to load daatabas from file
    pressToContinue();
    do                                                                  // loops until user exits the program
    {
        bool inSaveRecordsMenu = true;
        system("cls");
        std::cout << " ________________________________________________________________________________________________\n"
                    "|                                                                                                |\n"
                    "|                         WELCOME TO GROUP 1 STUDENT INFORMATION SYSTEM                          |\n"
                    "|________________________________________________________________________________________________|\n\n"
                << "What do you want to do?\n\n"
                << "[1] Add New Record\n"
                << "[2] Search Record\n"
                << "[3] Display All Records\n"
                << "[4] Display Specific Record\n"
                << "[5] Delete Record\n"
                << "[6] Save Current Records to File\n"
                << "[7] Exit Program\n\n";
        if (savedFile)
            std::cout << "";
        else
            std::cout << "Records not saved!\n\n"; // prints if there are changes in the file that are not saved
        std::cout << "Please type your selection [1-7]: ";  // asks for selection
        int choice;                                         // gets selection
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                           ADD RECORD                                           |\n"
                        "|________________________________________________________________________________________________|\n\n";
            addRecord(head); // calls add record function
            savedFile = false; // new changes to file therefore savedfile = false
            pressToContinue();
            break;
        case 2:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         SEARCH RECORDS                                         |\n"
                        "|________________________________________________________________________________________________|\n\n";
            searchRecord (head, search); // calls search record
            pressToContinue();
            break;
        case 3:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                      DISPLAY ALL RECORDS                                       |\n"
                        "|________________________________________________________________________________________________|\n\n";
            displayAllRecords(head, studentRecords); // calls display all records
            pressToContinue();
            break;
        case 4:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                    DISPLAY SPECIFIC RECORD                                     |\n"
                        "|________________________________________________________________________________________________|\n\n";
            if (head == nullptr)                    // prints if there are no nodes/student records yet
            {
                    std::cout<<"No data to be displayed. Please input at least one data.\n";
                    pressToContinue();
                    break;
            }
            else
            {
                do
                {              // asks for an id to search, loops until id is valid
                    std::cout << "Search record with ID number: ";      
                    while (!(std::cin >> search.studentID))
                    {
                        std::cout << "\nNot a number!\n\n";
                        std::cin.clear();
                        std::cin.ignore(512, '\n');
                        std::cout << "Search record with ID number: ";
                    }
                    if (search.studentID < 0 || search.studentID > 202499999)
                    {
                        std::cout << "\nInvalid student ID! With year 2024 and below only!\n\n";
                    }
                } while (search.studentID < 0 || search.studentID > 202499999);
                if(checkIDMatch(head, search.studentID))        // checks if the inputted id is in the records
                {
                    displaySpecificRecord(head, search.studentID);  // display the student details with matched id
                }
                else                                                // prints if no student is found in the records
                    std::cout << "\nNo student found with id '" << search.studentID << "'!\n";  
                pressToContinue();
            }
            break;
        case 5:
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         DELETE RECORD                                          |\n"
                        "|________________________________________________________________________________________________|\n\n";
            if (head == nullptr)                // prints if there are no nodes/student records yet
            {
                    std::cout<<"No data to be displayed. Please input at least one data.\n";
                    pressToContinue();
                    break;
            }
            else
            {
                do               // asks for an id to search, loops until id is valid
                {
                    std::cout << "\nDelete record with ID number: ";
                    while (!(std::cin >> search.studentID))
                    {
                        std::cout << "\nNot a number!\n\n";
                        std::cin.clear();
                        std::cin.ignore(512, '\n');
                        std::cout << "Search record with ID number: ";
                    }
                    if (search.studentID < 0 || search.studentID > 202499999)
                    {
                        std::cout << "\nInvalid student ID! With year 2024 and below only!\n\n";
                    }
                    } while (search.studentID < 0 || search.studentID > 202499999);

                    if(checkIDMatch(head, search.studentID))    // display the student details with matched id
                    {
                        displaySpecificRecord(head, search.studentID);
                        if(deleteRecord(head, search))          // calls delete function
                            savedFile = false;                  // if deleted, there are new chagnes in the record
                }
            else                                                // prints if no student is found in the records
                    std::cout << "\nNo student found with id '" << search.studentID << "'!\n";
                pressToContinue();
            }
            break;
        case 6:
            while (inSaveRecordsMenu == true)
            {
                system("cls");
                std::cout << " ________________________________________________________________________________________________\n"
                            "|                                                                                                |\n"
                            "|                                  SAVE CURRENT RECORDS TO FILE                                  |\n"
                            "|________________________________________________________________________________________________|\n\n";
                if (savedFile == true)
                {
                    std::cout << "File already saved!\n";   // displays if there are no new changes in the records
                    break;
                }
                else                                        // do if there are new changes in the records
                {
                    std::cout << "Are you sure you want to save new changes? [Y/N]: "; // asks the user if they want to save the file
                }
                std::cin>>confirmSaveToFile;
                if (confirmSaveToFile == 'y' || confirmSaveToFile == 'Y')   // if y, save records to file
                {
                    saveRecordsToFile(head, studentRecords);    // call save records to file function
                    inSaveRecordsMenu = false;
                    savedFile = true;
                    break;
                }
                else if (confirmSaveToFile == 'n' || confirmSaveToFile == 'N')  // if n, don't save records to file
                {    
                    savedFile = false;
                    std::cout<<"\nRedirecting you back to the menu...\n";
                    std::cin.ignore(10000, '\n');   
                    inSaveRecordsMenu = false;           // sets it false so that it won't loop
                }
                else
                {                                       // loops if confirmSaveToFile != y or != n
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout<<"\nInvalid selection! Press any key to try again.";   
                    system("pause>0");
                }
            }
            pressToContinue();
            break;
        case 7:
            while (inMenu == true) 
            {
                system("cls");
                std::cout << " ________________________________________________________________________________________________\n"
                            "|                                                                                                |\n"
                            "|                                          EXIT PROGRAM                                          |\n"
                            "|________________________________________________________________________________________________|\n\n";
                if (savedFile == true)                      
    {                                           // asks the users if they want to exit the program only if file is saved
                    std::cout << "Are you sure you want to exit and terminate the program? [Y/N] ";
                }
                else
                {                               // asks the users if they want to exit the program only if file is NOT saved
                    std::cout << "You have unsaved changes to your file!\n\nAre you sure you want to exit and terminate the program? [y/n] ";
                }
                std::cin >> confirmExitProgram;                                      
                if (confirmExitProgram == 'y' || confirmExitProgram == 'Y')         
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
                else if (confirmExitProgram == 'n' || confirmExitProgram == 'N')
                {    
                    std::cout<<"\nRedirecting you back to the menu...\n";
                    pressToContinue();
                    std::cin.ignore(10000, '\n');
                    break;                          
                }
                else
                {                                  
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout<<"\nInvalid selection! Press any key to try again.";   
                    system("pause>0");
                }
                
            }
                break;
        default:
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\nInvalid selection! Press any key to try again.";
            system("pause>0");
        }
    } while (inMenu == true);
    return 0;
}

bool loadRecordsFromFile(studentNode*& head, std::fstream& studentRecords)
{
    studentRecords.open("student_records.txt", std::ios::in);
    if (!studentRecords.is_open())
    {
        std::cerr << "File not found or unable to open.\n"; // displays error message if file can't be opened for some reason
        return false;
    }
    else
    {
        std::string file = "student_records.txt" ;
        if (isFileEmpty(file))                              // checks if file is existing, but empty
        {
            std::cout<<"No data loaded! File is currently empty. Please input at least one data.\n";\
            studentRecords.close();                         // closefile before returning to main
            return true;
        }

        std::cout << "Reading records from file...\n\n";    // reads the file if the file existing and not empty
        while (!studentRecords.eof())                       // reads all the data in the file until the end of the file
        {
            studentNode* newStudent = new studentNode;
            newStudent->next = nullptr;
                                                                        // csv = comma seperated-values
            studentRecords >> newStudent->studentInfo.studentID;        // reads csv and converts it into a linked list
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
                head = newStudent;              // sets head to the first node in the linked list
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
        studentRecords.close();                 // closefile before returning to main
    }
    return true;                                // returns true if file is existing and has finished reading data from the file
}

bool isFileEmpty(const std::string& filename)   // checks if a file is empty, used in loadrecords function
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) { 
        file.close(); 
        return true;
    }

    file.close();
    return false; 
}

void saveRecordsToFile(studentNode* head, std::fstream& studentRecords) // saves records in linked list form to csv or the text file
{
    std::cout << "\nSaving records to file...\n";
    studentRecords.open("student_records.txt", std::ios::out | std::ios::trunc);    // open file and truncate outdated file
    if (!studentRecords.is_open())
    {
        std::cerr << "Unable to open file for writing.\n";
        return;
    }
    studentNode* temp = head;
    while (temp != nullptr)             // loops until the end of the linked list is reached
    {                                   // prints student infos to the file
        studentRecords << std::endl << temp->studentInfo.studentID << "," << temp->studentInfo.lastName << "," <<
                                        temp->studentInfo.firstName << "," << temp->studentInfo.birthday << "," <<
                                        temp->studentInfo.address << "," << temp->studentInfo.gender << "," <<
                                        temp->studentInfo.degreeProgram << "," << temp->studentInfo.yearLevel;
        temp = temp->next;
    }
    studentRecords.close();             // close file
    std::cout << "\nFile succesfully saved!\n"; // prints after printing student data to the file
    return;
}

void addRecord(studentNode*& head)                  // adds new records to the linked list
{
    studentNode* newStudent = new studentNode;
    newStudent -> next = nullptr;

    do
    {
        do
        {
            std::cout << "Enter Student ID Number: ";               // asks for the new student's id number
            while (!(std::cin>>newStudent->studentInfo.studentID))  // only accepts integer values for  id number
            {
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
        if (checkIDMatch(head, newStudent->studentInfo.studentID))  // check if id is already taken
        {
            std::cout<<"\nThat student ID already exists!\n\n";     // prints if id is already taken
        }
    } while (checkIDMatch(head, newStudent->studentInfo.studentID));    // asks again for the new student's id number if id is already taken

    std::cin.ignore();
    std::cout << "Enter Last Name: ";                       // asks new student's last name
    getline(std::cin, newStudent->studentInfo.lastName);    // get new student's last name
    std::cout << "Enter First Name: ";                      // asks new student's first name
    getline(std::cin, newStudent->studentInfo.firstName);   // get new student's first name
    std::cout << "Enter Birthday [MM/DD/YYYY]: ";           // asks new student's birthday
    getline(std::cin, newStudent->studentInfo.birthday);    // get new student's birthday
    std::cout << "Enter Address: ";                         // asks new student's address
    getline(std::cin, newStudent->studentInfo.address);     // get new student's address

    char selectGender;
    do
    {
        std::cout << "Enter Gender [M/F]: ";                // asks new student's gender
        std::cin >> selectGender;
        if (selectGender != 'M' && selectGender != 'm'
            && selectGender != 'F' && selectGender != 'f')
        {
            std::cout<<"\nInvalid gender selection!\n\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (selectGender != 'M' && selectGender != 'm'     // loops if gender != m or f
            && selectGender != 'F' && selectGender != 'f');

    switch (selectGender)                                   // sets new student's gender to the corresponding values of m and f
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
    std::cin.ignore();                                      // clears input buffer to avoid error in the next input
    std::cout << "Enter Degree Program: ";                  // asks new student's degree program/course
    getline(std::cin, newStudent->studentInfo.degreeProgram);   // gets new student's degree program/course

    int selectYearLevel;
    do
    {
        std::cout << "Enter Year Level [1 - 5]: ";          // asks from 1st year to fifth year
        std::cin >> selectYearLevel;
        if (selectYearLevel < 1 || selectYearLevel > 5)
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "\nInvalid year level selection!\n\n";
        }
        else
        {
            switch (selectYearLevel)
            {
            case 1:
                newStudent->studentInfo.yearLevel = "1st Year";     // sets new student's yr level to the corresponding values of 1 to 5
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
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "\nInvalid selection! Press any key to try again.";
                system("pause>0");
                break;
            }
        }
    } while (selectYearLevel < 1 || selectYearLevel > 5);

    if (head == nullptr)                // appends the new student's info (from id to year level) to the very first of the lniked list
    {                                   // only append to the very first of the lniked list if there are no existing student node/records
        head = newStudent;
    }
    else
    {
        studentNode* temp = head;
        while (temp->next != nullptr)   // appends the new student's info (from id to year level) to the end of the linked list
        {
            temp=temp->next;
        }
        temp->next = newStudent;
    }
}

bool checkIDMatch(studentNode* head, int studentidattempt)  // checks if inputted id is already in the records
{
    studentNode* current = head;
    while (current)
    {
        if (current->studentInfo.studentID == studentidattempt)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void searchRecord (studentNode* head, studentDetails search)    // displays an entire new menu for searching records
{
    bool inSearchRecord = true;         // initializes values
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
        bool foundStudent = false;      // used to print if there is/are no data found in the records 
        int studentCounter = 1;         // used in displaying the table
        studentNode* current = head;
        if (current == nullptr)         // prints if there are no records in the linked list
        {
            std::cout<<"No data to be displayed. Please input at least one data.\n";
            inSearchRecord = false;
        }
        else
        {
            system("cls");
            std::cout << " ________________________________________________________________________________________________\n"
                        "|                                                                                                |\n"
                        "|                                         SEARCH RECORDS                                         |\n"
                        "|________________________________________________________________________________________________|\n\n";
            std::cout << "How do you want to search?\n\n"
                        << "[1] Search by Last Name\n"
                        << "[2] Search by First Name\n"
                        << "[3] Search by Gender\n"
                        << "[4] Search by Degree Program\n"
                        << "[5] Search by Year Level\n"
                        << "[6] Exit to Main Menu\n\n"
                        << "Please type your selection [1-6]: ";
            std::cin >> choiceSearch;                       // asks the user to select an option
            switch (choiceSearch)                           // get option
            {
                case 1:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nSearch records with last name: ";   // asks user to input the last name he/she is searching for
                    getline(std::cin, search.lastName);
                    while (current)
                    {
                        lastNameCStr = current->studentInfo.lastName.c_str();   //converts last name to cstring
                        searchLastNameCStr = search.lastName.c_str();           //converts user input last name to cstring
                        if (isStringEqualNotCaseSensitive(lastNameCStr, searchLastNameCStr) && foundStudent == false)
                        {                               // checks if user input last name matches a last name in the linked list
                            displayFirstRowTable();     // display the first row of the table if a student is found with the same last name
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(lastNameCStr, searchLastNameCStr))
                        {                               // display student details of the student with the matched last name
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)                           // prints the last printing line for the table
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                if (!foundStudent)                              // prints if no student is found
                        std::cout << "\nNo student found with last name '" << search.lastName << "'!\n";
                    pressToContinue();
                    break;
                case 2:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nSearch records with fIrst name: "; // asks user to input the first name he/she is searching for
                    getline(std::cin, search.firstName);
                    while (current)
                    {
                        firstNameCStr = current->studentInfo.firstName.c_str(); //converts first name to cstring
                        searchFirstNameCStr = search.firstName.c_str();         //converts user input first name to cstring
                        if (isStringEqualNotCaseSensitive(firstNameCStr, searchFirstNameCStr) && foundStudent == false)
                        {                               // checks if user input first name matches a first name in the linked list
                            displayFirstRowTable();     // display the first row of the table if a student is found with the same first name
                            foundStudent = true;
                        }
                        if (isStringEqualNotCaseSensitive(firstNameCStr, searchFirstNameCStr))
                        {                               // display student details of the student with the matched first name
                            displayRecordDetails(current, studentCounter);
                            studentCounter++;
                        }
                        current = current->next;
                    }
                    if (foundStudent)                       // prints the last printing line for the table
                        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
                if (!foundStudent)                          // prints if no student is found
                        std::cout << "\nNo student found with first name '" << search.firstName << "'!\n";
                    pressToContinue();
                    break;
                case 3:
                    do
                    {
                        std::cout << "\nSearch records with gender [M/F]: ";    // asks user to input gender he/she is searching for
                        std::cin >> selectGender;                               // get gender from user
                        if (selectGender != 'M' && selectGender != 'm'
                            && selectGender != 'F' && selectGender != 'f')
                        {
                            std::cout<<"\nInvalid gender selection!\n";
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                        }
                    } while (selectGender != 'M' && selectGender != 'm'
                            && selectGender != 'F' && selectGender != 'f');
                    switch (selectGender)                       // loops if gender input in invalid
                    {
                        case 'm':
                        case 'M':
                            search.gender = "Male";             // initializes the values for user's input
                            break;
                        case 'f':
                        case 'F':
                            search.gender = "Female";
                            break;
                    }
                    while (current)
                    {
                        genderCStr = current->studentInfo.gender.c_str();   // same process with searching last name and first name above
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
                case 4:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "\nSearch records with degree program: ";  // asks the user to input degree program he/she is searching for
                    getline(std::cin, search.degreeProgram);                // get degree program from user
                    while (current)
                    {
                        degreeProgramCStr = current->studentInfo.degreeProgram.c_str(); // same process with last name, first name, and gender
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
                case 5:
                    do
                    {                                           // asks the user to input year level he/she is searching for
                        std::cout << "\nSearch records with year level [1 - 5]: ";
                        std::cin >> selectYearLevel;            // gets year level from user 
                        if (selectYearLevel < 1 || selectYearLevel > 5)
                        {
                            std::cout<<"\nInvalid year level selection!\n\n";
                            std::cin.clear();
                        } 
                    } while (selectYearLevel < 1 || selectYearLevel > 5);   // loops if input is invalid
                    switch (selectYearLevel)
                    {
                        case 1:
                            search.yearLevel = "1st Year";          // initialies values from year level 1 to 5 into a string variable
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
                        yearLevelCStr = current->studentInfo.yearLevel.c_str();     // same process with last name, first name, 
                        searchYearLevelCStr = search.yearLevel.c_str();             // gender and degree program above
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
                case 6:
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

void displayFirstRowTable()             // displays the category list in the table
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

void displayRecordDetails(studentNode* head, int studentCounter)    // display the details of the student
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
}

void displaySpecificRecord(studentNode* head, int searchID)     // displays a specific record using a student id as input
{
    int studentCounter = 1;
    bool foundStudent = false;
    studentNode* current = head;
    
    while (current)
    {
        if (searchID == current->studentInfo.studentID && foundStudent == false)
        {
            displayFirstRowTable();                         // displays the first row of the table
            displayRecordDetails(current, studentCounter);  // displays the student's details
            studentCounter++;
            foundStudent = true;
        }
        current = current->next;
    }
    if (foundStudent)
        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";
}

bool isStringEqualNotCaseSensitive(const char string[], const char searchString[])  // used to check if a string is equal without
{                                                                                   // case sensitivity 

    char copyString[50] = "";
    for(int i = 0; i<strlen(string);i++)
    {
        copyString[i] = toupper(string[i]); // converts string being compared to uppercase
    }

    char copySearchString[50] = "";
    for(int i = 0; i<strlen(searchString);i++)
    {
        copySearchString[i] = toupper(searchString[i]); // converts the string to uppercase 
    }

    bool isStringEqual;
    isStringEqual=strcmp(copyString,copySearchString)==0;   // compares the two converted string if they are equal

    return isStringEqual;                                   // returns true if string is equal not case sensitive
}

void displayAllRecords(studentNode* head, std::fstream& studentRecords) // display all the records found in the linked list
{
    system("cls");
    std::cout << " ________________________________________________________________________________________________\n"
                "|                                                                                                |\n"
                "|                                      DISPLAY ALL RECORDS                                       |\n"
                "|________________________________________________________________________________________________|\n\n";
    int studentCounter = 1;
    if (head == nullptr)
    {
        std::cout << "No data to be displayed. Please input at least one data.\n";
    }
    else
    {
        std::cout << "Set window to fullscreen for better viewing.\n\n";    // prints the categories of the table

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

        while (head != nullptr)                           // reiterates until the end of linked list
    {                                                     // prints every student records found in the linked list
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
        std::cout << "\n|" << std::setfill('-') << std::setw(158) << "" << "|\n";   // prints the last line of the table
    }
}

bool deleteRecord(studentNode*& head, studentDetails search)    // used to delete a record by searching the id in the linked list
{

    studentNode* current = head;
    studentNode* prev = nullptr;
    char confirmDeleteFile;
    bool inDeleteRecord = true;

    while (current != nullptr && inDeleteRecord)    // traverses the linked list until a matched id is found
    {
        if (current->studentInfo.studentID == search.studentID)
        {                                                // asks if user is sure to delete a record
            std::cout << "\nAre you sure you want to delete this record? [Y/N]: ";
            std::cin >> confirmDeleteFile;               // gets user choice

            if (confirmDeleteFile == 'y' || confirmDeleteFile == 'Y')
            {
                if (prev == nullptr)        // if the record to be deleted is the head
                {
                    head = current->next;   // sets the next node of the as the new head
                } else
                {
                    prev->next = current->next;    // links the previous node and the node after the deleted node
                }
                delete current;             // delete the record
                std::cout << "\nFile successfully deleted\n";
                return true;                // function returns a true value if a record is deleted
            } else if (confirmDeleteFile == 'n' || confirmDeleteFile == 'N')
            {
                std::cout << "\nRedirecting you back to the menu...\n";
                inDeleteRecord = false;     // function returns a false value if user decides to not delete a record
                return false;
            } else
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');       // asks user again if input is invalid
                std::cout << "\nInvalid selection! Press any key to try again.";   
                system("pause>0");
            }
        }
        prev = current;           // used to link the nodes between a deleted node
        current = current->next;
    }
    return false;
}

void freeMemory (studentNode* head) // frees the memory after using the program
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