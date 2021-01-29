#include<string>
#include <fstream>
#include<iostream>
using namespace std;

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

//    int Hash(string k)
//    {
//        int h1 = 0, g = 1;
//        int p = 701;
//
//        for(int i=0; i<k.size(); ++i)
//        {
//            h1 = (h1 + g * (k[i] + 1)) % N;
//            g = (g * p) % N;
//        }
//        return h1;
//    }
    int Hash(string k)
    {
        int h2 = 0, g = 2, p = 883;
        int cur = 1;

        for(int i=0; i<k.size(); i++)
        {
            //h2 = (g + h2 ^ k[i]) % N;
            h2 = (h2 + g * (k[i] + 1) + cur) % N;
            g = (g * p) % N;
            cur = (cur * 26) % N;
        }
        return h2;
    }


    SymbolInfo* c_lookup(string k, int &slot, int &index)
    {
        int pos = Hash(k);
        slot = pos;
        index = 0;

        SymbolInfo *temp;
        temp = sarr[pos];

        while(temp!=0)
        {
            if (temp->get_name() == k)
                return temp ;
            temp = temp->s ; //move to next node
            index ++;
        }
        return 0;
    }

    bool c_insert(SymbolInfo k, int &slot, int &index)
    {
        SymbolInfo *found = c_lookup(k.get_name(), slot, index);
        if(found != 0)
        {
            cout << "< " << found->get_name() << " , " << found->get_type() << " > ";
            return false;
        }

        int pos = Hash(k.get_name());
        slot = pos;
        //index = 0;

        SymbolInfo * newNode = new SymbolInfo() ;
        newNode->set_name(k.get_name()) ;
        newNode->set_type(k.get_type()) ;
        if(sarr[pos] == NULL)
        {
            sarr[pos] = newNode;
            index  = 0;
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
            index = c;
        }
        current_size++;
        return true;
    }

    bool c_delete(string k, int &slot, int &index)
    {
        int pos = Hash(k);

        SymbolInfo *temp, *prev ;
        temp = sarr[pos] ; //start at the beginning
        slot = pos;
        index = 0;
        while (temp != 0)
        {
            if (temp->get_name() == k)
                break ;
            prev = temp;
            temp = temp->s ; //move to next node
            index++;
        }
        if (temp == 0)
            return false ; //item not found to delete
        if (temp == sarr[pos]) //delete the first node
        {
            sarr[pos] = sarr[pos]->s ;
            delete temp;
            current_size--;
        }
        else
        {
            prev->s = temp->s ;
            delete temp;
            current_size--;
        }
        return true;
    }

    void c_print()
    {
        //cout << "ScopeTable # " << id << endl;
        SymbolInfo * temp;
        for(int i=0; i<N; ++i)
        {
            //cout<<"Slot "<<i<<"----> ";
            cout << i << "----> ";
            temp = sarr[i];
            while(temp!=0)
            {
                cout << " < " <<temp->get_name() << " : " << temp->get_type() << " > ";
                temp = temp->s;
            }
            cout<<endl;
        }
        cout << endl;
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

public:
    SymbolTable()
    {
        scope = NULL;
    }

    void enter_Scope(int N, int &sid)
    {
        ScopeTable *newscope = new ScopeTable(N);
        newscope->parentScope = scope ; //point to previous first node
        scope = newscope ; //set list to point to newnode as this is now the first node
        sid = scope->id;
    }

    bool exit_Scope(int &sid)
    {
        sid = scope->id;
        ScopeTable * temp = scope;
        scope = scope->parentScope;

        delete(temp);
        //curid--;

        if(scope)
            return true;
        else
            return false;
    }

    bool t_insert(SymbolInfo k, int &sid, int &slot, int &index)
    {
        sid = scope->id;
        return scope->c_insert(k, slot, index);
    }

    bool t_remove(string k, int &sid, int&slot, int&index)
    {
        sid = scope->id;
        return scope->c_delete(k, slot, index);
    }

    SymbolInfo* t_lookup(string k, int &sid, int &slot, int &index)
    {
        SymbolInfo * temp;
        ScopeTable * curscope = scope;

        while(curscope)
        {
            sid = curscope->id;
            temp = curscope->c_lookup(k, slot, index);
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

int main()
{
    freopen("1605071_input.txt", "r", stdin);
    freopen("1605071_output.txt", "w", stdout);
    //ifstream fin("input.txt");

    int n;
    char ch;
    cin >> n;

    SymbolTable st;
    int scope_id;
    st.enter_Scope(n, scope_id);

    while(cin >> ch)
    {
        //char ch;
        //cin >> ch;
        if(ch == 'I')
        {
            string name, type;
            cin >> name >> type;
            cout << ch << " " << name << " " << type << endl << endl;
            int sid, slot, index;
            SymbolInfo newnode(name, type);

            if(st.t_insert(newnode, sid, slot, index) == true)
                cout << "Inserted in ScopeTable# " << sid << " at position " << slot << " , " << index << endl;
            else
                //cout << "< " << name << " , " << type << " >" << " already exists in current ScopeTable" << endl;
                cout << " already exists in current ScopeTable" << endl;

            cout << endl;
        }
        else if(ch == 'L')
        {
            string name;
            cin >> name;
            cout << ch << " " << name << endl << endl;
            int sid, slot, index;

            if(st.t_lookup(name, sid, slot, index))
                cout << "Found in ScopeTable# " << sid << " at position " << slot << " , " << index << endl;
            else
                cout << "Not found" << endl << endl;
        }
        else if(ch == 'D')
        {
            string s;
            cin >> s;
            cout << ch << " " << s << endl << endl;
            int sid, slot, index;

            if(st.t_remove(s, sid, slot, index))
            {
                cout << "Found in ScopeTable# " << sid << " at position " << slot << " , " << index << endl;
                cout << "Deleted entry at " << slot << " , " << index << " from current ScopeTable" << endl;
            }
            else
                cout << "Not found" << endl;

            cout << endl;
        }
        else if(ch == 'P')
        {
            char another;
            cin >> another;
            cout << ch << " " << another << endl << endl;

            if(another == 'C')
            {
                st.print_cur();
                cout << endl;
            }
            else if(another == 'A')
            {
                st.print_all();
                cout << endl;
            }
//            else
//                continue;
        }

        else if(ch == 'S')
        {
            cout << ch << endl << endl;
            int sid;
            st.enter_Scope(n, sid);

            cout << "New ScopeTable with id " << sid << " created" << endl << endl;
        }
        else if(ch == 'E')
        {
            cout << ch << endl << endl;
            int sid;
            bool b = st.exit_Scope(sid);

            cout << "ScopeTable with id " << sid << " removed" << endl << endl;

            if(b == false)
            {
                cout << "No scope available" << endl;
                break;
            }
        }
//        else
//        {
//            //continue;
//            break;
//        }

    }

    return 0;
}
