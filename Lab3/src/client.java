import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.net.Socket;

public class client {
	
	
	public static void main(String[] argv) throws Exception {
	
		Socket socket = new Socket("127.0.0.1", 55554);

		byte[] array = new byte[1024];
		
		InputStream in = socket.getInputStream();
		
		FileOutputStream out = new FileOutputStream("src/FileTransfer2.txt");
		
		BufferedOutputStream bOut = new BufferedOutputStream(out);
		
		int bytes = in.read(array, 0, array.length);
		
		bOut.write(array, 0, bytes);
		
		bOut.close();
		
		socket.close();
	}
}
