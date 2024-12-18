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
        void findLongestPath(Node*, std::vector<int>& , std::vector<int>&) const;
        void findAllLongestPaths(Node*, std::vector<int>&, std::vector<std::vector<int>>&) const;
        void printSmallerThan(Node* node, int value) const;
    public:
        BST();
        BST(const std::vector<int>&);
        void insert(int);
        void remove(int);
        void print() const;
        void inorder(Node*) const;
        void clear();
        void printRightmostPath() const;
        void printLongestPath() const;
        void printAllLongestPaths() const;
        void printSmallestPath() const;
        void printSmallerThan(int) const;
        ~BST();
};

BST::BST() : root(nullptr)
{

}

BST::BST(const std::vector<int>& arr) : root(nullptr)
{
    for (int val : arr)
    {
        insert(val);
    }
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

void BST::clear()
{
    while(root)
    {
        removeNode(root);
    }
}

void BST::printRightmostPath() const
{
    Node* current = root;
    std::cout << "Rightmost Path: ";
    while (current)
    {
        std::cout << current->val << " ";
        if (current->right)
            current = current->right;
        else
            current = current->left;
    }
    std::cout << std::endl;
}

void BST::printLongestPath() const
{
    std::vector<int> longestPath;
    std::vector<int> currentPath;
    findLongestPath(root, currentPath, longestPath);
    std::cout << "Longest Path: ";
    for (int val : longestPath)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void BST::findLongestPath(Node* node, std::vector<int>& currentPath, std::vector<int>& longestPath) const
{
    if (!node) return;
    currentPath.push_back(node->val);
    if (!node->left && !node->right)
    {
        if (currentPath.size() > longestPath.size())
        {
            longestPath = currentPath;
        }
    }
    findLongestPath(node->left, currentPath, longestPath);
    findLongestPath(node->right, currentPath, longestPath);
    currentPath.pop_back();
}

void BST::printAllLongestPaths() const
{
    std::vector<std::vector<int>> allLongestPaths;
    std::vector<int> currentPath;
    findAllLongestPaths(root, currentPath, allLongestPaths);
    std::cout << "All Longest Paths:" << std::endl;
    for (const auto& path : allLongestPaths)
    {
        for (int val : path)
        {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void BST::findAllLongestPaths(Node* node, std::vector<int>& currentPath, std::vector<std::vector<int>>& allLongestPaths) const
{
    if (!node) return;
    currentPath.push_back(node->val);
    if (!node->left && !node->right)
    {
        if (allLongestPaths.empty() || currentPath.size() > allLongestPaths[0].size())
        {
            allLongestPaths.clear();
            allLongestPaths.push_back(currentPath);
        }
        else if (currentPath.size() == allLongestPaths[0].size())
        {
            allLongestPaths.push_back(currentPath);
        }
    }
    findAllLongestPaths(node->left, currentPath, allLongestPaths);
    findAllLongestPaths(node->right, currentPath, allLongestPaths);
    currentPath.pop_back();
}

void BST::printSmallestPath() const
{
    if (!root) return;
    std::queue<std::pair<Node*, std::vector<int>>> q;
    q.push({root, {root->val}});
    while (!q.empty())
    {
        auto p = q.front();
        Node* current = p.first;
        std::vector<int> path = p.second;
        q.pop();
        if (!current->left && !current->right)
        {
            std::cout << "Smallest Path: ";
            for (int val : path)
            {
                std::cout << val << " ";
            }
            std::cout << std::endl;
            return;
        }
        if (current->left)
        {
            std::vector<int> leftPath = path;
            leftPath.push_back(current->left->val);
            q.push({current->left, leftPath});
        }
        if (current->right)
        {
            std::vector<int> rightPath = path;
            rightPath.push_back(current->right->val);
            q.push({current->right, rightPath});
        }
    }
}

void BST::printSmallerThan(int value) const
{
    printSmallerThan(root, value);
}

void BST::printSmallerThan(Node* node, int value) const
{
    if (!node) return;
    printSmallerThan(node->left, value);
    if (node->val < value)
    {
        std::cout << node->val << " ";
    }
    if (node->val < value)
    {
        printSmallerThan(node->right, value);
    }
}

int main()
{
    BST tree({1,-1,2,-3,-3,5,3,6,3,5,-2});
    tree.print();
    std::cout << std::endl;
    tree.printRightmostPath();
    tree.printLongestPath();
    tree.printAllLongestPaths();
    tree.printSmallestPath();
    tree.printSmallerThan(3);
    return 0;
}