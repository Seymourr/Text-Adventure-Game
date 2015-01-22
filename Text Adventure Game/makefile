default: spel.out
	./spel.out
	
spel.out: Actor.cpp Commands.cpp Env.cpp Human.cpp Item.cpp Keys.cpp Master.cpp NPC.cpp Container.h Outside.cpp 
	g++ -std=c++11 -static-libstdc++ -g  Actor.cpp Commands.cpp Env.cpp Human.cpp Item.cpp Keys.cpp Master.cpp NPC.cpp Container.h Outside.cpp -o spel.out
