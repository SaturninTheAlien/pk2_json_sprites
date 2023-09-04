all:
	g++ -std=c++17 main.cpp pk2sprite_repository.cpp pk2sprite.cpp -o server.x
	
run:
	./server.x