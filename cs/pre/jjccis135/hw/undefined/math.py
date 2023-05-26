#!/usr/bin/env python3


#bk = (k − 1)3 + 4k + 2


def math():
    for i in range(5):
        calc = (i - 1)**3 + 4*i + 2
        print(calc)

def math2():
    thesum = 0
    for i in range(1,4):
        calc = 3*i**2 + 9
        thesum += calc
    print(thesum)

def math3():
    theproduct = 0
    for i in range(3, 10):
        calc = (i*(i+2) / (i - 1) * (i + 1))
        theproduct = theproduct * calc
        
    print(theproduct)
def main():
    """ main """
    math3()

    return 0


if __name__ == '__main__':
    main()





















