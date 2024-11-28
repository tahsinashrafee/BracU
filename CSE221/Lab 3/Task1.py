#!/usr/bin/env python
# coding: utf-8

# In[6]:


file=open("input1.txt","r")
f_2=file.read().split("\n")
D={}
for i in f_2[1:]:
    l=i.split()
    D[l[0]]=l[1:]
print(D)
f_3=open("output1.txt","w")
f_3=open("output1.txt","a")
for x,y in D.items():
    f_3.write(x+" - ")
    for i in y:
        f_3.write(i+" - ")
    f_3.write("\n")


# In[ ]:




