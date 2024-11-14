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
        int numberOfNodes(Node*) const;
        int numberOfLeaves(Node*)const;
        int height(Node*) const;
        int occurences(Node* , int) const;
        Node* findMin(Node*) const; 
    public:
        BST();
        void insert(int);
        void remove(int);
        void print() const;
        void inorder(Node*) const;
        int numberOfNodes() const;
        int numberOfLeaves() const;
        int height() const;
        int occurences(int) const;
        int numberOfNodes(int) const;
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

BST::Node* BST::findMin(Node* node) const 
{
    while (node && node->left != nullptr) 
    {
        node = node->left;
    }
    return node;
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

BST::~BST()
{
    while(root)
    {
        removeNode(root);
    }
}

int BST::numberOfNodes(Node* root) const
{
    if(root == nullptr)
    {
        return 0;
    }
    return 1 + numberOfNodes(root->left) + numberOfNodes(root->right);
}

int BST::numberOfNodes() const
{
    return numberOfNodes(root);
}

int BST::numberOfLeaves(Node* root) const
{
    if(root == nullptr)
    {
        return 0;
    }
    if(root-> left ==nullptr && root->right == nullptr)
    {
        return 1;
    }
    return numberOfLeaves(root->left) + numberOfLeaves(root->right);
}

int BST::numberOfLeaves() const
{
    return numberOfLeaves(root);
}

int BST::height(Node* root) const
{
    if(root == nullptr)
    {
        return -1;
    }
    return 1 + std::max(height(root->left),height(root->right));
}

int BST::height() const
{
    return height(root);
}

int BST::occurences(Node* root , int x) const
{
    if(root == nullptr)
    {
        return 0;
    }
    return (root->val == x) + occurences(root->left , x) + occurences(root->right , x);
}

int BST::occurences(int x) const
{
    return occurences(root,x);
}

int BST::numberOfNodes(int layer) const
{
    int cur = -1;
    int curnum = 0;
    std::queue<Node*> q;
    q.push(root);
    cur = 0;
    curnum = 1;
    while(!q.empty())
    {
        if(cur == layer) return curnum;
        for(int i = 0 ; i < curnum ; i++)
        {
            Node* tmp = q.front();
            q.pop();
            if(tmp->left)q.push(tmp->left);
            if(tmp->right)q.push(tmp->right);
        }
        cur++;
        curnum = q.size();
    }
    return -1;
}

int main()
{
    BST tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(4);
    tree.insert(3);
    tree.insert(0);
    tree.insert(6);
    tree.insert(5);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(-2);
    tree.print();
    std::cout << std::endl;
    std::cout << "Number of Nodes : " << tree.numberOfNodes() << std::endl;
    std::cout << "Number of Leaves : " << tree.numberOfLeaves() << std::endl;
    std::cout << "Height of tree : " << tree.height() << std::endl;
    std::cout << "Occurence of 3 : " << tree.occurences(3) << std::endl;
    std::cout << "Occurence of 0 : " << tree.occurences(0) << std::endl;
    std::cout << "Occurence of 10 : " << tree.occurences(10) << std::endl;
    std::cout << "Number of Nodes on layer 0 : " << tree.numberOfNodes(0) << std::endl;
    std::cout << "Number of Nodes on layer 1 : " << tree.numberOfNodes(1) << std::endl;
    std::cout << "Number of Nodes on layer 2 : " << tree.numberOfNodes(2) << std::endl;
    std::cout << "Number of Nodes on layer 3 : " << tree.numberOfNodes(3) << std::endl;
    std::cout << "Number of Nodes on layer 4 : " << tree.numberOfNodes(4) << std::endl;
    std::cout << "Number of Nodes on layer 5 : " << tree.numberOfNodes(5) << std::endl;
}