all:
	g++ -std=c++17 main.cpp pk2sprite_repository.cpp spriteclass.cpp -o server.x
	
run:
	./server.x