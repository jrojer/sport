#include <cstdio>
#include <vector>

struct Stack
{
    void push(char a)
    {
        if (i == array.size())
        {
            array.push_back(0);
        }
        array[i++] = a;
    }

    char pop()
    {
        return array[--i];
    }

    size_t size()
    {
        return i;
    }

    std::vector<char> array;
    int i = 0;
};

bool IsCorrect(const char *s)
{
    const char closing[] = {')', ']', '}'};
    const char opening[] = {'(', '[', '{'};
    Stack stack;
    for (int i = 0; s[i] > 0; ++i)
    {
        char ch = s[i];
        for (int j = 0; j < 3; ++j)
        {
            if (ch == opening[j])
            {
                stack.push(ch);
                break;
            }
            if (ch == closing[j] && (stack.size() == 0 || stack.pop() != opening[j]))
            {
                return false;
            }
        }
    }
    if (stack.size() > 0)
    {
        return false;
    }
    return true;
}

int main()
{
    char s[100001] = {};
    scanf("%s", s);
    printf("%s\n", IsCorrect(s) ? "yes" : "no");
    return 0;
}