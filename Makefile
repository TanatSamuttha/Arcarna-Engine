SRC := $(shell powershell -Command "(Get-ChildItem source -Recurse -Filter *.cpp).FullName")
SRC_NOENT := $(shell powershell -Command "(Get-ChildItem source -Recurse -Filter *.cpp | Where-Object { $$_.FullName -notmatch '[\\/]+EntryPoint[\\/]+' }).FullName")
TEST := $(shell powershell -Command "(Get-ChildItem test -Recurse -Filter *.cpp).FullName")

compile:
	g++ $(SRC) -Isource/engine -Isource/workspace -Idependencies/glfw/include -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -std=c++20 -O3 -o app

run:
	./app

compile-test-ecs:
	g++ $(SRC_NOENT) Test/ECS.cpp -Isource/engine -Isource/workspace -Idependencies/glfw/include -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -Itest -std=c++20 -O3 -o test

compile-test-scene:
	g++ $(SRC_NOENT) Test/Scene.cpp -Isource/engine -Isource/workspace -Idependencies/glfw/include -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -Itest -std=c++20 -O3 -o test

compile-test-vector2:
	g++ $(SRC_NOENT) Test/Vector2.cpp -Isource/engine -Isource/workspace -Idependencies/glfw/include -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -Itest -std=c++20 -O3 -o test

compile-test-angle:
	g++ $(SRC_NOENT) Test/Angle.cpp -Isource/engine -Isource/workspace -Idependencies/glfw/include -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -Itest -std=c++20 -O3 -o test

compile-test-physics:
	g++ $(SRC_NOENT) Test/Physics.cpp -Isource/engine -Isource/workspace -Idependencies/glfw/include -Ldependencies/glfw/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32 -Itest -std=c++20 -O3 -o test

run-test:
	./test