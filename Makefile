SRC := $(shell powershell -Command "(Get-ChildItem source -Recurse -Include *.cpp,*.c).FullName")
SRC_NOENT := $(shell powershell -Command "(Get-ChildItem source -Recurse -Include *.cpp,*.c | Where-Object { $$_.FullName -notmatch '[\\/]+EntryPoint[\\/]+' }).FullName")
TEST := $(shell powershell -Command "(Get-ChildItem test -Recurse -Include *.cpp,*.c).FullName")
VENDOR := $(shell powershell -Command "(Get-ChildItem vendor -Recurse -Include *.cpp,*.c).FullName")
INCLUDE := -Isource/engine -Isource/workspace -Isource/config -Ivendor/glfw/include -Ivendor/glad/include -Ivendor/stb_image
LIBS := -Lvendor/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32

build:
	mkdir Build

compile:
	g++ $(SRC) $(VENDOR) $(INCLUDE) $(LIBS) -std=c++20 -O3 -o Build/App -static

run:
	./Build/App

compile-test-ecs:
	g++ $(SRC_NOENT) $(VENDOR) Test/ECS.cpp -Itest $(INCLUDE) $(LIBS) -std=c++20 -O0 -o Build/Test -g

compile-test-scene:
	g++ $(SRC_NOENT) $(VENDOR) Test/Scene.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/Test -g

compile-test-vector2:
	g++ $(SRC_NOENT) $(VENDOR) Test/Vector2.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/Test -g

compile-test-angle:
	g++ $(SRC_NOENT) $(VENDOR) Test/Angle.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/Test -g

compile-test-physics:
	g++ $(SRC_NOENT) $(VENDOR) Test/Physics.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/Test -g

compile-test-renderer:
	g++ $(SRC_NOENT) $(VENDOR) Test/Renderer.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o test -g

test-ecs:
	make compile-test-ecs
	./Build/Test

test-scene:
	make compile-test-scene
	./Build/Test

test-vector2:
	make compile-test-vector2
	./Build/Test

test-angle:
	make compile-test-angle
	./Build/Test

test-physics:
	make compile-test-physics
	./Build/Test

test-renderer:
	make compile-test-renderer
	./Build/Test

test-all:
	@g++ $(SRC_NOENT) $(VENDOR) Test/ECS.cpp -Itest $(INCLUDE) $(LIBS) -std=c++20 -O0 -o Build/TestECS -g
	./Build/TestECS
	@g++ $(SRC_NOENT) $(VENDOR) Test/Scene.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/TestScene -g
	./Build/TestScene
	@g++ $(SRC_NOENT) $(VENDOR) Test/Vector2.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/TestVector2 -g
	./Build/TestVector2
	@g++ $(SRC_NOENT) $(VENDOR) Test/Angle.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/TestAngle -g
	./Build/TestAngle
	@g++ $(SRC_NOENT) $(VENDOR) Test/Physics.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/TestPhysics -g
	./Build/TestPhysics
	@g++ $(SRC_NOENT) $(VENDOR) Test/Renderer.cpp $(INCLUDE) $(LIBS) -Itest -std=c++20 -O0 -o Build/TestRenderer -g
	./Build/TestRenderer