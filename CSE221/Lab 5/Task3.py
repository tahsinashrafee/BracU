

file=open("input3.txt", "r")
file_2=file.read().split()[1:]
list=[int(i) for i in file_2[:-1]]
list.sort()
l_2=file_2[-1]

vis_1=[]
vis_2=[]
l_3=0
l_4=0
s=""

for i in l_2:
    if i=="J":
        a=0
        for j in list:
            if j not in vis_1:
                a=j
                break
        l_3+=a
        vis_1+=[a]
        s+=str(a)
    else:
        a=0
        for i in vis_1[::-1]:
            if j not in vis_2:
                a=j
                break
        l_4+=a
        vis_2 += [a]
        s+=str(a)
res=f'{s} \n'
res+=f"Jack will list for {str(l_3)} hours\n"
res+=f"Jill will list for {str(l_4)} hours"
file=open("output3.txt","w")
file.write((res))
file.close()
print(res)





