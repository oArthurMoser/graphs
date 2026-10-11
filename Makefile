.PHONY: all m1 m2 run-m1 run-m2 clean

all: m1 m2

m1:
	$(MAKE) -C m1 build

m2:
	$(MAKE) -C m2 build

run-m1:
	$(MAKE) -C m1 run

run-m2:
	$(MAKE) -C m2 run

clean:
	$(MAKE) -C m1 clean
	$(MAKE) -C m2 clean

