# Author: Zachery Creech
# COSC365 Spring 2021: HW7 handicap.py

import sys
from golfer import Golfer, Course, Score
from datetime import date

if len(sys.argv) != 3:
	print('Must provide arguments <scorefile> <coursefile>')

courses = {}

# open the course file and read in all courses
with open(sys.argv[2], 'r') as f:
	for line in f:
		split = line.strip().split()
		
		# skip empty lines
		if not split:
			continue

		# create a course and add it to the dictionary of courses if it doesn't already exist
		# otherwise add the rating and slope, ignore all other lines
		if split[0] == 'Course':
			name = ' '.join(split[1:])
			if name not in courses:
				course = Course()
				course.name = name
				courses[name] = course
		elif split[0] == 'Rating':
			course.rating = float(split[1])
			course.slope = float(split[3])

golfers = {}

# open the score file and read in all scores, creating golfer objects as needed
with open(sys.argv[1], 'r') as f:
	for line in f:
		score = Score()
		split = line.strip().split()
		
		# skip empty lines
		if not split:
			continue
		
		name = split[3]
		if name not in golfers:
			golfer = Golfer()
			golfer.name = name
			golfers[name] = golfer
		score.date = date(int(split[2]), int(split[0]), int(split[1]))
		score.score = int(split[4])
		score.course = courses[' '.join(split[5:])]
		golfers[name].scores.append(score)

# flatten the golfers dictionary into a list of just the golfer objects
golfers = golfers.values()

# compute all handicaps
for golfer in golfers:
	golfer.computeHandicap()

# sort the list in ascending order of handicap then print them
golfers = sorted(golfers, key=lambda golfer: golfer.handicap)

for golfer in golfers:
	print('{0:5.2f} {1:s}'.format(golfer.handicap, golfer.name))
