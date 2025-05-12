USE_GDB			 ?= false
LIST_DEBUG ?= false

CXX         = g++
OPT_FLAGS   = -mavx2 -pg -g
OPT_LEVEL   ?= -O3
CXXFLAGS    = -Wall -Wextra -std=c++17 -I$(LIB_DIR) $(OPT_FLAGS) $(OPT_LEVEL)

LDFLAGS  = -D _DEBUG -ggdb3 -std=c++17 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++14-compat -Wmissing-declarations -Wcast-align -Wcast-qual                	\
 -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness               \
 -Wformat=2 -Winline -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion         \
 -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default            \
 -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing                  \
 -Wno-old-style-cast -Wno-varargs -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer              \
 -Wlarger-than=81920 -Wstack-usage=81920 -pie -fPIE -Werror=vla # -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,leak,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr


ifeq (LIST_DEBUG, true)
	CXXFLAGS += -D LIST_DEBUG
endif

ifeq (USE_GDB, true)
	LDFLAGS +- -g
endif

SRC_DIR     = src
LIB_DIR     = lib
BIN_DIR     = obj
BUILD_DIR   = build

SRC_CPP     = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_CPP     = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRC_CPP))
ARCHIVE     = $(BIN_DIR)/logger.a

.PHONY: all clean rebuild

all: $(ARCHIVE)

$(ARCHIVE): $(OBJ_CPP) | $(BUILD_DIR)
	ar rcs $@ $(OBJ_CPP)
	# $(CXX) $(OBJ_CPP) -o $@ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR) $(TARGET)

rebuild: clean all