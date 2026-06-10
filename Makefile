BUILD_DIR  := build/debug
CPP_FILES  := homework_06/include/ballistics.hpp homework_06/src/ballistics.cpp homework_06/src/main.cpp homework_06/tests/ballistics_tests.cpp
TIDY_FILES := homework_06/src/ballistics.cpp homework_06/src/main.cpp homework_06/tests/ballistics_tests.cpp

.PHONY: format build test lint quality

format:
	clang-format -i $(CPP_FILES)
	cmake-format -i homework_06/CMakeLists.txt

build:
	cmake --preset debug
	cmake --build --preset debug

test: build
	ctest --test-dir $(BUILD_DIR) --output-on-failure

lint: build
	clang-tidy -p $(BUILD_DIR) $(TIDY_FILES)

quality: format build lint test