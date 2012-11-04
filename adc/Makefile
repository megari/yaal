TARGETS = channels.hh prescaler_constants.hh

all: $(TARGETS)


channels.hh: channels.sh
	./$< > $@

prescaler_constants.hh: prescaler_constants.py
	./$< > $@

clean:
	rm -f $(TARGETS)
