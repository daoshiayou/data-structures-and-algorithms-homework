/*
��Ŀ��
���ڼ򵥵�����������ʽ����ʵ�����¹��ܣ�

1.�������������ǰ׺���ʽ���������ţ�����׺���ʽ�����Դ����ţ����׺���ʽ���������ţ����ܹ��ڼ�����ڲ������һ�ű��ʽ��������������ͼʾ��ʾ�������ַ�ͼ��ͼ�ε���ʽ����
2.���ڹ���õ��ڲ����ʽ�������������û���Ҫ�������Ӧ��ǰ׺���ʽ���������ţ�����׺���ʽ�����Դ����ţ����������������ţ�����׺���ʽ���������ţ���
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

template <class T>
class BinaryTree;

template <class T>
class BinaryTreeNode
{
    friend class BinaryTree<T>;

private:
    T info;
    BinaryTreeNode<T> *lChild;
    BinaryTreeNode<T> *rChild;

public:
    BinaryTreeNode() : lChild(NULL), rChild(NULL){};
    BinaryTreeNode(const T ele) : info(ele), lChild(NULL), rChild(NULL) {}
    BinaryTreeNode(const T ele, BinaryTreeNode<T> *l, BinaryTreeNode<T> *r) : info(ele), lChild(l), rChild(r) {}

    T value() { return info; }
    BinaryTreeNode<T> *leftChild() { return lChild; }
    BinaryTreeNode<T> *rightChild() { return rChild; }

    void setLeftChild(BinaryTreeNode<T> *lc) { this->lChild = lc; }
    void setRightChild(BinaryTreeNode<T> *rc) { this->rChild = rc; }
    void setValue(const T val) { this->info = val; }
    bool isLeaf()
    {
        if (lChild == NULL && rChild == NULL)
        {
            return true;
        }
        return false;
    }
};

template <class T>
class BinaryTree
{
private:
    BinaryTreeNode<T> *root;

public:
    BinaryTree() { root = NULL; }
    BinaryTree(BinaryTreeNode<T> *node)
    {
        root = node;
    }
    bool isEmpty()
    {
        return root == NULL;
    }
    BinaryTreeNode<T> *Root() { return root; }
};

//��׺���ʽת��Ϊ��׺���ʽ
string infixToPost(const string &infix)
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
        else if ((fixch >= 48 && fixch <= 57) || fixch == '.' || (fixch >= 65 && fixch <= 90) || (fixch >= 97 && fixch <= 122))
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
            cout << "��������δ֪����" << fixch << "���������������" << endl;
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
//��׺���ʽת��Ϊ��׺���ʽ
string postfixToIn(const string &postfix)
{
    char fixch;
    Stack<string> operands;
    int pos = 0; //��pos��¼������λ��
    for (int i = 0; i <= postfix.length(); i++)
    {
        fixch = postfix[i];
        if (fixch == ' ' || fixch == '\0')
        {
            if (postfix[i - 1] >= 48 && postfix[i - 1] <= 57 || (postfix[i - 1] >= 65 && postfix[i - 1] <= 90) || (postfix[i - 1] >= 97 && postfix[i - 1] <= 122))
            {
                string str = postfix.substr(pos, i - pos);
                operands.push(str);
                pos = i + 1;
            }
            else if (postfix[i - 1] == '+' || postfix[i - 1] == '-')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "��׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (operands.isEmpty())
                {
                    cout << "��׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op2);
                temp += op2 + postfix[i - 1] + op1;
                operands.push(temp);
                pos = i + 1;
            }
            else if (postfix[i - 1] == '*' || postfix[i - 1] == '/')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "��׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (op1.find("+") != -1 || op1.find("-") != -1)
                {
                    op1 += ")";
                    op1.insert(0, "(");
                }
                if (operands.isEmpty())
                {
                    cout << "��׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op2);
                if (op2.find("+") != -1 || op2.find("-") != -1)
                {
                    op2 += ")";
                    op2.insert(0, "(");
                }
                temp += op2 + postfix[i - 1] + op1;
                operands.push(temp);
                pos = i + 1;
            }
            else
            {
                if (i == postfix.length())
                {
                    continue;
                }
                cout << "���ʽ�к���δ֪����" << postfix[i - 1] << "�����������" << endl;
            }
        } //- + 1 * + 2 3 4 5
    }
    string infix;
    if (operands.isEmpty())
    {
        cout << "��׺ת��׺ʱջ��" << endl;
        return NULL;
    }
    operands.pop(infix);
    return infix;
}
//��׺���ʽת��Ϊǰ׺���ʽ
//(a+b)*(c+d)ת��Ϊ* + a b + c d
string infixToPre(const string &infix)
{
    string temp;
    Stack<char> stack;
    char ch, fixch;
    for (int i = infix.length() - 1; i > -1; i--)
    {
        fixch = infix[i];
        stack.top(ch);
        if (fixch == ' ')
        {
            continue;
        }
        else if ((fixch >= 48 && fixch <= 57) || fixch == '.' || (fixch >= 65 && fixch <= 90) || (fixch >= 97 && fixch <= 122))
        {
            temp += fixch;
        }
        else if (fixch == ')')
        {
            stack.push(infix[i]);
        }
        else if (fixch == '(')
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
                while (ch != ')')
                {
                    temp += ' ';
                    temp += ch;
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
            temp += ' ';
            while (!(stack.isEmpty()) && (ch == '*' || ch == '/'))
            {
                stack.pop(ch);
                temp += ch;
                temp += ' ';
                stack.top(ch);
            }
            stack.push(fixch);
        }
        else if (fixch == '*' || fixch == '/')
        {
            temp += ' ';
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
        temp += ' ';
        stack.pop(ch);
        temp += ch;
    }
    string prefix;
    for (int i = temp.length() - 1; i > -1; i--)
    {
        prefix += temp[i];
    }
    return prefix;
}
//ǰ׺���ʽת��Ϊ��׺���ʽ
string prefixToIn(const string &prefix)
{
    char fixch;
    Stack<string> operands;
    int pos = prefix.length(); //��pos��¼������λ��
    for (int i = prefix.length() - 1; i >= -1; i--)
    {
        if (i >= 0)
            fixch = prefix[i];
        if (fixch == ' ' || fixch == '\0' || i == -1)
        {
            if (prefix[i + 1] >= 48 && prefix[i + 1] <= 57 || (prefix[i + 1] >= 65 && prefix[i + 1] <= 90) || (prefix[i + 1] >= 97 && prefix[i + 1] <= 122))
            {
                string str = prefix.substr(i + 1, pos - i);
                operands.push(str);
                pos = i - 1;
            }
            else if (prefix[i + 1] == '+' || prefix[i + 1] == '-')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "ǰ׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (operands.isEmpty())
                {
                    cout << "ǰ׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op2);
                temp += op2 + prefix[i + 1] + op1;
                operands.push(temp);
                pos = i - 1;
            }
            else if (prefix[i + 1] == '*' || prefix[i + 1] == '/')
            {
                string op1, op2, temp;
                if (operands.isEmpty())
                {
                    cout << "ǰ׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op1);
                if (op1.find("+") != -1 || op1.find("-") != -1)
                {
                    op1 += "(";
                    op1.insert(0, ")");
                }
                if (operands.isEmpty())
                {
                    cout << "ǰ׺ת��׺ʱջ��" << endl;
                    return NULL;
                }
                operands.pop(op2);
                if (op2.find("+") != -1 || op2.find("-") != -1)
                {
                    op2 += "(";
                    op2.insert(0, ")");
                }
                temp += op2 + prefix[i + 1] + op1;
                operands.push(temp);
                pos = i - 1;
            }
            else
            {
                cout << "���ʽ�к���δ֪���ţ����������" << endl;
            }
        }
    }
    string temp;
    if (operands.isEmpty())
    {
        cout << "ǰ׺ת��׺ʱջ��" << endl;
        return NULL;
    }
    operands.pop(temp);
    string infix;
    for (int i = temp.length() - 1; i > -1; i--)
    {
        infix += temp[i];
    }
    return infix;
}

//��(a+b*(c-d))-e/f -> ��a b c d - * + e f / - -> ǰ - + a * b - c d / e f
//��׺���ʽת��Ϊ������
BinaryTree<string> expToTree(string expression)
{
    /**
        1.ɨ����ʽ
        2.��������������װΪһ�������������ջ
        3.������������������ջ��ȡ����������װΪ�����������ջ����һ��pop���Ľ����Ϊ�Һ��ӣ�
        4.ɨ�������ջ�����һ�������Ϊ�������ĸ�
     */
    char fixch;
    Stack<BinaryTreeNode<string> *> operands;
    int pos = 0; //��pos��¼������λ��
    for (int i = 0; i <= expression.length(); i++)
    {
        fixch = expression[i];
        if (fixch == ' ' || fixch == '\0')
        {
            if ((expression[i - 1] >= 48 && expression[i - 1] <= 57) || (expression[i - 1] >= 65 && expression[i - 1] <= 90) || (expression[i - 1] >= 97 && expression[i - 1] <= 122))
            {
                BinaryTreeNode<string> *node = new BinaryTreeNode<string>(expression.substr(pos, i - pos));
                // cout << expression.substr(pos, i - pos) << "��ջ" << endl;
                operands.push(node);
                pos = i + 1;
            }
            else if (expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/')
            {
                BinaryTreeNode<string> *node = new BinaryTreeNode<string>(expression.substr(i - 1, 1));
                BinaryTreeNode<string> *op1, *op2;
                if (operands.isEmpty())
                {
                    cout << i << "ջ��" << endl;
                }
                operands.pop(op1);
                node->setRightChild(op1);
                if (operands.isEmpty())
                {
                    cout << i << "ջ��" << endl;
                }
                operands.pop(op2);
                node->setLeftChild(op2);
                operands.push(node);
                pos = i + 1;
            }
            else
            {
                cout << "���ʽ�к���δ֪���ţ����������" << endl;
            }
        }
    }
    if (!operands.isEmpty())
    {
        BinaryTreeNode<string> *root;
        operands.pop(root);
        BinaryTree<string> tree(root);
        return tree;
    }
    else
    {
        cout << "��֪������ջ���ˣ����һ�°�" << endl;
        return NULL;
    }
}

//�������ı�ʾ
template <class T>
void showBinaryTree(BinaryTreeNode<T> *root, int height)
{
    // cout << "I'm testing" << height << endl;
    if (root == NULL)
    {
        return;
    }
    // cout << "I'm testing r" << height << endl;
    showBinaryTree(root->rightChild(), height + 1);
    for (int i = 0; i < height; i++)
    {
        cout << " \t";
    }
    cout << root->value() << endl;
    // cout << "I'm testing l" << height << endl;
    showBinaryTree(root->leftChild(), height + 1);
}

//������ת��׺���ʽ(��������)
template <class T>
struct stackEle
{
    BinaryTreeNode<T> *point;
    bool tag; //true ������������  false ������������
};

template <class T>
string treeToPostfix(BinaryTree<T> *tree)
{
    string postfix;
    if (tree->isEmpty())
    {
        cout << "������Ϊ��" << endl;
        return NULL;
    }
    Stack<stackEle<T>> node;
    BinaryTreeNode<T> *point = tree->Root();
    stackEle<T> ele;
    while (!node.isEmpty() || point)
    {
        while (point)
        {
            ele.point = point;
            ele.tag = false;
            node.push(ele);
            point = point->leftChild();
        }
        if (node.isEmpty())
        {
            cout << "ջ�գ�����д�ĺ��㷨" << endl;
        }
        node.pop(ele);
        point = ele.point;
        if (!ele.tag)
        {
            ele.tag = true;
            node.push(ele);
            point = point->rightChild();
        }
        else
        {
            postfix += point->value() + " ";
            point = NULL;
        }
    }
    return postfix;
}

int main()
{
    while (1)
    {
        cout << "��ѡ�����룺" << endl;
        cout << "1�� ��׺���ʽ" << endl;
        cout << "2�� ǰ׺���ʽ" << endl;
        cout << "3�� ��׺���ʽ" << endl;
        cout << "������ �˳�" << endl;
        char choice;
        cin >> choice;
        cin.clear();
        cin.ignore(1024,'\n');
        BinaryTree<string> tree;
        switch (choice)
        {
        case '1':
        {
            cout << "��������׺���ʽ:" << endl;
            char buff[1024];
            cin.getline(buff, 100, '\n');
            string infix(buff);
            string postfix = infixToPost(infix);
            tree = expToTree(postfix);
            cout << "ת����Ķ��������£�" << endl;
            showBinaryTree(tree.Root(), 0);
            break;
        }
        case '2':
        {
            cout << "������ǰ׺���ʽ�����ÿո�ָ���:" << endl;
            char buff[1024];
            cin.getline(buff, 100, '\n');
            string prefix(buff);
            string postfix = infixToPost(prefixToIn(prefix));
            tree = expToTree(postfix);
            cout << "ת����Ķ��������£�" << endl;
            showBinaryTree(tree.Root(), 0);
            break;
        }
        case '3':
        {
            cout << "�������׺���ʽ�����ÿո�ָ���:" << endl;
            char buff[1024];
            cin.getline(buff, 100, '\n');
            string postfix(buff);
            tree = expToTree(postfix);
            cout << "ת����Ķ��������£�" << endl;
            showBinaryTree(tree.Root(), 0);
            break;
        }
        default:
            return -1;
        }
        while (1)
        {
            cout << "��ѡ������������" << endl;
            cout << "1�� ��׺���ʽ" << endl;
            cout << "2�� ǰ׺���ʽ" << endl;
            cout << "3�� ��׺���ʽ" << endl;
            cout << "������ �˻�" << endl;
            cin >> choice;
            cin.clear();
            cin.ignore(1024,'\n');
            string postfix = treeToPostfix(&tree);
            switch (choice)
            {
            case '1':
                cout << "���������ɵ���׺���ʽΪ��" << postfixToIn(postfix) << endl;
                break;
            case '2':
                cout << "���������ɵ�ǰ׺���ʽΪ��" << infixToPre(postfixToIn(postfix)) << endl;
                break;
            case '3':
                cout << "���������ɵĺ�׺���ʽΪ��" << postfix << endl;
                break;
            default:
                break;
            }
            if (choice != '1' && choice != '2' && choice != '3')
                break;
        }
    }
    return 0;
}