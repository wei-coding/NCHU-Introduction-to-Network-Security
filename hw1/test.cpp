#include <iostream>
using namespace std;
int main(){
    string t;
    string line;
    cout << "cin:" << endl;
    cin >> t;
    cout << "getline:";
    cin.ignore();
    getline(cin,line);
    cout << "next";
}