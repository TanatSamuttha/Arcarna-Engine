
# ==========================================
# Arcarna Engine - Build Configuration
# ==========================================

# Default platform: linux or windows
# Override: make PLATFORM=windows compile
PLATFORM ?= linux

CXXFLAGS_RELEASE := -std=c++20 -O3
CXXFLAGS_TEST := -std=c++20 -O0 -g

APP_LINUX := Build/App
APP_WINDOWS := Build/App.exe

TEST_LINUX := Build/Test
TEST_WINDOWS := Build/Test.exe


# ==========================================
# Source Files
# ==========================================

# Use PowerShell only on native Windows.
# Linux and Linux-to-Windows cross-compilation use find.
ifeq ($(OS),Windows_NT)

SRC_CPP := $(shell powershell -NoProfile -Command "(Get-ChildItem Source -Recurse -Include *.cpp).FullName")
SRC_C := $(shell powershell -NoProfile -Command "(Get-ChildItem Source -Recurse -Include *.c).FullName")

SRC_NOENT_CPP := $(shell powershell -NoProfile -Command "(Get-ChildItem Source -Recurse -Include *.cpp | Where-Object { $$_.FullName -notmatch '[\\/]+EntryPoint[\\/]' }).FullName")
SRC_NOENT_C := $(shell powershell -NoProfile -Command "(Get-ChildItem Source -Recurse -Include *.c | Where-Object { $$_.FullName -notmatch '[\\/]+EntryPoint[\\/]' }).FullName")

else

SRC_CPP := $(shell find Source -type f -name '*.cpp')
SRC_C := $(shell find Source -type f -name '*.c')

SRC_NOENT_CPP := $(shell find Source -type f -name '*.cpp' ! -path '*/EntryPoint/*')
SRC_NOENT_C := $(shell find Source -type f -name '*.c' ! -path '*/EntryPoint/*')

endif


# Explicitly select project dependencies.
# Do not compile every .c file under Vendor.
VENDOR_CPP := Vendor/stb_image/stb_image.cpp
VENDOR_C := Vendor/glad/src/glad.c


# ==========================================
# GLFW - Linux Source Files (X11 backend)
# ==========================================

GLFW_LINUX_C := \
	Vendor/glfw-linux/src/context.c \
	Vendor/glfw-linux/src/init.c \
	Vendor/glfw-linux/src/input.c \
	Vendor/glfw-linux/src/monitor.c \
	Vendor/glfw-linux/src/platform.c \
	Vendor/glfw-linux/src/vulkan.c \
	Vendor/glfw-linux/src/window.c \
	Vendor/glfw-linux/src/egl_context.c \
	Vendor/glfw-linux/src/osmesa_context.c \
	Vendor/glfw-linux/src/null_init.c \
	Vendor/glfw-linux/src/null_monitor.c \
	Vendor/glfw-linux/src/null_window.c \
	Vendor/glfw-linux/src/null_joystick.c \
	Vendor/glfw-linux/src/posix_module.c \
	Vendor/glfw-linux/src/posix_time.c \
	Vendor/glfw-linux/src/posix_thread.c \
	Vendor/glfw-linux/src/posix_poll.c \
	Vendor/glfw-linux/src/linux_joystick.c \
	Vendor/glfw-linux/src/x11_init.c \
	Vendor/glfw-linux/src/x11_monitor.c \
	Vendor/glfw-linux/src/x11_window.c \
	Vendor/glfw-linux/src/xkb_unicode.c \
	Vendor/glfw-linux/src/glx_context.c

GLFW_LINUX_LIB := Vendor/glfw-linux/libarcarna-opengl.a
AR := ar


# ==========================================
# Include Paths
# ==========================================

INCLUDE_COMMON := \
	-ISource/Engine \
	-ISource/Workspace \
	-ISource/Config \
	-IVendor/glad/include \
	-IVendor/stb_image \
	-ITest

INCLUDE_LINUX := $(INCLUDE_COMMON) \
	-IVendor/glfw-linux/include \
	-IVendor/glfw-linux/include/GLFW \
	-IVendor/glfw-linux/src

INCLUDE_WINDOWS := $(INCLUDE_COMMON) \
	-IVendor/glfw-windows/include \
	-IVendor/glfw-linux/include \
	-IVendor/glfw-linux/include/GLFW


# ==========================================
# Platform Toolchains and Libraries
# ==========================================

LINUX_CC := gcc
LINUX_FLAGS := $(CXXFLAGS_RELEASE) -D_GLFW_X11 -D_DEFAULT_SOURCE
LINUX_TEST_FLAGS := $(CXXFLAGS_TEST) -D_GLFW_X11 -D_DEFAULT_SOURCE

LINUX_LIBS := \
	-lX11 -lXrandr -lXinerama -lXcursor -lXi -lXext \
	-lGL -ldl -pthread -lm -lrt -lstdc++

ifeq ($(OS),Windows_NT)
WINDOWS_CXX := g++
else
WINDOWS_CXX := x86_64-w64-mingw32-g++
endif

WINDOWS_FLAGS := $(CXXFLAGS_RELEASE) -static
WINDOWS_TEST_FLAGS := $(CXXFLAGS_TEST) -static

WINDOWS_LIBS := \
	-LVendor/glfw-windows/lib-mingw-w64 \
	-lglfw3 -lopengl32 -lgdi32


# ==========================================
# Selected Platform
# ==========================================

ifeq ($(PLATFORM),linux)

APP := $(APP_LINUX)
TEST_APP := $(TEST_LINUX)

TEST_CXX := $(LINUX_CC)
TEST_FLAGS := $(LINUX_TEST_FLAGS)
TEST_INCLUDE := $(INCLUDE_LINUX)
TEST_GLFW_C := $(GLFW_LINUX_C)
TEST_LIBS := $(LINUX_LIBS)

else ifeq ($(PLATFORM),windows)

APP := $(APP_WINDOWS)
TEST_APP := $(TEST_WINDOWS)

TEST_CXX := $(WINDOWS_CXX)
TEST_FLAGS := $(WINDOWS_TEST_FLAGS)
TEST_INCLUDE := $(INCLUDE_WINDOWS)
TEST_GLFW_C :=
TEST_LIBS := $(WINDOWS_LIBS)

else

$(error PLATFORM must be linux or windows)

endif


# ==========================================
# Build Directory
# ==========================================

.PHONY: build clean compile run \
	command-linux command-windows \
	compile-linux compile-windows \
	compile-test-ecs compile-test-scene \
	compile-test-vector2 compile-test-angle \
	compile-test-physics compile-test-renderer \
	test-ecs test-scene test-vector2 \
	test-angle test-physics test-renderer test-all

ifeq ($(OS),Windows_NT)

build:
	@if not exist Build mkdir Build

clean:
	@if exist Build rmdir /s /q Build

else

build:
	@mkdir -p Build

clean:
	rm -rf Build

endif

# ==========================================
# Compile OpenGL Dependencies (Linux)
# ==========================================

.PHONY: compile-opengl

$(GLFW_LINUX_LIB): $(GLFW_LINUX_C) Vendor/glad/src/glad.c
	@set -e; \
	tmp=$$(mktemp -d); \
	trap 'rm -rf "$$tmp"' EXIT; \
	for src in $(GLFW_LINUX_C) Vendor/glad/src/glad.c; do \
		obj="$$tmp/$$(basename "$$src" .c).o"; \
		gcc -O3 -D_GLFW_X11 -D_DEFAULT_SOURCE \
			$(INCLUDE_LINUX) -c "$$src" -o "$$obj"; \
	done; \
	$(AR) rcs $(GLFW_LINUX_LIB) "$$tmp"/*.o

compile-opengl: $(GLFW_LINUX_LIB)

# ==========================================
# Compile Application
# ==========================================

command-linux: build compile-opengl
	$(LINUX_CC) $(INCLUDE_LINUX) $(LINUX_FLAGS) \
		$(SRC_CPP) $(VENDOR_CPP) $(SRC_C) \
		-o $(APP_LINUX) \
		-LVendor/glfw-linux -larcarna-opengl \
		$(LINUX_LIBS)

command-windows: build
	$(WINDOWS_CXX) $(INCLUDE_WINDOWS) $(WINDOWS_FLAGS) \
		$(SRC_CPP) $(VENDOR_CPP) \
		-x c $(SRC_C) $(VENDOR_C) -x none \
		-o $(APP_WINDOWS) $(WINDOWS_LIBS)

compile-linux: command-linux

compile-windows: command-windows

compile: command-$(PLATFORM)


# ==========================================
# Run Application
# ==========================================

run: compile
	$(RUN_PREFIX)$(APP)


# ==========================================
# Compile Tests
# ==========================================

TEST_BASE := $(TEST_CXX) $(TEST_INCLUDE) $(TEST_FLAGS) \
	$(SRC_NOENT_CPP) $(VENDOR_CPP)

TEST_TAIL := $(SRC_NOENT_C) $(VENDOR_C) \
	$(TEST_GLFW_C) -o $(TEST_APP) $(TEST_LIBS)

compile-test-ecs: build
	$(TEST_BASE) Test/ECS.cpp $(TEST_TAIL)

compile-test-scene: build
	$(TEST_BASE) Test/Scene.cpp $(TEST_TAIL)

compile-test-vector2: build
	$(TEST_BASE) Test/Vector2.cpp $(TEST_TAIL)

compile-test-angle: build
	$(TEST_BASE) Test/Angle.cpp $(TEST_TAIL)

compile-test-physics: build
	$(TEST_BASE) Test/Physics.cpp $(TEST_TAIL)

compile-test-renderer: build
	$(TEST_BASE) Test/Renderer.cpp $(TEST_TAIL)


# ==========================================
# Run Tests
# ==========================================

test-ecs: compile-test-ecs
	$(RUN_PREFIX)$(TEST_APP)

test-scene: compile-test-scene
	$(RUN_PREFIX)$(TEST_APP)

test-vector2: compile-test-vector2
	$(RUN_PREFIX)$(TEST_APP)

test-angle: compile-test-angle
	$(RUN_PREFIX)$(TEST_APP)

test-physics: compile-test-physics
	$(RUN_PREFIX)$(TEST_APP)

test-renderer: compile-test-renderer
	$(RUN_PREFIX)$(TEST_APP)


# ==========================================
# Run All Tests
# ==========================================

test-all:
	$(MAKE) PLATFORM=$(PLATFORM) test-ecs
	$(MAKE) PLATFORM=$(PLATFORM) test-scene
	$(MAKE) PLATFORM=$(PLATFORM) test-vector2
	$(MAKE) PLATFORM=$(PLATFORM) test-angle
	$(MAKE) PLATFORM=$(PLATFORM) test-physics
	$(MAKE) PLATFORM=$(PLATFORM) test-renderer
