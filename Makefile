# Makefile in qss/

CC = gcc
CFLAGS = -Wall -g -O3   # Opzioni comuni: tutti i warning, informazioni di debug
LDFLAGS =               # Opzioni per il linker (se ce ne fossero, es. -lm per libreria matematica)

# Directory per gli header e i sorgenti della libreria
LIB_DIR = wlibs
INCLUDE_DIR = $(LIB_DIR) # La directory wlibs contiene anche gli header

# Files sorgente del progetto
MAIN_SRC =wmain.c
LIB_SRCS = $(LIB_DIR)/wvector.c $(LIB_DIR)/wembedding.c $(LIB_DIR)/wstring.c # Aggiungi qui tutti i .c della tua libreria

# Tutti i files sorgente da compilare
SRCS = $(MAIN_SRC) $(LIB_SRCS)

# Files oggetto corrispondenti
# Sostituisce .c con .o per ogni file sorgente, mantenendo il percorso
OBJS = $(SRCS:.c=.o)

# Nome dell'eseguibile finale
TARGET = qss

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $@

# Regola per compilare i files .c in .o
# -I$(INCLUDE_DIR) dice a GCC dove cercare gli header
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
