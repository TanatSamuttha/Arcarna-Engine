PLATFORM ?= linux

CXXFLAGS := -std=c++20 -O3
TESTFLAGS := -std=c++20 -O0 -g

SRC := $(shell find Source -type f \( -name '*.cpp' -o -name '*.c' \))
CORE_SRC := $(shell find Source -type f \( -name '*.cpp' -o -name '*.c' \) ! -path '*/EntryPoint/*')
VENDOR_SRC := Vendor/stb_image/stb_image.cpp Vendor/glad/src/glad.c

TESTS := ecs scene vector2 angle physics renderer event
TEST_SOURCE_ecs := Test/ECS.cpp
TEST_SOURCE_scene := Test/Scene.cpp
TEST_SOURCE_vector2 := Test/Vector2.cpp
TEST_SOURCE_angle := Test/Angle.cpp
TEST_SOURCE_physics := Test/Physics.cpp
TEST_SOURCE_renderer := Test/Renderer.cpp
TEST_SOURCE_event := Test/Event.cpp

INCLUDES := \
	-ISource/Engine -ISource/Workspace -ISource/Config \
	-IVendor/glad/include -IVendor/stb_image -IVendor/ariadne -ITest

ifeq ($(PLATFORM),linux)

CXX := g++
APP := Build/App
TEST_APP := Build/Test

INCLUDES += -IVendor/glfw-linux/include \
            -IVendor/glfw-linux/include/GLFW \
            -IVendor/glfw-linux/src
DEFINES := -D_GLFW_X11 -D_DEFAULT_SOURCE

LDLIBS := -lX11 -lXrandr -lXinerama -lXcursor -lXi -lXext \
	-lGL -ldl -pthread -lm -lrt
GLFW_LINK := -LBuild -larcarna-opengl
GLFW_DEP := Build/libarcarna-opengl.a

GLFW_NAMES := context init input monitor platform vulkan window \
	egl_context osmesa_context null_init null_monitor null_window \
	null_joystick posix_module posix_time posix_thread posix_poll \
	linux_joystick x11_init x11_monitor x11_window xkb_unicode glx_context

GLFW_SRC := $(addprefix Vendor/glfw-linux/src/,$(addsuffix .c,$(GLFW_NAMES)))
GLFW_OBJ := $(patsubst Vendor/glfw-linux/src/%.c,Build/glfw/%.o,$(GLFW_SRC))

Build/glfw/%.o: Vendor/glfw-linux/src/%.c | build
	@mkdir -p $(@D)
	gcc -O3 $(INCLUDES) $(DEFINES) -c $< -o $@

$(GLFW_DEP): $(GLFW_OBJ)
	ar rcs $@ $^

else ifeq ($(PLATFORM),windows)

ifeq ($(OS),Windows_NT)
CXX := g++
else
CXX := x86_64-w64-mingw32-g++
endif

APP := Build/App.exe
TEST_APP := Build/Test.exe

INCLUDES += -IVendor/glfw-windows/include
LDFLAGS := -static
LDLIBS := -LVendor/glfw-windows/lib-mingw-w64 -lglfw3 -lopengl32 -lgdi32

else

$(error PLATFORM must be linux or windows)

endif

.PHONY: build clean compile run test-all \
	$(addprefix compile-test-,$(TESTS)) \
	$(addprefix test-,$(TESTS))

$(addprefix compile-test-,$(TESTS)): compile-test-%: build $(GLFW_DEP)
	$(CXX) $(INCLUDES) $(DEFINES) $(TESTFLAGS) \
		$(CORE_SRC) $(VENDOR_SRC) $(TEST_SOURCE_$*) \
		-o $(TEST_APP) $(LDFLAGS) $(GLFW_LINK) $(LDLIBS)

$(addprefix test-,$(TESTS)): test-%: compile-test-%
	$(RUN_PREFIX)$(TEST_APP)

build:
	mkdir -p Build

clean:
	rm -rf Build

compile: build $(GLFW_DEP)
	$(CXX) $(INCLUDES) $(DEFINES) $(CXXFLAGS) \
		$(SRC) $(VENDOR_SRC) -o $(APP) \
		$(LDFLAGS) $(GLFW_LINK) $(LDLIBS)

run: compile
	$(RUN_PREFIX)$(APP)

compile-test-%: build $(GLFW_DEP)
	$(CXX) $(INCLUDES) $(DEFINES) $(TESTFLAGS) \
		$(CORE_SRC) $(VENDOR_SRC) $(TEST_SOURCE_$*) \
		-o $(TEST_APP) $(LDFLAGS) $(GLFW_LINK) $(LDLIBS)

test-%: compile-test-%
	$(RUN_PREFIX)$(TEST_APP)

test-all:
	@set -e; for t in $(TESTS); do \
		$(MAKE) test-$$t PLATFORM=$(PLATFORM); \
	done