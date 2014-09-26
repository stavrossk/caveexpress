SO_EXT                    = so
SO_LDFLAGS                = -shared
SO_CFLAGS                 = -fpic
SO_LIBS                  := -ldl

SDL_LIBS                 += $(EMSCRIPTEN_TARGET_ROOT)/emsdk/sdl2/lib/libSDL2.a
SDL_CFLAGS               += -I$(EMSCRIPTEN_TARGET_ROOT)/emsdk/sdl2/include/SDL2
#SDL_IMAGE_LIBS           += $(EMSCRIPTEN_TARGET_ROOT)/emsdk/sdl2/lib/libSDL2_image.a
#SDL_IMAGE_CFLAGS         +=
SDL_MIXER_LIBS           += $(EMSCRIPTEN_TARGET_ROOT)/emsdk/sdl2/lib/libSDL2_mixer.a
SDL_MIXER_CFLAGS         +=

CFLAGS                   += -D_GNU_SOURCE -D_BSD_SOURCE -D_XOPEN_SOURCE
CFLAGS                   += -Wno-c++11-extensions -Wno-shift-op-parentheses -Wno-warn-absolute-paths
# CFLAGS                   += --jcache
# LDFLAGS                  += --jcache
EMSCRIPTEN               := 1
EXE_EXT                  ?= .html
HAVE_SDL_IMAGE_H         ?= 1
HAVE_SDL_MIXER_H         ?= 1

#(APPNAME)_LDFLAGS       += -s DEAD_FUNCTIONS="['_glPushClientAttrib','_glPopClientAttrib','_glPointSize']"
$(APPNAME)_LDFLAGS       += -s WARN_ON_UNDEFINED_SYMBOLS=1
#$(APPNAME)_LDFLAGS       += -s LEGACY_GL_EMULATION=1
#$(APPNAME)_LDFLAGS       += -s TOTAL_MEMORY=134217728
ifdef DEBUG
#$(APPNAME)_LDFLAGS       += -s LABEL_DEBUG=1
#$(APPNAME)_LDFLAGS       += -s GL_DEBUG=1
$(APPNAME)_LDFLAGS       += -s FS_LOG=1
$(APPNAME)_LDFLAGS       += -s ASSERTIONS=2
$(APPNAME)_LDFLAGS       += -g4
CFLAGS                   += -g4
else
#$(APPNAME)_LDFLAGS       += --closure 1
endif
#$(APPNAME)_LDFLAGS       += -O2
$(APPNAME)_LDFLAGS       += --shell-file contrib/installer/html5/shell.html
$(APPNAME)_LDFLAGS       += --js-library contrib/installer/html5/library.js
#$(APPNAME)_LDFLAGS       += --js-library contrib/installer/html5/lua.js
#$(APPNAME)_LDFLAGS       += --memory-init-file 1
ifeq ($(Q),)
$(APPNAME)_LDFLAGS       += -s VERBOSE=1
endif
