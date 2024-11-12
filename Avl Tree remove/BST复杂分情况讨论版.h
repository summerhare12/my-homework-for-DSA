#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
      { }
    
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Deep copy.
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move.
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );
        
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ) const
    {
        if( isEmpty( ) )
            cout << "Empty tree" << endl;
        else
            printTree( root );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
     
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

  protected:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode   *left;
        BinaryNode   *right;
        int       height;

        BinaryNode( const Comparable & ele, BinaryNode *lt, BinaryNode *rt, int h = 1 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }
        
        BinaryNode( Comparable && ele, BinaryNode *lt, BinaryNode *rt, int h = 1 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };

    BinaryNode *root;


    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        
        balance( t );
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        
        balance( t );
    }
     
    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */

    BinaryNode* find_parent(const Comparable &x, BinaryNode *root) const 
    {
    if (root == nullptr || (root->left == nullptr && root->right == nullptr)) {
        return nullptr;
    }

    if ((root->left != nullptr && root->left->element == x) || (root->right != nullptr && root->right->element == x)) 
    {
        return root;
    }

    if (x < root->element) 
    {
        return find_parent(x, root->left);
    } 
    else 
    {
        return find_parent(x, root->right);
    }
    }

    BinaryNode *find(const Comparable &x, BinaryNode * & t) const//查找函数，用于返回节点
    {
         if( t == nullptr )
         {
            std::cout<<"Not Found"<<endl;
            return nullptr;
         }
            
        else if( x < t->element )
            return find( x, t->left );
        else if( x > t->element )
            return find( x, t->right );
        else
            return t;    
    }

    BinaryNode *detachMin(BinaryNode *&t)//
    {
        if(t == nullptr)
            return nullptr;
        else{
            BinaryNode * minNode = findMin(t);
            BinaryNode * parent = find_parent(minNode->element, root);
            //只有在含有两个子节点的情况下会调用detachMin，所以无需考虑子树的根本身是最小节点的情况
                parent->left = nullptr;//删除该节点，因为是最小节点，所以一定在左边
            return minNode;
        }
    }

    // void updateRoot(BinaryNode *newRoot)//删除根节点需要更新根节点信息，否则print操作无法实现
    // {
    //     root = newRoot;
    // }
    void UpgradeHeight( BinaryNode * & Node, BinaryNode * & root)//某个节点被删除后，所在的子树回溯整条都要更新高度
    {   
        if (Node == nullptr || root == nullptr) 
        {   return;  }
        
        BinaryNode * hunter = root;
        while(hunter != Node)
        {   
            if (Node->element < hunter->element) 
            {
                if (hunter->left != nullptr && hunter->right != nullptr) 
                {
                    hunter->height = std::max(hunter->left->height - 1, hunter->right->height) + 1;
                } 
                else if (hunter->left != nullptr)
                {
                    hunter->height = hunter->left->height;
                } 
                else if (hunter->right != nullptr) 
                {
                    hunter->height = hunter->right->height;
                } 
                else
                {
                    hunter->height = 1;
                }
                hunter = hunter->left;
            } 
            else 
            {
                if (hunter->left != nullptr && hunter->right != nullptr) 
                {
                    hunter->height = std::max(hunter->right->height - 1, hunter->left->height) + 1;
                } 
                else if (hunter->left != nullptr) 
                {
                    hunter->height = hunter->left->height;
                } 
                else if (hunter->right != nullptr)
                {
                    hunter->height = hunter->right->height;
                } 
                else {
                    hunter->height = 1;
                    }
                hunter = hunter->right;
                }
        }

    }

    void retrospective_balance( BinaryNode * & parent, BinaryNode * & root)//对发生remove的节点，回溯整条子树都进行balance
    {
        if((parent == nullptr)||(root == nullptr))
            return;
        else
        {
            while(parent != root)
            {
                balance(parent);
                parent = find_parent(parent->element,root);
            }
            balance(parent);
        }

    }

    void remove( const Comparable & x, BinaryNode * & root )
    {
        if (root == nullptr)
            return;
        else if (!(contains(x, root)))//不包含该节点
            return;//没找到，不操作
        else{
            BinaryNode *toRemove = find(x, root);
            if (toRemove == root)//防止对根找父节点出错，单独考虑
            {
                if((toRemove->right == nullptr)&&(toRemove->left == nullptr))//单节点树
                {
                    delete toRemove;
                    root = nullptr;
                    toRemove = nullptr;
                    return;
                }
                else if(toRemove->right == nullptr)
                {
                    root = toRemove->left;
                    delete toRemove;
                    toRemove = nullptr;
                }
                else
                {
                    BinaryNode *parent = find_parent(findMin(toRemove->right)->element,root);
                    BinaryNode *right_Min_child = detachMin(toRemove->right);

                    if (parent == root)
                    {
                        right_Min_child->left = root->left;
                        right_Min_child->right = nullptr;
                        root = right_Min_child;
                        right_Min_child->height = right_Min_child->left->height + 1;
                        balance(right_Min_child);
                        delete toRemove;
                        toRemove = nullptr;

                    }
                    else
                    {
                        right_Min_child->left = root->left;
                        right_Min_child->right = root->right;
                        root = right_Min_child;//删除根节点需要更新根节点信息，否则print操作无法实现
                        UpgradeHeight(parent, root);//更新高度
                        retrospective_balance(parent,root);
                        delete toRemove;
                        toRemove = nullptr;
                    }
                    }
                return;
            }
            else if((toRemove->left == nullptr)&&(toRemove->right == nullptr))//叶子
            {
                BinaryNode * parent = find_parent(x, root);
                UpgradeHeight(toRemove,root);
                if(x < parent->element)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                delete toRemove;
                toRemove = nullptr;
                retrospective_balance(parent,root);
                return;
            }
            else if(toRemove->left == nullptr)//只有右子节点
            {
                BinaryNode * parent = find_parent(x, root);
                UpgradeHeight(toRemove,root);//高度只需修改至x所在节点之前即可，子节点不改
                if(x < parent->element)
                    parent->left = toRemove->right;
                else
                    parent->right = toRemove->right;
                delete toRemove;
                toRemove = nullptr;
                retrospective_balance(parent,root);
                return;
            }
            else if(toRemove->right == nullptr)//只有左子节点
            {
                BinaryNode * parent = find_parent(x, root);
                UpgradeHeight(toRemove,root);
                if(x < parent->element)
                    parent->left = toRemove->left;
                else
                    parent->right = toRemove->left;
                delete toRemove;
                toRemove = nullptr;
                retrospective_balance(parent,root);
                return;
                }
            else//有两个子节点
            {
                BinaryNode * parent = find_parent(x, root);
                BinaryNode * parent_Min = find_parent(findMin(toRemove->right)->element,root);
                BinaryNode * right_Min_child = detachMin(toRemove->right);
                right_Min_child->left = toRemove->left;
                right_Min_child->right = toRemove->right;
                
                if(x < parent->element)
                    parent->left = right_Min_child;
                else
                    parent->right = right_Min_child;
                if(parent_Min == toRemove)//parent_Min为toRemove，段错误？
                {
                    UpgradeHeight(right_Min_child,root);
                    delete toRemove;
                    toRemove = nullptr;
                    retrospective_balance(right_Min_child,root);
                }
                else
                {
                    UpgradeHeight(parent_Min,root);
                    delete toRemove;
                    toRemove = nullptr;
                    retrospective_balance(parent_Min,root);
                }
                return;
            }

            }
    }
    
    
    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
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
                
        t->height = std::max( height( t->left ), height( t->right ) ) + 1;
    }
    
    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t ) const
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }
        // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height( BinaryNode *t ) const
    {
        return t == nullptr ? 0 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild( BinaryNode * & k2 )
    {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild( BinaryNode * & k1 )
    {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild( BinaryNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild( BinaryNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif
