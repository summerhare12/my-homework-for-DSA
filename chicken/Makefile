# Makefile  
  
# 编译器  
CC = g++  
  
# 编译器选项  
CFLAGS = -Wall  
  
# 目标文件  
TARGET = chicken.exe  
  
# 源文件  
SOURCE = chicken.cpp  
  
all: $(TARGET)  
  
$(TARGET): $(SOURCE)  
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)  
  
clean:  
	rm -f $(TARGET)  