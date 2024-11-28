

file = open("input2.txt","r")
file_2=file.read()
file.close()
list=(file_2.split("\n"))
l_2=[]

for tasks in list[1:]:
    st,end=tasks.split()
    l_2+=[[int(end),int(st)]]
a=str(list[0].split()[1])
l_2.sort()
s=1
q=[]
b=int(a)
sum=0
for i in l_2:
    if b!=0:
        sum+=1
        b-=1
        q+=[i[0]]
    else:
        for j in range(len(q)):
            if q[j]<=i[1]:
                q.pop(j)
                q+=[i[0]]
                sum+=1

file=open("output2.txt","w")
file.write(str(sum))
file.close()
print(sum)





