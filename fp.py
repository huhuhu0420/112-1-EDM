from fpgrowth_py import fpgrowth
from get_author import get_author

data = get_author('./dataset/author_10.txt')
print(len(data))
print('get data')

freqItemSet, rules = fpgrowth(data, minSupRatio=0.2, minConf=0.1)
# print(freqItemSet)
print(rules)  