#include <iostream>
#include <fstream>

struct Elem
{
    int data;          
    Elem* left;
    Elem* right;
    Elem* parent;
};


Elem* MAKE(int data, Elem* p)
{
    Elem* q = new Elem;        
    q->data = data;
    q->left = nullptr;
    q->right = nullptr;
    q->parent = p;
    return q;
}


void ADD(int data, Elem*& root)
{
    if (root == nullptr) {
        root = MAKE(data, nullptr);
        return;
    }
    Elem* v = root;
    while ((data < v->data && v->left != nullptr) || (data > v->data && v->right != nullptr))
        if (data < v->data)
            v = v->left;
        else
            v = v->right;
    if (data == v->data)
        return;
    Elem* u = MAKE(data, v);
    if (data < v->data)
        v->left = u;
    else
        v->right = u;
}


Elem* SEARCH(int data, Elem* v)    
{
    if (v == nullptr)
        return v;
    if (v->data == data)
        return v;
    if (data < v->data)
        return SEARCH(data, v->left);
    else
        return SEARCH(data, v->right);
}


void DELETE(int data, Elem*& root)
{
   
    Elem* u = SEARCH(data, root);
    if (u == nullptr)
        return;

    if (u->left == nullptr && u->right == nullptr && u == root)
    {
        delete root;
        root = nullptr;
        return;
    }  

    if (u->left == nullptr && u->right != nullptr && u == root)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }
  
    if (u->left != nullptr && u->right == nullptr && u == root)
    {
        Elem* t = u->left;
        while (t->right != nullptr)
            t = t->right;
        u->data = t->data;
        u = t;
    }   

    if (u->left != nullptr && u->right != nullptr)
    {
        Elem* t = u->right;
        while (t->left != nullptr)
            t = t->left;
        u->data = t->data;
        u = t;
    }

    Elem* t;
    if (u->left == nullptr)
        t = u->right;
    else
        t = u->left;

    if (u->parent->left == u)
        u->parent->left = t;
    else
        u->parent->right = t;

    if (t != nullptr)
        t->parent = u->parent;
    delete u;
}
 

void SEARCH2(int data, Elem* v, int c, int a) 
{
    if (v == nullptr)
    {
        std::cout << a << " not founded ";
        return;
    }
    else 
    if (v->data == data)
    {
        std::cout <<a <<" founded " << c;
        return;
    }
    else
        if (data < v->data)
        SEARCH2(data, v->left, c + 1, a);
    else
        SEARCH2(data, v->right, c + 1, a);
}


void DEEP(int data, Elem* v, int c, char znak, int a)
{
    if (v == nullptr)
        return;
    else 
    if (v->data == data)
    {
        if (znak == '+')
        std::cout << a << " added " << c;
        else
        std::cout << a << " deleted " << c;

        return;
    }
    else
        if (data < v->data)
        DEEP(data, v->left, c+1, znak, a);
        else
        DEEP(data, v->right, c+1,znak, a);
}


void CLEAR(Elem*& v)
{
    if (v == nullptr)
        return;
  
    CLEAR(v->left);
    
    CLEAR(v->right);

    delete v;
    v = nullptr;
}


int main()
{
    Elem* root = nullptr;
    std::ifstream in("input.txt");
    
    char znak;
    int a;
    while (!in.eof())
    {
        in >> znak;
        in >> a;
        if (znak == '+')
        {
            ADD(a, root);
            DEEP(a, root, 0, znak, a);
            std::cout << '\n';
        }
        else
        if (znak == '?')
        {
            SEARCH2(a, root, 0, a);
            std::cout << '\n';
        }
        else
        if (znak == '-')
        {
            DEEP(a, root, 0, znak, a);
            DELETE(a, root);
            std::cout << '\n';
        }
        else
        if (znak == 'E')
        {
            std::cout << "end";
            break;
        }
    }
    CLEAR(root);
    return 0;
}
