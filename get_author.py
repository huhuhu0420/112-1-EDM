
def get_author(path):
    authors = []

    with open (path, encoding='utf-8') as f:
        while True:
            line = f.readline()
            if not line:
                break
            line = line.split(',')
            line[-1] = line[-1].strip()
            authors.append(line)
    return authors