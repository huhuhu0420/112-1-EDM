
class node:
    name: str
    count: int


def insert(tree: list, data: list):
    item = data[0]
    flag = False
    for i in tree:
        if item in i.keys():
            i[item] += 1
            flag = True
            break
    if not flag:
        tree.append({item: 1})
    now = None
    for i in tree:
        if item in i.keys():
            now = i
            break
    if len(data[1:]) > 0:
        if "child" not in now:
            now["child"] = []
        insert(now["child"], data[1:])


def printTree(tree: dict):
    for i in tree:
        print(i, tree[i])
        if i == "child":
            printTree(tree[i])


def main():
    FrequentHeaderTable = {}
    FP_tree = {'root': 0, 'child': []}
    dataSet = []
    # n = int(input("Enter the number of transactions: "))
    # for i in range(n):
    #     dataSet.append(input().split())
    # minSup = int(input("Enter the minimum support: "))
    # dataSet = [['1', '2', '3', '4'], ['1', '2', '4'], ['1', '2'], ['2', '3', '4'], ['2', '3']]
    dataSet = [['M', 'O', 'N', 'K', 'E', 'Y'], ['D', 'O', 'N', 'K', 'E', 'Y'], ['M', 'A', 'K', 'E'], ['M', 'U', 'C', 'K', 'Y'], ['C', 'O', 'O', 'K', 'I', 'E']]
    #remove duplicate
    tp = []
    for i in dataSet:
        tmp = []
        for j in i:
            if j not in tmp:
                tmp.append(j)
        tp.append(tmp)
    dataSet = tp
    print(dataSet)
    minSup = 3
    for i in dataSet:
        for j in i:
            if j in FrequentHeaderTable:
                FrequentHeaderTable[j] += 1
            else:
                FrequentHeaderTable[j] = 1
    HeaderTable = {i: FrequentHeaderTable[i] for i in FrequentHeaderTable}
    FrequentHeaderTable = {i: FrequentHeaderTable[i] for i in FrequentHeaderTable if FrequentHeaderTable[i] >= minSup}
    for data in dataSet:
        nl = []
        for item in data:
            if HeaderTable[item] >= minSup:
                nl.append(item)
        data = nl
        data.sort(key=lambda x: FrequentHeaderTable[x], reverse=True)
        if len(data) > 0:
            print(data)
            insert(FP_tree['child'], data)
    
    print(FP_tree)
    # pattern mining
    print(FrequentHeaderTable)
    freq_1 = []
    for i in FrequentHeaderTable:
        freq_1.append([i, FrequentHeaderTable[i]])
    freq_1.sort(key=lambda x: x[1], reverse=True)
    print(freq_1)


main()
"""
# TEST data
5
1 2 3 4
1 2 4
1 2
2 3 4
2 3 
"""
