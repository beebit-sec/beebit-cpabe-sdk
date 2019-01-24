import sys
import pycpabe

argc = len(sys.argv)

if argc < 6:
	print("Usage: keygen [sk] [pk] [mk] [no] [a1] ... [aN]")
	print("sk: path to generate secret key")
	print("pk: path to public key")
	print("mk: path to master key")
	print("no: number of attributeds in generated secret key")
	print("a1 ... aN: attributes")
	sys.exit()

sk = sys.argv[1]
pk = sys.argv[2]
mk = sys.argv[3]
no = int(sys.argv[4])
attrs = []
for i in range(5,5+no):
	print("Attribite %d: %s" % (i-5, sys.argv[i]))
	attrs.append(sys.argv[i])

if pycpabe.cpabe_vkeygen(sk, pk, mk, no, attrs) == -1:
	print("Keygen failed!")
	sys.exit()

print("Keygen success!")
print("Secret key: %s" % sk)
