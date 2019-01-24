import sys
import pycpabe

argc = len(sys.argv)

if argc < 5:
	print("Usage: enc [pk] [pt] [ap] [ct]")
	print("pk: path to public key")
	print("pt: path to original file (plain text)")
	print("ap: access policy")
	print("ct: path to encrypted file (cipher text)")
	sys.exit()

pk = sys.argv[1]
pt = sys.argv[2]
ap = sys.argv[3]
ct = sys.argv[4]

if pycpabe.cpabe_fenc(pk, pt, ap, ct) == -1:
	print("Encrypt failed!")
	sys.exit()

print("Encrypt success!")
print("File (%s) encrypted to file (%s) with policy (%s)." % (pt, ct, ap))
