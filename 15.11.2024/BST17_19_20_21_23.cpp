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
    public:
        BST();
        void insert(int);
        void remove(int);
        void print() const;
        void inorder(Node*) const;
        int getWidth() const;
        int oneChildNodes() const; 
        int twoChildNodes() const; 
        int getMin() const;
        int numberOfZeros() const;
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
    if(x < root->val)
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

int BST::getWidth() const 
{
    if (!root) 
    {
        return 0;
    }
    std::queue<Node*> q;
    q.push(root);
    int mx = 0;
    while (!q.empty()) 
    {
        int cur = q.size();
        mx = std::max(mx, cur);
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
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
    return mx;
}

int BST::oneChildNodes() const 
{
    if (!root) 
    {
        return 0;
    }
    std::queue<Node*> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty()) 
    {
        int cur = q.size();
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            if((current -> left && !(current -> right)) || (current -> right && !(current -> left))) ++cnt;
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
    return cnt;
}

int BST::twoChildNodes() const 
{
    if (!root) 
    {
        return 0;
    }
    std::queue<Node*> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty()) 
    {
        int cur = q.size();
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            if(current -> left && current -> right) ++cnt;
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
    return cnt;
}

int BST::getMin() const 
{
    if(!root) return 0;
    Node* node = root;
    while (node && node->left != nullptr) 
    {
        node = node->left;
    }
    return node->val;
}

int BST::numberOfZeros() const
{
    if (!root) 
    {
        return 0;
    }
    std::queue<Node*> q;
    q.push(root);
    int cnt = 0;
    while (!q.empty()) 
    {
        int cur = q.size();
        for (int i = 0; i < cur; i++) 
        {
            Node* current = q.front();
            if(current-> val == 0) ++cnt;
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
    return cnt;
}

int main()
{
    BST tree;
    tree.insert(1);
    tree.insert(0);
    tree.insert(2);
    tree.insert(-1);
    tree.insert(-2);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);
    tree.insert(3);
    tree.insert(5);
    std::cout << tree.getWidth() << std::endl;
    std::cout << tree.oneChildNodes() << std::endl;
    std::cout << tree.twoChildNodes() << std::endl;
    std::cout << tree.getMin() << std::endl;
    std::cout << tree.numberOfZeros() << std::endl;
    return 0;
}