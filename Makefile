CXX=g++
CFLAGS=-Wall -pedantic
LDFLAGS=-lX11 -lpthread -lm -lz
INSTALLDIR=/usr/local

NAME=jastegal
FILES=utils.o jastegal.o encode.o decode.o compress.o

ifeq (${DEBUG},1)
	CFLAGS += -g3
endif

all: $(FILES)
	${CXX} ${LDFLAGS} -o ${NAME} ${FILES}

$(FILES): $(FILES:.o=.cpp)
	${CXX} ${CFLAGS} -c $*.cpp

install:
	mkdir -p ${INSTALLDIR}/bin
	install -m 0755 ${NAME} ${INSTALLDIR}/bin

clean:
	rm ${FILES}
	rm ${NAME}

uninstall:
	rm -f ${INSTALLDIR}/bin/${NAME}


