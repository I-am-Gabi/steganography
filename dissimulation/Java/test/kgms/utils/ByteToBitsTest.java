package kgms.utils;

import org.junit.Test;

import static org.junit.Assert.*;

public class ByteToBitsTest {

    @Test
    public void testGetBitsLeft() throws Exception {
        ByteToBits b = new ByteToBits();
        int nbBytes = 2;
        b.addData(new byte[nbBytes], nbBytes);
        assertEquals("Result", nbBytes * Bits.BYTE_SIZE, b.getBitsLeft());
    }

    @Test
    public void testGetBits() throws Exception {
        ByteToBits b = new ByteToBits();
        byte nb = (byte)0b10100101;
        byte tab [] = {nb, nb, nb, nb, nb, nb};
        b.addData(tab, tab.length);
        assertEquals("Result", (byte)0b00000101, b.getBits(3));
        assertEquals("Result", (byte)0b00000001, b.getBits(3));
        assertEquals("Result", (byte)0b00000011, b.getBits(3));
        assertEquals("Result", (byte)0b00000010, b.getBits(3));
    }
}