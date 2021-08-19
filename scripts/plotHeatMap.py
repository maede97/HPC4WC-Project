import sys
import matplotlib.pyplot as plt
import numpy as np
import subprocess
import os
import seaborn as sns
import pandas as pd

# be in subdirectory build/sry/executables and type make && ./block_i > ../../../scripts/output/name.txt
# run the file in subfolder scripts python3 plotHeatMap.py
data = open("output/out.txt","r")
number = 0
blocking_i = []
blocking_j = []
blocking_ij = []

time_i = []
time_j = []
time_ij = []

readTimeflag = 0


it = 0
for lines in data.readlines():
    if "Performing" in lines:
        number = lines.split("over ")[1].split(" ")[0]
    if "==================" in lines:
        break
    if "-blocking-size-i" in lines and "-blocking-size-j" in lines:
        blocking_ij.append([int(lines.split("-i ")[1].split(" ")[0]),
                            int(lines.split("-j ")[1].split("\n")[0])])
        readTimeflag = 1
    elif "-blocking-size-i" in lines:
        blocking_i.append(int(lines.split("-i ")[1].split(" ")[0]))
        readTimeflag = 2
    elif "-blocking-size-j" in lines:
        blocking_j.append(int(lines.split("-j ")[1].split("\n")[0]))
        readTimeflag = 3
    if "on average" in lines:
        if readTimeflag == 1:
            time_ij.append(float(lines.split("took ")[1].split(" seconds")[0]))
            readTimeflag = 0
        elif readTimeflag == 2:
            time_i.append(float(lines.split("took ")[1].split(" seconds")[0]))
            readTimeflag = 0
        elif readTimeflag == 3:
            time_j.append(float(lines.split("took ")[1].split(" seconds")[0]))
            readTimeflag = 0


sns.set_theme()


idx_i = [x[0] for x in blocking_ij]
idx_j = [x[1] for x in blocking_ij]
print(idx_i)
print(idx_j)
df = pd.DataFrame({"blocking i": idx_i, "blocking j":idx_j, "times ij":time_ij})
result = df.pivot(index="blocking i", columns="blocking j", values="times ij")
cmap = sns.diverging_palette(220, 20, as_cmap=True)
sns.heatmap(result,annot=True, fmt="g",cmap=cmap)
plt.title("Heatmap of ij-blocking")
plt.show()