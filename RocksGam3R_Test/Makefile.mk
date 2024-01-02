CC = gcc
CFLAGS = -Wall -g

# Standardziel, falls kein Ziel beim Aufruf angegeben wird
TARGET ?= HelloWorld

# Regel, um das Hauptziel zu erstellen (standardmäßig nur das ausführbare Programm)
only_executable: 
	@echo "Building $(TARGET)"
	@make VERBOSE=1 $(TARGET)

# Regel, um das ausführbare Programm zu erstellen
$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).o
	@echo "Executable $(TARGET) created successfully"

# Regel, um alle Dateien zu erstellen
all: $(TARGET).o
	@echo "All files created successfully"

# Regel, um die Objektdatei zu erstellen
$(TARGET).o: $(TARGET).s
	$(CC) $(CFLAGS) -c $(TARGET).s
	@echo "Object file $(TARGET).o created successfully"

# Regel, um die Assemblerausgabe zu erstellen
$(TARGET).s: $(TARGET).i
	$(CC) $(CFLAGS) -S $(TARGET).i
	@echo "Assembler file $(TARGET).s created successfully"

# Regel, um die Präprozessorausgabe zu erstellen
$(TARGET).i: $(TARGET).c
	$(CC) $(CFLAGS) -E $(TARGET).c -o $(TARGET).i
	@echo "Preprocessed file $(TARGET).i created successfully"

# Regel, um alle generierten Dateien zu löschen
clean_all: clean
	rm -f $(TARGET).i $(TARGET).s
	@echo "All generated files cleaned successfully"

# Reinigungsregel
clean:
	@echo "Removing Executable and Object file"
	rm -f $(TARGET) $(TARGET).o
	@echo "Cleaned up successfully"
