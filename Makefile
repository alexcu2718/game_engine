BUILD_DIR := build

configure:
	cmake -S . -B $(BUILD_DIR) -G Ninja

build: configure
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/src/main

clean:
	rm -rf $(BUILD_DIR)
