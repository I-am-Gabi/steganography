package kgms.utils;

import org.junit.Test;

import static org.junit.Assert.*;

public class BitsTest {


    @Test
    public void testEncodeByte() throws Exception {
        byte origin = (byte) 224;
        byte information = (byte) 7;
        assertEquals("Result", (byte) 231, Bits.encodeByte(origin, information, 5));
    }

    @Test
    public void testByteToString() throws Exception {
        assertEquals("Result", "00000001", Bits.byteToString((byte) 1));
        assertEquals("Result", "10001010", Bits.byteToString((byte) 138));
        assertEquals("Result", "00101101", Bits.byteToString((byte) 45));
    }

    @Test
    public void testgetMostSignBits() throws Exception {
        assertEquals("Result", (byte)0b00001110, Bits.getMostSignBits((byte)0b11100100, 4));
    }

    @Test
    public void testDecodeByte() throws Exception {
        byte b = (byte) 231;
        assertEquals("Result", (byte) 7, Bits.decodeByte(b, 3));
    }

    @Test
    public void testReplaceLessSignBits() throws Exception {
        assertEquals("Result", (byte)0b10110101,
                Bits.replaceLessSignBits((byte)0b10110001, (byte)0b01101101, 3));
    }
}