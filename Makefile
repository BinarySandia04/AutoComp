all:
	g++ run.cpp -lstdc++fs -std=gnu++0x -o run
	./run
set:
	g++ setup.cpp -lstdc++fs -std=gnu++0x -o setup
	./setup
