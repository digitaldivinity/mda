korch: jac3dkorch.cpp mda.h
	g++ -fopenmp -std=c++11 -O3  jac3dkorch.cpp -o arr
testing: jac3dkorch.cpp mda.h
	g++ -fopenmp -std=c++11 -O3 -DKORCH_TESTING jac3dkorch.cpp -o arr 
standard: jac3d.cpp
	g++ -fopenmp -std=c++11 -O3 jac3d.cpp -o arr
run:
	./arr 384 100
