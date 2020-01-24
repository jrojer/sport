#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

int main()
{
    vector<int> v{6,2,4};
    sort(v.rbegin(),v.rend());
    return 0;
}