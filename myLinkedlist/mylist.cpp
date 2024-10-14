#include<iostream>
#include<initializer_list>

template<typename T>
class SingleLinkedList
{
private:
class node
{
    private:
    T data;
    node* next = nullptr;
    public:
    node(const T& newdata){data = newdata;}
    friend class SingleLinkedList<T>;
};
node* head = nullptr;
node* currentposition = nullptr;
int size = 0;

void linkNewlist(node* &newnode)//my own defined function to simply certain process, like line65, 74 and 88
{
    if (head == nullptr)
    {
        head = newnode;
        currentposition = newnode;
    }
    else
    {
        currentposition->next = newnode;
        currentposition = newnode;
    }
    size++;
    }


public:
void makeEmpty()
{
    node* p = head;
    while(p != nullptr){
        node* toDelete = p;
        p = p->next;
        delete toDelete;
    }
}

void initialization()
{
    makeEmpty();
    head = nullptr;
    currentposition = nullptr;
    size = 0;
}

SingleLinkedList(){};

~SingleLinkedList()
{
    makeEmpty();
}

SingleLinkedList(std::initializer_list<T> inputlist)
{
    for (const auto &value : inputlist){
        node* newnode = new node(value);
        linkNewlist(newnode);
        }
}

SingleLinkedList(const SingleLinkedList<T>& knownlist)
{
    node* tempPointer = knownlist.head;
    while(tempPointer != nullptr){
        node* newnode = new node(tempPointer->data);
        linkNewlist(newnode);
        tempPointer = tempPointer->next;
    }
}

const SingleLinkedList<T> & operator=(const SingleLinkedList<T>& knownlist)
{
    if (this == &knownlist)
        return *this;
    else if (this->head != nullptr)
        initialization();
    node* tempPointer = knownlist.head;
    while(tempPointer != nullptr){
        node* newnode = new node(tempPointer->data);
        linkNewlist(newnode);
        tempPointer = tempPointer->next;
}
    return *this;

}

void printList()const
{
    node* p = head;
    while (p != nullptr){
        std::cout << p->data << "\t";
        p = p->next;
    }
    std::cout << std::endl; 
}

T getCurrentVal() const 
 {
    if(currentposition == nullptr){
        std::cout << "Empty current position! Can't get value!" << std::endl;
        return T();
    }
    else{
        return currentposition->data;
    }
 }

void setCurrentVal(const T &_val)
{
    if(currentposition == nullptr){
        std::cout << "Empty current position! Can't set value!" << std::endl;
        return;
    }
    else{
        currentposition->data = _val;
    }
}

bool isEmpty() const
{
    if(head == nullptr)
        return true;
    else
        return false;
}

void insert(T _val)
{
    if(isEmpty()){
        node* newnode = new node(_val);
        head = newnode;
        currentposition = newnode;
        size = 1;
    }
    else{
        node* newnode = new node(_val);
        newnode->next = currentposition->next;
        currentposition->next = newnode;
        size++;
    }
} 

void remove()
{
    if(isEmpty())
        return;
    else if(size == 1)
        initialization();
    else if(currentposition->next != nullptr){
        node* todelete = currentposition->next;
        currentposition->next = todelete->next;
        delete todelete;
        size--;
    }

}

bool find(const T &_val)//find value
{
    if(isEmpty())
        return false;
    else{
        node* seeker = head;
        while(seeker != nullptr){
            if(seeker->data == _val){
                currentposition = seeker;
                return true;
            }
            else
                seeker = seeker->next;
        }
            return false;
    }
}

void remove_improved_version()//change the function to remove the current node
{
    if(isEmpty()||currentposition == nullptr)
        return;
    else if(size == 1)
        initialization();
    else if(currentposition == head){  
        node* todelete = currentposition;  
        head = head->next;  
        currentposition = head;  
        delete todelete;  
        size--;  
    }  
    else{
        node* hunter = head;
        while (hunter->next != currentposition){
            hunter = hunter->next;
        }
        node* todelete = currentposition;
        currentposition = hunter;//i've made the current position the former one, cause no clear requirement.
        hunter->next = todelete->next;
        delete todelete;
        size--;
    }
}

};


int main(){
//SingleLinkedList<int> a;
SingleLinkedList<int> a{1,2,3,4,5};
int a_get = a.getCurrentVal();
std::cout << a_get << std::endl; //测试【取值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
//SingleLinkedList<char> b;
SingleLinkedList<char> b{'a','c','e'};
b.setCurrentVal('g');
b.printList(); //测试【定义值】操作是否正确，包括可能的空链表测试(//部分)，每种情况9分
SingleLinkedList<char> e;
std::cout << b.isEmpty() << " "
<< e.isEmpty() << std::endl; //测试【空链表判断】操作是否正确，18分
SingleLinkedList<double> c1;
SingleLinkedList<double> c2{1.5,2.0,9.0,4.7};
SingleLinkedList<double> c3;
c3 = c2;
c1.insert(3.0);
c2.insert(8.8);
bool f_c3 = c3.find(2.0);
c3.insert(8.8);
c1.printList();
c2.printList();
c3.printList(); //测试【插入】操作是否正确，每种情况6分
e.remove();
c1.remove();
bool f = c2.find(9.0);
c2.remove();
e.printList();
c1.printList();
c2.printList(); //测试【删除】操作是否正确，每种情况6分
return 0;
}
