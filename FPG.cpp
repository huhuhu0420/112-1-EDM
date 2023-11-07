#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vec;
typedef vector<vector<string>> transaction;
typedef map<string, int> nmap;
typedef set<string> itemset;
typedef map<itemset, int> cmap;
typedef map<int, cmap> fmap;
typedef cmap::iterator cit;
typedef itemset::iterator sit;
typedef fmap::iterator fit;
#define inf 111110
void setprint(itemset S)
{
    sit x;
    cout << "{";
    for (x = S.begin(); x != S.end(); x++) {
        cout << *x << ",";
    }
    cout << "}";
}
struct node {
    map<string, node*> next;
    node* back;
    string value;
    int counter;
    node()
    {
        back = NULL;
        value = "";
        counter = 1;
    }
    node(string v, node* par)
    {
        back = par;
        value = v;
        counter = 1;
    }
    node(string v, node* par, int inc)
    {
        back = par;
        value = v;
        counter = inc;
    }
};
typedef vector<node*> nlist;
typedef map<int, node*> smap;
typedef map<string, nlist> tdata;
typedef tdata::iterator tdit;
typedef smap::iterator smit;
typedef nmap::iterator nit;
class tree {
public:
    node head;
    tdata info;
    node* curb;
    tree()
    {
        head = node();
        curb = &head;
    }
    void add(string x)
    {
        if ((curb->next).find(x) == (curb->next).end()) {
            node* temp = new node(x, curb);
            curb->next[x] = temp;
            curb = temp;
            info[x].push_back(temp);
        } else {
            node* temp = (curb->next)[x];
            temp->counter = temp->counter + 1;
            curb = temp;
            // cout <<temp->counter<<" "<<x<<"\n";
            // info[x].push_back(temp);
        }
    }
    void add_c(string x, int inc)
    {
        if ((curb->next).find(x) == (curb->next).end()) {
            node* temp = new node(x, curb, inc);
            curb->next[x] = temp;
            curb = temp;
            info[x].push_back(temp);
        } else {
            node* temp = (curb->next)[x];
            temp->counter = temp->counter + inc;
            curb = temp;
            // cout <<temp->counter<<" "<<x<<"\n";
            // info[x].push_back(temp);
        }
    }
    void reset()
    {
        curb = &head;
    }
};
void fmaprint(fmap x)
{
    // fmap is map from int to another map<itemset,int>
    fit it;
    for (it = x.begin(); it != x.end(); it++) {
        cmap y = x[it->first];
        cit it1;
        for (it1 = y.begin(); it1 != y.end(); it1++) {
            setprint(it1->first);
            cout << " --> ";
            cout << (it1->second) << "\n";
        }
    }
}
fmap L;
nmap guide;
bool cmp(const string& x, const string& y)
{
    return guide[x] > guide[y];
}
void tdataprint(tdata x)
{
    tdit it;
    for (it = x.begin(); it != x.end(); it++) {
        cout << it->first << "		---		";
        for (int j = 0; j < x[it->first].size(); j++) {
            cout << x[it->first][j]->counter << " ";
        }
        cout << "\n";
    }
}
int numsup = -1;

void fpgrowth(tree st, itemset init)
{
    // Formation of Frequent pattern bases
    tdit it;
    tdata inx = st.info;
    for (it = inx.begin(); it != inx.end(); it++) {
        itemset init1 = init;
        init1.insert(it->first);
        string cur = it->first;
        nlist X = (st.info)[cur];
        int sum = 0;
        for (int j = 0; j < X.size(); j++) {
            sum += X[j]->counter;
        }
        (L[init1.size()])[init1] = sum;
        transaction T1;
        vec counts;
        tree st1 = tree();
        nmap guide1;
        for (int j = 0; j < X.size(); j++) {
            T1.push_back(vector<string>());
            stack<string> S;
            node* temp = X[j]->back;
            while ((temp->value) != "") {
                S.push(temp->value);
                temp = temp->back;
            }
            while (!S.empty()) {
                T1[T1.size() - 1].push_back(S.top());
                string num = S.top();
                if (guide1.find(num) == guide1.end()) {
                    guide1[num] = X[j]->counter;
                } else {
                    guide1[num] = guide1[num] + X[j]->counter;
                }
                S.pop();
            }
            counts.push_back(X[j]->counter);
        }
        for (int j = 0; j < T1.size(); j++) {
            st1.reset();
            for (int k = 0; k < T1[j].size(); k++) {
                if (guide1[T1[j][k]] >= numsup) {
                    st1.add_c(T1[j][k], counts[j]);
                }
            }
        }
        fpgrowth(st1, init1);
    }
    // tdataprint(st1.info);
    /*
    for (int j=0;j<T1.size();j++)
    {
            for (int k=0;k<T1[j].size();k++)
            {
                    cout <<T1[j][k]<<" ";
            }
            cout <<"  -----  ";
            cout <<counts[j];
            cout <<"\n";
    }*/
}
int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "Usage: ./{exe_name} <filename> <MIN_SUPPORT_COUNT>\n";
        return 0;
    }
    // Input for transaction DB T. I am assuming the data is already given in sorted format
    double minconf;
    numsup = stoi(argv[2]);
    transaction T;
    string filename = argv[1];
    ifstream fp;
    fp.open(filename, ifstream::in);
    string line;
    while (getline(fp, line)) {
        T.push_back(vector<string>());
        stringstream sin;
        string token;
        sin << line;
        int num;
        while (getline(sin, token, ',')) {
            T[T.size() - 1].push_back(token);
            if (guide.find(token) == guide.end()) {
                guide[token] = 1;
            } else {
                guide[token] = guide[token] + 1;
            }
        }
    }
    auto start = chrono::steady_clock::now(), milestone = chrono::steady_clock::now();
    // Sorting step complete
    for (int j = 0; j < T.size(); j++) {
        sort(T[j].begin(), T[j].end(), cmp);
    }
    // Tree creation and element obtaining
    tree st = tree();
    // int cur = -1,tval = INT_MAX;
    for (int j = 0; j < T.size(); j++) {
        st.reset();
        for (int k = 0; k < T[j].size(); k++) {
            if (guide[T[j][k]] >= numsup) {
                st.add(T[j][k]);
            }
        }
    }
    itemset init = itemset();
    fpgrowth(st, init);
    fmaprint(L);
    milestone = chrono::steady_clock::now();
    cout << "time cost: " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";
    return 0;
}
