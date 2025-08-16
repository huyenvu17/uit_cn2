#include <iostream>
using namespace std;
int main()
{
    int age; cin>>age;
    char gender; cin>>gender;
    if(age > 0 && age < 21 && (gender == 'M' || gender == 'm'))
        cout << 3;
    else if(age > 0 && age < 21 && (gender == 'F' || gender == 'f'))
        cout << 4;
    else if(age >= 21 && age < 100 && (gender == 'M' || gender == 'm'))
        cout << 1;
    else if(age >= 21 && age < 100 && (gender == 'F' || gender == 'f'))
        cout << 2;
    else
        cout << "I do not know why";
    return 0;
}