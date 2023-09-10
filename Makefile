all:
	gcc main.c -lpthread -o main -Wall -Wextra -g

clean:
	rm main