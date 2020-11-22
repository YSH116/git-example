#include <iostream>
#include <string>

using namespace std;

template<class T>
class Queue
{
public:

    Queue(string);
    string getData();
    void pop();
    void push(T);
    T top();
    bool empty();

private:
    T *array;
    int capacity;
    int first, end;
};

template<class T>
class Stack
{
public:
    Stack();
    void pop();
    void push(T);
    T top();
    bool empty();

private:
    T* array;
    int first;
    int capacity;
};

string infixToPostfix(string);
int postfixToAns(string);
bool valid(string);

int main(int argc, char *argv[])
{
    int N, one = 0;
    char E;
    string initial, infix, postfix, in;

    cin >> initial;
    Queue<char> qu(initial);

    while (cin >> in)
    {
        if (in == "Dequeue")
        {
            cin >> N;
            while (N--)
                qu.pop();
        }
        else if (in == "Enqueue")
        {
            cin >> E;
            qu.push(E);
        }
        else if (in == "Print")
        {
            if (one)
                cout << endl;
            else
                one = 1;

            infix = qu.getData();
            cout << infix << endl;
            if (!valid(infix))
                cout << "Invalid";
            else
            {
                postfix = infixToPostfix(infix);
                cout << postfix << endl << postfixToAns(postfix);
            }
        }
        else
            cout << "error command\n";
    }

    return 0;
}

template<class T>
Queue<T>::Queue(string ini)
{
    capacity = ini.length() * 2;
    array = new T[capacity];
    first = 0;
    end = ini.length();

    for (int i = 1; i <= end; i++)
        array[i] = ini[i - 1];
}

template<class T>
string Queue<T>::getData()
{
    string ans;
    if (end < first)
    {
        for (int i = first + 1; i < capacity; i++)
            ans += array[i];
         
        for (int i = 0; i <= end; i++)
            ans += array[i];
    } else
    {
        for (int i = first + 1; i <= end; i++)
            ans += array[i];
    }

    return ans;
}

template<class T>
void Queue<T>::pop()
{
    first = (first + 1) % capacity;
    array[first].~T();
}

template<class T>
void Queue<T>::push(T a)
{
    if ((end + 1) % capacity == first)
    {
        T* newArray = new T[capacity * 2];
        string cur = getData();
        first = 0;
        end = cur.length();

        for (int i = 1; i <= end; i++)
            newArray[i] = cur[i - 1];

        T* del = array;
        array = newArray;
        delete[] del;
    }

    end = (end + 1) % capacity;
    array[end] = a;
}

template<class T>
T Queue<T>::top()
{
    if (!empty())
        return (first + 1) % capacity;
    else
        return NULL;
}

template<class T>
bool Queue<T>::empty()
{
    if (first == end)
        return true;
    
    return false;
}

string infixToPostfix(string infix)
{
    string ans;
    Stack<char> sta;

    for (int i = 0; i < infix.length(); i++)
    {
        if (infix[i] >= '0' && infix[i] <= '9')
            ans += infix[i];
        else if (infix[i] == '+' || infix[i] == '-')
        {
            while (sta.top() == '*' || sta.top() == '/' || sta.top() == '+' || sta.top() == '-')
            {
                ans += sta.top();
                sta.pop();
            }
            sta.push(infix[i]);
        }
        else if (infix[i] == '*' || infix[i] == '/')
        {
            while (sta.top() == '*' || sta.top() == '/')
            {
                ans += sta.top();
                sta.pop();
            }
            sta.push(infix[i]);
        }
        else if (infix[i] == '(')
            sta.push(infix[i]);
        else if (infix[i] == ')')
        {
            while (sta.top() != '(')
            {
                ans += sta.top();
                sta.pop();
            }
            sta.pop();
        }
        else
            throw "error: In function infixToPostfix";
    }

    while (!sta.empty())
    {
        ans += sta.top();
        sta.pop();
    }

    return ans;
}

int postfixToAns(string post)
{
    int a, b;
    Stack<int> sta;

    for(int i = 0; i < post.length(); i++)
    {
        if (post[i] >= '0' && post[i] <= '9')
        {
            sta.push(post[i] - '0');
        }
        else
        {
            b = sta.top();
            sta.pop();
            a = sta.top();
            sta.pop();

            switch (post[i])
            {
            case '+':
                sta.push(a + b);
                break;
            case '-':
                sta.push(a - b);
                break;
            case '*':
                sta.push(a * b);
                break;
            case '/':
                sta.push(a / b);
                break;
            }
        }
    }
    return sta.top();
}

bool valid(string infix)
{
    int left = 0;
    
    if (infix[0] == '+' || infix[0] == '-' || infix[0] == '*' || infix[0] == '/' || infix[0] == ')')
        return false;

    for (int i = 0; i < infix.length() - 1; i++)
    {
        switch (infix[i]) {
            case '9':
            case '8':
            case '7':
            case '6':
            case '5':
            case '4':
            case '3':
            case '2':
            case '1':
            case '0':
                if ((infix[i + 1] <= '9' && infix[i + 1] >= '0') || infix[i + 1] == '(')
                    return false;
                break;
            case '+':
            case '-':
            case '*':
                if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' || infix[i + 1] == ')')
                    return false;
                break;
            case '/':
                if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' || infix[i + 1] == ')' || infix[i + 0] == '0')
                    return false;
                break;
            case '(':
                if (infix[i + 1] == '+' || infix[i + 1] == '-' || infix[i + 1] == '*' || infix[i + 1] == '/' || infix[i + 1] == ')')
                    return false;

                left++;
                break;
            case ')':
                if ((infix[i + 1] <= '9' && infix[i + 1] >= '0') || infix[i + 1] == '(')
                    return false;
                
                left--;
                break;
        }
    }

    switch (infix[infix.length() - 1])
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
            return false;
            break;
        case ')':
            left--;
    }

    if (left)
        return false;
    
    return true;
}

template<class T>
Stack<T>::Stack()
{
    capacity = 10;
    first = -1;
    array = new T[capacity];
}

template<class T>
void Stack<T>::pop()
{
    if (first != -1)
        array[first--].~T();
}

template<class T>
void Stack<T>::push(T a)
{
    if (first == capacity - 1)
    {
        T* newArray = new T[capacity * 2];
        for (int i = 0; i <= first; i++)
            newArray[i] = array[i];
        
        T* del = array;
        array = newArray;
        delete[] del;
        capacity = capacity * 2;
    }

    array[++first] = a;
}

template<class T>
T Stack<T>::top()
{
    if (first == -1)
        return '\0';
    
    return array[first];
}

template<class T>
bool Stack<T>::empty()
{
    if (first == -1)
        return true;
    else
        return false;
}

// By ARui