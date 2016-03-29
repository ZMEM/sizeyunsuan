#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// class Of opation
class opation
{
public:
    // ���캯��
    opation();
    // ���캯��
    ~opation();
    // ���ɺ���num���������ֵ�������ʽ���
    void CreateEx(int num);
    // �����ɵı��ʽ�������������������������
    int Count();
    // ��������ɵı��ʽ
    void Display();
     
private:
    // �Ƚ�����������ȼ�
    bool opIsHigher();
    // �õ��������Ȩֵ
    int GetPriOfop(const char op);
 
private:
    int Result;
        // ���ʽ�Ľ��
    char op;
        // ���ʽ�������
    opation *zuojiedian;
        // ���ʽ����ڵ�
    opation *youjiedian;
        // ���ʽ���ҽڵ�
    bool isRoot;
        // �ñ��ʽ�Ƿ�Ϊ���յı��ʽ
    opation *Parent;
        // ���ʽ�ĸ��ڵ�
    bool isLeft;
        // �Ƿ�Ϊ��ڵ�(Ϊ������Ǽ�������)
};
opation::opation()
: Result(0)
, op('\0')
, zuojiedian(NULL)
, youjiedian(NULL)
, Parent(NULL)
, isLeft(false)
{
     
}
 
opation::~opation()
{
    if(zuojiedian != NULL)
    {
        delete zuojiedian;
    }
 
    if (youjiedian != NULL)
    {
        delete youjiedian;
    }
}
 
void opation::CreateEx(int num)
{
    if (1 == num)
    {
        return ;
    }
    else
    {
        int mode = rand() % 4;
        if (0 == mode)
        {
            op = '+';
        }
        else if (1 == mode)
        {
            op = '-';
        }
        else if (2 == mode)
        {
            op = '*';
        }
        else
        {
            op = '/';
        }
 
        zuojiedian = new opation();
        youjiedian = new opation();
        zuojiedian->Parent = this;
        zuojiedian->isLeft = true;
        youjiedian->Parent = this;
        youjiedian->isLeft = false;
 
        int numLeft = num - rand() % num;
        if (numLeft == num)
        {
            numLeft = 1;
        }
 
        zuojiedian->CreateEx(numLeft);
        youjiedian->CreateEx(num - numLeft);
    }
}
 
 
int opation::Count()
{
    if (zuojiedian != NULL && youjiedian != NULL)
    {
        int lResult = 0;
        int rResult = 0;
 
        lResult = zuojiedian->Count();
        rResult = youjiedian->Count();
 
        while (lResult >= 5000 || lResult <= 0)
        {
            lResult = zuojiedian->Count();
        }
 
        while (rResult >= 5000 || rResult <= 0)
        {
            rResult = youjiedian->Count();
        }
 
        if ('+' == op)
        {
            Result = lResult + rResult;
        }
 
        else if ('-' == op)
        {
            Result = lResult - rResult;
            if (Result < 0)
            {
                opation *temp = zuojiedian;
                zuojiedian = youjiedian;
                zuojiedian->isLeft = true;
                youjiedian = temp;
                youjiedian->isLeft = false;
                Result = rResult - lResult;
            }
        }
 
        else if ('*' == op)
        {
            int getNum = 0;
            Result = lResult * rResult;
            while(Result >= 3000)
            {
                lResult = zuojiedian->Count();
                rResult = youjiedian->Count();
                getNum++;
 
                if (getNum > 3000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        op = '+';
                        Result = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        op = '-';
                        Result = lResult - rResult;
                        if (Result < 0)
                        {
                            opation *temp = zuojiedian;
                            zuojiedian = youjiedian;
                            zuojiedian->isLeft = true;
                            youjiedian = temp;
                            youjiedian->isLeft = false;
                            Result = rResult - lResult;
                        }
                    }
 
                    return Result;
                }
 
                Result = lResult * rResult;
            }
        }
 
        else if ('/' == op)
        {
            int getNum = 0;
            while (0 == lResult || 0 == rResult || lResult % rResult != 0)
            {
                lResult = zuojiedian->Count();
                rResult = youjiedian->Count();
                getNum++;
                if(getNum > 2000)
                {
                    int mode = rand() % 2;
                    if (0 == mode)
                    {
                        op = '+';
                        Result = lResult + rResult;
                    }
                    else if (1 == mode)
                    {
                        op = '-';
                        Result = lResult - rResult;
                        if (Result < 0)
                        {
                            opation *temp = zuojiedian;
                            zuojiedian = youjiedian;
                            zuojiedian->isLeft = true;
                            youjiedian = temp;
                            youjiedian->isLeft = false;
                            Result = rResult - lResult;
                        }
                    }
 
                    return Result;
                }
            }
 
            Result = lResult / rResult;
        }
    }
    else
    {
        Result = rand() % 5000;
        while (Result == 0)
        {
            Result = rand() % 5000;
        }
    }
 
    return Result;
}
 
void opation::Display()
{
    if(zuojiedian != NULL && youjiedian != NULL)
    {
        if (!opIsHigher())
        {
            cout << '(';
        }
        zuojiedian->Display();
        cout << " " << op << " ";
        youjiedian->Display();
        if (!opIsHigher())
        {
            cout << ')';
        }
    }
    else
    {
        cout << Result;
    }
}
 
bool opation::opIsHigher()
{
    if (NULL == Parent)
    {
        return true;
    }
    if (isLeft)
    {
        return GetPriOfop(this->op) >= GetPriOfop(Parent->op);
    }
    else
    {
        return GetPriOfop(this->op) > GetPriOfop(Parent->op);
    }
}
 
int opation::GetPriOfop(const char op)
{
    if ('\0' == op)
    {
        return 3;
    }
    else if ('/' == op || '*' == op)
    {
        return 2;
    }
    else if ('+' == op || '-' == op)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    opation *pRoot = NULL;
 
    int numOfopation = 0;
 
    int numOfNumber = 0;
 
    cout << "please input the number of arithmetic expressions:" << endl;
 
    cin >> numOfopation;
 
    int Result = 0;
    srand((int)time(0));

 
    for (int i = 0; i < numOfopation; i++)
    {
        pRoot = new opation();
        numOfNumber = rand() % 7 + 2;
        pRoot->CreateEx(numOfNumber);
        Result = pRoot->Count();
        while (Result >= 5000 || Result <= 0)
        {
            Result = pRoot->Count();
        }
        pRoot->Display();
        cout << " = " << Result;
        cout << endl;
        delete pRoot;
    }
    return 0;
}
