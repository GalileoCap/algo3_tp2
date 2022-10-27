CXX := g++
CFLAGS := -std=c++11 -lm -lcrypt -O2 -pipe #TODO: Flags

SRCDIR := ./src
BUILDDIR := ./build
TESTDIR := ./tests

ej1DIR := $(SRCDIR)/ej1
ej2DIR := $(SRCDIR)/ej2
ej3DIR := $(SRCDIR)/ej3
ej4DIR := $(SRCDIR)/ej4

ENTREGA := Cappella_Mallol_Teplizky_Stemberg.zip

default: main
.PHONY: clean

entrega: clean
	zip $(ENTREGA) Makefile README.md src test -r9
	
all: clean builddir main debug test submit
main: clean builddir ej1_main ej2_main ej3_main ej4_main
debug: clean builddir ej1_debug ej2_debug ej3_debug ej4_debug
test: clean builddir ej1_test ej2_test ej3_test ej4_debug
submit: clean builddir ej1_submit ej2_submit ej3_submit ej4_submit

%_main: builddir
	$(CXX) $(CFLAGS) $($*DIR)/*.cc -o $(BUILDDIR)/$*

%_debug: builddir
	$(CXX) $(CFLAGS) -g -D DEBUG $($*DIR)/*.cc -o $(BUILDDIR)/$@

%_test: builddir
	$(CXX) $(CFLAGS) \
		$(filter-out $($*DIR)/main.cc, $(wildcard $($*DIR)/*.cc)) \
		test/{$*,gtest-1.8.1/*}.cc \
		-o $(BUILDDIR)/$@

ej1_submit: builddir
	@printf "To submit ej1 do: \ncat $(ej1DIR)/{utils.h,dfs.h,*.cc} > $(BUILDDIR)/$@.cc && sed -i '/#pragma once/d' $(BUILDDIR)/$@.cc && sed -i '/#include \"/d' $(BUILDDIR)/$@.cc && $(CXX) $(CFLAGS) $(BUILDDIR)/$@.cc -o $(BUILDDIR)/$@\n"


ej2_submit: builddir
	@printf "TODO: Submit EJ2\n"

ej3_submit: builddir
	@printf "TODO: Submit EJ3\n"

ej4_submit: builddir
	@printf "TODO: Submit EJ4\n"

builddir:
	mkdir -p $(BUILDDIR)

clean:
	rm -rf $(BUILDDIR) $(ENTREGA)
