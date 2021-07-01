import sys
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) >  1:
    data = np.loadtxt(sys.argv[1])

    plt.matshow(data)
    plt.savefig("mat.png")
