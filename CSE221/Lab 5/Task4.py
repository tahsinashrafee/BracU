

file=open("input4.txt", "r")
file_2=file.read().split()
l=[int(i) for i in file_2]
l_2=[]
for i in range(0,len(l),2):
    if l[i]==0 and l[i+1]==0:
        l_2=l_2
    else:
        s=0
        for j in range(l[i],l[i+1]+1):
            if str(j**(1/2)).split('.')[1]=='0':
                s+=1
        l_2.append(s)
res=''
for i in l_2:
    res+=f'{str(i)}\n'
file=open("output4.txt","w")
file.write((res))
file.close()
print(res)




