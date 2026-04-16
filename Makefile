all:
	@cc src/*.c 		\
		-o main 		\
		-Wall -Werror 	\
		-I include 		\
		-O3 -ffast-math -march=native -flto

clean:
	@rm main