import matplotlib.pyplot as plt
import numpy as np
y1=[]
y2=[]
y3=[]
f1 = open('ThreadA_runtimes.txt', 'r')
for each in f1:
    y1.append(float(each))
f1.close()
f2 = open('ThreadB_runtimes.txt', 'r')
for each in f2:
    y2.append(float(each))
f2.close()
f3= open('ThreadC_runtimes.txt', 'r')
for each in f3:
    y3.append(float(each))
f1.close()
barWidth = 0.3
fig = plt.subplots(figsize =(10, 10))
br1 = np.arange(len(y1))
br2 = [x + barWidth for x in br1]
br3 = [x + barWidth for x in br2]
plt.bar(br1, y1, color ='cornsilk', width = barWidth,
        edgecolor ='black', label ='SCHED_OTHER')
plt.bar(br2, y2, color ='b', width = barWidth,
        edgecolor ='black', label ='SCHED_RR')
plt.bar(br3, y3, color ='violet', width = barWidth,
        edgecolor ='black', label ='SCHED_FIFO')
 
plt.xlabel('Thread Priority', fontweight ='bold', fontsize = 15,style='italic')
plt.ylabel('Process Time', fontweight ='bold', fontsize = 15,style='italic')
plt.xticks([r + barWidth for r in range(10)],
        ['Priority=5\nNice Value:-20', 'Priority=10\nNice Value:-16', 'Priority=20\nNice Value:-12', 'Priority=30\nNice Value:-10', 'Priority=40\nNice Value:-5','Priority=50\nNice Value:0','Priority=60\nNice Value:5','Priority=70\nNice Value:10','Priority=80\nNice Value:15','Priority=90\nNice Value:19'],fontsize=8)
plt.legend()
plt.show()
