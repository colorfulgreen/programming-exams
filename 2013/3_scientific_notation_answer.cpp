#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char s[100];
    cin >> s;

    int len = strlen(s);
    int offset = 0;
    bool start_number = false;
    bool after_dot = false;
    char number[100] = {};
    int number_index = 0;

    for(int i=0; i<len; i++) {
        if('1' <= s[i] && s[i] <= '9') {
            number[number_index++] = s[i];
            if(!after_dot && start_number)
                offset -= 1;
            start_number = true;
        }
        else if(s[i] == '0') {
            if(start_number) 
                number[number_index++] = s[i];
            else {
                if(after_dot)
                    offset += 1;
            }
        }
        else if(s[i] == '.') {
            after_dot = true;
            if(!start_number)
                offset += 1;
        }
    }
    cout << number[0];
    if(strlen(number) >= 2)
        cout << '.';
    for(int i=1; i<strlen(number); ++i)
        cout << number[i];
    cout << 'e';
    cout << -offset << endl;

    return 0;
}
