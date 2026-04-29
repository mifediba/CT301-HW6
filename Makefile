# Compiler
GPP = g++

# Compilation flags
GPPFlags = -Wall -Wextra -Werror -Wfatal-errors -std=c++20

# Source and output names 
SRC = GameOfLife.cpp BasicGOL.cpp ThreeStateGOL.cpp WrapAroundGOL.cpp RollingHistory.cpp GOLApp.cpp
HEADER = GameOfLife.h BasicGOL.h ThreeStateGOL.h WrapAroundGOL.h RollingHistory.h

HWNUM = HW6
TARNAME = Marytheresa_Ifediba

# Target name
TARGET = GOLApp

# Compile
$(HWNUM).a: GameOfLife.o BasicGOL.o ThreeStateGOL.o WrapAroundGOL.o RollingHistory.o
	ar -rcs $(HWNUM).a $^
	rm $^

# Clean
clean:
	rm -f $(TARGET)
	@echo "Removed all object files."

package:
	tar -c Makefile $(filter-out GOLApp.cpp, $(SRC)) $(HEADER) -f $(HWNUM)_$(TARNAME).tar
