import sys
import pycpabe as pc

argc = len(sys.argv)

if argc < 4:
	print("Usage: encdec [pk] [sk] [ap]")
	print("pk: path to publc key")
	print("sk: path to secret key")
	print("ap: access policy")
	sys.exit()

pk = sys.argv[1]
sk = sys.argv[2]
ap = sys.argv[3]

data = sys.stdin.readline().split('\n')[0]
print data

ct = pc.new_cpabebuf()
ct = pc.cpabe_enc_b(pk, data, len(data), ap, ct)

if ct is None:
	print("Encrypt failed!")
	sys.exit()
clen = pc.cpabebuf_len(ct)
print("Encrypt success!")
print("[ct len = %d]" % (clen));

pt = pc.new_cpabebuf()
pt = pc.cpabe_dec_b(pk, sk, pc.cdata(pc.cpabebuf_data(ct), clen), clen, pt)

if pt is None:
	print("Decrypt failed!")
	sys,exit()

plen = pc.cpabebuf_len(pt)
print("Decrypt success!")
print("%s [pt len = %d]" % (pc.cdata(pc.cpabebuf_data(pt), plen), plen))
