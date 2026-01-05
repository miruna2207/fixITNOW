# Compilatorul folosit
CXX = g++
# Flag-uri pentru compilare (C++17 pentru unique_ptr și mapări moderne)
CXXFLAGS = -std=c++17 -Wall -I. -IGestiuneAngajati -IGestiuneElectrocasnice -Ielectronics

# Identificăm automat toate fișierele .cpp din foldere și subfoldere
SRCS = main.cpp \
       ServiceManager.cpp\
       $(wildcard employees/*.cpp)\
       $(wildcard GestiuneAngajati/*.cpp) \
       $(wildcard GestiuneElectrocasnice/*.cpp) \
       $(wildcard electronics/*.cpp)\
       $(wildcard GestiuneCereri/*.cpp)


# Numele executabilului final
TARGET = service.exe

# Regula principală
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Curățarea fișierelor generate
clean:
	del $(TARGET)