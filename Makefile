# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -g -O2 -MMD -MP -I/opt/X11/include
LDFLAGS = -L/opt/X11/lib -lX11

# Target executable
TARGET = rainet

# Source directories
SRCDIR = .
OBJDIR = obj

# Find all .cc files recursively
SOURCES = $(shell find $(SRCDIR) -name "*.cc")

# Generate object file names
OBJECTS = $(SOURCES:./%.cc=$(OBJDIR)/%.o)

# Generate dependency files
DEPS = $(OBJECTS:.o=.d)

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files to object files
$(OBJDIR)/%.o: ./%.cc
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Include dependency files
-include $(DEPS)

# Clean build artifacts
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Declare phony targets
.PHONY: all clean