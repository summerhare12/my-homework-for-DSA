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
