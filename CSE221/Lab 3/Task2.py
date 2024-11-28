#!/usr/bin/env python
# coding: utf-8

# In[7]:


def bfs(a,b,c):
    l_1=[]
    l_2=[a]
    l_3=l_2[0]+" "
    while len(l_2)!=0:
        for i in c[l_2[0]]:
            if i not in l_1:
                l_3+=i+" "
            if i==b:
                l_2=[]
                break
            l_2+=[i]
            l_1+=[i]
        if len(l_2)!=0:
            l_2.pop(0)
        else:
            break
    return (l_3).strip(",")

file=open("input1.txt","r")
f_2=file.read().split("\n")
c={}
for i in f_2[1:]:
    l= i.split()
    c[l[0]] = l[1:]
l_3=(bfs("1","12",c))
f_3=open("output2.txt","w")
f_3.write(l_3)


# In[ ]:




