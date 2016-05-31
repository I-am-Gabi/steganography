package kgms.utils;

import kgms.message.Message;

import java.io.IOException;


/**
 * This class is a wrapper to manipulate the files as a simple chain of bytes
 * @author KGMS
 */
public class FileByteStreamReader {
    private long bytesRead;
    private ByteToBits parser;
    private byte[] endData;
    private Message in;
    private static final int CACHE_BYTE_SIZE = 32;

    public FileByteStreamReader(){
        endData = new byte[0];
    }

    public void openMsg(Message m) throws IOException {
        parser = new ByteToBits();
        in = m;
        bytesRead = 0;
        readBytesFromFile();
    }

    public void setEndData(byte[] data){
        endData = data;
    }

    public byte getBits(int nbBits) throws IOException {
        if (parser.getBitsLeft() <= nbBits)
            readBytesFromFile();
        return parser.getBits(nbBits);
    }
    
    /**
     * Extract the FileChannel associated with the file and gives its size
     * @return The number of bytes contained in the file
     * @throws IOException 
     */
    public long getFileSize() throws IOException {
        return in.getFileSize();
    }

    /**
     * Counts the numbers bits left to read in the file
     * @return The numbers bits left to read in the file
     * @throws IOException
     */
    private long getBitsLeftInFile() throws IOException{
        return (in.getBytesLeft()) * Bits.BYTE_SIZE;
    }

    public long getBitsLeft() throws IOException {
        return getBitsLeftInFile() + parser.getBitsLeft()
                + (endData.length * Bits.BYTE_SIZE);
    }

    /**
     * Reads the bytes from the file, storing result into a BytetoBits parser to manipulate bits
     * @see ByteToBits
     * @throws IOException 
     */
    private void readBytesFromFile() throws IOException {
//        System.out.println("avant: " + getBitsLeftInFile() / 8);
//        getBitsLeftInFile();
        if (!in.isEmpty()){
            byte[] tab = new byte[CACHE_BYTE_SIZE];
            int count = in.read(tab);
            this.bytesRead += count;
            parser.addData(tab, count);
        }else if (endData.length > 0){
            parser.addData(endData, endData.length);
            endData = new byte[0];
        }
//        System.out.println("apres: " + getBitsLeftInFile() / 8);
    }
}
