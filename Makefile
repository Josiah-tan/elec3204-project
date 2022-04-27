.PHONY: all test
	
all:
	arduino-cli compile -u -p /dev/ttyS5 -b arduino:avr:uno -v
	python3 client.py
	# "arduino-cli compile -u -p /dev/ttyS"..port.." -b arduino:avr:uno -v

test:
	arduino-cli compile -u -p /dev/ttyS5 -b arduino:avr:uno -v
	python3 test.py
