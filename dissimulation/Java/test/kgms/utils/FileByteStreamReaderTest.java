package kgms.utils;

import kgms.message.StandardMessage;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.TemporaryFolder;

import java.io.*;

import static org.junit.Assert.*;

public class FileByteStreamReaderTest {

    @Rule
    public TemporaryFolder temporaryFolder = new TemporaryFolder();

    public String fileString;

    @Before
    public void setup() throws IOException {
        fileString = "Ceci est un test!";
        File f = temporaryFolder.newFile("file.txt");
        BufferedWriter out = new BufferedWriter(new FileWriter(f));
        out.write(fileString);
        out.close();
    }

    /*@Test
    public void testOpenFile() throws Exception {
        File f = temporaryFolder.getRoot().listFiles()[0];
        FileByteStreamReader fbs = new FileByteStreamReader();
        fbs.openMsg(f);

        *//*BufferedReader in = new BufferedReader(new FileReader(f));
        assertEquals("Faux", fileString, in.readLine());*//*
    }*/

    @Test
    public void testGetBits() throws Exception {
        File f = temporaryFolder.getRoot().listFiles()[0];
        FileByteStreamReader fbs = new FileByteStreamReader();
        fbs.openMsg(new StandardMessage(f));
        //Lire la première lettre
        byte c = (byte)(fbs.getBits(5) << 3);
        c = (byte)(c | fbs.getBits(3));
        assertEquals("Result", fileString.charAt(0), (char)c);
        //Lire la troième lettre avec le cas particulier inter-octet
        fbs.getBits(5);
        c = (byte)(fbs.getBits(5) << 6);
        c = (byte)(c | fbs.getBits(6));
        assertEquals("Result", fileString.charAt(2), (char)c);
        //Lire la quatrième lettre
        assertEquals("Result", fileString.charAt(3), (char)fbs.getBits(8));
    }

    @Test
    public void testGetFileSize() throws Exception {
        File f = temporaryFolder.getRoot().listFiles()[0];
        FileByteStreamReader fbs = new FileByteStreamReader();
        fbs.openMsg(new StandardMessage(f));

        assertEquals("Result", f.length(), fbs.getFileSize());
    }

    @Test
    public void testGetBitsLeft() throws Exception {
        File f = temporaryFolder.getRoot().listFiles()[0];
        FileByteStreamReader fbs = new FileByteStreamReader();
        fbs.openMsg(new StandardMessage(f));

        int bitsToRead = 1;
        fbs.getBits(bitsToRead);
        assertEquals("Result", (f.length() * Bits.BYTE_SIZE) - bitsToRead, fbs.getBitsLeft());
    }

    @Test
    public void testAdditionalData() throws Exception {
        File f = temporaryFolder.getRoot().listFiles()[0];
        FileByteStreamReader fbs = new FileByteStreamReader();
        fbs.openMsg(new StandardMessage(f));

        String endStr = "Je suis l'additional data";
        fbs.setEndData(endStr.getBytes());
        String str = "";
        while(fbs.getBitsLeft() > 0){
            str = str + (char)fbs.getBits(8);
        }
        assertEquals("Result", fileString + endStr, str);
    }
}