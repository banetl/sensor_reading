REQUIREMENTS=requirements.txt
TRASH=**/*.pyc **/__pycache__ python/sensor_pb2.py

all: comp

comp:
	protoc -I=. --python_out=./python ./sensor.proto

init:
	pip3 install -r $(REQUIREMENTS)

clean:
	rm -rf $(TRASH)

.PHONY: init clean comp all
