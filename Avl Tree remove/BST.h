#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 


template <typename Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{ nullptr } {}

    BinarySearchTree(const BinarySearchTree &rhs) : root{ clone(rhs.root) } {}

    BinarySearchTree(BinarySearchTree &&rhs) noexcept : root{ rhs.root } {
        rhs.root = nullptr;
    }

    ~BinarySearchTree() {
        makeEmpty();
    }

    const Comparable &findMin() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree(std::ostream &out = std::cout) const {
        if (isEmpty()) {
            out << "Empty tree" << std::endl;
        } else {
            printTree(root, out);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    void remove(const Comparable &x) {
        if( isEmpty( ) )
            throw UnderflowException{ };
        remove(x, root);
    }

    BinarySearchTree &operator=(const BinarySearchTree &rhs) {
    if (this != &rhs) {
        BinarySearchTree temp(rhs);
        std::swap(root, temp.root);
    }
    return *this;
}

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

protected:
    struct BinaryNode
    {
        Comparable element;  
        BinaryNode *left;    
        BinaryNode *right;   
        int height;
        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt,int h=0)
            : element{ theElement }, left{ lt }, right{ rt },height{h} {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt,int h=0)
            : element{ std::move(theElement) }, left{ lt }, right{ rt },height{h} {}
    };

    BinaryNode *root;  

    BinaryNode *findMin(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    BinaryNode *findMax(BinaryNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const {
        if (t == nullptr) {
            return false;
        }
        if (x < t->element) {
            return contains(x, t->left);
        } 
        else if (x > t->element) {
            return contains(x, t->right);
        } 
        else {
            return true;  
        }
    }

    void printTree(BinaryNode *t, std::ostream &out) const {
        if (t != nullptr) {
            printTree(t->left, out);  
            out << t->element << std::endl;  
            printTree(t->right, out);  
        }
    }

    void makeEmpty(BinaryNode * &t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void insert(const Comparable &x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{x, nullptr, nullptr};
        } 
        else if (x < t->element) {
            insert(x, t->left);
        } 
        else if (x > t->element) {
            insert(x, t->right);
        } 
        else 
        {
        }
       balance(t);
    }

    void insert(Comparable &&x, BinaryNode * &t) {
        if (t == nullptr) {
            t = new BinaryNode{std::move(x), nullptr, nullptr};
        } else if (x < t->element) {
            insert(std::move(x), t->left);
        } else if (x > t->element) {
            insert(std::move(x), t->right);
        } else {
        }
        balance(t);
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

    BinaryNode *detachMin(BinaryNode *&t)
    {
        if(t==nullptr)
            return nullptr;
        if(t->left == nullptr)//左子树为空，即为子树最小节点
        {
            BinaryNode *right_Min_child = t;
            t=t->right;//直接用右子节点替换 
            balance(t);
            right_Min_child->right = nullptr;
            return right_Min_child;
        }
        else//如果左子树不为零，还没找到最小节点，递归向左继续查找
        {
            balance(t);//此时递归前每次balance，可以实现从树叶向根的回溯平衡
            return detachMin(t->left);
        }
    }
    
    void remove(const Comparable &x, BinaryNode * &root)
    {
        if (root == nullptr) //空树情形
        {
            return;  
        }

        if (x < root->element) 
        {
            remove(x, root->left);
            balance(root);
        } 

        else if (x > root->element)
        {
            remove(x, root->right);
            balance(root);
        } 

        else if (root->left != nullptr && root->right != nullptr) //有两个子节点
        {  
            BinaryNode *right_Min_child = detachMin(root->right); 
            right_Min_child->left = root->left;
            right_Min_child->right = root->right;
            delete root;
            root = right_Min_child;
        } 
        // else if (root->left != nullptr || root->right != nullptr)//仅有一个子树
        // {
        //     BinaryNode *toRemove = root;
        //     root = (root->left != nullptr) ? root->left : root->right;//直接由子节点替代
        //     delete toRemove;
        //     toRemove = nullptr;
        // }//此种情况，原子树本身平衡，替代后的新节点无需平衡操作

        // else//叶子
        // {
        //     delete root;
        //     root = nullptr;//删除即可，无需平衡，父节点及更高节点的平衡在递归中已经完成
        // }
        else 
        {
            BinaryNode *toRemove = root;
            root = (root->left != nullptr) ? root->left : root->right;//上面两种注释掉的情形，该实现都能直接涵盖
            delete toRemove;
            toRemove = nullptr;
        }
    }
        
    static const int ALLOWED_IMBALANCE = 1;
    int height( BinaryNode *t ) const
    {
        return t == nullptr ? 0 : t->height;//空节点的高度改为0
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }
    
    void balance( BinaryNode * & t )
    {
        if( t == nullptr )
            return;
        
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );
                
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }


    void doubleWithLeftChild( BinaryNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    void doubleWithRightChild( BinaryNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};