from cubes import *
p = Cubes();
def h1(n): #heuristic function depending on how many cubes are not in the position they should be
    error_cube_no=0
    current_state=n.state
    gstate=p.goal #get the current and the goal state and save them in two new variables
    L1=[] #convert them in lists of lists so we can make any changes we want
    L2=list(current_state)
    for x in L2:
        y=list(x)
        L1.append(y)
    L3=[]
    L4=list(gstate)
    for x in L4:
        y=list(x)
        L3.append(y)
    #L1 and L3 are Lists of lists that store the Current and the Goal state
    while L1 != []:
        i=L1.pop()
        j=L3.pop() #Each time ,remove the position of each last cube in the two lists and compare them
        #if they are not the same,that means that the cube is not where it should be so raise the error_cube_no
        if i != j:
            error_cube_no=error_cube_no+1
    return error_cube_no  #Return the sum of the position_errors of the cubes
        
s,explored=astar_search(p,h1)

sol=s.solution()
path=s.path()

print("Initial state: State: {0}".format(path[0].state))
print("------------------------------------ BEST PATH -------------------------------------")

for i in range(1,len(path)) :
	state = path[i].state
	cost = path[i].path_cost
	if i > 0 : # The initial state has not an action that results to it
		action = sol[i-1]

        if action[1] == 0:
            print "Moving block {0} on the table. \t\t  \t\t {1} \t ".format(action[0],state)
        else:
            print "Moving block {0} on block {1}. \t\t  \t\t {2} \t ".format(action[0],action[1],state)

print("------------------------------------ OTHER PATHS -------------------------------------")

for node in explored:
	sol=node.solution()
	path=node.path()

	for i in range(1,len(path)) :
		state = path[i].state
		cost = path[i].path_cost
		if i > 0 : # The initial state has not an action that results to it
			action = sol[i-1]

	        if action[1] == 0:
	            print "Moving block {0} on the table. \t\t  \t\t {1} \t ".format(action[0],state)
	        else:
	            print "Moving block {0} on block {1}. \t\t  \t\t {2} \t ".format(action[0],action[1],state)
	print("-------------------------------------------------------------------------")
