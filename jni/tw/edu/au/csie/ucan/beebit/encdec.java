package tw.edu.au.csie.ucan.beebit;
import java.util.Scanner;
import java.nio.charset.StandardCharsets;

class encdec {
	public static void main(String[] args) {
		cpabeJNI bee = new cpabeJNI();
		Scanner scan = new Scanner(System.in);
		String s = scan.next();

		byte[] ct = bee.enc("./pubKey", s, "role <= 2");
		String ct_str = new String(ct, StandardCharsets.UTF_8);
		System.out.print("ENC SUCCESS(JNI): (Ciphertext) " + ct.length + "\n");

    		byte[] pt = bee.dec("./pubKey", "./secKey_ok", ct);
		String pt_str = new String(pt, StandardCharsets.UTF_8);
		System.out.print("ENC SUCCESS(JNI): " + pt_str + " " + pt.length + "\n");
	}	
}
