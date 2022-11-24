import matplotlib.pyplot as plt
import numpy as np
y1=[]
y2=[]
y3=[]
f1 = open('output_q1_2.txt', 'r')
y=[]
for each in f1:
    y.append(float(each))
f1.close()
y1.append(y[0])
y2.append(y[1])
y3.append(y[2])
barWidth = 0.3
fig = plt.subplots(figsize =(3,1))
br1 = np.arange(len(y1))
br2 = [x + barWidth for x in br1]
br3 = [x + barWidth for x in br2]
plt.bar(br1, y1, color ='cornsilk', width = barWidth,
        edgecolor ='black', label ='SCHED_OTHER')
plt.bar(br2, y2, color ='b', width = barWidth,
        edgecolor ='black', label ='SCHED_RR')
plt.bar(br3, y3, color ='violet', width = barWidth,
        edgecolor ='black', label ='SCHED_FIFO')
 
plt.xlabel('Process Priority', fontweight ='bold', fontsize = 20,style='italic')
plt.ylabel('Process Time', fontweight ='bold', fontsize = 20,style='italic')
plt.xticks([r + barWidth for r in range(1)],
        ['Priority=1\nNice Value:0'],fontsize=10)
plt.legend()
plt.show()
