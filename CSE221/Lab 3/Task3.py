#!/usr/bin/env python
# coding: utf-8

# In[7]:


def dfs(q,a,b,c,p):
    for i in q[c]:
        if p in a:
            break
        if i not in a:
            a+=[i]
            b+=[i]
            dfs(q,a,b,i,p)
    return b
file=open("input1.txt","r")
f_2=file.read().split("\n")
q={}
n=f_2[0]
for i in f_2[1:]:
    x=i.split()
    q[x[0]]=x[1:]

output=dfs(q,["1"],["1"],"1","12")
print(output)
f_2=""
f_3=open("output3.txt","w")
for i in output:
    f_2+=i+" "
f_3.write(f_2.strip(","))


# In[ ]:




