
from get_author import get_author

def test():
    datas = get_author('./dataset/author.txt')
    # datas = [['a', 'b', 'c'], ['e', 'f', 'g'], ['a', 'b', 'c', 'd'], ['a', 'b', 'c', 'd'], ['a', 'b', 'c', 'd', 'z'], ['g', 'e']]
    divides = []
    flag = 0
    for data in datas:
        dataset  = set(data)
        for divide in divides:
            flag = 0
            if dataset.isdisjoint(divide[0]) == False:
                # print(dataset, divide[0])
                flag = 1
            if flag == 1:
                divide.append(dataset)
                break
        if flag == 0:
            divides.append([dataset])
    
    i = 0
    for divide in divides:
        path = './divide_data/' + str(i) + '.txt'
        print(divide)
        with open(path, 'w') as f:
            for d in divide:
                f.writelines(','.join(d) + '\n')
        i += 1
    
test()