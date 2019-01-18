P ?=	/dev/ttyUSB0
E ?=	m328p
BR :=	9600

.PHONY: all
all:
	pio run -e $(E)

.PHONY: upload
upload:
	pio run --target program -e $(E)

.PHONY: serial
serial:
	picocom -b $(BR) -fn $(P)

.PHONY: dev
dev: all upload serial

.PHONY: clean
clean:
	pio run --target clean -e $(E)

