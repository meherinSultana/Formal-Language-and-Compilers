#include <bits/stdc++.h>

using namespace std;
int isSep(char c)
{
    return (c == ';' || c == ',' || c == '\'') ? 1 : 0;
}

int isOp(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '>' || c == '<' || c == '!' || c == '=') ? 1 : 0;
}

int isDigit(char c)
{
    return (c >= '0' && c <= '9') ? 1 : 0;
}

int isPar(char c)
{
    return (c == ')' || c == '(' || c == '}' || c == '{') ? 1 : 0;
}

int isSepa(const string& str)
{
    return (str.size() == 1 && isSep(str[0])) ? 1 : 0;
}

int isKey(const string& str)
{
    if (str == "int" || str == "float" || str == "char" || str == "else" || str == "if")
        return 1;
    return 0;
}

int isOper(const string& str)
{
    if (str.size() > 2)
        return 0;
    if (str.size() == 1)
    {
        if (isOp(str[0]))
            return 1;
        return 0;
    }
    if (isOp(str[0]) && str[1] == '=')
        return 1;
    return 0;
}

int isParen(const string& str)
{
    return (str.size() == 1 && isPar(str[0])) ? 1 : 0;
}

int isNum(const string& lex)
{
    int i, l, s;
    i = 0;
    if (isDigit(lex[i]))
    {
        s = 1;
        i++;
    }
    else if (lex[i] == '.')
    {
        s = 2;
        i++;
    }
    else
        s = 0;
    l = lex.size();
    if (s == 1)
        for (; i < l; i++)
        {
            if (isDigit(lex[i]))
            {
                s = 1;
            }
            else if (lex[i] == '.')
            {
                s = 2;
                i++;
                break;
            }
            else
            {
                s = 0;
                break;
            }
        }
    if (s == 2)
        if (isDigit(lex[i]))
        {
            s = 3;
            i++;
        }
        else
            s = 0;
    if (s == 3)
        for (; i < l; i++)
        {
            if (isDigit(lex[i]))
                s = 3;
            else
            {
                s = 0;
                break;
            }
        }
    if (s == 3)
        s = 1;
    return s;
}

int isId(const string& str)
{
    int x = 0;
    for (size_t i = 0; i < str.size(); i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')
        {
            x = 1;
            continue;
        }
        else if (isDigit(str[i]) == 1)
        {
            if (x == 0)
                return 0;
        }
        else
            return 0;
    }
    return 1;
}

int main()
{
    vector<char> a;
    vector<char> b;
    int error = 0;
    ifstream file("input.txt");
    if (!file.is_open())
    {
        cout << "No such file." << endl;
        return 0;
    }
    char ch;
    while (file.get(ch))
    {
        a.push_back(ch);
    }
    a.push_back('\0');
    cout << "Input:" << endl;
    cout.write(a.data(), a.size());
    cout << endl;

    int flag = 0;
    size_t n = a.size();
    size_t j = 0;
    int sepOn = 0;
    for (size_t i = 0; i < n; i++)
    {
        if (isSep(a[i]))
        {
            if (a[i] == '\'')
            {
                if (sepOn)
                {
                    sepOn = 0;
                    b.push_back(' ');
                    b.push_back(a[i]);
                }
                else
                {
                    b.push_back(a[i]);
                    b.push_back(' ');
                    sepOn = 1;
                }
            }
            else
            {
                b.push_back(' ');
                b.push_back(a[i]);
            }
        }
        else if (isOp(a[i]) == 1)
        {
            if (a[i + 1] == '=')
            {
                b.push_back(' ');
                b.push_back(a[i]);
                b.push_back(a[i + 1]);
                i++;
                b.push_back(' ');
            }
            else
            {
                b.push_back(' ');
                b.push_back(a[i]);
                b.push_back(' ');
            }
            flag = 1;
        }
        else if (isDigit(a[i]) == 1)
        {
            if (flag == 0)
            {
                flag = 1;
                b.push_back(' ');
            }
            b.push_back(a[i]);
        }
        else if (isPar(a[i]) == 1)
        {
            b.push_back(' ');
            b.push_back(a[i]);
            if (a[i] != ')' && a[i] != '}')
                b.push_back(' ');
        }
        else
        {
            flag = 1;
            b.push_back(a[i]);
        }
    }
    b.push_back('\0');
    cout << "\n\n";
    cout << "Output-1(Lexems are separated):" << endl;
    cout.write(b.data(), b.size());
    cout << endl;

    cout << "\n\n";
    cout << "Output-2(Lexems are categorized):" << endl;
    a[0] = '\0';
    j = 0;
    for (size_t i = 0; i < b.size(); i++)
    {
        if (b[i] == ' ')
        {
            a[j++] = '\0';
            if (strlen(a.data()) == 0)
            {
                j = 0;
                continue;
            }
            if (isSepa(a.data()) == 1)
            {
                cout << "[sep " << a.data() << "] ";
            }
            else if (isKey(a.data()) == 1)
            {
                cout << "[kw " << a.data() << "] ";
            }
            else if (isId(a.data()) == 1)
            {
                cout << "[id " << a.data() << "] ";
            }
            else if (isOper(a.data()) == 1)
            {
                cout << "[op " << a.data() << "] ";
            }
            else if (isParen(a.data()) == 1)
            {
                cout << "[par " << a.data() << "] ";
            }
            else if (isNum(a.data()) == 1)
            {
                cout << "[num " << a.data() << "] ";
            }
            else
            {
                error = 1;
                cout << "[unkn " << a.data() << "] ";
            }
            j = 0;
        }
        else
        {
            a[j++] = b[i];
        }
    }

    a[j++] = '\0';
    if (strlen(a.data()) > 0)
    {
        if (isSepa(a.data()) == 1)
        {
            cout << "[sep " << a.data() << "] ";
        }
        else if (isKey(a.data()) == 1)
        {
            cout << "[kw " << a.data() << "] ";
        }
        else if (isId(a.data()) == 1)
        {
            cout << "[id " << a.data() << "] ";
        }
        else if (isOper(a.data()) == 1)
        {
            cout << "[op " << a.data() << "] ";
        }
        else if (isParen(a.data()) == 1)
        {
            cout << "[par " << a.data() << "] ";
        }
        else if (isNum(a.data()) == 1)
        {
            cout << "[num " << a.data() << "] ";
        }
        else
        {
            cout << "[unkn " << a.data() << "] ";
        }
    }
    if (error == 1)
    {
        cout << "\n\nError Message:" << endl;
        cout << "INVALID [unkn 100.o5]" << endl;
    }

    return 0;
}
