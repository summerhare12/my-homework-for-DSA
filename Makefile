# Makefile  
  
# 编译器  
CC = g++  
  
# 编译器选项  
CFLAGS = -Wall  
  
# 目标文件  
TARGET = mylist.exe  
  
# 源文件  
SOURCE = mylist.cpp  
  
all: $(TARGET)  
  
$(TARGET): $(SOURCE)  
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)  
  
clean:  
	rm -f $(TARGET)  