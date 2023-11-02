#include <bits/stdc++.h>
using namespace std;
struct Node{
    string name;
    int count;
    Node* parent;
    vector<Node*> children;
};
map<string, vector<pair<int, set<string>>>> frequent_itemsets;
void insert(Node* root, vector<string> path){
    Node* cur = root;
    for (auto name : path){
        bool flag = false;
        for (auto child : cur->children){
            if (child->name == name){
                child->count++;
                cur = child;
                flag = true;
                break;
            }
        }
        if (!flag){
            Node* new_node = new Node;
            new_node->name = name;
            new_node->count = 1;
            new_node->parent = cur;
            cur->children.push_back(new_node);
            cur = new_node;
        }
    }
}
void mining(Node* root, set<string> path){
    if (root->children.empty()) return;
    for (auto child : root->children){
        if (path.size() > 1){
            frequent_itemsets[child->name].push_back(make_pair(child->count, path));
        }
        path.insert(child->name);
        mining(child, path);
        path.erase(child->name);   
    }
}

int main(){
    set<string> s;
    map <string, int> m;
    // read file
    // ifstream fin("part.txt");
    ifstream fin("author.txt");
    vector <vector <string> > v;
    string line, token;
    while(getline(fin, line)){
        // split by comma
        // if there is no comma or empty line, continue
        if(/*line.find(',') == string::npos|| */line.empty()) continue;
        stringstream ss(line);
        vector <string> temp;
        while(getline(ss, token, ',')){
            // remove space
            // token.erase(remove(token.begin(), token.end(), ' '), token.end());
            // insert into set
            temp.push_back(token);
            if (s.find(token) == s.end()){
                s.insert(token);
                m[token] = 1;
            }
            else{
                m[token]++;
            }
        }
        v.push_back(temp);
    }
    map<string, int> mg3;
    for (auto i : s){
        // cout << i << " " << m[i] << endl;
        if (m[i] >= 3) {
            mg3[i] = m[i];
        }
    }

    for (auto & author_vec : v){
        erase_if(author_vec, [&mg3](string author){return mg3.find(author) == mg3.end();});
    }
    erase_if(v, [](vector<string> author_vec){return author_vec.empty();});
    for (auto author_vec : v){
        sort(author_vec.begin(), author_vec.end(), [&mg3](string a, string b){return mg3[a] > mg3[b];});
    }
    int total = 0, vs = v.size();
    Node* root = new Node;
    root->name = "root";
    root->count = 0;
    root->parent = NULL;
    for (auto author_vec : v){
        total++;
        insert(root, author_vec);
        if (total % 100000 == 0){
            cout << total << "/" << vs << endl;
        }
    }
    cout << "insert done" << endl;
    mining(root, set<string>());
    cout << "mining done" << endl;
    for (auto &author_data : frequent_itemsets){
        int l = author_data.second.size();
        for (int i = 0; i < l; i++){
            for (int j = i + 1; j < l; j++){
                if(i == j)continue;
                if (author_data.second[i].second == author_data.second[j].second){
                    author_data.second[i].first += author_data.second[j].first;
                    author_data.second[j].first = 0;
                }
            }
        }
        erase_if(author_data.second, [](pair<int, set<string>> p){return p.first < 3;});
    }
    erase_if(frequent_itemsets, [](pair<string, vector<pair<int, set<string>>>> p){return p.second.empty();});
    cout << "erase done" << endl;
    ofstream fout("result.txt");
    for (auto author_data : frequent_itemsets){
        for (auto p : author_data.second){
            fout << "{"<<author_data.first << ", ";
            for (auto s : p.second){
                fout << s ;
                if (s != *p.second.rbegin()) fout << ", ";
            }
            fout << "}: " << p.first << " times" << "\n";
        }
        // fout << "\n";
    }

}   
