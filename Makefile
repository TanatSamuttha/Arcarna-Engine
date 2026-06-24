compile:
	g++ src/engine/*.cpp src/workspace/script/*.cpp -O3 -std=c++17 -o app -Isrc

run:
	./app