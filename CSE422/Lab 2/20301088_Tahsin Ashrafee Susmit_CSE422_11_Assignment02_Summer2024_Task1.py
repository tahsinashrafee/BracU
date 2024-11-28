import random

def generate_csome(N,T):
    c_some = []
    for i in range (N*T):
        c_some.append(random.randint(0,1))
    return c_some

def generate_population(p_size, N, T):
    all_p = []
    for i in range(p_size):
        c_some = generate_csome(N, T)
        all_p.append(c_some)
    return all_p

def crossover(p1, p2):
    cut_at = random.randint(1, len(p1) - 1)
    c1 = p1[:cut_at] + p2[cut_at:]
    c2 = p2[:cut_at] + p1[cut_at:]
    return c1, c2

def fitness(c_some,N,T):
    penalty_overlap = 0
    peanlty_consistency = 0
    schedule = []
    for i in range(T):
        start = i * N
        end = (i + 1) * N
        slot = c_some[start:end]
        schedule.append(slot)

    for slot in schedule:
        slot_sum = sum(slot)
        if slot_sum > 1:
            penalty_overlap += (slot_sum - 1)

    for course in range(N):
        c = 0
        for slot in schedule:
            c += slot[course]
        peanlty_consistency += abs(c - 1)
    total = -(penalty_overlap + peanlty_consistency)
    return total

def mutate(c_some):
    position_to_change = random.randint(0, len(c_some) - 1)

    if c_some[position_to_change] == 0:
        c_some[position_to_change] = 1
    elif c_some[position_to_change] == 1:
        c_some[position_to_change] = 0
    return c_some

def select_p(all_p):
    return random.sample(all_p, 2)
        

def genetic_algorithm(N, T, p_size=10, times=100):

    generate_p = []
    for i in range (p_size):
        generate_p.append(generate_csome(N, T))
  
   
    for j in range(times):
        fit_list = []
        for k in generate_p:
            fit_list.append(fitness(k, N, T))

        new_p = []
        for l in range(p_size // 2):
            p1, p2 = select_p(generate_p)
            c1, c2 = crossover(p1, p2)
            mutate(c1)
            mutate(c2)
            new_p.append(c1)
            new_p.append(c2)

        generate_p = new_p
    
    best_fit = max(fit_list)
    best_chrom = generate_p[fit_list.index(best_fit)]
    
    return best_chrom, best_fit

def list_to_string(list):
    string = ''
    for i in list:
        string += str(i)
    return string


# N = int(input("Enter number of courses: "))
# T =   int(input("Enter number of time slots: "))
N,T = 3,3
courses = ["CSE110", "MAT110", "PHY112"]
length = int(N * T)
best_csome, best_fit = genetic_algorithm(N, T)
print("Best Chromosome:", list_to_string(best_csome))
print("Best Fitness:", best_fit)