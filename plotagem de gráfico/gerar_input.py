import random

min_value = 5
max_value = 1100
n = 1500
random_ints = [random.randint(min_value, max_value) for i in range(n)]

with open("input.txt","w") as file:
    for i in random_ints:
        file.write("{}\n".format(i))
