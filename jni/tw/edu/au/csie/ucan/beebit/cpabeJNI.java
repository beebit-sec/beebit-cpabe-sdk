package tw.edu.au.csie.ucan.beebit;

public class cpabeJNI {

	public static int EXIT_SUCCESS = 0;
	public static int EXIT_FAILURE = -1;

	public native int setup(String pk_path, String  mk_path);
	public native int keygen(String pk_path, String mk_path, String sk_path, int attr_no, String... params);
	public native int vkeygen(String pk_path, String mk_path, String sk_path, int attr_no, String[] params);
	public native byte[] enc(String pk_path, byte[] pt, String pllicy_str);
	public native byte[] dec(String pk_path, String sk_path, byte[] ct);
	public native int fenc(String pk_path, String pt_path, String policy_str, String ct_path);
	public native int fdec(String pk_path, String sk_path, String ct_path, String pt_path);

	static { System.loadLibrary("beebit-cpabe"); };
}
