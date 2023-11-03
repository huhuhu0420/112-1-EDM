import pandas as pd
from mlxtend.frequent_patterns import fpgrowth
from get_author import get_author
from mlxtend.preprocessing import TransactionEncoder

dataset = get_author('./dataset/author_10000.txt')
te = TransactionEncoder()
te_ary = te.fit(dataset).transform(dataset)
df = pd.DataFrame(te_ary, columns=te.columns_)
itemset = fpgrowth(df, min_support=0.001, use_colnames=True)
print(itemset)
