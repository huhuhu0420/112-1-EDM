#include <bits/stdc++.h>
using namespace std;
struct Node{
    string name;
    int count;
    Node* parent;
    map<string, Node*> children_map;
};
map<string, vector<pair<int, set<string>>>> frequent_itemsets;
void insert(Node* root, vector<string> path){
    Node* cur = root;
    for (auto name : path){
        bool flag = false;
        // for (auto child : cur->children){
            
        //     if (child->name == name){
        //         child->count++;
        //         cur = child;
        //         flag = true;
        //         break;
        //     }
        // }
        if (cur->children_map.find(name) != cur->children_map.end()){
            cur->children_map[name]->count++;
            cur = cur->children_map[name];
            flag = true;
        }
        if (!flag){
            Node* new_node = new Node;
            new_node->name = name;
            new_node->count = 1;
            new_node->parent = cur;
            cur->children_map[name] = new_node;
            cur = new_node;
        }
    }
}

void mining(Node* root, set<string> path){
    if (root->children_map.empty()) return;
    for (auto child : root->children_map){
        if (path.size() > 1){
            frequent_itemsets[child.second->name].push_back(make_pair(child.second->count, path));
        }
        path.insert(child.second->name);
        mining(child.second, path);
        path.erase(child.second->name);   
    }
}
void generate_combinations(const std::vector<string>& elements, int length, std::vector<string>& current_combination, int start, vector<pair<int, set<string>>>& result, int count) {
    if (length == 0) {
        result.emplace_back(make_pair(count, set<string>(current_combination.begin(), current_combination.end())));
        return;
    }

    for (int i = start; i < elements.size(); ++i) {
        current_combination.push_back(elements[i]);
        generate_combinations(elements, length - 1, current_combination, i + 1, result, count); // Start from the next index to avoid duplicates
        current_combination.pop_back();
    }
}
void generate(vector<pair<int, set<string>>>& v, pair<int, set<string>> target) {
    if (target.second.size() == 1) return;
    vector<pair<int, set<string>>> temp;
    vector<string> elements;
    for (auto element: target.second){
        elements.push_back(element);
    }
    for (int length = 1; length <= elements.size(); ++length) {
        std::vector<string> current_combination;
        generate_combinations(elements, length, current_combination, 0, temp, target.first);
        v.insert(v.end(), temp.begin(), temp.end());
    }
    
}


int main(){
    set<string> s;
    map <string, int> m;
    auto start = chrono::steady_clock::now(), milestone = chrono::steady_clock::now();
    // read file
    // ifstream fin("part.txt");
    // start reading file;
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
    cout << "data clean done\n"; 
    cout<< "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";
 
    Node* root = new Node;
    root->name = "root";
    root->count = 0;
    root->parent = NULL;
    for (auto author_vec : v){
        insert(root, author_vec);
    }
    cout << "insert done" << endl;
    cout<< "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";
 
    mining(root, set<string>());
    cout << "basic mining done" << endl;
    cout<< "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";
 
    for (auto &author_data : frequent_itemsets){
        vector<pair<int, set<string>>> temp;
        for (auto single_branch : author_data.second){
            generate(temp, single_branch);
        }
        for (auto p : temp){
            author_data.second.push_back(p);
        }

        int l = author_data.second.size();
        for (int i = 0; i < l; i++){
            for (int j = i + 1; j < l; j++){
                if (author_data.second[i].second == author_data.second[j].second){
                    author_data.second[i].first += author_data.second[j].first;
                    author_data.second[j].first = 0;
                }
            }
        }
        erase_if(author_data.second, [](pair<int, set<string>> p){return p.first < 3;});
    }
    erase_if(frequent_itemsets, [](pair<string, vector<pair<int, set<string>>>> p){return p.second.empty();});
    cout << "total mining done\n"; 
    cout<< "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";
    ofstream fout("result.txt");
    for (auto author_data : frequent_itemsets){
        for (auto p : author_data.second){
            fout << "{"<<author_data.first << ", ";
            for (auto s : p.second){
                fout << s ;
                if (s != *p.second.rbegin()) fout << ", ";
            }
            fout << "}: " << p.first << "\n";
        }
        // fout << "\n";
    }
    cout << "output done\n";
    cout << "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()-milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";

}   
