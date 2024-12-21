SRC = test.cpp
EXEC = test

# LaTeX 文件
TEX = report.tex
PDF = report.pdf

# 默认目标
all: run report

# 编译并运行程序
run: $(EXEC)
	./$(EXEC)

$(EXEC): $(SRC)
	g++ -o $(EXEC) $(SRC)

# 生成 PDF 报告
report: $(PDF)

$(PDF): $(TEX)
	xelatex $(TEX)

# 清理生成的文件
clean:
# 其他编译规则...

clean:
	rm -f $(EXEC) *.aux *.log *.out *.synctex.gz
.PHONY: all run report clean