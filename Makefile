.PHONY: all test graph
	
all:
	# compile and run client.py
	arduino-cli compile -u -p /dev/ttyS5 -b arduino:avr:uno -v
	python3 client.py
	# "arduino-cli compile -u -p /dev/ttyS"..port.." -b arduino:avr:uno -v

graph:
	# graph data from monitor_log.txt
	python3 graph.py

test:
	# compile and run the quick Python test.py script
	arduino-cli compile -u -p /dev/ttyS5 -b arduino:avr:uno -v
	python3 test.py

