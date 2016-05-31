package FileToByte;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.LinkedList;

public class FileByteStream {
    private long bytesRead;
    private int bitsLeftInCurrentByte;
    private byte currentByte;
    private FileInputStream in;
    private LinkedList<Byte> bytes;
    private static final int BYTES_TO_READ = 32;
    private static final int BYTE_SIZE = 8;

    public FileByteStream(){
        bytes = new LinkedList<>();
    }
    public void openFile(String filePath) throws IOException {
        in = new FileInputStream(filePath);
        readBits();
        bytesRead = 0;
        currentByte = bytes.pop();
        bitsLeftInCurrentByte = BYTE_SIZE;
    }
    //lis l'octet en commençant par le bit de poids fort (à gauche)
    private byte getBitsFromByte(byte b, int nbBits){
        return (byte) (b >>> (BYTE_SIZE - nbBits));
    }
    private void nextByte() throws IOException {
        if (bytes.size() < 1)
            readBits();
        currentByte = bytes.pop();
        ++bytesRead;
    }
    public Byte getBits(int nbBits) throws IOException {
        if (nbBits > bitsLeftInCurrentByte){
            byte b = getBitsFromByte(currentByte, bitsLeftInCurrentByte);
            nbBits -= bitsLeftInCurrentByte;
            b = (byte) (b << nbBits);
            nextByte();
            b = (byte) (b | getBitsFromByte(currentByte, nbBits));
            currentByte = (byte) (currentByte << nbBits);
            bitsLeftInCurrentByte = BYTE_SIZE - nbBits;
            return b;
        }else{
            bitsLeftInCurrentByte -= nbBits;
            byte b = getBitsFromByte(currentByte, nbBits);
            currentByte = (byte) (currentByte << nbBits);
            return b;
        }
    }
    public long getFileSize() throws IOException {
        return in.getChannel().size();
    }
    public long getBitsLeft() throws IOException {
        return ((getFileSize() - bytesRead - 1) * BYTE_SIZE) + bitsLeftInCurrentByte;
    }
    private void readBits() throws IOException {
        byte[] tab = new byte[BYTES_TO_READ];
        int count = in.read(tab);
        for (int i = 0; i < count; ++i)
            bytes.add(tab[i]);
    }
    public static void main(String[] args) throws IOException {
        FileByteStream f = new FileByteStream();
        f.openFile("E:\\Users\\Mathieu\\Documents\\GitHub\\kgms\\prototype\\java\\resources\\byte.txt");
        System.out.println(f.getBitsLeft());
        System.out.println(Integer.toBinaryString(f.getBits(8)));
        System.out.println(f.getBitsLeft());
    }
}
