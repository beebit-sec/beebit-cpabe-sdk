package tw.edu.au.csie.ucan.beebit;

class enc {
	public static void main(String[] args) {
		cpabeJNI bee = new cpabeJNI();
		int len = bee.fenc("./pubKey", "./data", "role <= 2", "default");
		if(len == -1)
		{
			System.out.print("ENC FAILED(JNI)\n");
		}
		System.out.print("ENC SUCCESS(JNI) [len=" + len + "]\n");
	}	
}
