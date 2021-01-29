#include<cstdio>
#include<cstdlib>
#include<string>
#include<vector>
#include <fstream>
#include<iostream>

using namespace std;

extern FILE *logout;
extern FILE *errorout;

class SymbolInfo
{
    string name;
    string type;
    string spec;
    
    int check_func;//kono id func kina r func declare kora hoyeche kina age check kore
    int def_func;//kono id func kina r func define kora hoyeche kina age check kore
    int check_undeclared_var;
    vector<string> saveddecvar;
    vector<string> saveddecspec;
    vector <string> savedvar; //param gulor nam rakhe
    vector <string> savedspec; //param gulor spec rakhe
    vector<int> savedsid;
    vector <string> unic_savedfunc_var;
    string ret_type;
    int psize;

public:
    string code;
    string arrsize;
    string namewidid;
    int varid;

    SymbolInfo *s;
    
    SymbolInfo()
    {
        //cout << "HERE 0" << endl;
        name = "";
        type = "";
        spec = "";
        namewidid = "";
        varid = 0;
        code = "";
        check_func = 0;
        def_func = 0;
        check_undeclared_var = 0;
        s = 0;
        psize = 0;
        ret_type = "";
        arrsize = "";
    }

    SymbolInfo(string name, string type)
    {
        //cout << "HERE 2" << endl;
        this->name = name;
        this->type = type;
        namewidid = "";
        //varid = 0;
        check_func = 0;
        def_func = 0;
        check_undeclared_var = 0;
        s = 0;
        psize = 0;
        ret_type = "";
        code = "";
        //arrsize = "";
    }

    SymbolInfo(string name, string type, string spec)
    {
        //cout << "HERE 3" << endl;
        this->name = name;
        this->type = type;
        this->spec = spec;
        namewidid = "";
        //varid = 0;
        check_func = 0;
        def_func = 0;
        check_undeclared_var = 0;
        s = 0;
        psize = 0;
        ret_type = "";
        code = "";
        //arrsize = "";
    }

    SymbolInfo(string name, string type, string spec, string arrsize)
    {
        //cout << "HERE 4" << endl;
        this->name = name;
        this->type = type;
        this->spec = spec;
        namewidid = "";
        //varid = 0;
        this->arrsize = arrsize;
        check_func = 0;
        def_func = 0;
        check_undeclared_var = 0;
        s = 0;
        psize = 0;
        ret_type = "";
        code = "";
    }

    SymbolInfo(string name, string type, string spec, string arrsize, int varid)
    {
        //cout << "HERE 5" << endl;
        this->name = name;
        this->type = type;
        this->spec = spec;
        this->varid = varid;
        this->arrsize = arrsize;
        namewidid = "";
        check_func = 0;
        def_func = 0;
        check_undeclared_var = 0;
        s = 0;
        psize = 0;
        ret_type = "";
        code = "";
    }

    SymbolInfo(string spec)
    {
        this->spec = spec;
        code = "";
        namewidid = "";
    }

    SymbolInfo(const SymbolInfo *sym)//notun likhlam
    {
        name = sym->name;
        type = sym->type;
        spec = sym->spec;
        code = sym->code;
    }

    /*SymbolInfo(int check_func)
    {
        this->check_func = check_func;
    }*/

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

    void set_spec(string sp)
    {
        spec = sp;
    }

    string get_spec()
    {
        return spec;
    }

    void set_varid(int vid)
    {
        varid = vid;
    }

    int get_varid()
    {
        return varid;
    }

    void set_namewidid(string nameid)
    {
        namewidid = nameid;
    }

    string get_namewidid()
    {
        return namewidid;
    }

    void set_code(string c)
    {
        code = c;
    }

    string get_code()
    {
        return code;
    }

    void set_check_func(int f)
    {
        check_func = f;
    }

    int get_check_func()
    {
        return check_func;
    }

    void set_def_func(int f)
    {
        def_func = f;
    }

    int get_def_func()
    {
        return def_func;
    }

    void set_check_undeclared_var(int a)
    {
        check_undeclared_var = a;
    }

    int get_check_undecalred_var()
    {
        return check_undeclared_var;
    }

    void set_savedparam(string name, string spec)
    {
        savedvar.push_back(name);
        savedspec.push_back(spec);
    }

    void set_saveddecparam(string name, string spec)
    {
        saveddecvar.push_back(name);
        saveddecspec.push_back(spec);
    }

    void set_savedsid(int sid)
    {
        savedsid.push_back(sid);
    }
    
    vector<string> get_savedname()
    {
        return savedvar;
    }

    vector<string> get_savedspec()//this should be return type
    {
        return savedspec;
    }

    void clearvector()
    {
        savedvar.clear();
        savedspec.clear();
    }

    vector<string> get_saveddecname()
    {
        return saveddecvar;
    }

    vector<string> get_saveddecspec()//this should be return type
    {
        return saveddecspec;
    }

    vector<int> get_savedsid()
    {
        return savedsid;
    }

    void set_unic_savedfunc_var(string name)
    {
        unic_savedfunc_var.push_back(name);
    }

    vector<string> get_unic_savedfunc_var()
    {
        return unic_savedfunc_var;
    }

    void set_para_list_size(vector<string> savedspec)
    {
        psize = savedspec.size();
    }

    int get_para_list_size()
    {
        return psize;
    }

    void set_ret_type(string sr)
    {
        ret_type = sr;
    }

    string get_ret_type()
    {
        return ret_type;
    }

};

extern int curid;

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
            //fprintf(logout,"\n<%s : %s> ",found->get_name().c_str(),found->get_type().c_str());
            //fprintf(logout, " already exists in scope table.\n");
            return false;
        }

        int pos = Hash(k->get_name());
        //slot = pos;
        //index = 0;

        SymbolInfo * newNode = new SymbolInfo() ;
        newNode->set_name(k->get_name()) ;
        newNode->set_type(k->get_type()) ;
        if(k->get_spec() != "") newNode->set_spec(k->get_spec());
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
        //fprintf(logout,"\nScopeTable # %d\n", id);
        SymbolInfo * temp;
        for(int i=0; i<N; ++i)
        {
            temp = sarr[i];
            if(temp != 0)
            {
            fprintf(logout, "%d ----> ", i);
            
            while(temp!=0)
            {
                /*fprintf(logout,"<%s : %s ",temp->get_name().c_str(),temp->get_type().c_str());
                if(temp->get_spec() != "") fprintf(logout,": %s > ",temp->get_spec().c_str());
                else fprintf(logout, ">");*/

                fprintf(logout, "< %s ", temp->get_name().c_str());
                if(temp->get_type() == "FUNC_ID" || temp->get_type() == "ARRAY_ID")
                    fprintf(logout, ", ID");
                else
                    fprintf(logout, ", %s", temp->get_type().c_str());
                fprintf(logout, " >");    

                if(temp->get_spec() != "") 
                    fprintf(logout," , %s > ",temp->get_spec().c_str());

                if(temp->get_varid() != 0)
                {
                    fprintf(logout," , %d > ",temp->get_varid());
                }        
                else 
                    fprintf(logout, ">");

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

    void enter_Scope()
    {
        int sid;
        ScopeTable *newscope = new ScopeTable(N);
        newscope->parentScope = scope ; //point to previous first node
        scope = newscope ; //set list to point to newnode as this is now the first node
        sid = scope->id;
        fprintf(logout, "\nNew scopetable with id %d created\n", sid);
    }

    bool exit_Scope()
    {
        int sid = scope->id;
        ScopeTable * temp = scope;
        scope = scope->parentScope;

        delete(temp);
        //curid--;

        fprintf(logout, "\nScopetable with id %d removed\n", sid);

        if(scope)
            return true;
        else
        {
            fprintf(logout, "\nNo scope available\n");
            return false;
        }    
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

    int find_sid(string k)
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
                return curscope->id;
            }
        }
        return 0;
    }

    SymbolInfo* current_t_lookup(string k)
    {
        SymbolInfo * temp;
        ScopeTable * curscope = scope;

        //while(curscope)
        //{
            int sid = curscope->id;
            temp = curscope->c_lookup(k);
            if(temp != 0)
            {
                return temp;
            }
        //}
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
            //cout << "ScopeTable # " << sid << endl;
            fprintf(logout,"\nScopeTable # %d\n", sid);
            temp->c_print();
            temp = temp->parentScope;
        }
        //cout << endl;
        fprintf(logout, "\n");
    }

};

