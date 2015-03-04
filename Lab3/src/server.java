import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class server {
  public static void main(String[] args) throws IOException {
	  
    ServerSocket serverSocket = new ServerSocket(2000);
    System.out.println("Start");
    File file = new File("src/file.txt");
    System.out.println(file.toString());
    
    while (true) {
    	
      Socket socket = serverSocket.accept();
      byte[] array = new byte[(int) file.length()];
      BufferedInputStream buffer = new BufferedInputStream(new FileInputStream(file));
      buffer.read(array, 0, array.length);
      
      OutputStream out = socket.getOutputStream();
      System.out.println(array);
      out.write(array, 0, array.length);
      out.flush();
      socket.close();
      System.out.println("Closed");
    }
  }
}