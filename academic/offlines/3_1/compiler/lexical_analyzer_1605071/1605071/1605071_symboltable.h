#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include <fstream>
#include<iostream>

using namespace std;



string token_str;
string log_str;
string unfin_str;
string log_com;
string log_mulcom;
int ex;
int excom;
int exmulcom;

FILE *logout;
FILE *tokenout;

class SymbolInfo
{
    string name;
    string type;

public:
    SymbolInfo *s;
    SymbolInfo()
    {
        name = "";
        type = "";
        s = 0;
    }

    SymbolInfo(string name, string type)
    {
        this->name = name;
        this->type = type;
        s = 0;
    }

    void set_name(string sn)
    {
        name = sn;
    }

    string get_name()
    {
        return name;
    }

    void set_type(string st)
    {
        type = st;
    }

    string get_type()
    {
        return type;
    }
};

int curid;

class ScopeTable
{

    SymbolInfo **sarr;
    int N, current_size;
public:

    int id;
    ScopeTable *parentScope;

    ScopeTable()
    {
        N=0;
        current_size = 0;
        parentScope = NULL;
        curid ++;
        id = curid;
    }

    ScopeTable(int c)
    {
        N = c;
        current_size = 0;
        sarr = new SymbolInfo * [N];
        for(int i=0; i<N; i++)
        {
            sarr[i] = 0;
        }
        curid ++;
        id = curid;
    }


    int Hash(string k)
    {
        int h2 = 0, g = 2, p = 883;
        int cur = 1;

        for(int i=0; i<k.size(); i++)
        {
            h2 = (h2 + g * (k[i] + 1) + cur) % N;
            g = (g * p) % N;
            cur = (cur * 26) % N;
        }
        return h2;
    }


    SymbolInfo* c_lookup(string k)
    {
        int pos = Hash(k);
        //slot = pos;
        //index = 0;

        SymbolInfo *temp;
        temp = sarr[pos];

        while(temp!=0)
        {
            if (temp->get_name() == k)
                return temp ;
            temp = temp->s ; //move to next node
            //index ++;
        }
        return 0;
    }

    bool c_insert(SymbolInfo *k)
    {
        SymbolInfo *found = c_lookup(k->get_name());
        if(found != 0)
        {
            fprintf(logout,"\n<%s : %s> ",found->get_name().c_str(),found->get_type().c_str());
            fprintf(logout, " already exists in scope table.\n");
            return false;
        }

        int pos = Hash(k->get_name());
        //slot = pos;
        //index = 0;

        SymbolInfo * newNode = new SymbolInfo() ;
        newNode->set_name(k->get_name()) ;
        newNode->set_type(k->get_type()) ;
        if(sarr[pos] == NULL)
        {
            sarr[pos] = newNode;
            //index  = 0;
        }
        else
        {
            int c  = 1;
            //SymbolInfo * temp = new SymbolInfo();
            SymbolInfo * temp = sarr[pos];
            while(temp->s)
            {
                temp = temp->s;
                c++;
            }
            temp->s = newNode;
            //index = c;
        }
        current_size++;
        return true;
    }

   

    void c_print()
    {
        //cout << "ScopeTable # " << id << endl;
        fprintf(logout,"\nScopeTable # %d\n", id);
        SymbolInfo * temp;
        for(int i=0; i<N; ++i)
        {
            temp = sarr[i];
            if(temp != 0)
            {
            fprintf(logout, "%d ----> ", i);
            
            while(temp!=0)
            {
                fprintf(logout,"<%s : %s> ",temp->get_name().c_str(),temp->get_type().c_str());
                temp = temp->s;
            }
            fprintf(logout, "\n");
            }
        }
    }

    ~ScopeTable()
    {
        //write your codes here
        for(int i=0; i<N; i++)
        {
            SymbolInfo *temp;
            temp = sarr[i];

            while(temp)
            {
                SymbolInfo* t = temp->s;

                delete(temp);
                temp = t;
                current_size--;
            }
        }
        delete[] sarr;
    }
};

class SymbolTable
{
    ScopeTable *scope;
    int N;

public:
    SymbolTable()
    {
        scope = NULL;
        //N = n;
    }
    
    SymbolTable(int size)
    {
        N = size;
        scope = new ScopeTable(N);
    }

    void enter_Scope(int N)
    {
        int sid;
        ScopeTable *newscope = new ScopeTable(N);
        newscope->parentScope = scope ; //point to previous first node
        scope = newscope ; //set list to point to newnode as this is now the first node
        sid = scope->id;
    }

    bool exit_Scope()
    {
        int sid = scope->id;
        ScopeTable * temp = scope;
        scope = scope->parentScope;

        delete(temp);
        //curid--;

        if(scope)
            return true;
        else
            return false;
    }

    bool insert(SymbolInfo *k)
    {
        //sid = scope->id;
        return scope->c_insert(k);
    }

    SymbolInfo* lookup(string k)
    {
        SymbolInfo * temp;
        ScopeTable * curscope = scope;

        while(curscope)
        {
            int sid = curscope->id;
            temp = curscope->c_lookup(k);
            if(temp == 0)
            {
                curscope = curscope->parentScope;
            }
            else
            {
                return temp;
            }
        }
        return 0;
    }

    void print_cur()
    {

        scope->c_print();
    }

    void print_all()
    {
        ScopeTable * temp;
        temp = scope;
        //int sid = scope->id;
        while(temp!=0)
        {
            int sid = temp->id;
            cout << "ScopeTable # " << sid << endl;
            temp->c_print();
            temp = temp->parentScope;
        }
        cout << endl;
    }

};

