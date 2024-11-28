from queue import PriorityQueue
p_queue = PriorityQueue()

with open('input.txt', 'r') as read_input_file:
    cities_and_heuristic = {}
    for line in read_input_file:
        words = line.split()
        city_name = words[0]
        heuristic = words[1]
        cities_and_heuristic[city_name] = int(heuristic)
# print(cities_and_heuristic)

with open('input.txt', 'r') as read_input_file:
    graph = {}
    for line in read_input_file:
        words = line.split()
        city_name = words[0]
        d = words[2:] 
        graph[city_name] = d
# print(graph)

def A_star_algo(start,destination):
    p_queue.put((cities_and_heuristic[start], start, 'Null', 0)) #heuristic value, starting node, parent is null, distance is 0 as it is initial node
    path = {}
    path_string = ''
    path_found = False

    while True:
        current_node_info = p_queue.get()
        # print(current_node_info)
        node= current_node_info[1]
        parent = current_node_info[2]
        d = current_node_info[3]
        
        for i in range(0, len(graph[node]), 2): # loop incremented by 2 because in the dictonary the neighbouring node is followed by d in pairs
            path[node] = [parent, d]
            n_node = graph[node][i]
            cost = int(graph[node][i + 1])
            p_queue.put(( cities_and_heuristic[n_node] + cost + d, n_node, node, d + cost ))

        if node == destination:
            path_found = True
            no_of_times = len(path.keys())
            for i in range(no_of_times):
                if start != destination:
                    path_string = ' ' + '-> ' + destination + path_string
                    destination = path[destination][0]                
                else:
                    path_string = destination + path_string
                    return f"Path: {path_string} \nTotal distance: {d} km"
            return f"NO PATH FOUND"


start = input("Enter starting node: ")
destination = input("Enter destination node: ")

# start = "Arad"
# destination = "Bucharest"

path_string = A_star_algo(start,destination)
print(path_string)



