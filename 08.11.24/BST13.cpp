#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct Element
{
    int val;
    int left;
    int right;
};

class BST
{
    public:
        class Node
        {
            Node* left;
            Node* right;
            int val;
            Node(int v):left(nullptr) , right(nullptr) , val(v){} 
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
        void buildTree(Element* , int);
        void layerByLayer() const;
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

void BST::buildTree(Element* arr , int size)
{
    std::vector<Node*> v;
    for(int i = 0 ; i < size ; i++)
    {
        v.push_back(new Node(arr[i].val));
    }
    for(int i = 0 ; i < size ; i++)
    {
        if(arr[i].left != -1)v[i]->left = v[arr[i].left];
        if(arr[i].right != -1)v[i]->right = v[arr[i].right];
    }
    root = v[0];
}

void BST::layerByLayer() const
{
    if(root == nullptr)
    {
        return;
    }
    std::queue<Node*> q;
    q.push(root);
    while(!q.empty())
    {
        Node* tmp = q.front();
        std::cout << tmp -> val << " ";
        q.pop();
        if(tmp->left)q.push(tmp->left);
        if(tmp->right)q.push(tmp->right);
    }
}

int main()
{
    BST tree;
    Element* arr = new Element[5]{
        {1, 4, 2},
        {0, -1, -1},
        {3, -1, 3},
        {4, -1, -1},
        {-1, -1, 1}
    };
    tree.buildTree(arr , 5);
    tree.print();
}