
def get_author():
    authors = []

    with open ('./dataset/author.txt') as f:
        while True:
            line = f.readline()
            if not line:
                break
            line = line.split(',')
            line[-1] = line[-1].strip()
            authors.append(line)
    return authors