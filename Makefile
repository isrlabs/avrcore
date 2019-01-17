P :=	/dev/ttyUSB0
BR :=	9600

.PHONY: all
all:
	pio run

.PHONY: upload
upload:
	pio run --target program

.PHONY: serial
serial:
	picocom -b $(BR) -fn $(P)

.PHONY: dev
dev: all upload serial

.PHONY: clean
clean:
	pio run --target clean

