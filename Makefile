all:
	gcc main.c -lpthread -o main -Wall -Wextra

clean:
	rm main