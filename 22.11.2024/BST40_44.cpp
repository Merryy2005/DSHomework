#include <iostream>
#include <algorithm>
#include <queue>

class BST
{
    public:
        class Node
        {
            Node* left;
            Node* right;
            int val;
            Node(int v) : left(nullptr) , right(nullptr) , val(v){} 
            ~Node()
            {
                left = nullptr;
                right = nullptr;
            }
            friend class BST;
        };
    private:
        Node* root;
        void insert(Node*& , int);
        void remove(Node*& , int);
        void removeNode(Node*&);
        Node* findMin(Node*) const; 
        int subtreeSize(Node*) const;
        int numberOfLeaves(Node*) const;
    public:
        BST();
        void insert(int);
        void remove(int);
        void print() const;
        void inorder(Node*) const;
        void findFullLevels() const; 
        void findFNonDecreasingLevels() const;
        void initlizeWithSubtreeNodes();
        void initlizeWithNumberOfLeaves();
        void initlizeWithNumberOfNonLeaves();
        ~BST();
};

BST::BST() : root(nullptr)
{

}

void BST::insert(int x)
{
    insert(root , x);
}

void BST::insert(Node*& root , int x)
{
    if(root == nullptr)
    {
        root = new Node(x);
        return;
    }
    if(x <= root->val)
    {
        insert(root->left , x);
    }
    else
    {
        insert(root->right , x);
    }
    return;
}

void BST::remove(int x) 
{
    remove(root, x);
}

void BST::remove(Node*& ptr, int x) 
{
    if (ptr == nullptr) 
    {
        return; 
    }
    if (x < ptr->val) 
    {
        remove(ptr->left, x);  
    } 
    else if (x > ptr->val) 
    {
        remove(ptr->right, x); 
    } 
    else 
    {
        removeNode(ptr);
    }
}

void BST::removeNode(Node*& ptr) 
{
    if (ptr == nullptr) 
    {
        return;
    }
    if (ptr->left == nullptr && ptr->right == nullptr)
    {
        delete ptr;
        ptr = nullptr;
    } 
    else if (ptr->left == nullptr) 
    {
        Node* temp = ptr;
        ptr = ptr->right;
        delete temp;
    } 
    else if (ptr->right == nullptr) 
    {
        Node* temp = ptr;
        ptr = ptr->left;
        delete temp;
    } 
    else 
    {
        Node* successor = findMin(ptr->right);
        ptr->val = successor->val;          
        remove(ptr->right, successor->val); 
    }
}

void BST::print() const
{
    inorder(root);
}

void BST::inorder(Node* p) const
{
    if(!p)
    {
        return;
    }
    inorder(p->left);
    std::cout << p->val << " ";
    inorder(p->right);
    return;
} 

BST::Node* BST::findMin(Node* node) const 
{
    while (node && node->left != nullptr) 
    {
        node = node->left;
    }
    return node;
}

BST::~BST()
{
    while(root)
    {
        removeNode(root);
    }
}

void BST::findFullLevels() const
{
    if (!root) 
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    int level = 0;
    while (!q.empty()) 
    {
        int cur = q.size();
        bool p = true;
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            if(!current -> left || !current -> right) p = false;
            q.pop();
            if (current->left) 
            {
                q.push(current->left);
            }
            if (current->right) 
            {
                q.push(current->right);
            }
        }
        if(p) std::cout << level << " ";
        level++;
    }
    std::cout << std::endl;
    return;
}

void BST::findFNonDecreasingLevels() const
{
    if (!root) 
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    int level = 0;
    while (!q.empty()) 
    {
        int cur = q.size();
        bool p = true;
        Node* prev;
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            if(i != 0 && current -> val < prev -> val) p = false;
            q.pop();
            if (current->left) 
            {
                q.push(current->left);
            }
            if (current->right) 
            {
                q.push(current->right);
            }
            prev = current;
        }
        if(p) std::cout << level << " ";
        level++;
    }
    std::cout << std::endl;
    return;
}

int BST::subtreeSize(Node* root) const
{
    if(root == nullptr) return 0;
    return 1 + subtreeSize(root->left) + subtreeSize(root->right);
}

void BST::initlizeWithSubtreeNodes()
{
    if (!root) 
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    root->val = subtreeSize(root);
    while (!q.empty()) 
    {
        int cur = q.size();
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            current->val = subtreeSize(current);
            q.pop();
            if (current->left) 
            {
                q.push(current->left);
            }
            if (current->right) 
            {
                q.push(current->right);
            }
        }
    }
    return;
}

int BST::numberOfLeaves(Node* root) const
{
    if(!root) return 0;
    if(!root->left && !root->right) return 1;
    return numberOfLeaves(root->left) + numberOfLeaves(root->right);
}

void BST::initlizeWithNumberOfLeaves()
{
    if (!root) 
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    root->val = numberOfLeaves(root);
    while (!q.empty()) 
    {
        int cur = q.size();
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            current->val = numberOfLeaves(current);
            q.pop();
            if (current->left) 
            {
                q.push(current->left);
            }
            if (current->right) 
            {
                q.push(current->right);
            }
        }
    }
    return;
}

void BST::initlizeWithNumberOfNonLeaves()
{
    if (!root) 
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    root->val = subtreeSize(root) - numberOfLeaves(root);
    while (!q.empty()) 
    {
        int cur = q.size();
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            current->val = subtreeSize(current) - numberOfLeaves(current);
            q.pop();
            if (current->left) 
            {
                q.push(current->left);
            }
            if (current->right) 
            {
                q.push(current->right);
            }
        }
    }
    return;
}

int main()
{
    BST tree;
    tree.insert(1);
    tree.insert(-1);
    tree.insert(2);
    tree.insert(-3);
    tree.insert(-3);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);
    tree.insert(3);
    tree.insert(5);
    tree.insert(-2);
    tree.print();
    std::cout << std::endl;
    std::cout << "Full levels: ";
    tree.findFullLevels();
    std::cout << "Non-Decreasing levels: ";
    tree.findFNonDecreasingLevels();
    std::cout << "Initilized with subtree nodes: ";
    tree.initlizeWithSubtreeNodes();
    tree.print();
    std::cout << std::endl;
    std::cout << "Initilized with number of leaves: ";
    tree.initlizeWithNumberOfLeaves();
    tree.print();
    std::cout << std::endl;
    std::cout << "Initilized with number of non-leaves: ";
    tree.initlizeWithNumberOfNonLeaves();
    tree.print();
    std::cout << std::endl;
    return 0;
}