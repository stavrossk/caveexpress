PKG_CONFIG_LIBS_FLAGS := --libs
PKG_CONFIG_CFLAGS_FLAGS := --cflags

# get only the variables with plain names
MAKE_ENV := $(shell echo '$(.VARIABLES)' | awk -v RS=' ' '/^[a-zA-Z0-9_]+$$/')
SHELL_EXPORT := $(foreach v,$(MAKE_ENV),$(v)='$($(v))')

#TODO the manually added linker flag is more a hack than a solution
define PKG_LIBS
$(shell $(SHELL_EXPORT) $(PKG_CONFIG) $(PKG_CONFIG_LIBS_FLAGS) $(1) --silence-errors || ( if [ -z "$(2)" ]; then echo "-l$(1)"; else echo "-l$(2)"; fi ))
endef

define PKG_CFLAGS
$(shell $(SHELL_EXPORT) $(PKG_CONFIG) $(PKG_CONFIG_CFLAGS_FLAGS) $(1) --silence-errors)
endef

define CMD_FIND
$(shell $(SHELL_EXPORT) which $(1))
endef

CFLAGS += -DHAVE_CONFIG_H
CFLAGS += -g
#CFLAGS += -pipe
#CFLAGS += -Winline
CFLAGS += -Wcast-qual
CFLAGS += -Wcast-align
CFLAGS += -Wpointer-arith
CFLAGS += -Wno-long-long
CFLAGS += -Wno-multichar
CFLAGS += -Wshadow
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wno-sign-compare
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wreturn-type
CFLAGS += -Wwrite-strings
CFLAGS += -Wno-variadic-macros
CFLAGS += -Wno-unknown-pragmas
CFLAGS += -I$(SRCDIR)
CFLAGS += -I$(SRCDIR)/libs

ifeq ($(PROFILING),1)
  CFLAGS  += -pg
  CCFLAGS += -pg
  LDFLAGS += -pg
endif

ifeq ($(DEBUG),1)
  CFLAGS  += -DDEBUG
  CCFLAGS  += -DDEBUG
else
  CFLAGS  += -DNDEBUG
  CCFLAGS  += -DNDEBUG
endif

#CXXFLAGS += -std=gnu++11
CXXFLAGS += -std=c++11
# clang stuff
ifneq (,$(findstring clang,$(CXX)))
#  CXXFLAGS += -Wexit-time-destructors
#  CXXFLAGS += -Wglobal-constructors
  CFLAGS += -Wno-extended-offsetof
  CFLAGS += -Wno-cast-align
  CFLAGS += -Wno-shift-op-parentheses
ifneq ($(TARGET_OS),nacl)
ifeq ($(DEBUG),1)
  CFLAGS += -fsanitize=address -fno-omit-frame-pointer
  LDFLAGS += -fsanitize=address
endif
ifeq ($(USE_CCACHE),1)
  CFLAGS += -Qunused-arguments
endif
endif
endif

CCFLAGS += $(CFLAGS)
CCFLAGS += -Wimplicit

#CCFLAGS += -Werror-implicit-function-declaration
#CCFLAGS += -Wimplicit-int
#CCFLAGS += -Wmissing-prototypes
#CCFLAGS += -Wdeclaration-after-statement
#CCFLAGS += -Wc++-compat

CXXFLAGS += $(CFLAGS)
#CXXFLAGS += -std=c++11
CXXFLAGS += -Wnon-virtual-dtor
CXXFLAGS += -Wno-reorder
