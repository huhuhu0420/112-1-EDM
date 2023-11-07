# 112_1_EDM

# HW02 
## 6.7

### (a) Apriori
#### Environment
```
python 3.11
```
#### Usage
```
python Apriori.py <filename> <min_support_rate>
```
### (b) FP-Growth

#### Environment
```
g++.exe (GCC) 11.2.0
```
#### compilation
```
g++ FPG.cpp -o fpg
```
#### usage
```
./fpg <filename> <min_support_count>
```

#### test01 - mushroom_1000
* apriori
```
python Aprori.py mushroom_1000.txt 0.6
```
* fp-growth
```command
./fpg mushroom_1000.txt 600
```

#### test02 - pumsb_star
* aprori
```
python Apriori.py pumsb_star.txt 0.6
``` 

* fp-growth
```
./fpg pumsb_star.txt 29000
```
|  | apriori | fp-growth |
| -- | -- | -- |
| mushroom_1000.txt | 4.48 s | 1.504 s |
| pumsb_star.txt | 15.37 s | 5.237 s |

## 6.15
### (a)
```
./fpg author.txt 200
```
time cost: 28.8 sec

### (b)
由於對於本資料Null invariance非常高，不能使用x^2, lift指標，kulczynski優點在於保留各自的sup，不會因為極端值影響。
每個教授共同合作的比例相較整個資料集非常低，導致pattern交集的sup都很小，為了保留每個relateion中的sup，因此kulczynski為較好的選擇。

## dataset

Ensure that your input file contains multiple lines indicating different transactions, with each item separated by a space.

dblp author dataset: [link](https://drive.google.com/file/d/1kcrMd2FV02W_7-toUJlrL-ULgg3L_4v7/view?usp=drive_link)

## Troubleshooting

If the program freezes for more than 5 minutes, it is likely due to insufficient RAM. The program will not stop but may take an extremely long time to complete. To address this issue, you have a few options:

1. Increase RAM: Consider upgrading your system's RAM capacity.
2. Modify File or Minimum Support Count: Adjust the input file or minimum support count to reduce computational load.

Even in cases where the program takes a long time to complete, it may still output partial patterns before finishing.

> Remember, if it feels like your program is taking an eternity to finish, just think of it as an opportunity to practice patience, the most underrated skill in programming!
