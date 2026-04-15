all:
	@cc src/*.c -o main -Wall -Werror -I include -O2

clean:
	@rm main