############################################################################

SRC := $(wildcard *.cpp)
HDR := $(wildcard *.h)
EXE := raytrace

############################################################################

CXX     :=  g++-4.8
CXXOPTS := -std=c++11
CXXOPTS += -O3
CXXOPTS += -DNDEBUG
CXXOPTS += -march=native
CXXOPTS += -fopenmp -lgomp

############################################################################

.PHONY: clean

raytrace: $(SRC) $(HDR)
	$(CXX) $(CXXOPTS) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)

############################################################################


