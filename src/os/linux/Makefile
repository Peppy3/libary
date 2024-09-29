
OBJ_FILES := file.o

all: $(OBJ_FILES)

%.o: $(TARGET_PATH)/%.c
	@echo $(CC) $< $@
	@$(CC) $(CFLAGS) -c $< -o $(BUILD_PATH)/$@


