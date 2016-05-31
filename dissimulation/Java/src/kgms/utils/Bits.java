package kgms.utils;

public class Bits {
    public static int BYTE_SIZE = 8;
    
    /**
     * Replace nbBits of origin byte with nbBits of information byte
     * @param origin The container byte
     * @param information The number of bits to dissumulate
     * @param nbBits Shift quantity
     * @return 
     */
    static public byte encodeByte(byte origin, byte information, int nbBits){
        return (byte) (((origin >> nbBits) << nbBits) | information);
    }

    static public byte replaceLessSignBits(byte origin, byte information, int nbBits){
        return (byte)(((origin >> nbBits) << nbBits)
                | (information & ((1 << nbBits) - 1)));
    }
    static public byte decodeByte(byte b, int nbBits){
        byte mask = 0;
        while (nbBits-- > 0) {
            mask = (byte) (mask << 1);
            ++mask;
        }
        return (byte) (b & mask);
    }

    static public int getLessSignBits(byte b, int nbBits){
        return ((b & 0b11111111) & ((int) Math.pow(2, nbBits) - 1));
    }
    //Ex getMSignBits(0b11100100, 4) returns 0b00001110
    static public byte getMostSignBits(byte b, int nbBits){
        return (byte)((b >> (BYTE_SIZE - nbBits) & ((1 << nbBits) - 1)));
    }

    static public String byteToString(byte b){
        return byteToStringRecursive(b, BYTE_SIZE); //8: number of bits in a byte
    }
    
    static private String byteToStringRecursive(byte b, int n){
        if (n == 1) return String.valueOf(Math.abs(b % 2));
        return byteToStringRecursive((byte) (b >> 1), n - 1) + String.valueOf(Math.abs(b % 2));
    }
}
