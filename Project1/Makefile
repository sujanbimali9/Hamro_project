CC = g++
CFLAGS = -I./httplib/ -I./rapidjson/

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
TARGET = build/online_food_order

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) 

build/%.o: %.cpp | build
	$(CC) -c $< -o $@ $(CFLAGS)

build:
	mkdir -p $@

clean:
	rm -rf build
