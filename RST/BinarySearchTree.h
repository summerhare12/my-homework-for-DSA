#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

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
// void remove( x )       --> Remove x
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
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
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
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
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


  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
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
        else
            ;  // Duplicate; do nothing
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
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    // void remove( const Comparable & x, BinaryNode * & t )
    // {
    //     if( t == nullptr )
    //         return;   // Item not found; do nothing
    //     if( x < t->element )
    //         remove( x, t->left );
    //     else if( t->element < x )
    //         remove( x, t->right );
    //     else if( t->left != nullptr && t->right != nullptr ) // Two children
    //     {
    //         t->element = findMin( t->right )->element;
    //         remove( t->element, t->right );
    //     }
    //     else
    //     {
    //         BinaryNode *oldNode = t;
    //         t = ( t->left != nullptr ) ? t->left : t->right;
    //         delete oldNode;
    //     }
    // }

    // 


    // BinaryNode *find_parent(BinaryNode *&child, BinaryNode *&root) const //寻亲函数，按节点查找版
    // {
    //     BinaryNode *hunter = root;//hunter用来定位父节点
    //     if( root == nullptr )
    //         return nullptr;//空子树情形
    //     else if( hunter == nullptr){
    //         std::cerr<<"No such a child"<<endl;//所要找的子树中没有该子节点，出错
    //         return nullptr;
    //     }
    //     else{
    //         if(child->element < hunter->element)
    //         {
    //             if(hunter->left == child)
    //                 return hunter;
    //             else 
    //                 find_parent(child, hunter->left);
    //         }
    //         else{
    //             if(hunter->right == child)
    //                 return hunter;
    //             else 
    //                 find_parent(child, hunter->right);                
    //         }

    //     }
    // }

    BinaryNode *find_parent(const Comparable &x, BinaryNode *&root) const //寻亲函数，按值查找版
    {
        BinaryNode *hunter = root;//hunter用来定位父节点
        if( root == nullptr )
            return nullptr;//空子树情形
        else if( hunter == nullptr){
            std::cerr<<"No such a child"<<endl;//所要找的子树中没有该子节点，出错
            return nullptr;
        }
        else{
            if(x < hunter->element)
            {
                if(hunter->left->element == x)
                    return hunter;
                else 
                    find_parent(x, hunter->left);
            }
            else{
                if(hunter->right->element == x)
                    return hunter;
                else 
                    find_parent(x, hunter->right);                
            }

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

     void remove( const Comparable & x, BinaryNode * & root )
    {
        if (!(contains(x, root)))//不包含该节点
            return;//没找到，不操作
        else{
            BinaryNode *toRemove = find(x, root);
            if (toRemove == root)//防止对根找父节点出错，单独考虑
            {
                BinaryNode * right_Min_child = detachMin(toRemove->right);
                right_Min_child->left = root->left;
                right_Min_child->right = root->right;
                root = right_Min_child;//删除根节点需要更新根节点信息，否则print操作无法实现
                delete toRemove;
                return;
            }
            else if((toRemove->left == nullptr)&&(toRemove->right == nullptr))//叶子
            {
                BinaryNode * parent = find_parent(x, root);
                if(x < parent->element)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                delete toRemove;
                return;
            }
            else if(toRemove->left == nullptr)//只有右子节点
            {
                BinaryNode * parent = find_parent(x, root);
                if(x < parent->element)
                    parent->left = toRemove->right;
                else
                    parent->right = toRemove->right;
                delete toRemove;
                return;
            }
            else if(toRemove->right == nullptr)//只有左子节点
            {
                BinaryNode * parent = find_parent(x, root);
                if(x < parent->element)
                    parent->left = toRemove->left;
                else
                    parent->right = toRemove->left;
                delete toRemove;
                return;
                }
            else//有两个子节点
            {
                BinaryNode * parent = find_parent(x, root);
                BinaryNode * right_Min_child = detachMin(toRemove->right);
                right_Min_child->left = toRemove->left;
                right_Min_child->right = toRemove->right;
                
                if(x < parent->element)
                    parent->left = right_Min_child;
                else
                    parent->right = right_Min_child;

                delete toRemove;
                return;
            }

            }
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
     * t is the node that roots the subtree.
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
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
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
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
