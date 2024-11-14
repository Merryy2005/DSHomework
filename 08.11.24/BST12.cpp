#include <iostream>
#include <algorithm>
#include <queue>

struct Element
{
    int val;
    bool isPresent;
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
        void levelOrderInsert(const Element* arr , int size);
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

void BST::levelOrderInsert(const Element* arr , int size) 
{
    std::queue<Node*> q;
    Node* currentNode = nullptr;
    for (int i = 0 ; i < size ; i++) 
    {
        if (arr[i].isPresent) 
        { 
            Node* newNode = new Node(arr[i].val);
            if (root == nullptr) 
            {
                root = newNode; 
            } 
            else 
            {
                q.push(root); 
                while (!q.empty())
                {
                    currentNode = q.front();
                    q.pop();
                    if (currentNode->left == nullptr && newNode->val < currentNode->val) 
                    {
                        currentNode->left = newNode;
                        break;
                    } 
                    else if (currentNode->right == nullptr && newNode->val >= currentNode->val) 
                    {
                        currentNode->right = newNode;
                        break;
                    } 
                    else 
                    {
                        if (currentNode->left != nullptr) q.push(currentNode->left);
                        if (currentNode->right != nullptr) q.push(currentNode->right);
                    }
                }
            }
        }
    }
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
    Element* arr = new Element[7]{
        {1, true},  
        {0, true},  
        {4, false}, 
        {3, true},  
        {0, true},  
        {6, false}, 
        {5, true}   
    };
    tree.levelOrderInsert(arr , 7);
    tree.layerByLayer();
}