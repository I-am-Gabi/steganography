package kgms.message;

import java.io.*;
import java.nio.channels.FileChannel;


public class StandardMessage implements Message{
    private FileInputStream in;
    private long bytesRead; 

    public StandardMessage(String msg) throws IOException{
        File f = new File(msg);
        if (!f.exists() || f.isDirectory()){
            f = File.createTempFile("tmp", "");
            BufferedWriter bw = new BufferedWriter(new FileWriter(f));
            bw.write(msg);
            bw.close();
        }
        in = new FileInputStream(f);
        bytesRead = 0;
    }

    public StandardMessage(File f) throws IOException{
        in = new FileInputStream(f);
        bytesRead = 0;
    }

    public byte getNextByte() throws IOException{
        ++bytesRead;
        return (byte)in.read();
    }

    public int read(byte[] tab) throws IOException {
        int count = in.read(tab);
        bytesRead += count > 0 ? count : 0;
        return count;
    }
    /**
    * Extract the FileChannel associated with the file and gives its size
    * @return The number of bytes contained in the file
    * @throws IOException 
    */
    public long getFileSize() throws IOException {
        return in.getChannel().size();
    }

    public boolean isEmpty() throws IOException{
        return getBytesLeft() <= 0;
    }
    public long getBytesLeft() throws IOException{
        return (getFileSize()) - bytesRead;
    }

    /*
     * Place le pointeur de lecture au début du message
     */
    public void reset() throws IOException{
        FileChannel fc = in.getChannel();
        bytesRead = 0;
        fc.position(0);// set the file pointer to byte position 0;
    }
}
