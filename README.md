# FP_Growth.cpp Usage Guide

## Environment

Windows MSYS2/UCRT64 

g++.exe (Rev2, Built by MSYS2 project) 13.2.0
## Compilation


Compile the program using the following command:

```bash
g++ -std=c++20 -O3 -fno-stack-limit FP_Growth.cpp -o <exe_name>
```
you might need to find you own lovely compiler that support c++20 and corresponding flag

## Execution

Run the compiled executable with the following command:

```bash
./<exe_name> <filename> <minimum_support_count>
```

## Troubleshooting

If the program freezes for more than 5 minutes, it is likely due to insufficient RAM. The program will not stop but may take an extremely long time to complete. To address this issue, you have a few options:

1. Increase RAM: Upgrade your system's RAM capacity.
2. Modify File or Minimum Support Count: Adjust the input file or minimum support count to reduce computational load.

Even in cases where the program takes a long time to complete, it may still output partial patterns before finishing.

> Remember, if it feels like your program is taking an eternity to finish, just think of it as an opportunity to practice patience, the most underrated skill in programming!

