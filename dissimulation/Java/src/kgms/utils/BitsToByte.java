package kgms.utils;

import java.util.LinkedList;

/**
 * BitsToByte is a util to form bytes from bits & to access those bytes
 * @author KGMS
 */
public class BitsToByte {
    private LinkedList<Byte> bytes;
    private byte currentByte;
    private int bitsInCurrentByte;

    public BitsToByte(){
        bytes = new LinkedList<>();
        currentByte = (byte) 0b00000000;
    }

    public int getByteLeft(){
        return bytes.size();
    }


    /**
     * Add nbBits bits contained in b into the currentByte
     * @param b Bits to add
     * @param nbBits The number of bits to add
     */
    public void addData(byte b, int nbBits){
        if (bitsInCurrentByte + nbBits < Bits.BYTE_SIZE){
//            System.out.println("Adding " + Bits.byteToString(b) + " [" + nbBits + "]");
            currentByte = Bits.replaceLessSignBits((byte)(currentByte << nbBits), Bits.getMostSignBits(b, nbBits), nbBits);
            bitsInCurrentByte += nbBits;
        }else{
//            System.out.println("Adding " + Bits.byteToString(b) + " [" + (Bits.BYTE_SIZE - bitsInCurrentByte) + "]");
            currentByte = Bits.replaceLessSignBits(
                    (byte) (currentByte << (Bits.BYTE_SIZE - bitsInCurrentByte)),
                    Bits.getMostSignBits(b, Bits.BYTE_SIZE - bitsInCurrentByte),
                    Bits.BYTE_SIZE - bitsInCurrentByte
            );
            bytes.add(currentByte);
            nbBits -= Bits.BYTE_SIZE - bitsInCurrentByte;
            b = (byte)(b << Bits.BYTE_SIZE - bitsInCurrentByte);
            bitsInCurrentByte = 0;
            addData(b, nbBits);
        }

        /*else{
            currentByte = Bits.replaceLessSignBits((byte)(currentByte << Bits.BYTE_SIZE - bitsInCurrentByte)
                    , (Bits.getMostSignBits(b , Bits.BYTE_SIZE - bitsInCurrentByte))
                    , Bits.BYTE_SIZE - bitsInCurrentByte);
            bytes.add(currentByte);
            currentByte = 0b00000000;
            bitsInCurrentByte = nbBits - (Bits.BYTE_SIZE - bitsInCurrentByte);
            currentByte = Bits.replaceLessSignBits(currentByte, Bits.getMostSignBits((byte)(b << Bits.BYTE_SIZE - bitsInCurrentByte)
                    , bitsInCurrentByte), bitsInCurrentByte);
        }*/
    }

    public void addData(byte[] b, int nbBits){
        if (nbBits == 0)
            return;
        for (int i = 1; (i * 8) < nbBits; ++i)
            addData(b[i - 1], 8);
        if(nbBits % 8 == 0)
            addData(b[(nbBits / 8) - 1], 8);
        else
            addData(b[nbBits / 8], nbBits % 8);
    }


    /**
     * @return A byte
     */
    public int read(byte[] byteTab){
        int i = 0;
        while(i < byteTab.length && this.getByteLeft() > 0)
            byteTab[i++] = bytes.remove(0);
        return i;
    }
}
