def pacman(dm_cost):
    def a_b_pruning(i, depth, max_player, a, b):
        if depth == 5:
            return scores[i % len(scores)]  

        if max_player:
            max_s = float('-inf')
            for j in range(2):  
                val = a_b_pruning(i * 2 + j, depth + 1, False, a, b)
                max_s = max(max_s, val)
                a = max(a, val)
                if b <= a:  
                    break
            return max_s
        else:
            min_s = float('inf')
            for j in range(2):  
                val = a_b_pruning(i * 2 + j, depth + 1, True, a, b)
                min_s = min(min_s, val)
                b = min(b, val)
                if b <= a:  
                    break
            return min_s
        
    scores = [3, 6, 2, 3, 7, 1, 2, 0]
    optimal_val = a_b_pruning(0, 0, True, float('-inf'), float('inf'))
    l_val, r_val = scores[1] , scores[4]

    l_val_magic = l_val - dm_cost
    r_val_magic = r_val - dm_cost

    if l_val_magic < r_val_magic:
        best_val = r_val_magic
        go_to = "right"
        
    else:
        best_val = l_val_magic
        go_to = "left"

    if best_val > optimal_val:
        print("The new minimax value is " + str(best_val) + ". Pacman goes " + go_to + " and uses dark magic") 
          
    else:
        print("The minimax value is " + str(optimal_val) + ". Pacman does not use dark magic")


pacman(2)
pacman(5)
