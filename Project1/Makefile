CC = g++
CFLAGS = -I./curl/ -I./rapidjson/
LDFLAGS = -L./curl/ -lcurl

SRCS = apis.cpp \
    CartScreen.cpp \
    Description.cpp \
    HomeScreen.cpp \
    Password.cpp \
    Login.cpp \
    Product.cpp \
    ProductCart.cpp \
    Response.cpp \
    Screen.cpp \


OBJS = $(addprefix build/,$(SRCS:.cpp=.o))
TARGET = build/apis

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

build/%.o: %.cpp | build
	$(CC) -c $< -o $@ $(CFLAGS)

build:
	mkdir -p $@

clean:
	rm -rf build
