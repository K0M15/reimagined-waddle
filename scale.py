#!/usr/bin/env python3
from sys import argv

def scale(filename:str, scale:float, prec:bool):
    f = None
    try:
        f = open(filename, "r")
    except OSError as e:
        print("File could not be opened: ", e)
        exit(1)
    ctr = 0
    while True:
        line = f.readline()
        if not line:
            break
        parts = line.split(' ')
        if (parts[0] == "tr"):
            try:
                vals = [part.split(',') for part in parts[1:4]]
                conv = [[float(val)*scale for val in block] for block in vals]
                if prec:
                    print(f"tr {conv[0][0]:.5f},{conv[0][1]:.5f},{conv[0][2]:.5f} {conv[1][0]:.5f},{conv[1][1]:.5f},{conv[1][2]:.5f} {conv[1][0]:.5f},{conv[1][1]:.5f},{conv[1][2]:.5f} {parts[4]}", end="")
                else:
                    print(f"tr {conv[0][0]:.0f},{conv[0][1]:.0f},{conv[0][2]:.0f} {conv[1][0]:.0f},{conv[1][1]:.0f},{conv[1][2]:.0f} {conv[1][0]:.0f},{conv[1][1]:.0f},{conv[1][2]:.0f} {parts[4]}", end="")
            except:
                print( f"Error on line {ctr} converting tr values" )
                exit(1)
        else:
            print(line)
    print()
                
    
def usage():
    print("Usage: ./scale.py <filename> <scalefactor>")
    print("You may redirect the output to a file")
    exit(1)

if __name__ == "__main__":
    if not (len(argv) == 3 or len(argv) == 4):
        usage()
    newscale = None
    try:
        newscale = float(argv[2])
    except ValueError:
        print("Wrong value for scale, must be convertable to float")
        usage()
    prec = True if "-prec" in argv else False
    scale(argv[1], newscale, prec)