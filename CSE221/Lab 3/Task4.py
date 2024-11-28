#!/usr/bin/env python
# coding: utf-8

# In[23]:


my_file = open("input4.txt", "r")
my_read_line = my_file.readlines()

a, b = my_read_line[1].split()
val = [[] for i in range(int(b))]

for i in range(2, 4):
    c, d = my_read_line[i].split()
    c, d = int(c), int(d)
    val[c - 1].append(d)
print(val, 'a')
x, y = my_read_line[4].split()
val_2 = [[] for i in range(int(y))]

for i in range(5, 9):
    c, d = my_read_line[i].split()
    c, d = int(c), int(d)
    val_2[c - 1].append(d)
print(val_2, 'a1')
vis = [0 for x in range(len(val))]
Result = []
q = []


def bfs(vis, g, n, p):
    vis[n - 1] = 1
    q.append(n)
    while q:
        n_2 = q.pop(0)
        print(n_2, 'f')
        if n_2 != p:
            print(g[n_2 - 1])
            for i in g[0:n_2 - 1]:
                if vis[i - 1] != 0:
                    continue
                vis[i - 1] = 1
                q.append(i)
        else:
            break
        print(n_2, 'f')
        Result.append(n_2)
    print('r', Result)
    return Result


ans1 = bfs(vis, val, 1, a)

print(ans1)

vis_2 = [0 for x in range(len(val_2))]
res_2 = []
q_2 = []


def bfs(vis_2, g, n, p):
    vis_2[n - 1] = 1
    q_2.append(n)
    while q:
        n_2 = q_2.pop(0)
        res_2.append(n_2)
        if n_2 == p:
            break
        else:

            for i in g[n_2 - 1]:
                if vis_2[i - 1] != 0:
                    continue
                vis_2[i - 1] = 1
                q_2.append(i)

    print('r2', res_2)
    return res_2


ans2 = bfs(vis_2, val_2, 1, x)
f_3 = open("output4.txt", "w")
f_3 = open("output4.txt", "a")
for i in Result:
    f_3.write(str(i))
for i in res_2:
    f_3.write(str(i))


# In[ ]:





# In[ ]:




