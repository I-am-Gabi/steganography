package kgms.message;

import kgms.utils.Bits;
import org.junit.Test;

import java.io.*;

import static org.junit.Assert.*;

public class HuffmanCompressionTest {

    @Test
    public void testConstructor() throws IOException {
        HuffmanCompression hf = new HuffmanCompression(new StandardMessage("a"), false, false, false, false, false);
        byte[] b = new byte[32];
        int count = hf.read(b);
        for (int i = 0; i < count; ++i){
            System.out.println(Bits.byteToString(b[i]));
        }
//        System.out.println(Bits.byteToString(hf.getWordPub((byte) 'a')[0]));
//        System.out.println(Bits.byteToString(hf.getWordPub((byte) 'b')[0]));
//        System.out.println(Bits.byteToString(hf.getWordPub((byte) 'c')[0]));
//        System.out.println(Bits.byteToString(hf.getWordPub((byte) 'd')[0]));
//        System.out.println(Bits.byteToString(hf.getWordPub((byte) 'e')[0]));
    }

    @Test
    public void testRead() throws Exception {
        HuffmanCompression hf = new HuffmanCompression(new StandardMessage("aabdecdaebade"), false, false, false, false, false);
        byte[] tab = new byte[32];
        int count = hf.read(tab);
        assertEquals("Number of symbols - 1", Bits.byteToString((byte)0b00000100), Bits.byteToString(tab[0]));

        assertEquals("ASCII for d", Bits.byteToString((byte)0b01100100), Bits.byteToString(tab[1]));
        assertEquals("two", Bits.byteToString((byte)0b00000010), Bits.byteToString(tab[2]));
        assertEquals("code for d with padding", Bits.byteToString((byte)0b00000000), Bits.byteToString(tab[3]));

        assertEquals("ASCII for e", Bits.byteToString((byte)0b01100101), Bits.byteToString(tab[4]));
        assertEquals("two", Bits.byteToString((byte)0b00000010), Bits.byteToString(tab[5]));
        assertEquals("code for e with padding", Bits.byteToString((byte)0b01000000), Bits.byteToString(tab[6]));

        assertEquals("ASCII for c", Bits.byteToString((byte)0b01100011), Bits.byteToString(tab[7]));
        assertEquals("three", Bits.byteToString((byte)0b00000011), Bits.byteToString(tab[8]));
        assertEquals("code for c with padding", Bits.byteToString((byte)0b10000000), Bits.byteToString(tab[9]));

        assertEquals("ASCII for b", Bits.byteToString((byte)0b01100010), Bits.byteToString(tab[10]));
        assertEquals("three", Bits.byteToString((byte)0b00000011), Bits.byteToString(tab[11]));
        assertEquals("code for b with padding", Bits.byteToString((byte)0b10100000), Bits.byteToString(tab[12]));

        assertEquals("ASCII for a", Bits.byteToString((byte)0b01100001), Bits.byteToString(tab[13]));
        assertEquals("two", Bits.byteToString((byte)0b00000010), Bits.byteToString(tab[14]));
        assertEquals("code for a with padding", Bits.byteToString((byte)0b11000000), Bits.byteToString(tab[15]));

        assertEquals("five: number of bits used in the last byte",
                Bits.byteToString((byte)0b00000101), Bits.byteToString(tab[16]));

        assertEquals("header size", 17, count);

        count = hf.read(tab);

        assertEquals("message 1/4", Bits.byteToString((byte)0b11111010), Bits.byteToString(tab[0]));
        assertEquals("message 2/4", Bits.byteToString((byte)0b00110000), Bits.byteToString(tab[1]));
        assertEquals("message 3/4", Bits.byteToString((byte)0b11011011), Bits.byteToString(tab[2]));
        assertEquals("message 4/4", Bits.byteToString((byte)0b10001000), Bits.byteToString(tab[3]));

        assertEquals("message size", 4, count);
    }

    @Test
    public void testCompressLevel6() throws Exception {
        HuffmanCompression hf = new HuffmanCompression(new StandardMessage("aabdecdaebade"), true, false, false, false, false);
        byte[] tab = new byte[32];

        int count = hf.read(tab);

        assertEquals("Number of symbols - 1", Bits.byteToString((byte)0b00000100), Bits.byteToString(tab[0]));
        assertEquals("D", Bits.byteToString((byte)0b01100100), Bits.byteToString(tab[1]));
        assertEquals("E", Bits.byteToString((byte)0b01100101), Bits.byteToString(tab[2]));
        assertEquals("C", Bits.byteToString((byte)0b01100011), Bits.byteToString(tab[3]));
        assertEquals("B", Bits.byteToString((byte)0b01100010), Bits.byteToString(tab[4]));
        assertEquals("A", Bits.byteToString((byte)0b01100001), Bits.byteToString(tab[5]));
        assertEquals("Shape", Bits.byteToString((byte)0b10011000), Bits.byteToString(tab[6]));

        assertEquals("five: number of bits used in the last byte",
                Bits.byteToString((byte)0b00000101), Bits.byteToString(tab[7]));

        assertEquals("header size", 8, count);

        count = hf.read(tab);

        /*for (int i = 0; i < count; ++i)
            System.out.println(Bits.byteToString(tab[i]));*/

        assertEquals("message 1/4", Bits.byteToString((byte)0b11111010), Bits.byteToString(tab[0]));
        assertEquals("message 2/4", Bits.byteToString((byte)0b00110000), Bits.byteToString(tab[1]));
        assertEquals("message 3/4", Bits.byteToString((byte)0b11011011), Bits.byteToString(tab[2]));
        assertEquals("message 4/4", Bits.byteToString((byte)0b10001000), Bits.byteToString(tab[3]));

        assertEquals("message size", 4, count);
    }

    @Test
    public void testGetBytesLeft() throws Exception {
        HuffmanCompression hf = new HuffmanCompression(new StandardMessage("aabdecdaebade"), false, false, false, false, false);
        byte[] tab = new byte[4];

        assertEquals("bytesLeft", 21, hf.getBytesLeft());
        int count = hf.read(tab);
        assertEquals("count", 4, count);
        assertEquals("bytesLeft", 17, hf.getBytesLeft());
        count = hf.read(tab);
        assertEquals("count", 4, count);
        assertEquals("bytesLeft", 13, hf.getBytesLeft());
        count = hf.read(tab);
        assertEquals("count", 4, count);
        assertEquals("bytesLeft", 9, hf.getBytesLeft());
        count = hf.read(tab);
        assertEquals("count", 4, count);
        assertEquals("bytesLeft", 5, hf.getBytesLeft());
        count = hf.read(tab);
        assertEquals("count", 4, count);
        assertEquals("bytesLeft", 1, hf.getBytesLeft());
        count = hf.read(tab);
        assertEquals("count", 1, count);
        assertEquals("bytesLeft", 0, hf.getBytesLeft());
        HuffmanCompression.Dictionnaire a = new HuffmanCompression.Dictionnaire();
    }

    @Test
    public void testGetFileSize() throws Exception {
        File f = new File ("E:\\home\\mathieu\\code\\github\\kgms\\dissimulation\\Java\\out\\production\\Dissimulation\\a.txt");
        BufferedWriter bf = new BufferedWriter(new FileWriter(f));
        for (int i = 0; i < 256; ++i)
            bf.write("" + (char)i);
        bf.close();
    }

    @Test
    public void testReset() throws Exception {

    }
}