#include"List.h"

int main()
{
    List<int> a({1,2,3,4,5});
    List<int> b = a;
    List<int> c({6,7,8});
    List<int> d;
    //List<int> null_tester;

    a.print_List();  
    b.print_List();     
    c.print_List();  
    d.print_List();  
  
    d = a = c;  
    a.print_List();
    d.print_List();

    c = c;
    c.print_List();
  
    List<int> e(std::move(b));//此后b已死，不可调用
    e.print_List(); 

    List<int> f({9,10});
    f.print_List();    
    d = std::move(f);//同理f已死  
    d.print_List();    
     
    List<int> h({12,13,14});
    h.push_front(11);
    h.push_back(15);//insert也在push_back里面完成测试了
    h.print_List();

    h.pop_front();
    h.pop_back();//remove完成了测试
    h.print_List();

    std::cout << "Front of h: " << h.front() << std::endl;
    std::cout << "Back of h: " << h.back() << std::endl;
 
    h.clear();
    std::cout << "List h after clear \n";
    h.print_List();

    std::cout << "Is h empty? " << (h.isEmpty() ? "Yes" : "No") << std::endl;
    a.print_List();
    std::cout << "Is a empty? " << (a.isEmpty() ? "Yes" : "No") << std::endl;
    std::cout << "Size of a is " << a.getsize() << std::endl;

    return 0;
}
    
     


