# Author: Zachery Creech
# COSC365 Spring 2021: HW7 frequency.py

import sys

if len(sys.argv) != 2:
	print('Must provide argument <filename>')
	exit(1)

all_words = []
freq = {}

# read the file line by line and add each word to a list
with open(sys.argv[1], 'r') as f:
	for line in f:
		all_words.extend(line.strip().split())
	
# count the words
for word in all_words:
	if word in freq:
		freq[word] += 1
	else:
		freq[word] = 1

# get the pairs and sort them, then print them in order
pairs = freq.items()

pairs = sorted(pairs, key=lambda pair: (pair[1], pair[0]))

for pair in pairs:
	print('{0:<20s}{1:>5d}'.format(pair[0], pair[1]))
