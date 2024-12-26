CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -DDEBUG -fmax-errors=2 -g

TARGET = $(basename $(SRC))

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

