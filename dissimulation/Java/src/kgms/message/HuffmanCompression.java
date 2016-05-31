package kgms.message;

import kgms.metrics.MetricsGenerator;
import kgms.utils.Bits;
import kgms.utils.BitsToByte;

import java.util.*;

import java.io.IOException;

public class HuffmanCompression implements Message{
    private BitsToByte btb;
    private BNode tree;
    private Message msg;
    private Map<Byte, Word> dictionnary;
    private long bytesInTranslatedMessage;
    private long bytesRead;
    private int[] freq;
    private int bitsLastByte;
    private int bitsAdded = 0;
    private  double compressionRate;
    private int originalMessNbByte;
    private boolean more;
    private boolean even_more;
    private boolean recursive;
    private boolean show;

    public HuffmanCompression(Message m, boolean more, boolean even_more, boolean recursive, boolean metrics, boolean show) throws IOException {
        this.more = more;
        this.show = show;
        this.even_more = even_more;
        this.recursive = recursive;
        if (more && even_more)
            more = false;
        btb = new BitsToByte();
        this.msg = m;
        MetricsGenerator mg = new MetricsGenerator();
        if (metrics)
            mg.setStartTime("compression");

        tree = createTree(scanFrequencies());
        createDictionnary(tree);
        calculateSize();
        msgHeader();

        if (metrics)
        {
            mg.setEndTime("compression");
            System.out.println("Compression process time : " + mg.getCompressionTime() + "ms");
            if(compressionRate > 0)
                System.out.println("Compression savings : " + compressionRate);
        }
    }

    private int[] scanFrequencies() throws IOException {
        int count, BUFFER_SIZE = 32;
        freq = new int[256];
        byte[] tab = new byte[BUFFER_SIZE];
        originalMessNbByte = (int) msg.getFileSize();
        while((count = msg.read(tab)) > 0)
            for (int i = 0; i < count; ++i)
                ++freq[tab[i] < 0 ? tab[i] + 256 : tab[i]];
        msg.reset();
        return freq;
    }

    private BNode createTree(int[] freq){
        //Sort BNodes by frequencies
        BNode[] nodes = new BNode[256];

        for (int i = 0; i < nodes.length; ++i)
            nodes[i] = new BNode((byte)i, freq[i]);

        Arrays.sort(nodes, (x, y) -> x.frequency - y.frequency);
        LinkedList<BNode> queue = new LinkedList<>();
        //Add BNodes by increasing order
        for (BNode n : nodes)
            if (n.frequency > 0)
                queue.add(n);
        //Algorithm
        while (queue.size() > 1){
            BNode n = new BNode((byte)0, 0, queue.get(0), queue.get(1));
            queue.remove();queue.remove();
            boolean added = false;
            for (int i = 0; i < queue.size(); ++i)
                if (queue.get(i).frequency > n.frequency) {
                    queue.add(i, n);
                    added = true;
                    break;
                }
            //If it must be in the last position
            if (!added)
                queue.add(n);
        }
        //queue.get(0).print();
        return queue.get(0);
    }

    private void createDictionnary(BNode tree){
        dictionnary = new HashMap<>();
        fillDictionnary(tree, new byte[8], 0);
        //Cas particulier 1 lettre
        if (dictionnary.size() == 1)
            dictionnary.put(tree.data, new Word(new byte[]{0}, 1));
        //Décaler les dernières cases vers la gauche
        for (Byte b : dictionnary.keySet()) {
            int bitsNumber = dictionnary.get(b).bitsNumber;
            byte[] word = dictionnary.get(b).word;
            if (bitsNumber % 8 != 0)
                word[bitsNumber / 8] =
                        (byte) (word[bitsNumber / 8] << (Bits.BYTE_SIZE - (dictionnary.get(b).bitsNumber % 8)));
        }
    }

    private void fillDictionnary(BNode n, byte[] word, int index){
        if (n.isLeaf()){
            dictionnary.put(n.data, new Word(word.clone(), index));
            return;
        }
        word[index / 8] = (byte)(word[index / 8] << 1 & 0b11111110);
        fillDictionnary(n.leftChild, word.clone(), index + 1);
        word[index / 8] = (byte)(word[index / 8] | 0b00000001);
        fillDictionnary(n.rightChild, word.clone(), index + 1);
    }

    private void msgHeader() throws IOException {
        btb.addData((byte)(dictionnary.keySet().size() - 1), 8);

        //Symbols & shape
        ArrayList<Byte> treeBytes = new ArrayList<>();
        ArrayList<Byte> symbols = new ArrayList<>();
        sweepTree(treeBytes, tree);
        byte[] shape = new byte[(treeBytes.size() / 8) + 1];
        //Cas particulier ou seulement une lettre
        if (treeBytes.size() == 1)
            symbols.add(treeBytes.get(0));
        for (int i = 1; i < treeBytes.size(); ++i){
            shape[(i - 1) / 8] = (byte)(shape[(i - 1) / 8] << 1);
            if (treeBytes.get(i) == null)
                shape[(i - 1) / 8] = (byte)(shape[(i - 1) / 8] | 0b00000001);
            else
                symbols.add(treeBytes.get(i));
        }
        //If compress more
        if (more){
            //Write symbols
            for (Byte  b : symbols) {
                btb.addData(b, 8);
            }
            //Write shape
            btb.addData(shape, (treeBytes.size() / 8) * 8);
            //Eventual last byte of shape + 0 padding
            if (treeBytes.size() % 8 > 0 && (treeBytes.size() - 3) > 8) {
                btb.addData((byte) (shape[(treeBytes.size() / 8)] << (Bits.BYTE_SIZE - treeBytes.size() % 8)), 8);
            }
            this.calculateCompressionRate(symbols, more);
        }else if (even_more){

        }else{
            for (Byte  b : symbols){
                int bitsNumber = dictionnary.get(b).bitsNumber;
                byte[] w = dictionnary.get(b).word;
                int asciiCode =  b.byteValue() & 0xff;
                if(show)
                    System.out.print("0x" + asciiCode + " : ");
                btb.addData(b, 8);
                btb.addData((byte)bitsNumber, 8);

                for (int i = 0; i < bitsNumber; i += 8){
                    if(show)
                        System.out.print(Bits.byteToString(w[i / 8]) + " ");
                    btb.addData(w[i / 8], 8);
                }
                if(show)
                    System.out.println("(" + bitsNumber + " significative bits starting from MSB)");
            }
            this.calculateCompressionRate(symbols, more);
        }
        btb.addData((byte)bitsLastByte, 8);
        bytesInTranslatedMessage += btb.getByteLeft();
        bytesRead += btb.getByteLeft();
    }

    private void sweepTree(ArrayList<Byte> b, BNode n){
        if (n.isLeaf()){
            b.add(n.data);
        }else{
            b.add(null);
            sweepTree(b, n.leftChild);
            sweepTree(b, n.rightChild);
        }
    }

    private void calculateSize() throws IOException {
        bytesInTranslatedMessage = 0;
        bytesRead = 0;
        int bitsRead = 0;
        byte[] buf = new byte[32];
        int count;
        bitsLastByte = 0;
        while ((count = msg.read(buf)) > 0){
            for (int i = 0; i < count; ++i)
                bitsRead += dictionnary.get(buf[i]).bitsNumber;
            bytesInTranslatedMessage += bitsRead / 8;
            bitsRead %= 8;
        }
        if (bitsRead > 0) {
            bitsLastByte = bitsRead;
            ++bytesInTranslatedMessage;
        }else bitsLastByte = 8;

        msg.reset();
    }

    private void calculateCompressionRate(ArrayList<Byte> symb, boolean more) {
        int compressMessNbByte = 1; //Number of symbols use + 1b to indicate this number
        int compressMessBits = 0;
        int dictionnaryNbOfByte = 0;
        for (Byte  b : symb) {
            int bitsNumber = dictionnary.get(b).bitsNumber;
            byte[] w = dictionnary.get(b).word;
            dictionnaryNbOfByte += 2 + (bitsNumber-1)/8+1;
            compressMessBits += freq[b.byteValue() & 0xff] * bitsNumber;
        }
        if (more) {
            int nbSymbols = dictionnary.keySet().size();
            compressMessNbByte += ((10 * nbSymbols - 4) % 8 == 0) ? (10 * nbSymbols - 4) / 8 : (10 * nbSymbols - 4) / 8 + 1;
        }

        else {
            compressMessNbByte += dictionnaryNbOfByte + 1;
        }
        compressMessNbByte += (compressMessBits-1)/8 + 1;
        //System.out.println("Compress Size : " + compressMessNbByte);
        //System.out.println("Original Size : " + originalMessNbByte);
        compressionRate = (1 - ((double)compressMessNbByte/originalMessNbByte))*100;
        if(compressionRate <= 0)
            System.out.println("Compression Rate : " + String.format("%.1f", compressionRate) + "(Negative saving)");
    }

    public void getCompressionRate(){
        System.out.println("Compression Rate : " + String.format("%.1f", compressionRate));
    }

    @Override
    public int read(byte[] tab) throws IOException {
        if (btb.getByteLeft() == 0 && msg.getBytesLeft() > 0)
            readBytesFromMessage(tab.length);
        int count = btb.read(tab);
        if(show) {
            for (int i = 0; i < count; ++i) {
                if (i % 4 == 0) System.out.println("");
                System.out.print(Bits.byteToString(tab[i]) + "  ");
            }
        }
        return count;
    }

    private void readBytesFromMessage(int goal) throws IOException {
        byte[] tab = new byte[goal];
        int count;
        while (btb.getByteLeft() < goal && (count = msg.read(tab)) > 0) {
            for (int i = 0; i < count; ++i){
                btb.addData(dictionnary.get(tab[i]).word, dictionnary.get(tab[i]).bitsNumber);
                bitsAdded += dictionnary.get(tab[i]).bitsNumber;
            }
        }
        bytesRead += bitsAdded / 8;
        bitsAdded %= 8;
        //Check end of message, padding with 0's
        if (msg.getBytesLeft() == 0 && bitsAdded > 0) {
            btb.addData((byte) 0b00000000, 7);
            ++bytesRead;
        }
    }
    @Override
    public long getBytesLeft() throws IOException {
        if (isEmpty()) return 0;
        return (bytesInTranslatedMessage - bytesRead) + btb.getByteLeft();
    }

    public boolean isEmpty() throws IOException {
        return msg.getBytesLeft() <= 0 && btb.getByteLeft() <= 0;
    }

    @Override
    public long getFileSize() throws IOException {
        return bytesInTranslatedMessage;
    }

    @Override
    public void reset() throws IOException {
        bytesRead = 0;
        msg.reset();
    }

    private class Word {
        private byte[] word;
        private int bitsNumber;
        public Word (byte[] word, int bitsNumber){
            this.word = word;
            this.bitsNumber = bitsNumber;
        }
    }
    private class BNode {
        private Byte data;
        private int frequency;

        private BNode leftChild;
        private BNode rightChild;

        public BNode(byte data, int freq) {
            this(data, freq, null, null);
        }

        public BNode(byte data, int freq, BNode leftChild, BNode rightChild){
            this.data = data;
            this.frequency = freq;
            this.leftChild = leftChild;
            this.rightChild = rightChild;
            if (leftChild != null)
                this.frequency += leftChild.getFrequency();
            if (rightChild != null)
                this.frequency += rightChild.getFrequency();
        }

        public boolean isLeaf(){
            return leftChild == null && rightChild == null;
        }

        /**** Getters ****/
        public byte getData(){
            return this.data;
        }
        public int getFrequency(){
            return this.frequency;
        }
        public BNode getLeft(){
            return this.leftChild;
        }
        public BNode getRight(){
            return this.rightChild;
        }

        /**** Setters ****/
        public void setData(byte data){
            this.data = data;
        }
        public void setFrequency(int freq){
            this.frequency = freq;
        }
        public void setLeft(BNode node){
            this.leftChild = node;
        }
        public void setRight(BNode node){
            this.rightChild = node;
        }
        public void print(){
            print("", true);
        }
        private void print(String prefix, boolean isTail) {
            System.out.println(prefix + (isTail ? "└── " : "├── ") + (char)data.byteValue());
            if (!isLeaf()) {
                rightChild.print(prefix + (isTail ? "    " : "│   "), false);
                leftChild.print(prefix + (isTail ? "    " : "│   "), true);
            }
        }
    }

    public static class Dictionnaire {

    }
}
