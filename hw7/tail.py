# Author: Zachery Creech
# COSC365 Spring 2021: HW7 tail.py

import sys

if len(sys.argv) != 3:
	print('Must provide arguments <filename> <n lines>')
	exit(1)

with open(sys.argv[1], 'r') as f:
	all_lines = f.readlines()
	for line in all_lines[-int(sys.argv[2]):]:
		print(line.strip())
