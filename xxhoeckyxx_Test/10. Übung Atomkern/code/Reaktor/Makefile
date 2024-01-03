# Enter here BIN-name and sources #
BIN      = exec.out
SOURCE   = main.cpp Prueffolge.cpp PrueffolgeReaktor.cpp Reaktor.cpp Atomkern.cpp
###################################

OBJF     = $(SOURCE:%.cpp=%.o)
DEPFILE  = .dep~
LFLAGS	 = -O2 -flto
CFLAGS   = -O2 -Wall -Wextra -std=c++2x

all: $(BIN)

-include $(DEPFILE)

$(DEPFILE): $(SOURCE)
    $(CXX) -MM $(CFLAGS) $(SOURCE) > $(DEPFILE)

$(BIN): $(OBJF)
    $(CXX) $(LFLAGS) $(OBJF) -o $(BIN) 

clean:
    rm -f $(OBJF) $(BIN) $(DEPFILE)

.cpp.o: 
    $(CXX) $(CFLAGS) -c $< -o $@
