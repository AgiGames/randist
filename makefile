CC = gcc
CFLAGS = -I/home/agi/c-libs/pcg-c-0.94/include
LDFLAGS = -L/home/agi/c-libs/pcg-c-0.94/src
LDLIBS = -lpcg_random -lm

TARGET = rng
SRCS = main.c randist.c

$(TARGET): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
