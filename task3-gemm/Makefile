gemm: main.cpp
	g++ main.cpp -o gemm -O0 -Wall -Werror -std=c++11 

.PHONY: clean
clean:
	- rm -f gemm

.PHONY: run
run: 
	./gemm

.PHONY: rmdata
rmdata:
	- rm -rf data*	 