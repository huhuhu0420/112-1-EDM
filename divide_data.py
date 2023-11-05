
from get_author import get_author
import networkx as nx

def test():
    datas = get_author('./dataset/author.txt')
    print("get data")
    # datas = [['g'], ['a', 'b', 'c'], ['e', 'f', 'g'], ['a', 'b', 'c', 'd'], ['a', 'b', 'c', 'd'], ['a', 'b', 'c', 'd', 'z'], ['e'], ['z', 'f']]
    groups = []
    flag = 0
    G=nx.Graph()
    for d in datas:
        nx.add_path(G, d)
    components = list(nx.connected_components(G))
    # print(components)
    for component in components:
        group = []
        for data in datas:
            if component.issuperset(data):
                group.append(data)
        groups.append(group)
    
    i = 0
    for group in groups:
        path = './divide_data/' + str(i) + '.txt'
        # print(group)
        with open(path, 'w') as f:
            for g in group:
                f.writelines(','.join(g) + '\n')
        i += 1
    
test()