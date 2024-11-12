# 编译器和编译选项
CXX = g++
CXXFLAGS = -Wall -std=c++11

# 源文件和目标文件
SRC = test.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = test

# LaTeX 文件
TEX = report.tex
PDF = report.pdf

# 默认目标
all: run report

# 编译并运行程序
run: $(EXEC)
	./$(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 编译 LaTeX 报告
report: $(PDF)

$(PDF): $(TEX)
	xelatex $(TEX)

# 清理生成的文件
clean:
	rm -f $(OBJ) $(EXEC) *.aux *.log *.out

.PHONY: all run report clean