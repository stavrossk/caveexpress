TARGET             := jsonconvert

$(TARGET)_LINKER   := $(CXX)
$(TARGET)_FILE     := $(TARGET)$(EXE_EXT)
$(TARGET)_LDFLAGS  += $(SDL_LIBS) $(YAJL_LIBS) $(SDL_RWHTTP_LIBS) $(SQLITE3_LIBS) $(LUA_LIBS) $(SO_LIBS)
$(TARGET)_CFLAGS   += $(SDL_CFLAGS) $(YAJL_CFLAGS) $(SDL_RWHTTP_CFLAGS) $(SQLITE3_CFLAGS) $(LUA_CFLAGS)
$(TARGET)_SRCS      = \
	caveexpress/tools/JSONConvert.cpp \
	\
	engine/common/ConfigManager.cpp \
	engine/common/ConfigPersisterSQL.cpp \
	engine/common/ConfigVar.cpp \
	engine/common/CommandSystem.cpp \
	engine/common/Logger.cpp \
	engine/common/SQLite.cpp \
	engine/common/FileSystem.cpp \
	engine/common/LUA.cpp \
	engine/common/URI.cpp \
	engine/common/File.cpp \
	engine/common/String.cpp \
	\
	$(YAJL_SRCS) \
	\
	$(SDL_SRCS) \
	\
	$(SQLITE3_SRCS) \
	\
	$(LUA_SRCS)

ifneq ($(findstring $(TARGET_OS), mingw32 mingw64),)
	$(TARGET)_SRCS +=\
		engine/common/ports/Windows.cpp \
		engine/common/ports/project.rc
	$(TARGET)_LDFLAGS +=
endif

ifneq ($(findstring $(TARGET_OS), netbsd freebsd linux),)
	$(TARGET)_SRCS +=\
		engine/common/ports/Unix.cpp
	$(TARGET)_LDFLAGS +=
endif

ifeq ($(TARGET_OS),nacl)
	$(TARGET)_SRCS +=\
		$(SDL_NET_SRCS) \
		engine/common/ports/NaCl.cpp
	$(TARGET)_LDFLAGS +=
endif

ifeq ($(TARGET_OS),darwin)
	$(TARGET)_SRCS +=\
		engine/engine/common/ports/Unix.cpp \
		engine/engine/common/ports/Darwin.cpp \
		engine/engine/common/ports/CocoaLog.mm \
	$(TARGET)_LDFLAGS +=
endif

$(TARGET)_OBJS     := $(call ASSEMBLE_OBJECTS,$(TARGET))
$(TARGET)_CXXFLAGS := $($(TARGET)_CFLAGS)
$(TARGET)_CCFLAGS  := $($(TARGET)_CFLAGS)
