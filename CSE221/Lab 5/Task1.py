
file = open("input1.txt","r")
file_2=file.read()
file.close()
list=(file_2.split("\n")[1:])
l_2=[]

for i in list:
    l_3=i.split()
    if l_3==[]:
        continue
    else:
        st,end=l_3[0],l_3[1]
    l_2+=[[int(end),int(st)]]

s=1
l_2.sort()
t=l_2[0][0]

total=""
total+=str(l_2[0][1])+" "+str(l_2[0][0])+"\n"
for i in l_2[1:]:
    if i[1]==t or i[1]>t:
        s+=1
        t=i[0]
        total+=str(i[1])+" "+str(i[0])+"\n"

total=str(s)+"\n"+total
file =open("output1.txt","w")
file.write(total)
file.close()
print(total)





