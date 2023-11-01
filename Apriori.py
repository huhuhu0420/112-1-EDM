# calculate the execution time
import time


def Apriori(data, min_sup, min_conf):
    freq = {}
    sup_c = min_sup * len(data)
    for transaction in data:
        for item in transaction:
            freq[item] = freq.get(item, 0) + 1
    freq_1 = []
    for k in freq.keys():
        if freq[k] >= sup_c:
            freq_1 += [k]
    freq_1 = sorted(freq_1)
    freq_1 = [[i] for i in freq_1]
    freqSet = []
    freqSet.append(freq_1)
    k = 1
    while True:
        k += 1
        freqSet.append(generate(freqSet[-1]))
        if len(freqSet[-1]) == 0:
            break
        for i in freqSet[-1]:
            count = 0
            for j in data:
                if set(i).issubset(set(j)):
                    count += 1
            if count < sup_c:
                freqSet[-1].remove(i)
        print(freqSet[-1].__len__())
    print(freqSet)


def generate(freqSet):
    result = []
    for i in range(len(freqSet)):
        for j in range(i + 1, len(freqSet)):
            if freqSet[i][:-1] == freqSet[j][:-1] and freqSet[i][-1] < freqSet[j][-1]:
                result.append(freqSet[i] + [freqSet[j][-1]])
                if (result[-1][1:] not in freqSet):
                    result.pop()
    return result


def join(f1, f2):
    return f1.union(f2)


def read_data(file_name):
    data = []
    with open(file_name, 'r') as f:
        for line in f.readlines():
            data.append(list(map(int, line.strip().split(' '))))
    return data


if __name__ == '__main__':
    data = read_data('pumsb_star.dat')
    # data = [['M', 'O', 'N', 'K', 'E', 'Y'], ['D', 'O', 'N', 'K', 'E', 'Y'], ['M', 'A', 'K', 'E'], ['M', 'U', 'C', 'K', 'Y'], ['C', 'O', 'O', 'K', 'I', 'E']]
    data.sort()
    # print(data)
    start = time.time()
    Apriori(data, 0.6, 0.8)
    end = time.time()
    print(f'generating frequent itemsets takes {end - start} seconds')
    # generating frequent itemsets takes 36.05696654319763 seconds
