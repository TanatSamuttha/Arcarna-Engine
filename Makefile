SRC := $(shell powershell -Command "(Get-ChildItem source -Recurse -Filter *.cpp).FullName")

compile:
	g++ $(SRC) -Isource -std=c++20 -O3 -o app.exe

run:
	./app