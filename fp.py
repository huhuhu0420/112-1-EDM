from fpgrowth_py import fpgrowth
from get_author import get_author

data = get_author()
print(len(data))
print('get data')

freqItemSet, rules = fpgrowth(data, minSupRatio=0.000001, minConf=0.000001)
print(freqItemSet)
print(rules)  