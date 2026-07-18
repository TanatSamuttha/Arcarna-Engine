SRC := $(shell powershell -Command "(Get-ChildItem source -Recurse -Include *.cpp,*.c).FullName")
SRC_NOENT := $(shell powershell -Command "(Get-ChildItem source -Recurse -Include *.cpp,*.c | Where-Object { $$_.FullName -notmatch '[\\/]+EntryPoint[\\/]+' }).FullName")
TEST := $(shell powershell -Command "(Get-ChildItem test -Recurse -Include *.cpp,*.c).FullName")
INCLUDE := -Isource/engine -Isource/workspace -Isource/config -Idependencies/glfw/include -Ivendor/stb_image
LIBS := -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32

compile:
	g++ $(SRC) $(INCLUDE) $(LIBS) -std=c++20 -O3 -o app -static

run:
	./app

compile-test-ecs:
	g++ $(SRC_NOENT) Test/ECS.cpp -Itest $(INCLUDE) $(LIBS) -std=c++20 -O3 -o test -static

compile-test-scene:
	g++ $(SRC_NOENT) Test/Scene.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O3 -o test -static

compile-test-vector2:
	g++ $(SRC_NOENT) Test/Vector2.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O3 -o test -static

compile-test-angle:
	g++ $(SRC_NOENT) Test/Angle.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O3 -o test -static

compile-test-physics:
	g++ $(SRC_NOENT) Test/Physics.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O3 -o test -static

compile-test-sprite:
	g++ $(SRC_NOENT) Test/Sprite.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O3 -o test -static

test-ecs:
	make compile-test-ecs
	./test

test-scene:
	make compile-test-scene
	./test

test-vector2:
	make compile-test-vector2
	./test

test-angle:
	make compile-test-angle
	./test

test-physics:
	make compile-test-physics
	./test

test-sprite:
	make compile-test-sprite
	./test