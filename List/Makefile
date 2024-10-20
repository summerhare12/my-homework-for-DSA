# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -O2

# Targets and files
TARGET = List.exe
SOURCE = List.cpp
LATEX = xelatex
LATEX_SOURCE = ListReport.tex
LATEX_TARGET = ListReport.pdf

# Default target
all: $(TARGET) $(LATEX_TARGET)

# Compile List.cpp
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# Compile LaTeX document
$(LATEX_TARGET): $(LATEX_SOURCE)
	$(LATEX) $(LATEX_SOURCE)

# Clean up generated files
clean:
	rm -f $(TARGET) $(LATEX_TARGET) *.aux *.log *.out

.PHONY: all clean