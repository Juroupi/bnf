import sys
sys.path.append("./python")
from bnf import *

g = Grammar("data/par.bnf")
nt = g["W"]
n = 6

print(g)
print("number of element of size", n, ":", nt.getCardinality(n))
print("elements of size", n, ":", nt.getElements(n))
print("first element of size", n, ":", nt.getElement(n, 0))