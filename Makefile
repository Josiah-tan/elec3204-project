.PHONY: all test graph
	
all:
	arduino-cli compile -u -p /dev/ttyS5 -b arduino:avr:uno -v
	python3 client.py
	# "arduino-cli compile -u -p /dev/ttyS"..port.." -b arduino:avr:uno -v

graph:
	python3 graph.py

test:
	arduino-cli compile -u -p /dev/ttyS5 -b arduino:avr:uno -v
	python3 test.py

