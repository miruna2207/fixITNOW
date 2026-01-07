# --- CONFIGURARE COMPILATOR ---
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g
TARGET = service.exe

# --- DIRECTORII ȘI INCLUDE-URI ---
# Adăugăm toate folderele pentru ca g++ să găsească headerele
INCLUDES = -I. -Iemployees -Ielectronics -IGestiuneAngajati -IGestiuneElectrocasnice -IGestiuneCereri -IRaportari

# --- COLECTARE AUTOMATĂ SURSE ---
# Căutăm toate fișierele .cpp din toate folderele proiectului
SRCS = $(wildcard *.cpp) \
       $(wildcard employees/*.cpp) \
       $(wildcard electronics/*.cpp) \
       $(wildcard GestiuneAngajati/*.cpp) \
       $(wildcard GestiuneElectrocasnice/*.cpp) \
       $(wildcard GestiuneCereri/*.cpp) \
       $(wildcard Raportari/*.cpp)

# Generăm lista fișierelor obiect (.o)
OBJS = $(SRCS:.cpp=.o)

# --- REGULI DE COMPILARE ---

all: $(TARGET)

# Linkarea finală a executabilului
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regula universală pentru fișiere .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# --- COMENZI UTILITARE ---

# Curățare sigură pentru Windows (fără erori de tip Linux)
clean:
	@echo Curatare fisiere obiect...
	@if exist *.o del /q /s *.o 2>nul
	@if exist $(TARGET) del /q $(TARGET) 2>nul

# Rulează programul
run: all
	./$(TARGET)

# Șterge tot și recompilează de la zero
rebuild: clean all

.PHONY: all clean run rebuild