import sys
import matplotlib.pyplot as plt
import numpy as np

if len(sys.argv) == 3:
    data = np.loadtxt(sys.argv[1])

    plt.matshow(data)
    plt.savefig(sys.argv[2])

else:
    print("showmat.py <[in]mat-file> <[out]png-file>")