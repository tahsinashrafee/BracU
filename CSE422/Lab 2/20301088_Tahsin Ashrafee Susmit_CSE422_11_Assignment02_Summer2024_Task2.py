import random

def two_point(p1, p2):

    cut_1 = random.randint(1, len(p1) - 2)
    cut_2 = random.randint(cut_1 + 1, len(p1) - 1)
    c1 = p1[:cut_1] + p2[cut_1:cut_2] + p1[cut_2:]
    c2 = p2[:cut_1] + p1[cut_1:cut_2] + p2[cut_2:]
    return c1, c2

def list_to_string(list):
    string = ''
    for i in list:
        string += str(i)
    return string

p1 = [0, 0, 0, 1, 1, 1, 0, 0, 0]
p2 = [1, 1, 1, 0, 0, 0, 1, 1, 1]
c1, c2 = two_point(p1, p2)

print(f"Child 1:  {list_to_string(c1)}")
print(f"Child 2:  {list_to_string(c2)}")
