top_srcdir = .
prefix = /usr/local
bindir = ${prefix}/bin
mandir = ${prefix}/share/man

cpabe_dir = ${top_srcdir}/cpabe-0.11
example_dir = ${top_srcdir}/example
python_dir = ${top_srcdir}/python
pbc_dir = ${top_srcdir}/pbc-0.5.14
bswabe_dir = ${top_srcdir}/libbswabe-0.9
jni_dir = ${top_srcdir}/jni
jni_package_dir = ${jni_dir}/tw/edu/au/csie/ucan/beebit
glib_dir = ${top_srcdir}/glib-2.25.2
gmp_dir = ${top_srcdir}/gmp-6.1.2
openssl_dir = ${top_srcdir}/openssl-1.0.2l

JAVA_PATH = /opt/jdk1.8.0_131
JAVA_BIN_PATH = ${JAVA_PATH}/bin
JNI_H_PATH = ${JAVA_PATH}/include
JNI_OS_H_PATH = ${JAVA_PATH}/include/linux

PYTHON_H_PATH = /usr/include/python2.7

CC = gcc
CFLAGS  = -O3 -Wall -g -fPIC \
	-I${JNI_H_PATH} \
	-I${JNI_OS_H_PATH} \
	-I/usr/include/glib-2.0 \
	-I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
	-I/usr/include/pbc \
	-I/usr/local/include/pbc \
	-DPACKAGE_NAME=\"cpabe\" -DPACKAGE_TARNAME=\"cpabe\" -DPACKAGE_VERSION=\"0.11\" -DPACKAGE_STRING=\"cpabe\ 0.11\" -DPACKAGE_BUGREPORT=\"bethenco@cs.berkeley.edu\" -DPACKAGE_URL=\"\" -DSTDC_HEADERS=1 -DHAVE_SYS_TYPES_H=1 -DHAVE_SYS_STAT_H=1 -DHAVE_STDLIB_H=1 -DHAVE_STRING_H=1 -DHAVE_MEMORY_H=1 -DHAVE_STRINGS_H=1 -DHAVE_INTTYPES_H=1 -DHAVE_STDINT_H=1 -DHAVE_UNISTD_H=1 -DSTDC_HEADERS=1 -DHAVE_FCNTL_H=1 -DHAVE_STDDEF_H=1 -DHAVE_STRING_H=1 -DHAVE_STDLIB_H=1 -DHAVE_MALLOC=1 -DLSTAT_FOLLOWS_SLASHED_SYMLINK=1 -DHAVE_VPRINTF=1 -DHAVE_LIBCRYPTO=0 -DHAVE_LIBCRYPTO=0 -DHAVE_STRCHR=1 -DHAVE_STRDUP=1 -DHAVE_MEMSET=1 -DHAVE_GMP=1 -DHAVE_PBC=1 -DHAVE_BSWABE=1

LDFLAGS = -L. -lbeebit-cpabe \
	-lglib-2.0   \
	-Wl,-rpath /usr/local/lib -lgmp \
	-Wl,-rpath /usr/local/lib -lbswabe \
	-lpbc \
	-lcrypto \
	-lgmp

DISTNAME = beebit-cpabe-0.1

TARGETS  = libbeebit-cpabe-0.1.a cpabe-setup cpabe-keygen cpabe-enc cpabe-dec cpabe-encdec cpabe-encdecb

DEVTARGS = test-lang TAGS

MANUALS  = $(TARGETS:=.1)
HTMLMANS = $(MANUALS:.1=.html)

all: $(TARGETS)

python: _pycpabe.so
	cp _pycpabe.so ${python_dir}

_pycpabe.so: ${cpabe_dir}/bee-setup.o ${cpabe_dir}/common.o ${cpabe_dir}/bee-enc.o ${cpabe_dir}/policy_lang.o ${cpabe_dir}/bee-keygen.o ${cpabe_dir}/bee-dec.o ${python_dir}/pycpabe_wrap.o ${cpabe_dir}/cpabebuf.o
	$(CC) -shared -o $@ $^ /usr/local/lib/libbswabe.a /usr/local/lib/libpbc.a /usr/local/lib/libgmp.a /usr/local/lib/libglib-2.0.a /usr/local/lib/libssl.a /usr/local/lib/libcrypto.a

${python_dir}/pycpabe_wrap.c: ${python_dir}/pycpabe.i
	swig -python -builtin ${python_dir}/pycpabe.i

jni: libbeebit-cpabe-0.1.so
	${JAVA_BIN_PATH}/javac ${jni_package_dir}/cpabeJNI.java
	${JAVA_BIN_PATH}/javac -cp ${jni_dir} ${jni_package_dir}/setup.java
	${JAVA_BIN_PATH}/javac -cp ${jni_dir} ${jni_package_dir}/keygen.java
	${JAVA_BIN_PATH}/javac -cp ${jni_dir} ${jni_package_dir}/enc.java
	${JAVA_BIN_PATH}/javac -cp ${jni_dir} ${jni_package_dir}/dec.java
	${JAVA_BIN_PATH}/javac -cp ${jni_dir} ${jni_package_dir}/encdec.java

libbeebit-cpabe-0.1.so: ${cpabe_dir}/bee-setup.o ${cpabe_dir}/common.o ${cpabe_dir}/bee-enc.o ${cpabe_dir}/policy_lang.o ${cpabe_dir}/bee-keygen.o ${cpabe_dir}/bee-dec.o ${jni_dir}/cpabeJNI.o
	$(CC) -shared -o $@ $^ /usr/local/lib/libbswabe.a /usr/local/lib/libpbc.a /usr/local/lib/libgmp.a /usr/local/lib/libglib-2.0.a /usr/local/lib/libssl.a /usr/local/lib/libcrypto.a
	ln -f -s $@ libbeebit-cpabe.so

# user-level compilation
libbeebit-cpabe-0.1.a: ${cpabe_dir}/bee-setup.o ${cpabe_dir}/common.o ${cpabe_dir}/bee-enc.o ${cpabe_dir}/policy_lang.o ${cpabe_dir}/bee-keygen.o ${cpabe_dir}/bee-dec.o ${cpabe_dir}/cpabebuf.o
#	$(CC) -c $^ $(CFLAGS)
	$(AR) rcs -o $@ $^ 
	ln -f -s $@ libbeebit-cpabe.a

#setup.o common.o enc.o policy_lang.o keygen.o dec.

cpabe-setup:$(example_dir)/cpabe-setup.o 
	$(CC) -o $(example_dir)/$@ $^ $(LDFLAGS)

cpabe-keygen:$(example_dir)/cpabe-keygen.o 
	$(CC) -o $(example_dir)/$@ $^ $(LDFLAGS)

cpabe-enc:$(example_dir)/cpabe-enc.o
	$(CC) -o $(example_dir)/$@ $^ $(LDFLAGS)

cpabe-dec:$(example_dir)/cpabe-dec.o
	$(CC) -o $(example_dir)/$@ $^ $(LDFLAGS)

cpabe-encdec:$(example_dir)/cpabe-encdec.o
	$(CC) -o $(example_dir)/$@ $^ $(LDFLAGS)
cpabe-encdecb:$(example_dir)/cpabe-encdecb.o
	$(CC) -o $(example_dir)/$@ $^ $(LDFLAGS)

%.o: %.c *.h Makefile
	$(CC) -fPIC -c -o $@ $< $(CFLAGS) -I${PYTHON_H_PATH}

#libpbc:
#	$(shell cd ${pbc_dir}; sh configure; make; sudo make install)

#libbswabe:
#	$(shell cd ${bswabe_dir}; sh configure; make; sudo make install)

clean:
	rm -f libbeebit-cpabe-0.1.a libbeebit-cpabe.a libbeebit-cpabe-0.1.so libbeebit-cpabe.so _pycpabe.so
	rm -f ${example_dir}/cpabe-setup ${example_dir}/cpabe-keygen ${example_dir}/cpabe-enc ${example_dir}/cpabe-dec ${example_dir}/cpabe-encdec ${example_dir}/cpabe-encdecb ${example_dir}/*.o 
	rm -f ${jni_dir}/*Key* ${jni_dir}/cpabeJNI.o ${jni_package_dir}/*.class 
	rm -f ${python_dir}/*.pyc ${python_dir}/*.o ${python_dir}/*.c ${python_dir}/pycpabe.py ${python_dir}/_pycpabe.so
	echo "Hello Beebit" > ${example_dir}/data
	echo "Hello Beebit" > ${jni_dir}/data
	echo "Hello Beebit" > ${python_dir}/data
	$(shell cd cpabe-0.11; rm -f *.o)

install:
	sudo cp libbeebit-cpabe-0.1.a /usr/local/lib
	sudo ln -f -s /usr/local/lib/libbeebit-cpabe-0.1.a /usr/local/lib/libbeebit-cpabe.a
	sudo cp beebitcpabe.h /usr/local/include

uninstall:
	sudo rm /usr/local/lib/libbeebit-cpabe-0.1.a
	sudo rm /usr/local/lib/libbeebit-cpabe.a
	sudo rm /usr/local/include/beebitcpabe.h
