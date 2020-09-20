from search import * # This file imports utils.py so it should be in the same folder
import sys # System-specific parameters and functions


class WaterPouringProblem(Problem):
	#Derived class of search.problem
	#problem of 3 jugs with capacities 8,5,3
	def __init__(self):
			super(WaterPouringProblem,self).__init__((8,0,0),(4,4,0))

			self.capacities = (8,5,3)

	def actions(self,state):
		l = len(state)
		possible_actions = []
		for i in range(l):
			for j in range(l):
				if i!=j:
					possible_actions.append((i,j))

		valid_actions = []

		for action in possible_actions:
			if state[action[0]] != 0:
				valid_actions.append(action)
		return valid_actions


	def result(self,state,action):
		state2 = list(state)
		
		if state[action[0]] == 0:
			return state

		can_accept = self.capacities[action[1]] - state[action[1]]

		if can_accept > state[action[0]]:
			moving = state[action[0]]
		else:
			moving = can_accept

		state2[action[1]] += moving
		state2[action[0]] -= moving


		return tuple(state2)

def h(n): 
	current_state=n.state
	gstate=p.goal

	l = len(current_state) 
	cost = 0
	for i in range(l):
		cost += abs(current_state[i] - gstate[i])
	return cost


p = WaterPouringProblem()


s,explored=astar_search(p,h)

sol=s.solution()
path=s.path()

print("Initial state: State: {0}".format(path[0].state))

print("------------------------------------ BEST PATH -------------------------------------")

for i in range(1,len(path)) :
	state = path[i].state
	cost = path[i].path_cost
	if i > 0 : # The initial state has not an action that results to it
		action = sol[i-1]

		print "Pouring the content of jug {0} on jug {1}. \t\t  \t\t {2} \t ".format(action[0],action[1],state)


print("------------------------------------ OTHER PATHS -------------------------------------")

for node in explored:
	sol=node.solution()
	path=node.path()

	for i in range(1,len(path)):
		state = path[i].state
		cost = path[i].path_cost
		if i > 0 : # The initial state has not an action that results to it
			action = sol[i-1]

			print "Pouring the content of jug {0} on jug {1}. \t\t  \t\t {2} \t ".format(action[0],action[1],state)

	print("-------------------------------------------------------------------------")
