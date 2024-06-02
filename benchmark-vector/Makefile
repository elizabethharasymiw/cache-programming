target:
	g++ bench.cpp -std=c++11 -isystem benchmark/include \
  -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

run:
	./mybenchmark

clean:
	rm mybenchmark
