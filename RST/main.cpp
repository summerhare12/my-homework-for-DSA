#include"BinarySearchTree.h"
int main()
{
    BinarySearchTree<int> t;
    t.insert(7);
    t.insert(4);
    t.insert(6);
    t.insert(5);
    t.insert(3);
    t.insert(1);
    t.insert(2);
    t.insert(10);
    t.insert(9);
    t.insert(8);
    t.insert(12);
    t.insert(11);
    t.insert(13);
    std::cout<<"The tree is:"<<endl;
    t.printTree();

    t.remove(1);//删除叶子节点
    std::cout<<"After remove 1:"<<endl;
    t.printTree();

    t.remove(3);//只有右子节点
    std::cout<<"After remove 3:"<<endl;
    t.printTree();


    t.remove(7);//删除根节点
    std::cout<<"After remove 7:"<<endl;
    t.printTree();

    t.makeEmpty();
    std::cout<<"After makeEmpty:"<<endl;
    t.printTree();

    t.insert(7);
    t.insert(4);
    t.insert(6);
    t.insert(5);
    t.insert(3);
    t.insert(1);
    t.insert(2);
    t.insert(10);
    t.insert(9);
    t.insert(8);
    t.insert(12);
    t.insert(11);
    t.insert(13);

    std::cout<<"The tree is:"<<endl;
    t.printTree();
    t.remove(9);//只有左子节点
    std::cout<<"After remove 9:"<<endl;
    t.printTree();

    t.remove(10);//有两个子节点
    std::cout<<"After remove 10:"<<endl;
    t.printTree();

    t.remove(3);//有两个子节点，且右子树的最小节点恰为叶子
    std::cout<<"After remove 3:"<<endl;
    t.printTree();

    t.insert(7);
    t.insert(4);
    t.insert(6);
    t.insert(5);
    t.insert(3);
    t.insert(1);
    t.insert(2);
    t.insert(10);
    t.insert(9);
    t.insert(8);
    t.insert(12);
    t.insert(11);
    t.insert(13);

    std::cout<<"The tree is:"<<endl;
    t.printTree();

    t.remove(15);//移除不存在节点
    std::cout<<"After remove 15:"<<endl;
    t.printTree();

}