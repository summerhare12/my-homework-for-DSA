#include<iostream>
#include<utility>
#include<initializer_list>
#include<algorithm>

template<typename T>
class List
{
    private:
    
    struct Node
    {
        Node * pre = nullptr;
        Node * next = nullptr;
        T data ={};

        // Node() : data{}, pre{nullptr}, next{nullptr} {};  
    
        Node( const T & newdata = T{}, Node * p = nullptr, Node * n = nullptr)
            : data{newdata},pre{p},next{n}{};  

        Node( const T && newdata, Node * p = nullptr, Node * n = nullptr)
            : data{std::move(newdata)},pre{p},next{n}{};  
    };

    private:

    Node * head = nullptr;
    Node * tail = nullptr;
    int size = 0;

    void initialization()
    {
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->pre = head;
        const_iterator(tail);//如果不加这句，空链表直接insert会发生问题？
        size = 0;
    }

    public:

    class const_iterator
    {   
        protected:
        Node * current;

        const_iterator(Node * p): current{p}{};

        T & retrieve() const
        {   return (current->data);  }

        public:
        const_iterator():current(nullptr){};

        const T & operator*() const
        {   return retrieve();   }

        const_iterator & operator++()
        {
            current = current->next;//current为nullptr或tail情况?
            return *this;
        }

        const_iterator & operator++(int)
        {
            const_iterator originalpoint = *this;
            ++(*this);
            return originalpoint;
        }

        const_iterator & operator--()
        {
            current = current->pre;//current为nullptr或head情况?
            return *this;
        }

        const_iterator & operator--(int)
        {
            const_iterator originalpoint = *this;
            --(*this);
            return originalpoint;
        }

        bool operator==(const const_iterator & iter) const
        {   return (this->current == iter.current);   }

        bool operator!=(const const_iterator & iter) const
        {   return !(*this == iter);     }

        friend class List<T>;
    };

    class iterator: public const_iterator
    {   
        protected:
        iterator(Node * p): const_iterator(p){};   

        public:
        iterator();

        iterator & operator++()
        {
            this->current = this->current->next;//current为nullptr或tail情况?
            return *this;
        }

        iterator & operator++(int)
        {
            Node * originalpoint = this->current;
            ++(*this);
            return originalpoint;
        }

        iterator & operator--()
        {
            this->current = this->current->pre;//current为nullptr或head情况?
            return *this;
        }

        iterator & operator--(int)
        {
            Node * originalpoint = this->current;
            --(*this);
            return originalpoint;
        }

        T & operator*()
        {   return const_iterator::retrieve();   }

        const T & operator*() const
        {   return const_iterator::operator*();    }

        friend class List<T>;
    };



    public:

    List(){ initialization();  }   

    iterator begin()    {
        if (head == nullptr || head->next == nullptr)
        {
            std::cerr << "Error: head or head->next is nullptr in begin()" << std::endl;
            return iterator(nullptr);
        }
        return iterator(head->next);
    }
    const_iterator begin() const
        {
        if (head == nullptr || head->next == nullptr)
        {
            std::cerr << "Error: head or head->next is nullptr in begin()" << std::endl;
            return const_iterator(nullptr);
        }
        return const_iterator(head->next);
    }

    iterator end(){   return iterator(tail); }
    const_iterator end() const
    {   return iterator(tail); }


    iterator insert(iterator iter,const T & newdata)//current指向head？
    {
        Node * p = iter.current;
        Node * newnode = new Node(newdata, p->pre, p);
        p->pre->next = newnode;
        p->pre = newnode;
        size++;
        return iterator(newnode);
    }

    iterator insert(iterator iter,T && newdata)//current指向head？
    {
        Node * p = iter.current;
        Node * newnode = new Node(std::move(newdata), p->pre, p);
        p->pre->next = newnode;
        p->pre = newnode;
        size++;
        return iterator(newnode);
    }

    iterator remove(iterator iter)
    {
        if (iter.current == nullptr)
        {
            std::cerr << "Error: iterator is nullptr in remove()" << std::endl;
            return iter;
        }
        else
        {
        Node * p = iter.current;
        iterator latter(p->next);
        p->pre->next = p->next;
        p->next->pre = p->pre;
        delete p;
        size--;
        return latter;
        }
    }

    iterator remove(iterator upper,iterator lower)
    {
        iterator iter = upper;
        while( iter != lower )
            iter = remove(iter);
        return lower;
    }

    iterator remove_several(iterator upper,iterator lower)//优化版，和remove单个节点的逻辑不同,应该减少了指针操作
    {
        if (upper.current == nullptr || lower.current == nullptr)
            std::cerr << "Error: upper or lower iterator is nullptr in remove_several()" << std::endl;

        else
        {
            upper.current->pre->next = lower.current;
            lower.current->pre = upper.current->pre;
            
            iterator iter = upper;
            while( iter != lower ){
                Node * todelete = iter.current;
                ++iter;
                delete todelete;
                size--;
            }
        }

        return lower;
    }

    int getsize() const
    {   return size; }

    bool isEmpty() const
    {   return (getsize() == 0); }

    void clear()
    {   
        if(head == nullptr){
            std::cerr << "it's been cleaned before" << std::endl;
            return;
        }
        else
        //remove(begin(),end());
        remove_several(begin(),end());//我调用了remove一段，应该和逐个pop_front等价？
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }


    T & front(){    return(*begin());   }
    const T & front()const {    return(*begin());   }   

    T & back(){     return(*(--end()));    }
    const T & back()const {     return(*(--end()));    }

    void push_front(const T & newdata){  insert(begin(),newdata); }
    void push_front(T && newdata){  insert(begin(),newdata);    }
    //前面有针对左值和右值的两种insert,这里好像也没有必要再把newdata用move转换成左值？

    void push_back(const T & newdata){  insert(end(),newdata);  }
    void push_back(T && newdata){  insert(end(),newdata);  }

    void pop_front(){   remove(begin());    }
    void pop_back(){   remove(--end());    }


    // void linking(const List & list)//自己加的连接函数
    // {
    //     for(auto & x : list)
    //         push_back(x);
    // }

    // void linking(List && list)
    // {
    //     for(auto && x : list)
    //         push_back(x);//有两种push_back，同理
    // }


    List(std::initializer_list<T> newlist)
    {
        initialization();
        //linking(newlist);
        for(auto & x : newlist)
            push_back(x);
    }

    List(const List & newlist)
    {
        initialization();
        //linking(newlist);
        for(auto & x : newlist)
            push_back(x);
    }

    List(List && newlist)
    :size(newlist.size), head(newlist.head), tail(newlist.tail)
    {
        newlist.head = nullptr;  
        newlist.tail = nullptr;  
        newlist.size = 0; 
    }

    // List & operator=(List & newlist)
    // {
    //     if(this != &newlist)//为什么原程序没有判断这个捏？也没有清空可能有的内容？
    //     {
    //         clear();
    //         std::swap(size, newlist.size);
    //         std::swap(head, newlist.head);
    //         std::swap(tail, newlist.tail);
    //     }
    //     return (*this);
    // }

    List & operator=(const List & newlist)
    {
        if(this != &newlist)
        {
            clear();
            //linking(newlist);
            for(auto & x : newlist)
                push_back(x);
        }
        return (*this);
    }
    //如果不使用swap-and-copy策略的话也可以用前面定义过的linking函数

    // List & operator=(List && newlist)//好像没有被左值替代啊，右值检测如果没有写这个的话还是报错捏
    // {
    //     if(this != &newlist)
    //     {
    //         clear();
    //         std::swap(size, newlist.size);
    //         std::swap(head, newlist.head);
    //         std::swap(tail, newlist.tail);
            
    //     }
    //     return (*this);
    // }

    List & operator=(List && newlist)
    {
        if(this != &newlist)
        {
            clear();
            //linking(newlist);
            for(auto && x : newlist)
                push_back(x);
            // newlist.head = nullptr;
            // newlist.tail = nullptr;
        }
        return (*this);
    }

    void print_List()
    {   if(head != nullptr)
        {
            for( const_iterator iter = begin(); iter != end(); ++iter)
            std::cout << *iter << "\t";
            std::cout << std::endl;
        }
        else 
            std::cout << "List is empty or invalid" << std::endl;
        return;
    }


};