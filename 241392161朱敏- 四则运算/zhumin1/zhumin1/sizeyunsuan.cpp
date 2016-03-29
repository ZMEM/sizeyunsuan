#include <iostream>
#include <cstdlib>
#include <ctime>
 
using namespace std;
 
// class Of opation
class opation
{
public:
    // 构造函数
    opation();
    // 构造函数
    ~opation();
    // 生成含有num个运算数字的随机表达式框架
    void CreateEx(int num);
    // 给生成的表达式框架填入符合条件的随机的数字
    int Count();
    // 输出所生成的表达式
    void Display();
     
private:
    // 比较运算符的优先级
    bool opIsHigher();
    // 得到运算符的权值
    int GetPriOfop(const char op);
 
private:
    int Result;
        // 表达式的结果
    char op;
        // 表达式的运算符
    opation *zuojiedian;
        // 表达式的左节点
    opation *youjiedian;
        // 表达式的右节点
    bool isRoot;
        // 该表达式是否为最终的表达式
    opation *Parent;
        // 表达式的父节点
    bool isLeft;
        // 是否为左节点(为了输出是加括号用)
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
