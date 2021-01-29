#include<iostream>
using namespace std;

#include<stdio.h>
#include<stdlib.h>
#include <string>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class node
{
public:
    int key, degree;
    node *child_h, *prev, *parent, *next, *child_t;

    node(int key = 0, int degree = 0)
    {
        this->key = key;
        this->degree = degree;
        this->child_h = NULL;
        this->child_t = NULL;
        this->parent = NULL;
        this->prev = NULL;
        this->next = NULL;
    }

    void print_node(string s)
    {
        //cout << "level" << endl ;
        cout << s << key << '\n';
        node * it = child_h;
        while(it)
        {
            it->print_node(s + "    ");
            //cout << "level" ;
            it = it->next;
        }
    }
};

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0)
        return true ;
    else
        return false ;
}


int Queue::dequeue()
{
    if(length == 0)
        return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data)
        delete[] data; //deallocate memory
    data = 0; //set to NULL
}

class Binomial_Heap
{
    node * h; // h is the header of linked list of
public:
    Binomial_Heap()
    {
        h = NULL;
    }

    node * Find_Min()
    {
        node * x, * a;
        a = NULL;
        x = h;
        int mn = 99999;

        while(x != NULL)
        {
            if(x->key < mn)
            {
                mn = x->key;
                a = x;
            }
            x = x->next;
        }
        return a;
    }

    node * binomial_link(node * y, node * z)
    {
        y->next = z->next = y->prev = z->prev = 0;
        y->parent = z->parent = 0;
        if(y->key < z->key) // y choto hoile y er niche z lagabe
        {
            if(!y->child_h) // y er kono child na thakle
            {
                y->child_h = y->child_t = z; // only child is z
                z->parent = y;
                y->degree++;
                return y;
            }
            y->child_t->next = z;
            z->prev = y->child_t;
            y->child_t = z;
            z->parent = y;
            y->degree++;
            return y;
        }
        else // ar noyto z er niche y lagabe
        {
            if(!z->child_h) // z er kono child na thakle
            {
                z->child_h = z->child_t = y; // only child is y
                y->parent = z;
                z->degree++;
                return z;
            }
            z->child_t->next = y;
            y->prev = z->child_t;
            z->child_t = y;
            y->parent = z;
            z->degree++;
            return z;
        }
    }

    Binomial_Heap binomial_Heap_Union(Binomial_Heap &h1, Binomial_Heap &h2)
    {
        Binomial_Heap h_new;
        node *x, *y, *next_x, *next_y, *sum, *carry = 0, *it;

        x = h1.h;
        y = h2.h;

        while(x || y)
        {
            if(x)
                next_x = x->next;
            if(y)
                next_y = y->next;

            if(carry != NULL && (x == NULL || (carry->degree < x->degree)) && (y == NULL || (carry->degree < y->degree)))
            {
                sum = carry;
                carry = 0;
            }
            else if(y == NULL || (x != NULL && x->degree < y->degree))
            {
                if(carry != NULL)
                {
                    sum = 0;
                    carry = binomial_link(carry, x);
                }
                else
                {
                    sum = x;
                    carry = 0;
                }
                x = next_x;
            }
            else if(x == NULL || (y != NULL && y->degree < x->degree))
            {
                if(carry != NULL)
                {
                    sum = 0;
                    carry = binomial_link(carry, y);
                }
                else
                {
                    sum = y;
                    carry = 0;
                }
                y = next_y;
            }
            else
            {
                sum = carry;
                carry = binomial_link(x,y);
                x = next_x;
                y = next_y;
            }

            if(sum != NULL)
            {
                if(h_new.h == NULL)
                {
                    h_new.h = sum;
                    it = h_new.h;
                }
                else
                {
                    it->next = sum;
                    sum->prev = it;
                    it = it->next;
                }
            }
        }

        if(carry != NULL)
        {
            if(h_new.h == NULL)
                h_new.h = carry;
            else
            {
                it->next = carry;
                carry->prev = it;
            }
        }

        h1.h = h2.h = 0;
        return h_new;
    }

//    void insert_bi_heap(int x)
//    {
//        Binomial_Heap hp;
//
//        hp.h = new node(x);
//
//        hp = binomial_Heap_Union(*this, hp);
//        this->h = hp.h;
//    }

    void insert_bi_heap(int x)
    {
        Binomial_Heap hp;

        hp.h = new node(x);

        //hp.h = x;

        hp = binomial_Heap_Union(*this, hp);

        this->h = hp.h;
    }

    node * extract_Min()
    {
        if(!h)
        {
            node * z = new node(-1);
            return z;
        }

        node * x = Find_Min();

        if(!x->prev) // tar mane x = h
            h = x->next;
        else
            x->prev->next = x->next;

        if(x->next)
            x->next->prev = x->prev;

        Binomial_Heap hp;
        hp.h = x->child_h;
        hp = binomial_Heap_Union(*this, hp);
        this->h = hp.h;

        x->prev = x->next = x->parent = x->child_h = x->child_t = 0;

        return x;
    }

    void Display()
    {
        if (h == NULL)
        {
            cout<<"The Heap is empty"<<endl;
            return;
        }
        cout<<"The root nodes are: "<<endl;

        node * it = h;

        while (it != NULL)
        {
            it->print_node("");
            it = it->next;
        }
        cout<<endl;
    }

    void Print()
    {
        if (h == NULL)
        {
            cout<<"The Heap is empty"<<endl;
            return;
        }
        //Queue q;
        node * cur;

        node *a = h;
        while(a != NULL)
        {
            Queue q;
            int t = (int)a;
            q.enqueue(t);
            a = a->next;
            int i = 0;
            cout << endl;
            cout << "Level " << i << ": ";
            q.enqueue(-1);

            while(!q.empty())
            {
                int t = q.dequeue();
                if(t < 0)
                {
                    cout << endl;

                    if(!q.empty())
                    {
                        q.enqueue(-1);
                        i++;
                        cout << "level " << i << ": ";
                    }
                    //continue;
                }
                else
                {
                    node *p = (node *) t;
                    node *tn = p;
                    node *tc = tn->child_t;
//                    cout << "(" << tn->key << " , ";
//                    if(tn->parent) cout << tn->parent->key << ")    ";
//                    else cout << "-1)";
                    cout << tn->key << "\t";

                    for(int j=0; j<tn->degree; j++)
                    {
                        if(tc)
                        {
                            int s = (int) tc;
                            q.enqueue(s);
                            tc = tc->prev;
                        }
//                        else
//                        {
//                            break;
//                        }
                    }
                }
            }

//            if(a->parent!=NULL)
//                cout<<a->parent->key;
//            else
//                cout<<"-1";
//            cout<<"; ";

        }
        //cout << endl;
    }



};

int main()
{
    Binomial_Heap bh1, bh2;

    while(1)
    {
        cout << "heap1 : 1. Insert. 2. Find-Min. 3. Extract-Min" << endl;
        cout << "heap2 : 4. Insert. 5. Find-Min. 6. Extract-Min" << endl;
        cout << "7. Union. 8. Exit \n\tEnter choice : ";
        int c;
        cin >> c;

        if(c == 1)
        {
            int data;
            cin >> data;
            //node * x = new node(data);
            bh1.insert_bi_heap(data);
        }
        else if(c == 2)
        {
            cout << "Min: " << bh1.Find_Min()->key << endl;
        }
        else if(c == 3)
        {
            cout << "Min: " << bh1.extract_Min()->key << endl;
        }
        else if(c == 4)
        {
            int data;
            cin >> data;
            //node * x = new node(data);
            bh2.insert_bi_heap(data);
        }
        else if(c == 5)
        {
            cout << "Min: " << bh2.Find_Min()->key << endl;
        }
        else if(c == 6)
        {
            cout << "Min: " << bh2.extract_Min()->key << endl;
        }
        else if(c == 7)
        {
            bh1 = bh1.binomial_Heap_Union(bh1,bh2);
        }
        else if(c == 8)
        {
            break;
        }
        cout << "heap1: \n";
        bh1.Print();
        cout << "Drawing: \n";
        bh1.Display();

        cout << "heap2: \n";
        bh2.Print();
        cout << "Drawing: \n";
        bh2.Display();
    }

//    for(int i=0; i<10; i++)
//        bh.insert_bi_heap(i);
//
//    bh.Display();
//
//    node * a = bh.Find_Min();
//    cout << "MIN : " << a->key << endl;
//
//    int b = bh.extract_Min();
//    cout << "Min :" << b << endl;
//    bh.Display();

    return 0;
}
