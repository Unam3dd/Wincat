CC = cl.exe

SRC = src/server.c \
	src/stream.c \
	src/utils.c \
	src/client.c \
	src/help.c \
	src/main.c

INCLUDES = includes

OBJ_FILES = server.obj \
		stream.obj \
		utils.obj \
		client.obj \
		help.obj \
		main.obj

OUTPUT_NAME = wincat.exe

build:
	$(CC) /c /TC /I $(INCLUDES) $(SRC)
	link.exe $(OBJ_FILES) /MACHINE:x64 /LIBPATH:lib ws2_32.lib pthreadVCE3.lib
	move server.exe dist\$(OUTPUT_NAME)

all: build
	del $(OBJ_FILES)

clean:
	del $(OBJ_FILES)