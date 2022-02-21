# Author: Zachery Creech
# COSC365 Spring 2021: HW7 golfer.py

from datetime import date

# golfer object contains golfer's scores, name, and handicap
class Golfer:
	def __init__(self):
		self.scores = []
		self.name = ''
		self.handicap = 0.0
	
	# compute golfer's handicap based on the lowest 10 differentials from their last 20 games
	def computeHandicap(self):
		differentials = []
		total = 0
		
		# sort by date from longest ago to most recent, then take the 20 most recent
		recent = sorted(self.scores, key=lambda score: (score.date.year, score.date.month, score.date.day))[-20:]
		for score in recent:
			differential = (score.score - score.course.rating) * 113 / score.course.slope
			differentials.append(differential)
		differentials.sort()
		
		# find the average of the lowest 10 differentials
		for diff in differentials[0:10]:
			total += diff

		self.handicap = 0.96 * total / 10

# course object contains course's name, rating, and slope to calculate the differential
class Course:
	def __init__(self):
		self.name = ''
		self.rating = 0.0
		self.slope = 0.0

# score object contains the course object the score was made at (for calculating differential)
# as well as the score itself, and the date it occurred
class Score:
	def __init__(self):
		self.course = Course()
		self.score = 0
		self.date = date(1, 1, 1)
