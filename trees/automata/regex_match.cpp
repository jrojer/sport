#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <array>

using namespace std;

struct Node
{
    enum {any=-1,eps=-2};
    array<Node*,2> next;
    array<int,2> value;
};

struct StackItem
{
    Node* state;
    int pos;
};

bool solve(const string& s, const string& p) 
{
    vector<Node> nodes(1);
    nodes.reserve(p.size()+1);

    for(int i=0;i<p.size();++i)
    {
        if(p[i]=='*')
        {
            continue;
        }
        int ch = p[i] == '.' ? Node::any : p[i];
        bool loop = i+1<p.size() ? p[i+1]=='*' : false;

        Node* prev = &nodes.back();
        nodes.emplace_back();
        Node* curr = &nodes.back();
        prev->next[1] = curr; 
        if(loop)
        {
            prev->value[1] = Node::eps;
            curr->next[0] = curr;
            curr->value[0] = ch;
        }
        else
        {
            prev->value[1] = ch;
        }
    }

    const Node* last_state = &nodes.back();

    vector<StackItem> stack(1,{&nodes[0],0});

    while(!stack.empty())
    {
        auto item = stack.back();
        stack.pop_back();
        
        if(item.pos == s.size() && item.state == last_state)
        {
            return true;
        }

        for(int i=0;i<2;++i)
        {
            if(item.state->next[i] != nullptr)
            {
                int symbol = item.state->value[i];
                int next_pos = symbol == Node::eps ? item.pos : item.pos+1; 
                if(symbol == Node::eps || (item.pos < s.size() && (symbol == Node::any || symbol == s[item.pos])))
                {
                    stack.push_back({item.state->next[i],next_pos});
                }
            }
        }
    }

    return false;
}

struct TestCase
{
    string s;
    string p;
    bool res;
};

static const vector<TestCase> kTestCases = {
    {"a",".",true},
    {"a","",false},
    {"","",true},
    {"abc","..*.",true},
    {"ab","..*.",true},
    {"a","..*.",false},
    {"","..*.",false},
    {"abxxxcxx","c*c*abx*",false},
    {"abxxxxx","c*c*abx*",true},
    {"ccccabx","c*c*abx",true},
    {"cabx","c*c*abx",true},
    {"abx","c*c*abx",true},
    {"abc",".*",true},
    {"ccccc","c*......",false},
    {"ccccccc","c*......",true},
    {"cccccc","c*......",true},
    {"maix","m.*i",false},
    {"mississippix","m.*i.",true},
    {"mississippix","m.*i",false},
    {"mississippi","m.*i",true},
    {"mississippi","m.s*i.*ip*i",true},
    {"mississippi","..s*is*ip*i",true},
    {"mississippi","mis*is*ip*i",true},
    {"mississippi","mis*is*p*.",false},
    {"aab","c*a*b",true},
    {"aa","a",false},
    {"aa","a*",true},
    {"ab",".*",true},
};

void test()
{
    int i = 0;
    for(const auto& tc: kTestCases)
    {
        bool a = solve(tc.s,tc.p);
        bool b = tc.res;
        printf(a==b?"%d OK\n" : "%d FAIL\n",i);
        ++i;
    };
};

int main()
{
    test();
    return 0;
}
