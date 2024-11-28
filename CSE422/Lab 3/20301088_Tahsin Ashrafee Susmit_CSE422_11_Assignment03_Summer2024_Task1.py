import random

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


def mortal_kombat(player_1):
    result = []
    current_player = player_1
    scorpion_win = 0
    sub_zero_win = 0
    rounds = 3 

    for i in range(rounds):
        is_maximizing = current_player == 1
        winner_value = a_b_pruning(0, 0, is_maximizing, float('-inf'), float('inf'))
        if winner_value == -1:
            round_winner = "Scorpion"
            scorpion_win += 1
        else:
            round_winner = "Sub-Zero"
            sub_zero_win += 1

        result.append(round_winner)
        current_player = 1 - current_player
    if scorpion_win > sub_zero_win:
        winner = "Scorpion"
    else:
        winner = "Sub-Zero"

    return winner, result

scores = []
possible_scores = [1, -1]
for i in range(16):
    score = random.choice(possible_scores)
    scores.append(score)


player_1 = 0 
winner, round_winners = mortal_kombat(player_1)

print(f"Game Winner: {winner}")
print(f"Total Rounds Played: 3")
round_number = 1
for winner in round_winners:
    print(f"Winner of Round {round_number}: {winner}")
    round_number += 1
