import math

log_x = []
log_y = []

for x in range(1,1001):
    log_x.append(x)
for i in log_x:
    i = math.log2(i)
    log_y.append(i)

print(log_x)
print(log_y)