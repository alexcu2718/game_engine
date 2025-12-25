BUILD_DIR := build

.PHONY: configure build run clean

configure:
	VCPKG_DISABLE_METRICS=1 cmake -S . -B $(BUILD_DIR) -G Ninja \
		-DCMAKE_TOOLCHAIN_FILE=$(CURDIR)/vcpkg/scripts/buildsystems/vcpkg.cmake \
		-DVCPKG_TARGET_TRIPLET=arm64-osx \
		-DVCPKG_HOST_TRIPLET=arm64-osx \
		-DCMAKE_OSX_ARCHITECTURES=arm64

build: configure
	cmake --build $(BUILD_DIR)

run: build 
	./$(BUILD_DIR)/src/engine_app

clean:
	rm -rf $(BUILD_DIR)
