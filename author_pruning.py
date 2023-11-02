from get_author import get_author

def author_pruning(path):
    authors = get_author(path)
    with open('./dataset/pruning_author.txt', 'w') as f:
        for a in authors:
            if len(a) > 1:
                f.writelines(','.join(a) + '\n')

            
def main():
    author_pruning('./dataset/author.txt')

main()