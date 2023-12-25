import string
import random
filename = "in.txt"
MBsize = 1

totalSize = 1024 * 1024 * MBsize
maxLineSize = 100000
minLineSize = 1000

out = open(filename, "w")
curSize = 0
curMax = random.randint(minLineSize, maxLineSize)

for i in range(totalSize):
    letter = random.choice(string.ascii_letters + string.digits + ' ')
    out.write(letter)
    curSize += 1
    if curSize == curMax:
        curSize = 0
        out.write('\n')
        curMax = random.randint(minLineSize, maxLineSize)

out.close()
