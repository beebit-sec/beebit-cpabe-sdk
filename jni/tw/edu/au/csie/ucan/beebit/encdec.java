package tw.edu.au.csie.ucan.beebit;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.io.IOException;

class encdec {
	public static void main(String[] args) {
		cpabeJNI bee = new cpabeJNI();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = "";
		try {
			s = br.readLine();
		} catch(IOException e) {
			System.out.println(e.toString());
		} 

		byte[] ct = bee.enc("./pubKey", s.getBytes(), "role <= 2");
		String ct_str = new String(ct, StandardCharsets.UTF_8);
		System.out.print("ENC SUCCESS(JNI): (Ciphertext) " + ct.length + "\n");

    		byte[] pt = bee.dec("./pubKey", "./secKey_ok", ct);
		String pt_str = new String(pt, StandardCharsets.UTF_8);
		System.out.print("ENC SUCCESS(JNI): " + pt_str + " " + pt.length + "\n");
	}	
}
