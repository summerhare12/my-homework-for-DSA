#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>



using namespace std;

class arithmetic{
    public:

    void calculation(const string & str)
    {
        indicator = true;
        transform(str);
        if(indicator == false)
        {
            cerr << "ILLEGAL" << endl;
            return;
        }    
        print();  
        print_result();
    }

private:
    stack<char> operators;
    string postfix_expression;
    stack<double> numbers;
    bool indicator = true;//遇到非法情况，直接中止该表达式计算，进入测试程序下一个表达式

    int priority(char operators)//定义符号优先级
    {

        if(operators == '+' || operators == '-')
            return 1;
        else if(operators == '*' || operators == '/')
            return 2;
        else if(operators == '(' || operators == '[' || operators == '{')   
            return 0;   
        else
        {
            //cerr << "ILLEGAL" << endl;//未定义字符
            indicator = false;
            return -1;
        }
    }

    void right_bracket(char i)//集中处理右括号情况
    {
        char matching_bracket;
        if (i == ')') matching_bracket = '(';
        else if (i == ']') matching_bracket = '[';
        else if (i == '}') matching_bracket = '{';

        while (!operators.empty() && operators.top() != matching_bracket)
        {   
            postfix_expression += operators.top();
            operators.pop();
        }
        if (!operators.empty() && operators.top() == matching_bracket)
        {
            operators.pop();
        }
        else
        {
            //cerr << "ILLEGAL" << endl;//括号不匹配
            indicator = false;
        }
    }

    void transform(const string & expression)//将中缀表达式转化为后缀表达式
    {
        postfix_expression.clear(); 
        clear_stack(operators);
        clear_stack(numbers);
        int flag = 1;//正常情况下为0-1变量，用以指示运算符的连续出现个数，初值为1，检验开头为运算符
        int digit = 0;//用于小数点前位数计数，用于检验是否符合科学计数法规范
        bool point = false;//用于标记是否进入小数部分
        bool notion = false;//用于标记是否进入幂次部分
        for(char i : expression){
            if (i >= '0' && i <= '9')//数字情形，可能多位
            {   
                postfix_expression += i;
                flag = 0;
                if (point == false)
                    digit++;
            }
            else if (i == '.')
            {   
                if (notion == true)//科学计数法幂次不为整数，非法
                {
                    indicator = false;
                    return;                   
                }
                postfix_expression += i;
                flag = 0;
                point = true;                
            }
            else if (i == 'e')
            {
                if (digit > 1)//e前整数位数超过一位，不符合规范
                {
                    indicator = false;
                    return;
                }
                postfix_expression += i;
                flag = 1;
                digit = 0;
                point = false;//后跟幂次，新数恢复默认 
                notion = true;                             
            }
            else if ((i == '+' || i == '*' || i == '/' )&& flag == 0)//运算符
            {   
                flag++;
                while (!operators.empty() && priority(operators.top()) >= priority(i)) 
                { 
                    postfix_expression += operators.top();
                    operators.pop();
                }
                operators.push(i); 
                digit = 0;
                point = false;//后跟新数，恢复默认
                if (notion == true)
                    postfix_expression += 'E';                   
                notion = false; 
                postfix_expression += ' ';
            }

            else if ((i == '+' || i == '*' || i == '/' )&& flag >= 1)//运算符连续出现或在开头
            {   
                indicator = false;
                return;
            }
            
            else if (i == '-')
            {
                if (flag >= 2)
                {
                    indicator = false;
                    return;
                }
                else if (flag == 1)//意味着是负号
                {
                    postfix_expression += '-'; 
                    flag++;
                    digit = 0;
                    point = false;
                }
                else //flag == 0，意味着是减号，进行减法运算
                {
                    flag++;
                    while (!operators.empty() && priority(operators.top()) >= priority(i)) 
                    { 
                        postfix_expression += operators.top();
                        operators.pop();
                    }
                    operators.push(i); 
                    digit = 0;
                    point = false;
                    if (notion == true)
                        postfix_expression += 'E';  
                    notion = false;//对于科学计数法整体而言，进入新数，恢复默认，负号可能为整体的一部分，不可更改置零
                    postfix_expression += ' ';
                }
            }
   
            else if ( i == '(' || i == '[' || i == '{')
            {
                operators.push(i);
                digit = 0;
                point = false;
                if (notion == true)
                    postfix_expression += 'E'; 
                notion = false;
                postfix_expression += ' ';
            }

            else if (i == ')' || i == ']' || i == '}')
            {
                if (notion == true)
                    postfix_expression += 'E'; 
                right_bracket(i);
                notion = false;
            }

            else 
            {
                //cerr << "ILLEGAL" << endl;//未定义字符
                indicator = false;
            }

        }
        while (!operators.empty())
        {   
            postfix_expression += operators.top();
            operators.pop();
        }

    }


    double calculate()
    {   
        string num;
        int flag = 1;//在我的程序逻辑中，后缀表达式中的空格只出现在数字（包括负数）之前。
                     //flag用以表示数字即将开始。为保持逻辑一致，初值设为1
        for(char i : postfix_expression)
        {
            if (i == ' '|| i == 'e')
                flag = 1;
            
            if (i == '-' && flag == 1)//该部分if-else专用于处理数字（包括负数）并进行转化
            {
                num += i;
                // flag = 0;//此时切不可将flag置零！！必须出现数字后才能置零！
                //因为该组判断与下一组运算判断独立，置零后会满足下一组运算条件！
            }
            else if (i >= '0' && i <= '9' || i == '.')
            {
                num += i;
                flag = 0;
            }
            else if (!num.empty())
            {
                numbers.push(stod(num));
                num.clear();
            }

            if (i == '+' || i == '*' || i == '/' || i == 'E')//该部分if-else专用于处理运算
            {
                if (numbers.empty())
                {
                    indicator = false;
                    return -1;
                }
                double latter_number = numbers.top();//注意弹出顺序对应两个操作数顺序，对于除法有影响
                numbers.pop();
                
                if (numbers.empty())
                {
                    indicator = false;
                    return -1;
                }
                double former_number = numbers.top();
                numbers.pop(); 
                
                double result = fundamental(former_number,latter_number,i);
                numbers.push(result);
            }
            else if ( i == '-' && flag == 0)
            {
                if (numbers.empty())
                {
                    indicator = false;
                    return -1;
                }
                double latter_number = numbers.top();//注意弹出顺序对应两个操作数顺序，对于除法有影响
                numbers.pop();
                if (numbers.empty())
                {
                    indicator = false;
                    return -1;
                }
                double former_number = numbers.top();
                numbers.pop(); 
                
                double result = fundamental(former_number,latter_number,i);
                numbers.push(result);
            }
        }
        return numbers.top();
    }
    
    double fundamental(double former, double latter, char operators)
    {
        if (operators == '+')
        {
            return(former + latter);
        } 
        else if (operators == '-') 
        {
            return(former - latter);
        }
        else if (operators == '*') 
        {
            return(former * latter);
        }
        else if (operators == '/') 
        {
            if(latter == 0)//除数为零
            {
                //cerr << "ILLEGAL" << endl;
                indicator = false;
                return -404;//?
            }
            else
                return(former / latter);
        }
        else if (operators == 'E')//将E看作运算符，对后缀表达式中前两个由e分隔的数进行科学计数法运算
        {
            double power = pow(10,latter);
            return (former * power);
        }
    } 

    void print()
    {
        for(char i : postfix_expression)
        {
            cout << i ;
        }
        cout << endl;
    }

    void print_result()
    {   
        double result = calculate();
        if(indicator == false)
        {
            cerr << "ILLEGAL" << endl;
            return;
        }
        cout << result << endl;  
    }

    template<typename T>
    void clear_stack(stack<T>& s)
    {
        while (!s.empty())
        {
            s.pop();
        }
    }

};