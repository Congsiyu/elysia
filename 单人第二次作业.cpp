#include <iostream>
using namespace std;
const int INF = 0x3f3f3f3f;
int arr[] = { 0,-31,-41,-59,-26,-53,-58,-97,-93,-23,-84 };
int cnt = 10;
int MaxSum() {
    int res = -INF, sum = 0;
    for (int i = 1; i <= cnt; i++) {
        if (sum < 0) {
            sum = arr[i];
        }
        else {
            sum += arr[i];
        }
        res = max(res, sum);
    }
    if (res < 0)
    {
        return 0;
    }
    else
    {
        return res;
    }
}
int main()
{
    cout<<MaxSum();
    return 0;
}
