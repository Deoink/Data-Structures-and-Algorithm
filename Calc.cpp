#include <iostream>
using namespace std;

int main()
{
    char op;
    float no1, no2;
    
    cout << "Enter your number: ";
    cin >> no1;
    
    cout << "Input Operator: +, -, *, /: ";
    cin >> op;
    
    cout << "Enter another number: ";
    cin >> no2;

switch (op) {
    case '+':
        cout << no1 + no2;
    break;
    
    case '-':
        cout << no1 - no2;
    break;

    case '*':
        cout << no1 * no2;
    break;

    case '/':
        cout << no1 / no2;
    break;

    default:
        cout << "Error";
    }
    return 0;
}