#ifndef BST_ASSIGNMENT_HPP
#define BST_ASSIGNMENT_HPP
using namespace std;

#include <iostream>
#include <algorithm>

template <typename T>
class BST
{
public:
    // We have a Node class with more features now
    // In addition to pointers to the left and right child,
    // there is also a pointer to the parent of Node.  
    // The parent of the root should always be nullptr
    // We also hava a height field to store the height of 
    // a node in the tree.
    class Node 
    {
    public:
        T key;
        int height = 0;
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        // default constructor
        Node(){}
        // constructor that takes one or optionally 2 arguments
        // if only one argument is passed in the second argument 
        // defaults to nullptr
        Node(T k, Node* input_node = nullptr)
        {
            key = k;
            parent = input_node;
        }
    };

private:
    // The BST has two private variables, a pointer to the root
    // and an unsigned integer to hold its size
    // We make the style choice of indicating these are private 
    // data variables by having a trailing underscore in their names.
    Node* root_ = nullptr;
    unsigned int size_ = 0;


public:
    // Default constructor.  No action required on this one.
    BST(); 

    // Destructor.  We implement this for you.
    ~BST();

    //*** Methods for you to implement
    // insert
    // insert the key k into the BST while maintaining the BST property
    // Like std::set, if k is already in the tree then no action is taken
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void insert(T k);

    // successor
    // Return a pointer to the node containing the smallest key larger 
    // than k
    // Return nullptr if k is the largest key in the tree
    // Also return nullptr if k is not in the tree
    //*** For you to implement
    Node* successor(T k);

    // delete the minimum
    // Erase the minimum key in the tree
    // Take no action if tree is empty
    //*** For you to implement
    void delete_min();

    // erase
    // Locate the key k in the tree and remove it
    // If k is not in the tree you do not have to do anything
    // Update the size_ variable and heights of nodes accordingly
    //*** For you to implement
    void erase(T k);

    // Implement a right rotation about the node pointed to by 
    // node, as described in Lecture 8.6.  This will only be 
    // called when node has a left child.  
    // If left_child points to the left child of *node, 
    // then *left_child becomes the parent of *node, and the 
    // right subtree of *left_child becomes the left subtree of *node.  
    // Node heights should be properly updated after this operation.
    //*** For you to implement
    void rotate_right(Node* node);

    //*** End of methods for you to implement

    // Returns the number of keys in the tree
    // we implement this for you, but it is up to you to correctly
    // update the size_ variable
    unsigned size();

    // Prints out the keys in the tree via an in-order traversal
    // we implement this for you
    void print();

    void pretty_print(const std::string &prefix, const Node *node, bool is_left, bool has_left_sibling);
    void pretty_print();

    // Returns a pointer to the node containing the key k
    // We implement this for you
    Node* find(T k);

    // Creates a vector holding the keys in the tree by
    // doing an in-order traversal
    // We implement this for you, it is used in our testing.
    std::vector<T> make_vec();

    // The next two functions are to check your height values 
    // Please do not modify
    std::vector<int> your_postorder_heights();

    std::vector<int> real_postorder_heights();

    // get_root_value returns the value stored at the root
    // It used for testing purposes
    // No action needed on your part
    T get_root_value();

    // Return a pointer to the node containing the minimum key in the tree
    // We implement this for you
    Node* min();

private: 
    // We found it useful to have a "fix_height" function.
    // This assumes that the subtrees rooted at node's children have 
    // correct heights and then walks up the tree from node to the root 
    // correcting the heights.
    // You can implement this, or correct the heights another way
    void fix_height(Node* node)
    {
        // This condition will run as long as the parameter is not null
        if(node != nullptr)
        {
            // We can call the fix_height function to the parameter's right child
            // if its right child is not null
            if(node->right != nullptr) fix_height(node->right);

            // We can also call the fix_height function to the parameter's left child
            // if its left child is not null
            if(node->left != nullptr) fix_height(node->left);

            // We must instantiate a value as it cannot be called during the If conditions.
            int my_value = 0;

            // These two conditions will assign the height of the parameter's right child's height, 
            // or potentially its left child's height if its left child's height is higher 
            // than its right child's height
            if(node->right != nullptr) my_value = node->right->height;
            if(node->left != nullptr) my_value = (my_value < node->left->height) ? node->left->height:my_value;
            
            // The function can now conclude by assigning the parameter's height to either 0 if the parameter 
            // is a leaf node or our initialised integer if it is any other type of node. We must add 1 to
            // this value as we need to increment
            node->height=(node->right == nullptr && node->left == nullptr) ? node->height = 0 : (my_value+1); 
        } 
    }
    // make into a function
    // if its a null pointer return 

    // else make 2 ints -> left height and right height 
    // int left_height = node->left == null ? minus 1 : node's left height
    // int right_height = node->right == null ? minus 1 : node's right height
    // node-> height = std::max(left_height, right)height +1;
    // end w/ fix_height(node->parent)

    // The rest of these functions are already implemented

    // helper function for the destructor
    void delete_subtree(Node* node);

    // returns pointer to minimum node in subtree rooted by node
    // Assumes node is not nullptr
    Node* min(Node* node);

    // helper function for print
    void print(Node* node);

    // helper function for make_vec
    void make_vec(Node* node, std::vector<T>& vec);

    void your_postorder_heights(Node* node, std::vector<int>& vec);

    int real_postorder_heights(Node* node, std::vector<int>& vec);

};

// Default constructor
// You do not need to change this
template <typename T>
BST<T>::BST()
{
}

// Destructor
// We implement this for you
template <typename T>
BST<T>::~BST()
{
    delete_subtree(root_);
}

// helper function for destructor
template <typename T>
void BST<T>::delete_subtree(Node* node)
{
    if(node==nullptr)
    {
        return;
    }
    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}

//*** For you to implement
template <typename T>
void BST<T>::insert(T k)
{
    // if its a null pointer return 

    // else make 2 ints -> left height and right height 
    // int left_height = node->left == null ? minus 1 : node's left height
    // int right_height = node->right == null ? minus 1 : node's right height
    // node-> height = std::max(left_height, right)height +1;
    // end w/ fix_height(node->parent)
    
    // You can mostly follow your solution from Week 9 lab here
    // Add functionality to set the parent pointer of the new node created
    // ++size_;
    // Also remember to correct the heights on the path from the newly
    // inserted node to the root.
    // fix_height(start_fix);
    // node will iterate down through the tree starting from the root
    Node* node = root_;
    // prev_node will hold node's parent
    Node* prev_node = node;
    bool went_right;

    if(node == nullptr)
    {
        root_ = new Node(k);
        ++size_;
        return;
    }

    while(node != nullptr)
    {
        prev_node = node;
        if(k < node->key)
        {
            node = node->left;
            went_right = false;
        }
        else if (k > node->key)
        {
            node = node->right;
            went_right = true;
        }
        // item already in set
        else
        {
            return;
        }
    }
    // new node is either left or right child of prev_node
    if(went_right)
    {
        prev_node->right= new Node(k, prev_node);
    }
    else
    {
        prev_node->left= new Node(k, prev_node);
    }
    ++size_;
    fix_height(root_);
    // print();
}

//*** For you to implement
template <typename T>
typename BST<T>::Node* BST<T>::successor(T k)
{
    // There are two cases here.  
    // If the node containing k has a right child, then 
    // the successor will be the minimum node in its right subtree
    // Otherwise, the successor will be the first node with a key 
    // bigger than k on the path from the node with key k to the root.
    // In other words, it is the node where we last took a left turn when 
    // searching for the key k.

    // dummy return value so compiler does not complain

    // We need to instantiate 2 pointers: A pointer for k's parent
    // and a pointer for k
    Node *original_parent_val = find(k)->parent;
    Node *my_val = find(k);

    // This case will only run if k's right child isn't null
    if(nullptr == my_val->right)
    {
        // This loop will run only if k's parent isn't null and k is a right child
        while(nullptr != original_parent_val && original_parent_val->right == my_val)
        {
            // This now allows us to assign k the value of its parent until the loop ends
            if(nullptr != my_val) my_val = original_parent_val;

            // This also allows us to assign k's parent the value of its parent until the loop
            // ends, allowing progress until the function is complete
            if(nullptr != original_parent_val) original_parent_val = original_parent_val->parent;
        }
        // The loop should complete the function and we can now return our value which
        // is our successor
        return original_parent_val;
    }

    // This alternative case will run if the above If() is incorrect and will assign 
    // the minimum of the right subtree to our second pointer and end the function
    else return my_val = min(my_val->right);
}

//*** For you to implement
template <typename T>
void BST<T>::delete_min()
{
    // if tree is empty just return.
    //Node* min_node = min();
    // Now update pointers to remove min_node from the tree

    //delete min_node;
    //--size_;
    //fix_height(start_fix);

    // We begin by instantiating a pointer child node by determining if our 
    // min node has a left child. Its value becomes its left child if it does,
    // with its value becoming its right child if it does not. BST's min node
    // is also saved under a new pointer
    Node *next_level = (min()->left) ? min()->left : min()->right;
    Node *my_val = min();

    // We have 3 cases:
    // -Root is assigned the value of null if the minimum BST value has no children, or otherwise its left child's value,
    //  or its right child's value respectively
    // -Child's parent->left is assigned null if it has no children and the minimum BST value is the 
    //  same as its parent->left value
    // -Every other case, which assigns the parent of the minimum BST value's parent to the minimum BST value. Min()'s 
    //  parent->left value is also assigned the minimum BST's left or right child's current value respectively
    if(root_ == min()) root_ = (min()->right == nullptr && min()->left == nullptr) ? nullptr : next_level;
    else if((min() == my_val->parent->left) && (my_val->right == nullptr && min()->left == nullptr)) my_val->parent->left = nullptr;
    else
    {
        next_level->parent = min()->parent; 
        min()->parent->left = next_level;
    }

    // The swap has been completed and we are now able to free memory by deleting my_val.
    // It is best to also fix heights for the BST
    delete my_val;
    fix_height(root_);
}

//*** For you to implement
template <typename T>
void BST<T>::erase(T k)
{
    // Step 1: locate node holding key k
    // simply return if k is not in tree
    // let node_to_remove be a pointer to the node to be removed

    // Step 2: find a node, replacement, to replace node_to_remove
    // We break this down into 3 cases
    // Case 1: node_to_remove has no right child 
    // Case 2: node_to_remove has no left child 
    // Case 3: node_to_remove has both children
    // in this case replacement is successor of node_to_remove
    // There is a further instance of Case 3 that needs special handling.
    // This is where replacement is the right child of node_to_remove.
   
    // Once pointers have been correctly adjusted then don't forget to:
    // delete node_to_remove;
    // --size_;
    // fix the heights from the bottom-most node affected by the changes
    //fix_height(start_fix);

    // Erase cannot function unless we have two pointers. We need to establish whether or 
    // not the right child is null and assign the left child to the first if it is. We assign 
    // the right child to our first pointer if it is not null. The other pointer is simply to
    // store k
    Node *next_level = (find(k)->right == nullptr) ? find(k)->left : find(k)->right;
    Node *erase_var = find(k);

    // We need to assign the k's parent->left to null if k's a leaf node and k is equal to its parent->left
    if((nullptr == find(k)->left && erase_var->right == nullptr) && (erase_var == erase_var->parent->left)) erase_var->parent->left= nullptr;

    // We also need to assign the k's parent->right to null if k's a leaf node and k is equal to its parent->right
    if((erase_var->right == nullptr && nullptr == erase_var->left) && (erase_var->parent->right == erase_var)) erase_var->parent->right= nullptr;

    // our main condition says that if k is a leaf node, we should establish a successor pointer and begin
    // reassigning
    if(((erase_var->right != nullptr)) && ((erase_var->left != nullptr)))
    {
        Node *successor_copy = successor(k);
        // Our successor's parent->right will be assigned its right child if our successor is equal to its right child
        if(successor(k) == erase_var->right) successor_copy->parent->right=successor(k)->right;
        
        // Our successor's parent->left will otherwise be assigned its right child
        else successor_copy->parent->left=successor(k)->right;
        
        // We can now assign our successor's value to our second pointer. We must do a deep copy and not a shallow copy
        erase_var->key=successor_copy->key;
        erase_var=successor_copy;
    }
    
    // We need to assign the parent->left the value of the child pointer we instantiated. This will only run if its not a root node and the parent->left is not equal to k.
    // Right has the exact same condition
    else if((erase_var->right != nullptr || erase_var->left != nullptr) && (erase_var!=root_) && (erase_var->parent->left == erase_var)) erase_var->parent->left=next_level;
    else if((erase_var->right != nullptr || erase_var->left != nullptr) && (erase_var!=root_) && erase_var->parent->right == erase_var) erase_var->parent->right = next_level;
    
    // The child pointer's parent may be reassigned to the second pointer's parent if left or right child is null
    else if(erase_var->right != nullptr || erase_var->left != nullptr) next_level->parent=erase_var->parent;
    
    // We should either assign root to the child pointer we previously instantiated or keep it as it is. This however,
    // will only happen if root_ is not null and size of BST is not empty. We should also fix the height
    fix_height(root_);
    if(nullptr != root_&& size_!=0) root_= (root_ == erase_var) ? next_level : root_;

    // We can now free memory by deleting and adjust the size
    delete erase_var;
    size_--;
}

//*** For you to implement
template <typename T>
void BST<T>::rotate_right(Node* node)
{
    // Assumptions: node is not nullptr and must have a left child

    // Node* move_up_node = node->left;  
    
    // There are 3 pairs (parent and child) of pointers to change
    // 1) node's parent becomes move_up node's parent
    // 2) move_up_node's right child becomes node's left child
    // 3) move_up node becomes node's parent


    // Correct height of ancestors of node 
    // fix_height(node);
    
    // Root case: Ensures that root can be set to node left before any logic begins 
    // in the event that the node's parent is null
    if(nullptr == node->parent) root_ = node->left;

    // Initialises base pointer to the node's left since we're rotating right. The node's 
    // left val has been saved and can now become the node's right pointer to begin rotating
    Node *my_value = node->left;
    node->left = my_value->right;

    // Two cases required for function: node's parent->right to become base pointer if
    // the parameter is equal to the node's parent->right, also applying to the left side,
    // being that the node's parent->left to become base pointer if the parameter's
    // equal to the node's parent->left
    if((root_!= my_value) && node == node->parent->right) node->parent->right = my_value;
    else if ((root_!= my_value) && node == node->parent->left) node->parent->left = my_value;
    
    // updated base val's parent now needs to be assigned the parameter's parent. The 
    // updated base val's right child also needs to become the parameter
    my_value->parent = node->parent;
    my_value->right = node;

    // The rotation is completed by fixing the heights and assigning the updated
    // base value to the parent of the parameter
    fix_height(root_);
    node->parent = my_value;
}

// The rest of the functions bellow are already implemented

// returns a pointer to the minimum node
template <typename T>
typename BST<T>::Node* BST<T>::min()
{
    if(root_ == nullptr)
    {
        return root_;
    }
    else
    {
        return min(root_);
    }
}

// returns pointer to minimum node in the subtree rooted by node
// Assumes node is not nullptr
template <typename T>
typename BST<T>::Node* BST<T>::min(Node* node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    } 
    return node;
}

// returns a pointer to node with key k
template <typename T>
typename BST<T>::Node* BST<T>::find(T k)
{
    Node* node = root_;  
    while(node != nullptr && node->key != k)
    {
        node = k < node->key ?  node->left : node->right;
    }
    return node;  
}

template <typename T>
unsigned BST<T>::size()
{
    return size_;
}

// prints out the keys in the tree using in-order traversal
template <typename T>
void BST<T>::print()
{
    print(root_);
}

// you can modify what is printed out to suit your needs
template <typename T>
void BST<T>::print(Node* node)
{
    if(node == nullptr)
    {
        return;
    }
    print(node->left);
    std::cout << node->key << " height " << node->height << '\n';
    print(node->right);
}

// This is used in our testing, please do not modify
template <typename T>
typename std::vector<T> BST<T>::make_vec()
{
    std::vector<T> vec;
    vec.reserve(size_);
    make_vec(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::make_vec(Node* node, std::vector<T>& vec)
{
    if(node == nullptr)
    {
        return;
    }
    make_vec(node->left, vec);
    vec.push_back(node->key);
    make_vec(node->right, vec);
    
}

// This is used for our testing, please do not modify
template <typename T>
void BST<T>::your_postorder_heights(Node* node, std::vector<int>& vec)
{
    if(node == nullptr)
    {
        return;
    }
    your_postorder_heights(node->left, vec);
    your_postorder_heights(node->right, vec);
    vec.push_back(node->height);
}

// This is used for our testing, please do not modify
template <typename T>
int BST<T>::real_postorder_heights(Node* node, std::vector<int>& vec)
{
    if(node == nullptr)
    {
        return -1;
    }
    int left_height = real_postorder_heights(node->left, vec);
    int right_height = real_postorder_heights(node->right, vec);
    int node_height = 1 + std::max(left_height, right_height);
    vec.push_back(node_height);
    return node_height;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::your_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    your_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
typename std::vector<int> BST<T>::real_postorder_heights()
{
    std::vector<int> vec;
    vec.reserve(size_);
    real_postorder_heights(root_, vec);
    return vec;
}

// This is used for our testing, please do not modify
template <typename T>
T BST<T>::get_root_value()
{
    if(root_ == nullptr)
    {
        //std::cout << "Calling get_root_value on empty tree\n";
        T dummy {};
        return dummy;
    }
    else
    {
        return root_->key;
    }
}

template <typename T>
void BST<T>::pretty_print(const std::string &prefix, const Node *node, bool is_left, bool has_left_sibling)
{
    if (node != nullptr)
    {
        if (node != root_)
        {
            std::cout << prefix;

            if (is_left)
            {
                std::cout << "L└──";
            }
            else
            {
                std::cout << (has_left_sibling ? "R├──" : "R└──");
            }         
        }
        else
        {
            std::cout << "  ";
        }

        std::cout << node->key << std::endl;

        pretty_print(prefix + (is_left ? "   " : " |  "), node->right, false, node->left != nullptr);
        pretty_print(prefix + (is_left ? "   " : " |  "), node->left, true, false);
    }
}

template <typename T>
void BST<T>::pretty_print()
{
    pretty_print("", root_, true, false);
}


#endif

