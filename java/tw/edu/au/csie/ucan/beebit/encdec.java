package tw.edu.au.csie.ucan.beebit;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.nio.charset.StandardCharsets;
import java.io.IOException;

class encdec {
	public static void main(String[] args) {

		if(args.length < 3) {
			System.out.printf("Usage: encdec [pk] [sk] [ap]\n");
			System.out.printf("pk: path to public key\n");
			System.out.printf("sk: path to secret key\n");
			System.out.printf("ap: access policy\n");
			System.exit(-1);
		}

		String pk = args[0];
		String sk = args[1];
		String ap = args[2];

		cpabeJNI bee = new cpabeJNI();
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String s = "";
		try {
			s = br.readLine();
		} catch(IOException e) {
			System.out.println(e.toString());
		} 

		byte[] ct = bee.enc(pk, s.getBytes(), ap);
		if(ct == null) {
			System.out.printf("Encrypt failed!\n");
			System.exit(-1);
		}
		String ct_str = new String(ct, StandardCharsets.UTF_8);
		System.out.printf("Encrypt success!\n");
		System.out.printf("[ct len = %d]\n", ct.length);

    		byte[] pt = bee.dec(pk, sk, ct);
		if(pt == null) {
			System.out.printf("Decrypt failed!\n");
			System.exit(-1);
		}
		System.out.printf("Decrypt success!\n");
		String pt_str = new String(pt, StandardCharsets.UTF_8);
		System.out.printf("%s [pt len = %d]\n", pt_str, pt.length);
	}	
}
