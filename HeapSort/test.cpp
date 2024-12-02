#include"HeapSort.h"
#include <random>
#include <iterator>
#include <numeric>

vector<int> random_vector_production();
vector<int> ascending_vector_production();
vector<int> descending_vector_production();
vector<int> random_repeated_vector_production();
bool check(vector<int> & v);
void HeapSort_Check_Timing(vector<int> & v);

int main()
{
    // std::vector<int> v{7,6,5,4,3,2,1};
    // HeapSort1(v);
    // printHeap(v);


    // std::vector<int> v1 = random_vector_production();
    // MyHeap<int> h1;
    // h1.HeapSort2(v1);
    // cout << "Check if the sorting is right:" << check(v1) << "\n" << endl;

    vector<int> random_v = random_vector_production();//构造随机序列
    // vector<int> random_v_copy = random_v;
    cout << "Check if it is ordered:" << check(random_v) << "\n" << endl;

    vector<int> ascending_v = ascending_vector_production();//构造升序序列
    // vector<int> ascending_v_copy = ascending_v;
    
    vector<int> descending_v = descending_vector_production();//构造降序序列
    // vector<int> descending_v_copy = descending_v;

    vector<int> random_repeated_v = random_repeated_vector_production();  //构造有重复的随机序列 
    // vector<int> random_repeated_v_copy = random_repeated_v;


    cout << "For a random vector: \n" << endl;
    HeapSort_Check_Timing(random_v);


    cout << "For an ascending vector: \n" << endl;
    HeapSort_Check_Timing(ascending_v);


    cout << "For a descending vector: \n" << endl;
    HeapSort_Check_Timing(descending_v);


    cout << "For a random vector with repeated elements: \n" << endl;
    HeapSort_Check_Timing(random_repeated_v);

    return 0;
}
    
    vector<int> random_vector_production()
    {
        vector<int> random_v(1000100);
        iota(random_v.begin(), random_v.end(), 1);

        random_device rd;
        mt19937 g(rd());// 使用gpt提示可用的随机设备和 Mersenne Twister 引擎
        shuffle(random_v.begin(), random_v.end(), g);

        // for (int num : random_v) {
        //     std::cout << num << " ";
        // }
        // std::cout << std::endl; //用于自己检验输出，成立后不再工作
        return  random_v;
    }

    vector<int> ascending_vector_production()
    {
        vector<int> ascending_v(1000100);//完全正序无间隔的序列
        for(int i = 1; i <= ascending_v.size() - 1; i++)
        {
            ascending_v[i] = i;
        }
        return ascending_v;
        
    }

    vector<int> descending_vector_production()
    {
        vector<int> descending_v(1000100);
        for(int i = 1; i <= descending_v.size() - 1; i++)
        {
            descending_v[i] = descending_v.size() - i + 1;//完全降序无间隔的简单序列
        }
        return descending_v;
        
    }

    vector<int> random_repeated_vector_production()
    {
        vector<int> random_repeated_v = random_vector_production();//借用先前的随机序列生成函数
        std::random_device rd;
        std::mt19937 g(rd());
        for (int i = 999900; i <= 1000000; i++) 
        {
            int j = (i - 999900) % 10 + 1;//使j在1到10循环
            random_repeated_v[i] = random_repeated_v[j];
        }
        shuffle(random_repeated_v.begin(), random_repeated_v.end(), g);    // 再次打乱序列
        return random_repeated_v;
    }

    // bool check1(vector<int> & v)//搞错了，一开始当成检验是否是堆了
    // {
    //     int i, j;
    //     for(i = 1; i <= 1000100; i *= 2)//事实上2^20 > 1000000
    //     {
    //         for (j = i; j < i * 2 && 2 * j + 1 <= 1000100; j++)//每行的父节点，同时注意防止无子节点
    //         {
    //             if(v[2 * j] < v[j] || v[2 * j + 1] < v[j])//验证堆性质
    //                 return false;
    //         }
    //     }
    //     return true;
    // }

    // bool check2(vector<int> & v) //利用algorithm的堆工具is_heap也可以检验是否成堆
    // {
    //     return std::is_heap(v.begin(), v.end(), std::greater<int>());
    // }

    bool check(vector<int> & v)
    {
        bool flag1 = true, flag2 = true;
        for(int i = 1; i < v.size() - 1; i++)
        {
            if (v[i] > v[i + 1])//依次比较升序性质
            {
                flag1 =  false;
                break;
            }
        }
        
        for(int i = 1; i < v.size() - 1; i++)
        {
            if (v[i] < v[i + 1])//依次比较降序性质
            {
                flag2 =  false;
                break;
            }
        }
        return (flag1||flag2);//升序或降序均通过
    }

    void HeapSort_Check_Timing(vector<int> & v)
    {
        vector<int> v_copy1 = v;
        vector<int> v_copy2 = v;
        auto start1 = chrono::high_resolution_clock::now();
        HeapSort1(v);
        auto end1 = chrono::high_resolution_clock::now();
        chrono::duration<double> heap_sort_duration1 = end1 - start1;
        cout << "My HeapSort1 duration: " << heap_sort_duration1.count() << " seconds" << endl;
        cout << "Check if the sorting is right:" << check(v) << endl;

        auto start2 = chrono::high_resolution_clock::now();
        MyHeap<int> h;
        h.HeapSort2(v_copy1);
        auto end2 = chrono::high_resolution_clock::now();
        chrono::duration<double> heap_sort_duration2 = end2 - start2;
        cout << "My HeapSort2 duration: " << heap_sort_duration2.count() << " seconds" << endl;
        cout << "Check if the sorting is right:" << check(v_copy1) << endl;

        auto start3 = chrono::high_resolution_clock::now();
        make_heap(v_copy2.begin(), v_copy2.end());//必须先建堆，在堆的基础上才能调用sort_heap!!
        sort_heap(v_copy2.begin(), v_copy2.end());
        auto end3 = chrono::high_resolution_clock::now();
        chrono::duration<double> random_heap_sort_duration3 = end3 - start3;
        cout << "std::sort_heap duration: " << random_heap_sort_duration3.count() << " seconds" << endl; 
        cout << "Check if the sorting is right:" << check(v_copy2) << "\n" << endl;
    }