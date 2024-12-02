#include <algorithm>
#include <vector>
#include <iostream>
#include <chrono>
using namespace std;

void HeapSort1(vector<int> & v)
{
    make_heap(v.begin(),v.end());
    auto i = v.end();
    while(i != v.begin()){
        pop_heap(v.begin(),i);
        i--;
    }
    return;
}

void printHeap(vector<int> & v)
{
    for(auto i = v.begin();i != v.end();i++){
        cout << *i << " ";
    }
    cout << endl;
}

template<typename Comparable>
class MyHeap
{
    public:

    explicit MyHeap( int capacity = 1000100 ) : array( capacity + 1 ), currentsize{ 0 }
    { }

    explicit MyHeap(const vector<Comparable> & v ) : array( v.size( ) + 100 ), currentsize{ v.size( ) }
    {
        for( int i = 0; i < v.size( ); ++i )
            array[ i + 1 ] = v[ i ];
            BuildHeap(array);
    }

    int getsize()
    {
        return currentsize;
    }
    
    void BuildHeap(vector<Comparable> & v)
    {   
        for(auto i : v){
            insert(i);
        }
        return;
    }

    void insert(const Comparable & x)
    {
        if (currentsize == array.size() - 1)
            array.resize(array.size() * 2);
        array[++currentsize] = x; 
        PercolateUp(x);
    }

    Comparable deleteMin()
    {
        if (currentsize != 0)
        {
            if (currentsize == 1)
            {
                currentsize--;
                return array[1];
            }
            else{
                Comparable Min = array[1];
                array[1] = array[currentsize--];
                PercolateDown(1);
                return Min;
            }
        }
    }

    void HeapSort2(vector<Comparable> & v)
    {   
        BuildHeap(v);
        vector<Comparable> tempv;
        tempv.reserve(currentsize);//预留足够空间
        int originalsize = currentsize;      
        for(int i = 1; i <= originalsize; i++)
        {
            tempv.push_back(deleteMin());
        }
        currentsize = originalsize;
        v = tempv;
    }
        
    void printHeap()
    {
        for(int i =1; i <= currentsize; i++){
            cout << array[i] << " ";
        }
        cout << endl;
    }

    private:
        int currentsize;
        vector<Comparable> array;

    void PercolateUp(const Comparable & x)
    {
        int hole = currentsize;
        for (; x < array[hole / 2] && hole > 1; hole /= 2)
            array[hole] = std::move(array[hole / 2]);
        array[hole] = x;
    }

    void PercolateDown(int hole) // 自撰版本，逻辑更直接简单一些
    {
        Comparable t = array[hole];
        while(hole * 2 <= currentsize)
        {
            if(array[hole*2] > array[hole*2 + 1] && hole * 2 + 1 <= currentsize)
            {   
                if(array[hole*2 + 1] < t){
                array[hole] = array[hole*2 + 1];
                hole = hole*2 + 1;
                }
                else
                {   break; }
            }
            else
            {
                if(array[hole*2] < t){
                array[hole] = array[hole*2];
                hole = hole*2;
                }
                else
                {   break; }
            }
        }
        array[hole] = t;
        return;
    }

    // void PercolateDown( int hole )//课本代码版本
    // {
    //     int child;
    //     Comparable tmp = std::move( array[ hole ] );

    //     for( ; hole * 2 <= currentsize; hole = child )
    //     {
    //         child = hole * 2;
    //         if( child != currentsize && array[ child + 1 ] < array[ child ] )
    //             ++child;
    //         if( array[ child ] < tmp )
    //             array[ hole ] = std::move( array[ child ] );
    //         else
    //             break;
    //     }
    //     array[ hole ] = std::move( tmp );
    // }
};