OS_TARGET ?= LINUX
C_OPT ?= -O1

export BUILD_PATH := build
SRC_PATH := src
INCLUDE_PATH := include
TEST_PATH := test

ARCHIVE := libary.a

OBJ_FILES := ring_buff.o arena.o test.o

ERROR_FLAGS := -Wall -Wextra -Wno-unused-parameter -Wvla

export CFLAGS := -std=c11 $(ERROR_FLAGS) -DOS_TARGET=$(OS_TARGET) -I$(INCLUDE_PATH) 

MKDIR := mkdir

ifeq ($(OS_TARGET), LINUX)
TARGET_PATH := $(SRC_PATH)/os/linux
else ifeq ($(OS_TARGET), WINDOWS)
TARGET_PATH := $(SRC_PATH)/os/win
endif
export TARGET_PATH

TEST_ARTIFACT := test.out

all: static

TEST_FLAGS := -O1 -g3 -std=c11 $(ERROR_FLAGS) -DOS_TARGET=$(OS_TARGET) -I$(INCLUDE_PATH)
test: static
	@echo $(CC) $(TEST_ARTIFACT) $(TEST_PATH)/main.c 
	@$(CC) $(TEST_FLAGS) $(TEST_PATH)/main.c -o $(TEST_ARTIFACT) -L. -l:$(ARCHIVE)
	@echo -e "\n\nRunning tests:\n"
	@./$(TEST_ARTIFACT)

static: $(BUILD_PATH) $(TARGET_PATH) $(ARCHIVE)

$(ARCHIVE): $(OBJ_FILES)
	$(AR) rvc $(ARCHIVE) $(BUILD_PATH)/*

$(BUILD_PATH):
	$(MKDIR) -p $(BUILD_PATH)

%.o: $(SRC_PATH)/%.c
	@echo $(CC) $< $@
	@$(CC) $(C_OPT) $(CFLAGS) -c $< -o $(BUILD_PATH)/$@

.PHONY: $(TARGET_PATH)
$(TARGET_PATH):
	$(MAKE) -f $@/Makefile

clean:
	rm $(BUILD_PATH)/*
	rmdir $(BUILD_PATH)
	rm $(TEST_ARTIFACT)
	rm $(ARCHIVE)

