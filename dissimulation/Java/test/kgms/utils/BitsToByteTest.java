package kgms.utils;

import org.junit.Test;
import static org.junit.Assert.*;

/**
 * @author KGMS
 */
public class BitsToByteTest {

    @Test
    public void testGetBytesLeft() throws Exception {
        BitsToByte b = new BitsToByte();
        byte bits = (byte)0b10000010; //128
        assertEquals("Result", 0, b.getByteLeft());
        b.addData(bits, 8);
        assertEquals("Result", 1, b.getByteLeft());
        bits = 0b000010010; //18
        b.addData(bits, 5);
        assertEquals("Result", 1, b.getByteLeft());
        b.addData(bits, 3);
        assertEquals("Result", 2, b.getByteLeft());
    }

    @Test
    public void testRead() {
        BitsToByte b = new BitsToByte();
        byte byteTab[] = new byte[5];
        byte bits = (byte) 0b10000010; //128
        b.addData(bits, 8);
        b.read(byteTab);
        assertEquals("Result", (byte) 0b10000010, byteTab[0]);
        System.out.println(byteTab[1]);
    }

    @Test
    public void testRead2(){
        BitsToByte b = new BitsToByte();
        byte byteTab[] = new byte[5];
        byte bits = (byte) 0b10000010;
        b.addData(bits, 8);
        byte bits1 = 0b00010000;
        b.addData(bits1, 5);
        byte bits2 = 0b01011000;
        b.addData(bits2, 5);
        byte bits3 = 0b01001000;
        b.addData(bits3, 6);
        b.read(byteTab);
        assertEquals("Result", (byte) 0b10000010, byteTab[0]); //128
        assertEquals("Result", (byte) 0b00010010, byteTab[1]); //18
        assertEquals("Result", (byte) 0b11010010, byteTab[2]); //210
        assertEquals("Result", 0, byteTab[3]);
        assertEquals("Result", 0, byteTab[4]);
    }
}
