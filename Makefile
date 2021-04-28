CC=g++

IDIR =include
SRC=src
ODIR=bin

CFLAGS=-I $(IDIR)

# enter names of header files defined in `include/` here
_DEPS = rb_tree.h rb_node.h rb_iterator.h utils.h rb.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# enter `path/to/file.o` for each file defined in `src/` here
_OBJ = client.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

# generate object files for all source files, following the same directory structure
$(ODIR)/%.o: $(SRC)/%.cpp $(DEPS)
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

# final executable image
RBT : $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(ODIR) RBT
