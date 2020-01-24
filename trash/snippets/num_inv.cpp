#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


vector<int> merge(const vector<int>& a, const vector<int>& b, vector<int>& num_inv)
{
    vector<int> res;
    int i = 0;
    int j = 0;
    while(i < a.size() && j < b.size())
    {
        if(a[i] < b[j])
        {
            res.push_back(a[i]);
            num_inv[a[i]] += j;
            ++i;
        }
        else
        {
            res.push_back(b[j]);
           // num_inv[b[j]] += (a.size() - i);
            ++j;
        }
    }
    while(i < a.size())
    {
        res.push_back(a[i]);
        num_inv[a[i]] += j;
        ++i;
    }
    while(j < b.size())
    {
        res.push_back(b[j]);
        ++j;
    }
    return res;
}
/*
5 6 7 | 2 3 4

0 5 6 | 1 3 4 8
*/

// Complete the minimumBribes function below.
void minimumBribes(vector<int>& arr) 
{
    vector<int> num_inv(arr.size()+1);
    deque<vector<int>> q(arr.size());
    for(int i = 0; i < arr.size(); ++i)
    {
        q[i].push_back(arr[i]);
    }
    while(q.size() > 1)
    {
        int n = q.size();
        for(int i = 0; i + 1 < n; i+=2)
        {
            auto t1 = q.front();
            q.pop_front();
            auto t2 = q.front();
            q.pop_front();
            auto merge_res = merge(t1,t2,num_inv);
            q.push_back(merge_res);
        }
        if(n % 2 > 0)
        {
            auto t1 = q.front();
            q.pop_front();
            q.push_back(t1);
        }
    }
    if(all_of(num_inv.begin(),num_inv.end(),[](int x){ return x < 3;}))
    {
        cout << accumulate(num_inv.begin(), num_inv.end(), 0) << endl;
    }
    else
    {
        cout << "Too chaotic" << endl;
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string q_temp_temp;
        getline(cin, q_temp_temp);

        vector<string> q_temp = split_string(q_temp_temp);

        vector<int> q(n);

        for (int i = 0; i < n; i++) {
            int q_item = stoi(q_temp[i]);

            q[i] = q_item;
        }

        minimumBribes(q);
    }

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

