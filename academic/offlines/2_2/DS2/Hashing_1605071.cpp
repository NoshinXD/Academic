
#include<bits/stdc++.h>
#include<set>
#include<iostream>
using namespace std;

struct key_value_pair
{
    string key;
    int val;

    key_value_pair(string key, int val)
    {
        this->key = key;
        this->val = val;
    }
};

vector <key_value_pair> rand_word_gen(int length, int n)
{
    vector <key_value_pair> v;
    set <string> st;

    for(int i=0; i<n; i++)
    {
        string s = "";

        for(int j=0; j<length; j++)
        {
            char c= (abs(rand()) % 26) + 'a';
            s = s + c;
        }

        if(st.find(s) == st.end())
        {
            v.push_back(key_value_pair(s, v.size() + 1));
            st.insert(s);
        }
    }

//    for(int i=0; i<n; i++)
//    {
//        cout << v[i].key << " , " << v[i].val << endl;
//    }

    return v;
}

class HashTable
{
    #define DEL "DELETED_KEY"
    #define PENALTY 1000
    #define C1 857
    #define C2 111

    int N, current_size, c_col = 0, c_hit = 0, c_col_new = 0, c_hit_new = 0, d_col1 = 0, d_col2 = 0, d_hit1 = 0, d_hit2 = 0, p_col1 = 0, p_col2 = 0, p_hit1 = 0, p_hit2 = 0;
    vector <list<key_value_pair>> v, v_new;
    vector <string> d1_keys, d2_keys, p1_keys, p2_keys;
    vector <int> d1_vals, d2_vals, p1_vals, p2_vals;
    vector <bool> vis1, vis2, vis3, vis4;
public:
    HashTable(int c)
    {
        N = c;
        current_size = 0;
        v.resize(N);
        v_new.resize(N);
        vis1.resize(N);
        vis2.resize(N);
        vis3.resize(N);
        vis4.resize(N);
        d1_keys.resize(N);
        d2_keys.resize(N);
        d1_vals.resize(N);
        d2_vals.resize(N);
        p1_keys.resize(N);
        p2_keys.resize(N);
        p1_vals.resize(N);
        p2_vals.resize(N);
    }

    int auxHash(string k)
    {
        int h = 0;

        for(int i=0; i<k.size(); i++)
        {
            h = (h + k[i]) % N;
        }
        return h;
    }

    int Hash1(string k)
    {
        int h1 = 0, g = 1;
        int p = 701;

//        for(int i=0; i<k.size(); i++)
//        {
//            h1 = (g * h1 + k[i]) % N;
//        }
//        return h1;
        for(int i=0; i<k.size(); ++i) {
            h1 = (h1 + g * (k[i]-'a' + 1)) % N;
            g = (g * p) % N;
        }
        return h1;
    }

    int Hash2(string k)
    {
        int h2 = 0, g = 2, p = 883;
        int cur = 1;

        for(int i=0; i<k.size(); i++)
        {
            //h2 = (g + h2 ^ k[i]) % N;
            h2 = (h2 + g * (k[i]-'a' + 1) + cur) % N;
            g = (g * p) % N;
            cur = (cur * 26) % N;
        }
        return h2;
    }

    void c_insert(key_value_pair k)
    {
        int i = 0;
        //int col = 0;

        int pos = Hash1(k.key);

        if(!v[pos].empty())
            c_col++;

        v[pos].push_front(k);
        // current_size++;
    }

    void c_insert_new(key_value_pair k)
    {
        int i = 0;
        //int col = 0;

        int pos = Hash2(k.key);

        if(!v_new[pos].empty())
            c_col_new++;

        v_new[pos].push_front(k);
        // current_size++;
    }



    int c_search(string k)
    {
        int pos = Hash1(k);
        //int hit = 0;

        list<key_value_pair>::iterator i;

        for(i=v[pos].begin(); i != v[pos].end(); i++)
        {
            if(i->key == k)
            {
                break;
            }
            c_hit++;
        }

        if(i != v[pos].end())
            return i->val;
        else
            return -1;
    }

    int c_search_new(string k)
    {
        int pos = Hash2(k);
        //int hit = 0;

        list<key_value_pair>::iterator i;

        for(i=v_new[pos].begin(); i != v_new[pos].end(); i++)
        {
            if(i->key == k)
            {
                break;
            }
            c_hit_new++;
        }

        if(i != v_new[pos].end())
            return i->val;
        else
            return -1;
    }


    void c_delete(string k)
    {
        int pos = Hash1(k);

        list<key_value_pair>::iterator i;

        for(i=v[pos].begin(); i != v[pos].end(); i++)
        {
            if(i->key == k)
                break;
        }
        if(i != v[pos].end())
            v[pos].erase(i);
        // current_size--;
    }

    void c_delete_new(string k)
    {
        int pos = auxHash(k);

        list<key_value_pair>::iterator i;

        for(i=v_new[pos].begin(); i != v_new[pos].end(); i++)
        {
            if(i->key == k)
                break;
        }
        if(i != v_new[pos].end())
            v_new[pos].erase(i);
        // current_size--;
    }

    void d1_insert(key_value_pair k)
    {
        int h1 = Hash1(k.key);
        int h = auxHash(k.key);

        int i = 0;
        while(i < N)
        {
            int pos = (h1 + i * h) % N;

            if(d1_keys[pos].empty() || d1_keys[pos] == DEL)//or d_keys[pos] == DEL
            {
                d1_keys[pos] = k.key;
                d1_vals[pos] = k.val;
                vis1[h1] = true;
		        //vis2[h2] = true;
                return;
            }

            if(vis1[h1]) ++d_col1;
	        //if(vis2[h2]) ++d_col2;

            i++;
        }

        vis1[h1] = true;
        //vis2[h2] = true;

        cout << "Overflowed doubleHash" << endl;
        d_col1 += PENALTY;
        //d_col2 += PENALTY;
    }

    void d2_insert(key_value_pair k)
    {
        int h2 = Hash2(k.key);
        int h = auxHash(k.key);

        int i = 0;
        while(i < N)
        {
            int pos = (h2 + i * h) % N;

            if(d2_keys[pos].empty() || d2_keys[pos] == DEL)//or d2_keys[pos] == DEL
            {
                d2_keys[pos] = k.key;
                d2_vals[pos] = k.val;
                //vis1[h1] = true;
		        vis2[h2] = true;
                return;
            }

            //if(vis1[h1]) ++d_col1;
	        if(vis2[h2]) ++d_col2;

            i++;
        }

        //vis1[h1] = true;
        vis2[h2] = true;

        cout << "Overflowed doubleHash" << endl;
        //d_col1 += PENALTY;
        d_col2 += PENALTY;
    }

    int d1_search(string k)
    {
        int h1 = Hash1(k);
        int h = auxHash(k);
        vis1[h1] = true;
        //vis2[h2] = true;

        int i = 0;
        while(i < N)
        {
            int pos = (h1 + i * h) % N;

            //if(vis1[h1])
            if(vis1[pos])
                d_hit1++;
            //if(vis2[h2]) d_hit2++;


            if(d1_keys[pos] == k)//r kichu lagbe na
            {
                return d1_vals[pos];
            }

            i++;
        }
        return -1;
    }

    int d2_search(string k)
    {
        int h2 = Hash2(k);
        int h = auxHash(k);
        //vis1[h1] = true;
        vis2[h2] = true;

        int i = 0;
        while(i < N)
        {
            int pos = (h2 + i * h) % N;

            //if(vis1[h1]) d_hit1++;
            //if(vis2[h2])
            if(vis2[pos])
                d_hit2++;


            if(d2_keys[pos] == k)//r kichu lagbe na
            {
                return d2_vals[pos];
            }

            i++;
        }
        return -1;
    }

    void d1_delete(string k)
    {
        int h1 = Hash1(k);
        int h = auxHash(k);

        int i = 0;
        while(i < N)
        {
            int pos = (h1 + i * h) % N;

            if(d1_keys[pos] == k)//r kichu lagbe na
            {
                d1_keys[pos] = DEL;
                d1_vals[pos] = -1;
                return;
            }

            i++;
        }
    }

    void d2_delete(string k)
    {
        int h2 = Hash2(k);
        int h = auxHash(k);

        int i = 0;
        while(i < N)
        {
            int pos = (h2 + i * h) % N;

            if(d2_keys[pos] == k)//r kichu lagbe na
            {
                d2_keys[pos] = DEL;
                d2_vals[pos] = -1;
                return;
            }

            i++;
        }
    }

    void p1_insert(key_value_pair k)
    {
        int h1 = Hash1(k.key);
        int h = auxHash(k.key);

        int i = 0;
        while(i < N)
        {
            //cout << "p ins\n";
            int pos = (h1 + C1 * i * h + C2 * i * i) % N;

            if(p1_keys[pos].empty() || p1_keys[pos] == DEL)//or d_keys[pos] == DEL
            {
                p1_keys[pos] = k.key;
                p1_vals[pos] = k.val;
                vis3[h1] = true;
		        //vis4[h2] = true;
                return;
            }

            if(vis3[h1]) ++p_col1;
	        //if(vis4[h2]) ++p_col2;

            i++;
        }

        vis3[h1] = true;
        //vis4[h2] = true;

        cout << "Overflowed doubleHash" << endl;
        p_col1 += PENALTY;
        //p_col2 += PENALTY;
    }

    void p2_insert(key_value_pair k)
    {
        int h2 = Hash2(k.key);
        int h = auxHash(k.key);

        int i = 0;
        while(i < N)
        {
            //cout << "p ins\n";
            int pos = (h2 + C1 * i * h + C2 * i * i) % N;

            if(p2_keys[pos].empty() || p2_keys[pos] == DEL)//or d2_keys[pos] == DEL
            {
                p2_keys[pos] = k.key;
                p2_vals[pos] = k.val;
                //vis3[h1] = true;
		        vis4[h2] = true;
                return;
            }

            //if(vis3[h1]) ++p_col1;
	        if(vis4[h2]) ++p_col2;

            i++;
        }

        //vis3[h1] = true;
        vis4[h2] = true;

        cout << "Overflowed doubleHash" << endl;
        //p_col1 += PENALTY;
        p_col2 += PENALTY;
    }

    int p1_search(string k)
    {
        int h1 = Hash1(k);
        int h = auxHash(k);
        vis3[h1] = true;
        //vis4[h2] = true;

        int i = 0;
        while(i < N)
        {
            //cout << "p search\n";
            int pos = (h1 + C1 * i * h + C2 * i * i) % N;

            //if(vis3[h1])
            if(vis3[pos])
                p_hit1++;
            //if(vis4[h2]) p_hit2++;


            if(p1_keys[pos] == k)//r kichu lagbe na
            {
                return p1_vals[pos];
            }

            i++;
        }
        return -1;
    }

    int p2_search(string k)
    {
        int h2 = Hash2(k);
        int h = auxHash(k);
        //vis3[h1] = true;
        vis4[h2] = true;

        int i = 0;
        while(i < N)
        {
            //cout << "p search\n";
            int pos = (h2 + C1 * i * h + C2 * i * i) % N;

            //if(vis3[h1]) p_hit1++;
            //if(vis4[h2])
            if(vis4[pos])
                p_hit2++;


            if(p2_keys[pos] == k)//r kichu lagbe na
            {
                return p2_vals[pos];
            }

            i++;
        }
        return -1;
    }

    void p1_delete(string k)
    {
        int h1 = Hash1(k);
        int h = auxHash(k);

        int i = 0;
        while(i < N)
        {
            int pos = (h1 + C1 * i * h + C2 * i * i) % N;

            if(p1_keys[pos] == k)//r kichu lagbe na
            {
                p1_keys[pos] = DEL;
                p1_vals[pos] = -1;
                return;
            }

            i++;
        }
    }

    void p2_delete(string k)
    {
        int h2 = Hash2(k);
        int h = auxHash(k);

        int i = 0;
        while(i < N)
        {
            int pos = (h2 + C1 * i * h + C2 * i * i) % N;

            if(p2_keys[pos] == k)//r kichu lagbe na
            {
                p2_keys[pos] = DEL;
                p2_vals[pos] = -1;
                return;
            }

            i++;
        }
    }


    void c_print()
    {
        for(int i=0; i<N; i++)
        {
            cout << "List " << i << ": ";
            for(list<key_value_pair>:: iterator it = v_new[i].begin(); it!=v_new[i].end(); it++)
            {
                cout << (it->key) << "," << it->val << "; ";
            }
            cout << "\n";
        }
    }

    void d1_print()
    {
        cout << "Double Hash\n";
        for(int i=0; i<N; i++)
        {
            cout << i << " - " << d1_keys[i] << " , " << d1_vals[i] << "; " << "\n";
        }
    }

    void p1_print()
    {
        cout << "Custom Probing\n";
        for(int i=0; i<N; ++i)
        {
            cout << i << " - " << p1_keys[i] << " , " << p1_vals[i] << "\n";
        }
    }

//    void report_Gen(int cnt) {
//        cout << "Chain Method\n";
//        cout << "Hash 1 : " << c_col << " " << (double)c_hit/cnt << endl;
//        cout << "Hash 2 : " << c_col_new << " " << (double)c_hit_new/cnt << endl;
//        cout << endl;
//        cout << "Double Hashing" << endl;
//        cout << "Hash 1 : " << d_col1 << " " << (double)d_hit1/cnt << endl;
//        cout << "Hash 2 : " << d_col2 << " " << (double)d_hit2/cnt << endl;
//        cout << endl;
//        cout << "Custom Probe" << endl;
//        cout << "Hash 1 : " << p_col1 << " " << (double)p_hit1/cnt << endl;
//        cout << "Hash 2 : " << p_col2 << " " << (double)p_hit2/cnt << endl;
//   }

    void report_Gen(int cnt)
   {
       cout << "\n-----------------------------------------------------------------------";
       cout << "\n               |         Hash1         |  " << "            Hash2            ";
       cout << "\n-----------------------------------------------------------------------";
       cout << "\n               | " << "Collisions " << "|" << " Avg. Hit" << " |  Collisions  " << "|" << "  Avg. Hit";
       cout << "\n-----------------------------------------------------------------------";
       cout << "\nChaining Method|    " << c_col << "    |  " << (double)c_hit/cnt << "   |     " << c_col_new << "     |    " << (double)c_hit_new/cnt;
       cout << "\nDouble Hashing |    " << d_col1 << "    |  " << (double)d_hit1/cnt << "   |     " << d_col2 << "     |    " << (double)d_hit2/cnt;
       cout << "\nCustom Probing |    " << p_col1 << "    |  " << (double)p_hit1/cnt << "   |     " << p_col2 << "     |    " << (double)p_hit2/cnt;
       cout << "\n-----------------------------------------------------------------------";
       cout << "\n\n";
   }
};

int main()
{
    srand(time(0));

    int length = 7;

    int n;
    cin >> n;
    //n = 10000;

    HashTable h(n+n);

    vector <key_value_pair> v;
    v = rand_word_gen(length, n);

    int cnt = min(1000, n);

    while(1)
    {
        int choice;
//        cout << "1. Insert_in_Chaining. 2. Insert_in_Double Hashing 3. Insert_in_Custom_Probing. " << endl;
//        cout << "4. Search_in_Chainig. 5. Search_in_Double_Hashing. 6. Search_in_Custom_probing. " << endl;
//        cout << "7. Delete_in_Chainig. 8. Delete_in_Double_hashing. 9. Delete_in_Custom_Probing. " << endl;
//        cout << "10. Print_Chaining. 11. Print_Double_Hashing. 12. Print_Custom_probing. 13. Break. " << endl;

        cout<<"1. Insert.  2 .Search.  3. Delete.  4. Print.  5. Report_Generation  6. Break"<<endl;

        cin>>choice;
        if(choice==1)
        {
            for(int i=0; i<(int) v.size(); i++)
            {
                h.c_insert(v[i]);
                h.c_insert_new(v[i]);
                h.d1_insert(v[i]);
                h.d2_insert(v[i]);
                h.p1_insert(v[i]);
                h.p2_insert(v[i]);
            }
        }
        else if(choice==2)
        {
            int t;
            cout << "Please Enter Choice(t=0 for single value and t=1 for whole hashing) : ";
            cin >> t; //x===0 or 1
            if(t==0)
            {
                string x;
                cin >> x;
                int a = h.c_search(x);
                if(a!=-1)
                    cout<<"Found! The chaining-index is "<< a << endl;
                else
                    cout<<"Couldn't Found in Chaining!\n";

                int b = h.d1_search(x);

                if(b!=-1)
                    cout<<"Found! The Double_hashing-index is "<< b << endl;
                else
                    cout<<"Couldn't Found in Double_Hashing!\n";

                int c = h.p1_search(x);

                if(c!=-1)
                    cout<<"Found! The Custom_Probing-index is "<< c << endl;
                else
                    cout<<"Couldn't Found in Custom_Probing!\n";
            }

            else
            {
                int cnt = min(1000, n);
                random_shuffle(v.begin(), v.end());
                for(int i=0; i<cnt; ++i)
                {
                    int valc = h.c_search(v[i].key);
                    int valx = h.c_search_new(v[i].key);
                    int vald1 = h.d1_search(v[i].key);
                    int vald2 = h.d2_search(v[i].key);
                    int valp1 = h.p1_search(v[i].key);
                    int valp2 = h.p2_search(v[i].key);
                }
            }
        }

        else if(choice==3)
        {
            string x;
            cin>>x;
            h.c_delete(x);
            h.d1_delete(x);
            h.p1_delete(x);
        }
        else if(choice == 4)
        {
            h.c_print();
            h.d1_print();
            h.p1_print();
        }
        else if(choice == 5)
        {
            h.report_Gen(cnt);
        }
        else
        {
            break;
        }

    }
    return 0;
}

//int main()
//{
//    srand(time(0));
//
//    int length = 7;
//
//    int n;
//    cin >> n;
//    //n = 10000;
//
//    HashTable h(n+n);
//
//    vector <key_value_pair> v;
//    v = rand_word_gen(length, n);
//
//    for(int i=0; i<(int) v.size(); i++)
//    {
//        h.c_insert(v[i]);
//        h.c_insert_new(v[i]);
//        h.d1_insert(v[i]);
//        h.d2_insert(v[i]);
//        h.p1_insert(v[i]);
//        h.p2_insert(v[i]);
//        //h.p_insert(v[i]);
//        //h.d_print();
//        //cout << "\n\n";
//    }
//
//    // h.d_print();
//
//    int cnt = min(1000, n);
//    random_shuffle(v.begin(), v.end());
//    for(int i=0; i<cnt; ++i) {
//        int valc = h.c_search(v[i].key);
//        int valx = h.c_search_new(v[i].key);
//        int vald1 = h.d1_search(v[i].key);
//        int vald2 = h.d2_search(v[i].key);
//        int valp1 = h.p1_search(v[i].key);
//        int valp2 = h.p2_search(v[i].key);
//        //int valp = h.p_search(v[i].key);
////        if(valc != v[i].val || valx != v[i].val || vald != v[i].val || valp != v[i].val) {
////            cout << "Not Found! - 404 \n";
////            cout << "( " << v[i].key << " )\n";
////        }
//    }
//
//	// h.c_print();
//    h.report_Gen(cnt);
//
//    return 0;

//    string s;
//    cin >> s;
//
//    int r = h.d1_search(s);
//    cout << r << endl;
//
//    //h.d_print();
//    h.d1_delete(s);
    //h.d_print();
//    h.report_Gen_gen();

    //return 0;
//}

//int main() {
//    srand(time(0));
//
//    HashTable h(20);
//
//    string s;
//    while(cin >> s and s != "q") {
//        if(s == "i") {
//            string k;
//            int val;
//            cin >> k >> val;
//
//            h.d_insert(key_value_pair(k, val));
//        }
//        else if(s == "f") {
//            string k;
//            cin >> k;
//
//            int val = h.d_search(k);
//            cout << val << "\n";
//        }
//        else if(s == "d") {
//            string k;
//            cin >> k;
//
//            h.d_delete(k);
//        }
//    }
//
//    return 0;
//}
