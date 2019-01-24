import sys
import pycpabe

argc = len(sys.argv)

if argc < 3:
	print("Usage: setup [pk] [mk]")
	print("pk: path to generate public key")
	print("mk: path to generate master key")
	sys.exit()

pk = sys.argv[1]
mk = sys.argv[2]

if pycpabe.cpabe_setup('pk','mk') == -1:
	print("Setup failed!")
	sys.exit()

print("Setup success!")
print("Public key: %s" % pk)
print("Master key: %s" % mk)
