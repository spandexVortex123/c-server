all:
	gcc main.c init.c utils.c -o main -Wall -Wextra

clean:
	rm main