#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);


int wfs(set<int>& pool, const vector<vector<int>>& adj_list)
{
    vector<bool> visited(adj_list.size());
    int init_pool_size = pool.size();
    deque<int> q;
    q.push_back(*pool.rbegin());
    while(!q.empty())
    {
        int node = q.front();
        q.pop_front();
        pool.erase(node);
        visited[node] = true;
        for(int child: adj_list[node])
        {
           if(!visited[child]) 
           {
               q.push_back(child);
               visited[child] = true;
           }
        }
    }
    return init_pool_size - pool.size();
}

long cost_func(int a, int b, int n, int x)
{
    return x*(a-b) + b*n;
}

long min_cost(int a, int b, int n)
{
    return a < b ? cost_func(a,b,n,n) : cost_func(a,b,n,1);
}

// Complete the roadsAndLibraries function below.
long roadsAndLibraries(int n, int c_lib, int c_road, const vector<vector<int>>& cities) 
{
    long sum = 0;
    set<int> pool;
    for(int i =0;i<n;++i)
    {
        pool.insert(i);
    }
    vector<vector<int>> adj_list(n);
    for(const auto& c : cities)
    {
        int u = c[0] - 1;
        int v = c[1] - 1;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }
    while(!pool.empty())
    {
        int n0 = wfs(pool, adj_list);
        sum += min_cost(c_lib, c_road, n0);
    }
    return sum;
}

int main()
{
    freopen("graph_cost_input.txt", "r", stdin);

    int q;
    cin >> q;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string nmC_libC_road_temp;
        getline(cin, nmC_libC_road_temp);

        vector<string> nmC_libC_road = split_string(nmC_libC_road_temp);

        int n = stoi(nmC_libC_road[0]);

        int m = stoi(nmC_libC_road[1]);

        int c_lib = stoi(nmC_libC_road[2]);

        int c_road = stoi(nmC_libC_road[3]);

        vector<vector<int>> cities(m);
        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            for (int j = 0; j < 2; j++) {
                cin >> cities[i][j];
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        long result = roadsAndLibraries(n, c_lib, c_road, cities);

        cout << result << "\n";
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