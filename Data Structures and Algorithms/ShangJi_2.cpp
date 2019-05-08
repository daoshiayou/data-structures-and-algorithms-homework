/*
��Ŀ��
ʵ�ֱ��ʽ��ֵ�㷨��Ҫ���2��ʵ�֡�

1.��׺���ʽ�任Ϊ��׺  
2.��׺���ʽ��ֵ  
*/

#include <iostream>
#include <string>

using namespace std;

//������
template <class T>
class Link
{
private:
    T data;
    Link<T> *next;

public:
    Link(const T value = NULL, Link<T> *nextValue = NULL) : data(value), next(nextValue) {}
    void setData(const T value) { this->data = value; }
    void setNext(const Link<T> *nextP) { this->next = nextP; }
    T getData() { return this->data; }
    Link<T> *getNext() { return this->next; }
};

//�Զ���ջ
template <class T>
class Stack
{
private:
    Link<T> *topE; //ָ��ջ��Ԫ��
    int size;      //ջ�д��Ԫ������

public:
    Stack() : topE(NULL), size(0) {}
    void clear()
    {
        while (!this->isEmpty())
        {
            T ch;
            this->pop(ch);
        }
    }
    bool push(const T item)
    {
        if (this->isEmpty())
        {
            topE = new Link<T>(item);
            size++;
            return true;
        }
        else
        {
            Link<T> *temp = topE;
            topE = new Link<T>(item, temp); //error:�����µģ�ָ��֮ǰ�Ǹ�
            size++;
            return true;
        }
        return false;
    }
    bool pop(T &item)
    {
        if (this->isEmpty())
        {
            cout << "ջ�գ����ܳ�ջ" << endl; //The stack is empty, pop failed
            return false;
        }
        item = topE->getData();
        Link<T> *temp = topE->getNext();
        delete topE;
        topE = temp;
        size--;
        return true;
    }
    bool top(T &item)
    {
        if (this->isEmpty())
        {
            return false;
        }
        item = topE->getData();
        return true;
    }
    bool isEmpty()
    {
        return topE == NULL || size == 0;
    }
};

//��׺���ʽת��Ϊ��׺���ʽ
string infixToP(const string &infix)
{
    string postfix;
    Stack<char> stack;
    char ch, fixch;
    for (int i = 0; i < infix.length(); i++)
    {
        fixch = infix[i];
        stack.top(ch);
        if (fixch == ' ')
        {
            continue;
        }
        else if ((fixch >= 48 && fixch <= 57) || fixch == '.')
        {
            postfix += fixch;
        }
        else if (fixch == '(')
        {
            stack.push(infix[i]);
        }
        else if (fixch == ')')
        {
            if (stack.isEmpty())
            {
                cout << "���Ų�ƥ�䣬������������ʽ" << endl;
                stack.clear();
                return NULL;
            }
            else
            {
                stack.pop(ch);
                while (ch != '(')
                {
                    postfix += ' ';
                    postfix += ch;
                    if (!stack.pop(ch))
                    {
                        cout << "���Ų�ƥ�䣬������������ʽ" << endl;
                        stack.clear();
                        return NULL;
                    }
                }
            }
        }
        else if (fixch == '+' || fixch == '-')
        {
            postfix += ' ';
            while (!(stack.isEmpty()) && ch != '(')
            {
                stack.pop(ch);
                postfix += ch;
                postfix += ' ';
                stack.top(ch);
            }
            stack.push(fixch);
        }
        else if (fixch == '*' || fixch == '/')
        {
            postfix += ' ';
            while ((!stack.isEmpty()) && ch != '(' && ch != '+' && ch != '-')
            {
                stack.pop(ch);
                postfix += ch;
                postfix += ' ';
                stack.top(ch);
            }
            stack.push(fixch);
        }
        else
        {
            cout << "��������δ֪���ţ��������������" << endl;
            return NULL;
        }
    }
    while (!stack.isEmpty())
    {
        postfix += ' ';
        stack.pop(ch);
        postfix += ch;
    }
    return postfix;
}

//��׺���ʽ��ֵ
double postfixCal(const string &postfix)
{
    Stack<double> stack;
    for (int i = 0; i <= postfix.length(); i++)
    {
        static char fixch;
        static int pos = 0;
        fixch = postfix[i];
        /**
         *  ������ɨ�裬pos��¼�ո��λ��
         *      1.�����ո��\0���ж�ǰͷ�ǲ�������
         *          ���֣���ջ
         *          ���������ջ��ȡ������������������󽫽����ջ
         *      2.pos����
         * */
        if (fixch == ' ' || fixch == '\0')
        {
            if (postfix[i - 1] >= 48 && postfix[i - 1] <= 57)
            {
                const char *str = postfix.substr(pos, i - pos).c_str();
                double op = atof(str);
                stack.push(op);
                pos = i;
            }
            else if (postfix[i - 1] == '+' || postfix[i - 1] == '-' || postfix[i - 1] == '*' || postfix[i - 1] == '/')
            {
                double op1, op2;
                if (!stack.isEmpty())
                {
                    stack.pop(op1);
                }
                if (!stack.isEmpty())
                {
                    stack.pop(op2);
                }
                switch (postfix[i - 1])
                {
                case '+':
                    stack.push(op2 + op1);
                    break;
                case '-':
                    stack.push(op2 - op1);
                    break;
                case '*':
                    stack.push(op2 * op1);
                    break;
                case '/':
                    stack.push(op2 / op1);
                    break;

                default:
                    break;
                }
                pos = i;
            }
        }
    }
    double result;
    if (!stack.isEmpty())
    {
        stack.pop(result);
    }
    return result;
}

/**
 *���ԣ�
��������׺���ʽ
23+(34*45)/(5+6+7)
ջ��
ջ��
ջ��
23 34 45 * 5 6 + 7 + / +
 */

int main()
{
    string infix;
    while (1)
    {
        cout << "��������׺���ʽ:" << endl;
        // cin >> infix;
        char buff[1024];
        cin.getline(buff,100,'\n');
        string infix(buff);
        string postfix = infixToP(infix);
        cout << "����ĺ�׺���ʽΪ��" << endl;
        cout << postfix << endl;
        cout << "��ֵ���Ϊ��" << endl;
        cout << postfixCal(postfix) << endl;
    }
    return 0;
}