# Makefile cu compilare incrementală pentru Service Manager
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = service.exe

# Lista tuturor fișierelor sursă
SRCS = main.cpp \
       ServiceManager.cpp \
       employees/Angajat.cpp \
       employees/Tehnician.cpp \
       employees/Receptioner.cpp \
       employees/Supervizor.cpp \
       electronics/Electrocasnic.cpp \
       electronics/Laptop.cpp \
       electronics/TV.cpp \
       electronics/Frigider.cpp \
       electronics/Masina_Spalat.cpp \
       GestiuneAngajati/GestiuneAngajati.cpp \
       GestiuneElectrocasnice/GestiuneElectrocasnice.cpp \
       GestiuneCereri/cerereReparatie.cpp \
       GestiuneCereri/GestiuneCereri.cpp \
       Raportari/GestiuneRaportari.cpp

# Crează lista de fișiere obiect (.o) din surse
OBJS = $(SRCS:.cpp=.o)

# Include path-uri
INCLUDES = -I. -Iemployees -Ielectronics -IGestiuneAngajati -IGestiuneElectrocasnice -IGestiuneCereri -IRaportari

# Regula principală
all: $(TARGET)

# Linkarea executabilului din fișiere obiect
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regula generică pentru a compila orice .cpp în .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Curăță tot
clean:
	del $(TARGET) 2>nul
	del *.o 2>nul
	del employees\*.o 2>nul
	del electronics\*.o 2>nul
	del GestiuneAngajati\*.o 2>nul
	del GestiuneElectrocasnice\*.o 2>nul
	del GestiuneCereri\*.o 2>nul
	del Raportari\*.o 2>nul

# Compilează și rulează
run: $(TARGET)
	$(TARGET)

# Recompilează de la zero
rebuild: clean all

# Compilează DOAR main.cpp și face link rapid
mainonly: main.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o main.o
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)
	@echo "Recompilat doar main.cpp și făcut link!"

.PHONY: all clean run rebuild mainonly