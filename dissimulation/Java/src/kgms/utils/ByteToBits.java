package kgms.utils;

import java.util.LinkedList;

/**
 * ByteToBits is a util to manipulate bytes lists & to access bits within
 * @author KGMS
 */
public class ByteToBits {
    private LinkedList<Byte> bytes;
    private byte currentByte;
    private int bitsLeftInCurrentByte;

    public ByteToBits(){
        bytes = new LinkedList<>();
    }

    /**
     * Add the nbBytes bytes contained in data into the structure
     * @param data The list of bytes to add
     * @param nbBytes The number of the bytes to add
     */
    public void addData(byte data[], int nbBytes){
        for (int i = 0; i < nbBytes; i++)
            bytes.add(data[i]);
    }

    public int getBitsLeft(){
        return bitsLeftInCurrentByte + (Bits.BYTE_SIZE * bytes.size());
    }

    /**
     * Extract some bits from the currently treated byte
     * @param nbBits The amount of bits to extract from the current byte
     * @return A byte containing the bits asked
     */
    public byte getBits(int nbBits) {
        byte b;
        if (nbBits > bitsLeftInCurrentByte){
            nbBits -= bitsLeftInCurrentByte;
            b = (byte)(Bits.getMostSignBits(currentByte, bitsLeftInCurrentByte) << nbBits);
            currentByte = bytes.pop();
            bitsLeftInCurrentByte = Bits.BYTE_SIZE - nbBits;
            b = Bits.replaceLessSignBits(b, Bits.getMostSignBits(currentByte, nbBits), nbBits);
            currentByte = (byte)(currentByte << nbBits);
        }else{
            bitsLeftInCurrentByte -= nbBits;
            b = Bits.getMostSignBits(currentByte, nbBits);
            currentByte = (byte)(currentByte << nbBits);
        }
        return b;
    }
}
