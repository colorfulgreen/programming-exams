#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

/* NOTE 用一个 struct 记录位置 */
typedef struct number
{
    int num;
    int pos;
} Number;

bool cmp(Number a, Number b)
{
    return a.num < b.num;
}

/* test case
5
9 2 7 1 6

6
9 6 7 1 2 3
*/

int main()
{
    int n;
    cin >> n;
    vector<Number> array(n);
    for(int i=0; i<n; ++i) {
        cin >> array[i].num;
        array[i].pos = i + 1;
    }
    sort(array.begin(), array.end(), cmp);
    if(n % 2 == 0)
        cout << array[n/2 - 1].num << " " << array[n/2 - 1].pos << endl;
    cout << array[n/2].num << " " << array[n/2].pos << endl;
    
    return 0;
}
