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
        Node* findNode(Node*, int) const;
        Node* findMin(Node*) const; 
        Node* makeFull(Node*);
        void dfs(Node* , std::vector<int>&) const;
    public:
        BST();
        void insert(int);
        void remove(int);
        void print() const;
        void inorder(Node*) const;
        void removeSubTree(Node*);
        void removeSubTree(int);
        void removeLeaves();
        void makeFull();
        void clear();
        void printPaths() const;
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

BST::Node* BST::findNode(Node* node, int value) const
{
    if (node == nullptr || node->val == value)
    {
        return node;
    }
    if (value < node->val)
    {
        return findNode(node->left, value);
    }
    return findNode(node->right, value);
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

void BST::removeSubTree(Node* node)
{
    if (node == nullptr) return;
    removeSubTree(node->left);
    removeSubTree(node->right);
    delete node;
}

void BST::removeSubTree(int value)
{
    if (root == nullptr) return;
    if (root->val == value) 
    {
        removeSubTree(root);
        root = nullptr; 
        return;
    }
    Node* parent = nullptr;
    Node* current = root;
    while (current && current->val != value) 
    {
        parent = current;
        current = (value < current->val) ? current->left : current->right;
    }
    if (!current) return;
    removeSubTree(current);
    if (parent->left == current) 
        parent->left = nullptr;
    else 
        parent->right = nullptr;
}

void BST::removeLeaves()
{
    if (!root) return;

    std::queue<std::pair<Node*, Node*>> q;
    q.push({root, nullptr});

    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        if (!p.first->left && !p.first->right)
        {
            if (!p.second) 
            {
                delete p.first;
                root = nullptr;
            }
            else if (p.second->left == p.first)
            {
                delete p.first;
                p.second->left = nullptr;
            }
            else if (p.second->right == p.first)
            {
                delete p.first;
                p.second->right = nullptr;
            }
        }
        else
        {
            if (p.first->left) q.push({p.first->left, p.first});
            if (p.first->right) q.push({p.first->right, p.first});
        }
    }
}

void BST::makeFull()
{
    root = makeFull(root);
}

BST::Node* BST::makeFull(Node* node)
{
    if (!node) return nullptr;
    node->left = makeFull(node->left);
    node->right = makeFull(node->right);
    if (!node->left && node->right)
    {
        Node* toKeep = node->right;
        delete node;
        return toKeep;
    }
    if (node->left && !node->right)
    {
        Node* toKeep = node->left;
        delete node;
        return toKeep;
    }
    return node;
}

void BST::clear()
{
    while(root)
    {
        removeNode(root);
    }
}

void BST::printPaths() const
{
    std::vector<int> path;
    dfs(root, path);
}

void BST::dfs(Node* node, std::vector<int>& path) const
{
    if (!node) return;
    path.push_back(node->val);
    if (!node->left && !node->right)
    {
        for (int val : path)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
    dfs(node->left, path);
    dfs(node->right, path);
    path.pop_back();
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
    // tree.removeSubTree(-1);
    // tree.print();
    // std::cout << std::endl;
    // tree.removeLeaves();
    // tree.print();
    // std::cout << std::endl;
    // tree.makeFull();
    // tree.print();
    // std::cout << std::endl;
    // tree.clear();
    // tree.print();
    // std::cout << std::endl;
    tree.printPaths();
    return 0;
}