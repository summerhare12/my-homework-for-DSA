#include "expression_evaluator(exponential).h"

int main(){

    string a = "12+(11+25)*3+41/5";//检验四则运算和括号
    cout<< "expression:"<< a << endl;
    arithmetic a1;
    a1.calculation(a);


    string b = "[12+(11+25)*3]/2+41/5";//中括号
    cout<< "expression:"<< b << endl;
    arithmetic a2;
    a2.calculation(b);


    string c = "{[12+(11+25)*3]/2+41/5}*3";//大括号
    cout<< "expression:"<< c << endl;
    arithmetic a3;
    a3.calculation(c);
   

    string d = "12+(11+25]*3+41/5";//括号不配对
    cout<< "expression:"<< d << endl;
    a1.calculation(d);
  

    string e = "({12+[11+25)*3]/2+41/5}*3";//更多括号不配对
    cout<< "expression:"<< e << endl;
    a2.calculation(e);

    string f = "(11+25)/0+41/5";//除数为零
    cout<< "expression:"<< f << endl;
    a3.calculation(f);

    string g = "(11+25)*$$+41/&";//未定义字符
    cout<< "expression:"<< g << endl;
    a3.calculation(g);

    string h = "(11++25)*15+41/2";//运算符连续出现
    cout<< "expression:"<< h << endl;
    a3.calculation(h);

    string i = "+25*15+41/2";//运算符在开头
    cout<< "expression:"<< i << endl;
    a3.calculation(i);

    string j = "(1+-25)*15+41/2";//中间负数测试
    cout<< "expression:"<< j << endl;
    a3.calculation(j);

    string k = "-25*15+41/2";//开头负数测试
    cout<< "expression:"<< k << endl;
    a3.calculation(k);

    string l = "2e3*15+41/2";//开头科学计数法
    cout<< "expression:"<< l << endl;
    a3.calculation(l);

    string m = "2e-4*150+41/2";//开头科学计数法，负幂次方
    cout<< "expression:"<< m << endl;
    a3.calculation(m);

    string n = "26.1e5*15+41/2";//科学计数法不合规范
    cout<< "expression:"<< n << endl;
    a3.calculation(n);

    string o = "2.6*10.6+40.5/2.4";//含小数的运算
    cout<< "expression:"<< o << endl;
    a3.calculation(o);

    string p = "2.6e2.6*10.6+40.5/2.4";//科学计数法幂次非法
    cout<< "expression:"<< p << endl;
    a3.calculation(p);
}