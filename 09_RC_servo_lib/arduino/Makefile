CC=arduino
BOARD=arduino:avr:mega

SOURCE=src/manual_servo/manual_servo.ino

build:
	$(CC) --verify --board $(BOARD) -v $(SOURCE)

flash:
	$(CC) --upload --board $(BOARD) -v $(SOURCE)
