
with open('./mushroom_1000.dat', 'r') as f:
    data = []
    for line in f.readlines():
        data.append(','.join(list(map(str, line.strip().split(' ')))))
    with open('./mushroom_1000.txt', 'w') as f2:
        for line in data:
            f2.write(line + '\n')