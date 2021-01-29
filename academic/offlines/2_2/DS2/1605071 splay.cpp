#include<iostream>
using namespace std;
#include<bits/stdc++.h>

struct node
{
    int key;
    node *left, *right, *parent;

    node(int key)
    {
        this->key = key;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    }
};

class splay_tree
{
    node * root, *SL, *SR;
public:
    splay_tree()
    {
        root = NULL;
        SL = NULL;
        SR = NULL;
    }


    void left_rot(node *x)
    {
        node * y;
        y = x->right;
        x->right = y->left;

        if(y->left != NULL)
            y->left->parent = x;
        y->parent = x->parent;

        if(x->parent == NULL)
            root = y;
        else if(x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    void right_rot(node *x)
    {
        node * y;
        y = x->left;
        x->left = y->right;

        if(y->right != NULL)
            y->right->parent = x;
        y->parent = x->parent;

        if(x->parent == NULL)
            root = y;
        else if(x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }

    void splay(node * x)
    {
        if(x == NULL)
            return;

        node *p, *g;
        p =  NULL;
        g =  NULL;

        while(x->parent != NULL)
        {
            p = x->parent;
            g = p->parent;

            if(g == NULL)
            {
                if(p->left == x)
                    right_rot(p);
                else
                    left_rot(p);
            }
            else if(p->left == x && g->left == p)
            {
                right_rot(g);
                right_rot(p);
            }
            else if(p->right == x && g->right == p)
            {
                left_rot(g);
                left_rot(p);
            }
            else if(p->right == x && g->left == p)
            {
                left_rot(p);
                right_rot(g);
            }
            else
            {
                right_rot(p);
                left_rot(g);
            }
        }
    }

    node * mj(int key)//given key tree te thkle key return kore, nahole, given keyr parent return kore
    {
        node * current, * prev;

        current = root;
        prev = NULL;

        while(current != NULL)
        {
            prev = current;
            if(current->key == key)
                return current;
            else if(current->key < key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return prev;
    }

    node * find_parent(int key)
    {
        node * current, * prev;

        current = root;
        prev = NULL;

        while(current != NULL)
        {
            prev = current;
            if(current->key <= key)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
        return prev;
    }

    bool search(int x)
    {
        if(root == NULL)
            return false;

        node * temp = mj(x);
        splay(temp);

        if(root->key == x)
            return true;
        else
            return false;
    }

//    void split(node * x)
//    {
//        if(root == NULL)
//        {
//            return;
//        }
//        if(x == NULL)
//        {
//            SL = NULL;
//            SR = root;
//            return;
//        }
//        splay(x);
//
//        SL = root;
//        SR = root->right;
//
//        if(SL)
//            SL->right = NULL;
//        if(SR)
//            SR->parent = NULL;
//
//        root = NULL;
//    }
//
//    void insert(int x)
//    {
//        node * temp;
//        temp = vln(x);
//
//        if(temp && temp->key == x)
//        {
//            splay(temp);
//            return;
//        }
//
//        split(temp);
//
//        root = new node(x);
//        root->left = SL;
//        root->right = SR;
//        root->parent = NULL;
//
//        if(SL)
//            SL->parent = root;
//        if(SR)
//            SR->parent = root;
//    }


    void insert(int key)
    {
//        node * newnode = NULL;
//
//        if(!newnode)
//            newnode = new node(key);
//        else
//            newnode->key = key;
        node * newnode = new node(key);

        if(!root)
        {
            root = newnode;
            newnode = NULL;
            return;
        }
        node * temp = find_parent(key);//mj given key tree te thkle key return kore, nahole, given keyr parent return kore

//        if(temp->key == key)//agei jodi given key tree te exist kore tahole r notun kore insert korbe na, agertakei roote nie ashbe
//        {
//            splay(temp);
//            delete newnode;
//            return;
//        }
        if(key < temp->key)
        {
            temp->left = newnode;
        }
        else
        {
            temp->right = newnode;
        }
        newnode->parent = temp;

        splay(newnode);
        //root = newnode;
    }

    node * maximum(node *x)
    {
        while(x!= NULL && x->right != NULL)
        {
            x = x->right;
        }
        return x;
    }

    void join()
    {
        if(SL == NULL)
            root = SR;
        else
        {
            //node * x = vln(INFINITY);
            node * x = maximum(SL);
            splay(x);
            root = x;
            x->right = SR;
            if(SR != NULL)
                SR->parent = x;
        }
    }

    void del(int x)
    {
        if(root == NULL)
            return;
        node * temp = mj(x);
        splay(temp);

        if(root->key == x)
        {
            SL = root->left;
            if(SL != NULL)
                SL->parent = NULL;

            SR = root->right;
            if(SR != NULL)
                SR->parent = NULL;

            delete root;
            root = NULL;

            if(SL == NULL)
            {
                root = SR;
                return;
            }
            if(SR == NULL)
            {
                root = SL;
                return;
            }
            join();
        }
    }

//    void InOrder(node * current)
//    {
//        if (current)
//        {
//            InOrder(current->left);
//            cout<< "key: " <<current->key;
//            if(current->left)
//                cout<< " | left child: "<< current->left->key;
//            if(current->right)
//                cout << " | right child: " << current->right->key;
//            cout<< "\n";
//            InOrder(current->right);
//        }
//    }
//
//    void print()
//    {
//        InOrder(root);
//    }

//    void preOrder(node *current)
//    {
//        if (current != NULL)
//        {
//            printf("%d ", current->key);
//            if(current->left)
//                cout << " | left child: " << current->left->key;
//            if(current->right)
//                cout << " | right child: " << current->right->key;
//            cout << endl;
//            preOrder(current->left);
//            preOrder(current->right);
//        }
//    }
//
//    void print()
//    {
//        preOrder(root);
//    }


    void printWhitespaces(int count)
    {
        for (int i = 0; i < count; i++)
            cout<<" ";
    }

    int maxLevel(node* n)
    {
        if (n == NULL)
            return 0;

        return max(maxLevel(n->left),maxLevel(n->right)) + 1;
    }

    bool isAllElemetsNull(vector<node*> v)
    {
        for (unsigned int i=0; i<v.size(); i++)
        {
            if (v.at(i) != NULL)
                return false;
        }

        return true;
    }


    void printNodeInternal(vector<node*> nodes, int level, int maxLevel)
    {
        if (nodes.empty() || isAllElemetsNull(nodes))
            return;

        int floor = maxLevel - level;
        int endgeLines = (int) pow(2, (max(floor - 1, 0)));
        int firstSpaces = (int) pow(2, (floor)) - 1;
        int betweenSpaces = (int) pow(2, (floor + 1)) - 1;

        printWhitespaces(firstSpaces);
        //cout<<" ";
        vector<node*> newNodes ;
        for (int it=0; it<nodes.size(); it++)
        {
            node* Node = nodes.at(it);
            if (Node!=NULL)
            {
                cout<<Node->key;
                newNodes.push_back(Node->left);
                newNodes.push_back(Node->right);
            }
            else
            {
                newNodes.push_back(0);
                newNodes.push_back(0);
                cout<<" ";
            }

            printWhitespaces(betweenSpaces);
        }
        cout<<endl;

        for (int i = 1; i <= endgeLines; i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                printWhitespaces(firstSpaces - i);
                if (nodes.at(j) == NULL)
                {
                    printWhitespaces(endgeLines + endgeLines + i + 1);
                    continue;
                }

                if (nodes.at(j)->left != NULL)
                    cout<<"/";
                else
                    printWhitespaces(1);

                printWhitespaces(i + i - 1);

                if (nodes.at(j)->right != NULL)
                    cout<<"\\";
                else
                    printWhitespaces(1);

                printWhitespaces(endgeLines + endgeLines - i);
            }

            cout<<endl;
        }

        printNodeInternal(newNodes, level + 1, maxLevel);
    }

    void printNode(node* root)
    {
        int maxL = maxLevel(root);
        vector<node*> nodes;
        nodes.push_back(root);
        printNodeInternal(nodes, 1, maxL);
    }

    void print()
    {
        printNode(root);
    }

    void erase_des(node *current)
    {
        if (current)
        {
            if(current->left)
                erase_des(current->left);
            if(current->right)
                erase_des(current->right);
            delete current;
            current = NULL;
        }
    }

    ~splay_tree()
    {
        erase_des(root);
    }
};

int main()
{
    splay_tree s;

    while(1)
    {
        printf("1. Print. 2. Splay. 3. Search.\n");
        printf("4. Insert. 5. Delete. 6. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            s.print();
        }
        else if(ch==2)
        {
            int x;
            cin >> x;
            node * temp = s.mj(x);
            s.splay(temp);
        }
        else if(ch==3)
        {
            int x;
            cin >> x;
            if(s.search(x) == true)
                cout << "Found" << endl;
            else
                cout << "Not found" << endl;
        }
        else if(ch==4)
        {
            int x;
            cin >> x;
            s.insert(x);
        }

        else if(ch==5)
        {
            int x;
            cin >> x;
            s.del(x);
        }
        else
        {
            break;
        }
    }

    return 0;
}
