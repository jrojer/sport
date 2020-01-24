#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

/*

11111111111
111111
111111111
1111
1111111111111111
1111111
1111111
111111111
11111

*/

int recurse(const vector<int>& h, int l, int r, long& max_area)
{
    if(r - l <= 0)
    {
        return 0;
    }
    if(r - l == 1)
    {
        return h[l];
    }
    auto mid = min_element(h.begin() + l, h.begin() + r);
    int mid_pos = mid - h.begin();
    int min_l = recurse(h,l,mid_pos,max_area);
    int min_r = recurse(h,mid_pos+1,r,max_area);
    
    int this_min = *mid;
    if(min_l)
        this_min = min(this_min,min_l);
    if(min_r)
        this_min = min(this_min,min_r);
    long area = this_min * (r-l);
    if(area > max_area)
    {
        max_area = area;
    }
    return this_min;
}

long largestRectangle(vector<int>& h) 
{
    long max_area = 0;
    recurse(h,0,h.size(),max_area);
    return max_area;
}

int main()
{
    freopen("input.txt","r",stdin);

    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string h_temp_temp;
    getline(cin, h_temp_temp);

    vector<string> h_temp = split_string(h_temp_temp);

    vector<int> h(n);

    for (int i = 0; i < n; i++) {
        int h_item = stoi(h_temp[i]);

        h[i] = h_item;
    }

    long result = largestRectangle(h);

    cout << result << "\n";

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}