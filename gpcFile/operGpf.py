# !/usr/bin/env python
# -*- coding:utf-8 -*-

import os

def operGpf(filename, num):
    inFile = open(filename,"rb")
    outFile = open(filename+"_new", "w")
    for line in inFile.readlines():
        newLine = line.strip().split()
        if(len(newLine) == 2):
            num1 = float(newLine[0])-num
            num2 = float(newLine[1])-num
            outFile.write(str(num1) + " " + str(num2) + "\n")
        else:
            outFile.write(line)
            

def main():
    operGpf("D:\\git\\gpcViewer\\gpcFile\\arrows_old.gpf", 1300)

if __name__=="__main__":
    main()
