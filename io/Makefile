TARGETS = other.hh ports.hh

all: $(TARGETS)

other.hh: other.sh
	./$< > $@

ports.hh: ports.sh
	./$< > $@

clean:
	rm -f $(TARGETS)
