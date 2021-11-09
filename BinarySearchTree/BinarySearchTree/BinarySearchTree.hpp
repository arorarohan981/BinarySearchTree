//
//  BinarySearchTree.hpp
//  BinarySearchTree
//
//  Created by Rohan Arora on 09/11/21.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include <exception>
#include <utility>
#include <stack>

namespace mylib{

/*In the Binary Tree there is no order how data is added.In Binary Search tree order is Specified.
 Binary Tree is either an empty tree or a tree with atmost 2 nodes pointing to left and right binary trees.
 */
template <typename T>
class BinarySearchTree{
private:
    struct Node{
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        T data;
        
         explicit Node(T userdata);
        ~Node()=default;
    };
    std::unique_ptr<Node> root;
    
    
    /*Returns True if Node's Left Subtree is Empty or else Returns false*/
    bool isNodesLeftSubtreeEmpty(Node *ptr) const;
    
    /*Returns True if Node's Right Subtree is Empty or else Returns false*/
    bool isNodesRightSubtreeEmpty(Node *ptr) const;
    
    /*Prints Tree in PreOrder Technique */
    void preOrder(Node* Iternode) const;
    
    
    /*Prints Tree in PostOrder Technique */
    void postOrder(Node* Iternode) const;
    
    
    
    /*Prints Tree in InOrder Technique */
    void inOrder(Node* Iternode) const;
    
    
    /*Returns True if the Node is a Leaf Node or else returns false */
    bool isLeafNode(Node *ptr);
    
public:
    
    virtual ~BinarySearchTree();
    
    /*Checks if the Tree is Empty . Returns True if the Tree is Empty or else Returns False .*/
    bool isEmpty() const;
    
    
    /*Inserts the Data in the Tree. Returns True if the if the data is added successfully or else returns false*/
    bool add(T data);
    
    /*Prints Tree in PreOrder Technique
     Wrapper for Private Function PreOrder */
    void preOrderPrintTree() const;
    
    /*Prints Tree in PostOrder Technique
     Wrapper for Private Function PostOrder */
    void postOrderPrintTree() const;
    
    
    
    /*Prints Tree in InOrder Technique
     Wrapper for Private Function InOrder */
    void inOrderPrintTree() const;
    
   
    /*Deletes the Data Passed in the parameter of the Function if the data Does'nt exist it returns false or else returns true */
    bool remove(T userData);
    
};

template <typename T>
BinarySearchTree<T>::Node::Node(T userdata):data(userdata){
}


template <typename T>
bool BinarySearchTree<T>::isNodesLeftSubtreeEmpty(Node *ptr) const{
    if(ptr->left.get()==nullptr){
        return true;
    }
    return false;
}

template <typename T>
bool BinarySearchTree<T>::isNodesRightSubtreeEmpty(Node *ptr) const{
    if(ptr->right.get()==nullptr){
        return true;
    }
    return false;
}



template <typename T>
bool BinarySearchTree<T>::isEmpty() const{
    if(root==nullptr){
        return true;
    }
    return false;
}





template <typename T>
BinarySearchTree<T>::~BinarySearchTree<T>(){
    root.release();
}

template<typename T>
bool BinarySearchTree<T>::add(T userData){
    std::unique_ptr<Node> userNode = std::make_unique<Node>(userData);
    if(isEmpty()){
        root=std::move(userNode);
        return true;
    }
    /*Created a Node Iterator which will iterate in the tree for inserting Data */
    Node* iterNode=root.get();
 
    while (true) {
        if(userData==iterNode->data){
            throw std::invalid_argument("Keys can't be same ");
        }
        if(userData < iterNode->data){
            if( isNodesLeftSubtreeEmpty(iterNode)){
            iterNode->left=std::move(userNode);
              
                return true;
            }
            iterNode=iterNode->left.get();
        }else{
            if( isNodesRightSubtreeEmpty(iterNode)){
            iterNode->right=std::move(userNode);
                
                return true;
            }
            iterNode=iterNode->right.get();
        }
    }
    return false;
    
    
}


template <typename T>
void BinarySearchTree<T>::preOrderPrintTree() const{
    if(isEmpty()){
        std::cout<<"Tree is Empty "<<std::endl;
        return;
    }
    std::cout<<"Printing Data in Pre Order Technique : "<<std::endl;
    preOrder(root.get());
}


template <typename T>
void BinarySearchTree<T>::inOrderPrintTree() const{
    if(isEmpty()){
        std::cout<<"Tree is Empty "<<std::endl;
        return;
    }
    std::cout<<"Printing Data in In-Order Technique : "<<std::endl;
    inOrder(root.get());
}


template <typename T>
void BinarySearchTree<T>::postOrderPrintTree() const{
    if(isEmpty()){
        std::cout<<"Tree is Empty "<<std::endl;
        return;
    }
    std::cout<<"Printing Data in Post Order Technique : "<<std::endl;
    postOrder(root.get());
}


template <typename T>
void BinarySearchTree<T>::postOrder(Node* nodeIter) const{
    
    if(nodeIter->left.get()!=nullptr){
        postOrder(nodeIter->left.get());
    }
    if(nodeIter->right.get()!=nullptr){
        postOrder(nodeIter->right.get());
    }
    std::cout<<nodeIter->data<<std::endl;
}


template <typename T>
void BinarySearchTree<T>::preOrder(Node* nodeIter) const{
    
    std::cout<<nodeIter->data<<std::endl;
    if(nodeIter->left.get()!=nullptr){
        preOrder(nodeIter->left.get());
    }
    if(nodeIter->right.get()!=nullptr){
        preOrder(nodeIter->right.get());
    }
   
}


template <typename T>
void BinarySearchTree<T>::inOrder(Node* nodeIter) const{
    
    
    if(nodeIter->left.get()!=nullptr){
        inOrder(nodeIter->left.get());
    }
    std::cout<<nodeIter->data<<std::endl;
    if(nodeIter->right.get()!=nullptr){
        inOrder(nodeIter->right.get());
    }
   
}




template <typename T>
bool BinarySearchTree<T>::remove(T userData){
    if(isEmpty()){
        std::cout<<"Tree is Empty Cannot remove data "<<std::endl;
        return false;
    }
    std::stack<Node*> stackOfAddress{};
    Node *iterptr=root.get();
    while(true){
        if(isLeafNode(iterptr)){
            if(userData==iterptr->data){
                iterptr=stackOfAddress.top();
                if(iterptr->data<userData){
                    iterptr->right.reset();}
                else{
                    iterptr->left.reset();
                }
                return true;
            }
            
        }
    if(iterptr->data<userData)
    {
        stackOfAddress.push(iterptr);
        iterptr=iterptr->right.get();
    }else{
        stackOfAddress.push(iterptr);
        iterptr=iterptr->left.get();
    }
        }
           return true;
}


template <typename T>
bool BinarySearchTree<T>::isLeafNode(Node* ptr){
    if(ptr->left.get()==nullptr and ptr->right.get()==nullptr){
        return true;
    }
    return false;
}

}










#endif /* BinarySearchTree_hpp */
