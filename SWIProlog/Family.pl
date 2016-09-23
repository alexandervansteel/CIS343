male(alex).
male(max).
male(mike).
female(susie).
male(chuck).
female(mardelle).
male(tom).
female(sandy).

brotherof(alex, max).
brotherof(max, alex).

fatherof(mike, alex).
fatherof(mike, max).

motherof(susie, alex).
motherof(susie, max).

fatherof(chuck, mike).
motherof(mardelle, mike).

fatherof(tom, susie).
motherof(sandy, susie).

sisterof(X,Y)		:- 	dif(X,Y),
						female(X),
						(parentof(Z,X), parentof(Z,Y)).

brotherof(X,Y)		:-	dif(X,Y),
						male(X),
						(parentof(Z,X), parentof(Z,Y)).

siblingof(X,Y)		:-	dif(X,Y),
						parentof(Z,X), parentof(Z,Y).

motherof(X,Y)		:-	dif(X,Y),
						female(X),
						not(motherof(Z,X).

fatherof(X,Y)		:-	dif(X,Y),
						male(X)
						not(fatherof(Z,X).

parentof(X,Y)		:-	dif(X,Y),
						(motherof(X,Y) ; fatherof(X,Y)).

grandmotherof(X,Y)	:-	dif(X,Y),
						parentof(Z,Y),
						motherof(X,Z).

grandfatherof(X,Y)	:-	dif(X,Y),
						parentof(Z,Y), 
						fatherof(X,Z).

grandparentof(X,Y)	:-	dif(X,Y),
						(grandmotherof(X,Y) ; grandfatherof(X,Y)).