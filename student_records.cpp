#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ofstream outFile("student_records.txt");

    if (outFile.is_open()) {
        // Write sample records to the file
        outFile << "10294,Asher Tibayan,2005-07-05,Imus Cavite,M,BSCSSE,1\n";
        outFile << "12345,Pogi Ka,2024-03-19,Piyutek,M,BSCSSE,1\n";
        outFile.close();
        cout << "File 'student_records.txt' created successfully.\n";
    } else {
        cerr << "Unable to create file.\n";
    }

    return 0;
}
