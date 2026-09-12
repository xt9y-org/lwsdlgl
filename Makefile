CC ?= cc
AR ?= ar
PREFIX ?= $(if $(MSYSTEM_PREFIX),$(MSYSTEM_PREFIX),/usr/local)
VERSION := 0.1.0
ABI := 1
BUILD := build
DEPS := $(BUILD)/deps
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)

STATIC_LIBNAME := liblwsdlgl-$(VERSION).a
STATIC_ALIAS := liblwsdlgl.a
STATIC_LIB := $(BUILD)/$(STATIC_LIBNAME)

ifneq (,$(filter MINGW% MSYS% CYGWIN%,$(UNAME_S)))
SHARED_LIBNAME := lwsdlgl-$(VERSION).dll
SHARED_ALIAS := lwsdlgl.dll
SHARED_LIB := $(BUILD)/$(SHARED_LIBNAME)
IMPORT_LIB := $(BUILD)/liblwsdlgl.dll.a
SHARED_LDFLAGS := -shared -Wl,--export-all-symbols -Wl,--out-implib,$(IMPORT_LIB)
else ifeq ($(UNAME_S),Darwin)
SHARED_LIBNAME := liblwsdlgl-$(VERSION).dylib
SHARED_ALIAS := liblwsdlgl.dylib
SHARED_LIB := $(BUILD)/$(SHARED_LIBNAME)
SHARED_LDFLAGS := -dynamiclib -Wl,-install_name,@rpath/$(SHARED_LIBNAME)
else ifeq ($(UNAME_S),Linux)
SHARED_LIBNAME := liblwsdlgl-$(VERSION).so
SHARED_ALIAS := liblwsdlgl.so
SHARED_LIB := $(BUILD)/$(SHARED_LIBNAME)
SHARED_LDFLAGS := -shared -Wl,-soname,$(SHARED_LIBNAME)
else
$(error unsupported host OS: $(UNAME_S))
endif

PUBLIC_HEADERS := $(wildcard include/lwsdlgl/*.h)
SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c,$(BUILD)/%.o,$(SRC))

LOCAL_PKGCONFIG := $(PREFIX)/lib/pkgconfig:$(PREFIX)/lib64/pkgconfig:$(PREFIX)/share/pkgconfig
export PKG_CONFIG_PATH := $(LOCAL_PKGCONFIG):$(PKG_CONFIG_PATH)

PKG_CFLAGS := $(shell pkg-config --cflags sdl3 sdl3-shadercross 2>/dev/null)
PKG_LIBS := $(shell pkg-config --libs sdl3 sdl3-shadercross 2>/dev/null)

CPPFLAGS += -Iinclude $(PKG_CFLAGS)
CFLAGS ?= -O2
CFLAGS += -std=c11 -Wall -Wextra -Wpedantic -fPIC
LDFLAGS ?=

.PHONY: all clean check-deps deps deps-tools deps-sdl deps-shadercross install uninstall

all: check-deps $(STATIC_LIB) $(SHARED_LIB)

$(BUILD):
	mkdir -p $@

$(BUILD)/%.o: src/%.c $(PUBLIC_HEADERS) | $(BUILD)
	$(CC) $(CPPFLAGS) $(CFLAGS) -Werror -c $< -o $@

$(STATIC_LIB): $(OBJ)
	rm -f $@
	$(AR) rcs $@ $^

$(SHARED_LIB): $(OBJ)
	rm -f $@ $(IMPORT_LIB)
	$(CC) $(SHARED_LDFLAGS) -o $@ $^ $(LDFLAGS) $(PKG_LIBS)

check-deps:
	@command -v pkg-config >/dev/null 2>&1 || { \
		echo "error: pkg-config is required"; \
		echo "run: make deps"; exit 1; }
	@pkg-config --atleast-version=3.4.0 sdl3 >/dev/null 2>&1 || { \
		echo "error: SDL3 >= 3.4.0 development files must be installed system-wide or under PREFIX=$(PREFIX)"; \
		echo "run: make deps"; \
		echo "manual source install:"; \
		echo "  git clone --depth 1 https://github.com/libsdl-org/SDL.git"; \
		echo "  cmake -S SDL -B SDL/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DSDL_TESTS=OFF"; \
		echo "  cmake --build SDL/build"; \
		echo "  sudo cmake --install SDL/build --prefix $(PREFIX)"; exit 1; }
	@pkg-config --exists sdl3-shadercross >/dev/null 2>&1 || { \
		echo "error: SDL_shadercross development files must be installed system-wide or under PREFIX=$(PREFIX)"; \
		echo "run: make deps"; \
		echo "manual source install:"; \
		echo "  git clone --depth 1 --recurse-submodules https://github.com/libsdl-org/SDL_shadercross.git"; \
		echo "  cmake -S SDL_shadercross -B SDL_shadercross/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=$(PREFIX) -DSDLSHADERCROSS_VENDORED=ON -DSDLSHADERCROSS_CLI=OFF -DSDLSHADERCROSS_INSTALL=ON"; \
		echo "  cmake --build SDL_shadercross/build"; \
		echo "  sudo cmake --install SDL_shadercross/build --prefix $(PREFIX)"; exit 1; }

deps: deps-shadercross
	@echo "SDL3 and SDL_shadercross are ready."

deps-tools:
ifeq ($(UNAME_S),Darwin)
	@command -v brew >/dev/null 2>&1 || { echo "error: Homebrew is required on macOS: https://brew.sh"; exit 1; }
	@HOMEBREW_NO_AUTO_UPDATE=1 brew install pkg-config cmake ninja git sdl3
else ifneq (,$(filter MINGW% MSYS% CYGWIN%,$(UNAME_S)))
	@pacman -S --needed --noconfirm git make mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-pkgconf mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-SDL3
else ifeq ($(UNAME_S),Linux)
	@set -e; \
	if command -v apt-get >/dev/null 2>&1; then \
		sudo apt-get update; \
		sudo apt-get install -y build-essential pkg-config cmake ninja-build git; \
		sudo apt-get install -y libsdl3-dev || true; \
	elif command -v dnf >/dev/null 2>&1; then \
		sudo dnf install -y gcc gcc-c++ make pkgconf-pkg-config cmake ninja-build git; \
		sudo dnf install -y SDL3-devel || true; \
	elif command -v pacman >/dev/null 2>&1; then \
		sudo pacman -S --needed --noconfirm base-devel pkgconf cmake ninja git sdl3; \
	else \
		echo "No supported package manager found. Install a C compiler, make, pkg-config, cmake, ninja and git, then run make deps again."; exit 1; \
	fi
else
	@echo "error: unsupported host OS: $(UNAME_S)"; exit 1
endif

deps-sdl: deps-tools
	@set -e; \
	if pkg-config --atleast-version=3.4.0 sdl3 >/dev/null 2>&1; then \
		echo "SDL3 already installed: $$(pkg-config --modversion sdl3)"; \
	else \
		echo "SDL3 not found system-wide; building it into $(PREFIX)"; \
		rm -rf $(DEPS)/SDL; mkdir -p $(DEPS); \
		git clone --depth 1 https://github.com/libsdl-org/SDL.git $(DEPS)/SDL; \
		cmake -S $(DEPS)/SDL -B $(DEPS)/SDL/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(PREFIX) -DSDL_TESTS=OFF -DSDL_EXAMPLES=OFF; \
		cmake --build $(DEPS)/SDL/build; \
		if { [ -d "$(PREFIX)" ] && [ -w "$(PREFIX)" ]; } || { [ ! -d "$(PREFIX)" ] && [ -w "$$(dirname "$(PREFIX)")" ]; }; then cmake --install $(DEPS)/SDL/build --prefix $(PREFIX); \
		elif command -v sudo >/dev/null 2>&1; then sudo cmake --install $(DEPS)/SDL/build --prefix $(PREFIX); \
		else cmake --install $(DEPS)/SDL/build --prefix $(PREFIX); fi; \
	fi

deps-shadercross: deps-sdl
	@set -e; \
	if pkg-config --exists sdl3-shadercross >/dev/null 2>&1; then \
		echo "SDL_shadercross already installed: $$(pkg-config --modversion sdl3-shadercross)"; \
	else \
		echo "SDL_shadercross not found system-wide; building it into $(PREFIX)"; \
		rm -rf $(DEPS)/SDL_shadercross; mkdir -p $(DEPS); \
		git clone --depth 1 --recurse-submodules https://github.com/libsdl-org/SDL_shadercross.git $(DEPS)/SDL_shadercross; \
		cmake -S $(DEPS)/SDL_shadercross -B $(DEPS)/SDL_shadercross/build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$(PREFIX) -DCMAKE_PREFIX_PATH=$(PREFIX) -DSDLSHADERCROSS_VENDORED=ON -DSDLSHADERCROSS_SHARED=ON -DSDLSHADERCROSS_STATIC=OFF -DSDLSHADERCROSS_CLI=OFF -DSDLSHADERCROSS_INSTALL=ON; \
		cmake --build $(DEPS)/SDL_shadercross/build; \
		if { [ -d "$(PREFIX)" ] && [ -w "$(PREFIX)" ]; } || { [ ! -d "$(PREFIX)" ] && [ -w "$$(dirname "$(PREFIX)")" ]; }; then cmake --install $(DEPS)/SDL_shadercross/build --prefix $(PREFIX); \
		elif command -v sudo >/dev/null 2>&1; then sudo cmake --install $(DEPS)/SDL_shadercross/build --prefix $(PREFIX); \
		else cmake --install $(DEPS)/SDL_shadercross/build --prefix $(PREFIX); fi; \
	fi

install: check-deps $(STATIC_LIB) $(SHARED_LIB)
	install -d $(DESTDIR)$(PREFIX)/include/lwsdlgl $(DESTDIR)$(PREFIX)/lib
	install -m 0644 $(PUBLIC_HEADERS) $(DESTDIR)$(PREFIX)/include/lwsdlgl/
	install -m 0644 $(STATIC_LIB) $(DESTDIR)$(PREFIX)/lib/$(STATIC_LIBNAME)
ifneq (,$(filter MINGW% MSYS% CYGWIN%,$(UNAME_S)))
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m 0755 $(SHARED_LIB) $(DESTDIR)$(PREFIX)/bin/$(SHARED_LIBNAME)
	install -m 0644 $(IMPORT_LIB) $(DESTDIR)$(PREFIX)/lib/liblwsdlgl.dll.a
	cd $(DESTDIR)$(PREFIX)/bin && ln -sfn $(SHARED_LIBNAME) $(SHARED_ALIAS) 2>/dev/null || true
else
	install -m 0755 $(SHARED_LIB) $(DESTDIR)$(PREFIX)/lib/$(SHARED_LIBNAME)
	cd $(DESTDIR)$(PREFIX)/lib && ln -sfn $(SHARED_LIBNAME) $(SHARED_ALIAS)
endif
	cd $(DESTDIR)$(PREFIX)/lib && ln -sfn $(STATIC_LIBNAME) $(STATIC_ALIAS)

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/include/lwsdlgl
	rm -f $(DESTDIR)$(PREFIX)/lib/$(STATIC_LIBNAME) $(DESTDIR)$(PREFIX)/lib/$(STATIC_ALIAS)
ifneq (,$(filter MINGW% MSYS% CYGWIN%,$(UNAME_S)))
	rm -f $(DESTDIR)$(PREFIX)/bin/$(SHARED_LIBNAME) $(DESTDIR)$(PREFIX)/bin/$(SHARED_ALIAS) $(DESTDIR)$(PREFIX)/lib/liblwsdlgl.dll.a
else
	rm -f $(DESTDIR)$(PREFIX)/lib/$(SHARED_LIBNAME) $(DESTDIR)$(PREFIX)/lib/$(SHARED_ALIAS)
endif

clean:
	rm -rf $(BUILD)
