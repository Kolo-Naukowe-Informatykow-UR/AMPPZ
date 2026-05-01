import random

n = random.randint(1,200)
print(n)

for i in range(n):
    x = random.randint(2,8)
    word = ""
    for j in range(x):
        c = random.randint(65,90) #ASCI A-Z
        word = word + chr(c)
    print(word)

exit()