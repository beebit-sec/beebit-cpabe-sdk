package tw.edu.au.csie.ucan.beebit;

class dec {
	public static void main(String[] args) {
		cpabeJNI bee = new cpabeJNI();
		int len = bee.fdec("./pubKey","./secKey_ng","./data.cpabe");
		if(len == -1)
		{
			System.out.print("DEC FAILED WITH NG KEY(JNI)\n");
		}
 
		len = bee.fdec("./pubKey","./secKey_ok","./data.cpabe");
		if(len == -1)
		{
			System.out.print("DEC FAILED WITH OK KEY(JNI)\n");
		}
		System.out.print("DEC SUCCESS(JNI) [len=" + len + "]\n");
	}	
}
