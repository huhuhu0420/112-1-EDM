#include <bits/stdc++.h>
using namespace std;
int MIN_SUPPORT = 100;
struct Node {
    string name;
    int count;
    shared_ptr<Node> parent;
    map<string, shared_ptr<Node>> children_map;
};
map<string, vector<pair<int, set<string>>>> author_frequent_itemset;
void insert(shared_ptr<Node> root, vector<string> path)
{
    shared_ptr<Node> cur = root;
    for (auto name : path) {
        bool flag = false;
        if (cur->children_map.find(name) != cur->children_map.end()) {
            cur->children_map[name]->count++;
            cur = cur->children_map[name];
            flag = true;
        }
        if (!flag) {
            shared_ptr<Node> new_node = make_shared<Node>();
            new_node->name = name;
            new_node->count = 1;
            new_node->parent = cur;
            cur->children_map[name] = new_node;
            cur = new_node;
        }
    }
}

void mining(shared_ptr<Node> root, set<string> path)
{
    if (root->children_map.empty())
        return;
    for (auto child : root->children_map) {
        if (path.size() > 0) {
            author_frequent_itemset[child.second->name].push_back(make_pair(child.second->count, path));
        }
        path.insert(child.second->name);
        mining(child.second, path);
        path.erase(child.second->name);
    }
}
void generate_combinations(const std::vector<string>& elements, int length, std::vector<string>& current_combination, int start, vector<pair<int, set<string>>>& result, int count)
{
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
void generate(vector<pair<int, set<string>>>& v, pair<int, set<string>>& target)
{
    if (target.second.size() == 1)
        return;
    vector<string> elements;
    vector<string> current_combination;
    for (auto element : target.second) {
        elements.push_back(element);
    }
    for (int length = 1; length <= elements.size() - 1; ++length) {
        current_combination.clear();
        generate_combinations(elements, length, current_combination, 0, v, target.first);
    }
}
void combination_generate(pair<const string, vector<pair<int, set<string>>>>& author_data, int count, const string& filename)
{
    vector<pair<int, set<string>>>* dt = new vector<pair<int, set<string>>>();
    vector<pair<int, set<string>>>& temp = *dt;
    auto iter_s = author_data.second.begin(), iter_e = author_data.second.end();
    for (auto& single_branch : author_data.second) {
        generate(temp, single_branch);
        temp.emplace_back(single_branch);
    }
    int l = temp.size();
    for (int i = 0; i < l; i++) {
        for (int j = i + 1; j < l; j++) {
            if (temp[i].second == temp[j].second) {
                temp[i].first += temp[j].first;
                temp[j].first = 0;
            }
        }
    }
    erase_if(temp, [](pair<int, set<string>> p) { return p.first < MIN_SUPPORT; });
    ofstream fout("result_" /*+ to_string(static_cast<int>(floor(count / 10000)))*/ + filename, ios::app);
    for (auto p : temp) {
        fout << "{" << author_data.first << ", ";
        for (auto s : p.second) {
            fout << s;
            if (s != *p.second.rbegin())
                fout << ", ";
        }
        fout << "}: " << p.first << "\n";
    }
    fout.close();
    delete dt;
}

int main(int argc, char* argv[])
{
    if (argc != 3) {
        cout << "Usage: ./{exe_name} <filename> <MIN_SUPPORT_COUNT>\n";
        return 0;
    }
    string filename = argv[1];
    MIN_SUPPORT = atoi(argv[2]);
    set<string> s;
    map<string, int> m;
    auto start = chrono::steady_clock::now(), milestone = chrono::steady_clock::now();
    // read file
    // ifstream fin("part.txt");
    // start reading file;
    ifstream fin(filename);
    vector<vector<string>> v;
    string line, token;
    while (getline(fin, line)) {
        if (/*line.find(',') == string::npos|| */ line.empty())
            continue;
        stringstream ss(line);
        vector<string> temp;
        while (getline(ss, token, ',')) {
            temp.push_back(token);
            if (s.find(token) == s.end()) {
                s.insert(token);
                m[token] = 1;
            } else {
                m[token]++;
            }
        }
        v.push_back(temp);
    }
    map<string, int> mg3;
    for (auto i : s) {
        if (m[i] >= MIN_SUPPORT) {
            mg3[i] = m[i];
        }
    }

    for (auto& author_vec : v) {
        erase_if(author_vec, [&mg3](string author) { return mg3.find(author) == mg3.end(); });
    }
    erase_if(v, [](vector<string> author_vec) { return author_vec.empty(); });
    for (auto& author_vec : v) {
        sort(author_vec.begin(), author_vec.end(), [&mg3](string a, string b) { return mg3[a] > mg3[b]; });
    }
    cout << "data clean done\n";
    cout << "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";

    shared_ptr<Node> root = make_shared<Node>();
    root->name = "root";
    root->count = 0;
    root->parent = NULL;
    for (auto author_vec : v) {
        insert(root, author_vec);
    }
    cout << "insert done" << endl;
    cout << "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";

    mining(root, set<string>());
    cout << "basic mining done" << endl;
    cout << "segment cost " << chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - milestone).count() << " ms\n";
    milestone = chrono::steady_clock::now();
    cout << "already pass " << chrono::duration_cast<chrono::milliseconds>(milestone - start).count() << " ms\n";
    int fs = author_frequent_itemset.size(), count = 0;
    // delete origin result.txt from last run
    ofstream fout("result_" + filename, ios::trunc);
    for (auto& author_data : author_frequent_itemset) {
        count++;
        combination_generate(author_data, count, filename);
        if (count % 100 == 0)
            cout << "finish " << count << "/" << fs << '\n';
    }
    return 0;
}
