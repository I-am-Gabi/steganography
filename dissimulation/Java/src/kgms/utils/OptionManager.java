package kgms.utils;

import kgms.Channel;
import kgms.ImageFormat;
import kgms.message.HuffmanCompression;
import kgms.message.Message;
import kgms.message.StandardMessage;
import kgms.exceptions.WrongArgumentException;
import kgms.pattern.Pattern;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.InvalidPathException;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Arrays;
import java.util.Scanner;

/**
 * The OptionManager is parsing & reacting to the parameters passed by arguments to the main method
 * @author KGMS
 */
public class OptionManager{
    /*final String[] allowedOptions
            = new String[]{"Fin", "Fout", "in", "out", "msg", "b", "c", "p", "magic", "metrics"};*/
    /*final String[] allowedFin = new String[]{"JPEG", "JPG", "PNG", "BMP", "PPM", "PGM"};
    final String[] allowedFout = new String[]{"PNG", "BMP", "PPM", "PGM"};
    final String[] allowedChannels = new String[]{"Red", "Green", "Blue", "Alpha", "Gray"};
    final String[] allowedPatterns = new String[]{"direct", "reverse", "external_spiral", "internal_spiral"};*/
    final String[][] allowedArguments = {
            {"Fin", "JPEG", "JPG", "PNG", "BMP", "PPM", "PGM"},
            {"Fout", "PNG", "BMP", "PPM", "PGM"},
            {"c", "Red", "Green", "Blue", "Alpha", "Gray"},
            {"p", "direct", "reverse", "external_spiral", "internal_spiral"},
            {"in", "%ANY"},
            {"out", "%ANY"},
            {"msg", "%ANY"},
            {"b", "%ANY"},
            {"magic", "%ANY"},
            {"metrics", "%NONE"},
            {"compress", "%NONE"},
            {"show", "%NONE"}
    };
    private int         bArg = 1;
    private ImageFormat FinArg;
    private ImageFormat FoutArg;
    private Channel[]   cArg;
    private Pattern.PatternName pArg;
    private Path        inArg;
    private Path        outArg;
    private Message     msgArg;
    private byte[]      magicArg;
    private boolean     metricsArg;
    private boolean     compressArg;
    private boolean     compressMoreArg;
    private boolean     compressEvenMoreArg;
    private boolean     compressRecursiveArg;
    private boolean     showArg;

    public OptionManager(String[] args) throws WrongArgumentException, IOException {
        checkOptions(args);
    }
    private void checkOptions(String [] args) throws WrongArgumentException, IOException {
        for (int i = 0; i < args.length; ++i) {
            if (!args[i].equals("-metrics") && !args[i].equals("-compress")
                    && !args[i].equals("-show") && i == args.length - 1)
                throw new WrongArgumentException("The argument " + args[i] + " takes a parameter.");
            switch (args[i]) {
                case "-metrics":
                    metricsArg = true;
                    break;
                case "-compress":
                    compressArg = true;
                    while (i + 1< args.length){
                        if (args[i + 1].equals("more")){
                            compressMoreArg = true;
                            ++i;
                        }else if (args[i + 1].equals("even_more")){
                            compressEvenMoreArg = true;
                            ++i;
                        }else if (args[i + 1].equals("recursive")){
                            compressRecursiveArg = true;
                            ++i;
                        }else break;
                    }
                    break;
                case "-show":
                    showArg = true;
                    break;
                case "-b":
                    try {
                        bArg = Integer.parseInt(args[i + 1]);
                    } catch (NumberFormatException e) {
                        throw new WrongArgumentException("The argument -b takes a number as parameter.");
                    }
                    ++i;
                    break;
                case "-Fin":
                    try {
                        FinArg = ImageFormat.valueOf(args[i + 1].toUpperCase());
                    } catch (IllegalArgumentException e) {
                        throw new WrongArgumentException("Wrong parameter for argument -Fin.");
                    }
                    if (!FinArg.getAllowIn())
                        throw new WrongArgumentException(FinArg.name() + " is not allowed as input format.");
                    ++i;
                    break;
                case "-Fout":
                    try {
                        FoutArg = ImageFormat.valueOf(args[i + 1].toUpperCase());
                    } catch (IllegalArgumentException e) {
                        throw new WrongArgumentException("Wrong parameter for argument -Fout.");
                    }
                    if (!FoutArg.getAllowOut())
                        throw new WrongArgumentException(FoutArg.name() + " is not allowed as output format.");
                    ++i;
                    break;
                case "-c":
                    String[] channels = args[i + 1].split(",");
                    //Chercher si un channel est en double
                    for (int j = 0; j < channels.length; ++j) {
                        for (int k = 0; k < channels.length; ++k)
                            if (k != j && channels[k].equals(channels[j]))
                                throw new WrongArgumentException("Wrong parameter for argument -c.");
                    }
                    cArg = new Channel[channels.length];
                    for (int j = 0; j < cArg.length; ++j) {
                        try {
                            cArg[j] = Channel.valueOf(channels[j].toUpperCase());
                        } catch (IllegalArgumentException e) {
                            throw new WrongArgumentException("Wrong parameter for argument -c.");
                        }
                    }
                    ++i;
                    break;
                case "-p:":
                    try {
                        pArg = Pattern.PatternName.valueOf(args[i + 1]);
                    } catch (IllegalArgumentException e) {
                        throw new WrongArgumentException("Wrong parameter for argument -p.");
                    }
                    ++i;
                    break;
                case "-in":
                    try {
                        inArg = Paths.get(args[i + 1]);
                        if (!Files.exists(inArg))
                            throw new WrongArgumentException("Wrong parameter for argument -in");
                    } catch (InvalidPathException e) {
                        throw new WrongArgumentException("Wrong parameter for argument -in");
                    }
                    ++i;
                    break;
                case "-out":
                    try {
                        outArg = Paths.get(args[i + 1]);
                    } catch (InvalidPathException e) {
                        throw new WrongArgumentException("Wrong parameter for argument -in");
                    }
                    ++i;
                    break;
                case "-msg":
                    String msg = args[i + 1];
                    if (msg.equals("stdin")){
                        System.out.println("Please enter the message or a path to it");
                        Scanner s = new Scanner (System.in);
                        msg = s.nextLine();
                    }
                    try {
                        msgArg = new StandardMessage(msg);
                    } catch (IOException e) {
                        throw new WrongArgumentException("IOException for argument -msg");
                    }
                    ++i;
                    break;
                case "-magic":
                    String str = args[i + 1];
                    ByteBuffer b = ByteBuffer.allocate(str.length()/2);
                    b.putInt(Integer.parseInt(str, 16));
                    magicArg = b.array();
                    ++i;
                    break;
                default:
                    throw new WrongArgumentException("Unknown argument " + args[i]);
            }
        }
        //Mandatory arguments
        if (inArg == null)
            throw new WrongArgumentException("Missing argument -in");
        if (msgArg == null)
            throw new WrongArgumentException("Missing argument -msg");
        //Défauts
        if (outArg == null){
            FoutArg = ImageFormat.PNG;
            outArg = Paths.get("result");
        }
        if (FinArg == null){
            String ext = inArg.toString().substring(inArg.toString().lastIndexOf('.') + 1);
            switch (ext.toLowerCase()){
                case "png":
                    FinArg = ImageFormat.PNG;
                    break;
                case "ppm":
                    FinArg = ImageFormat.PPM;
                    break;
                case "pgm":
                    FinArg = ImageFormat.PGM;
                    break;
                case "bmp":
                    FinArg = ImageFormat.BMP;
                    break;
                case "jpg":
                    FinArg = ImageFormat.JPG;
                    break;
                case "jpeg":
                    FinArg = ImageFormat.JPEG;
                    break;
                default:
                    throw new WrongArgumentException("Unknown input image file type.");
            }
        }
        if (FoutArg == null){
            if (FinArg.getAllowOut())
                FoutArg = FinArg;
            else
                FoutArg = ImageFormat.PNG;
        }
        if (cArg == null) {
            if (Arrays.equals(FoutArg.getAllowedChannels(), new Channel[]{Channel.GRAY}))
                cArg = new Channel[]{Channel.GRAY};
            else
                cArg = new Channel[]{Channel.RED, Channel.GREEN, Channel.BLUE};
        }
        if (pArg == null)
            pArg = Pattern.PatternName.DIRECT;
        if (magicArg == null){
            String str = "48454C50";
            ByteBuffer b = ByteBuffer.allocate(str.length()/2);
            b.putInt(Integer.parseInt(str, 16));
            magicArg = b.array();
        }
        //Check channels autorisés
        if (!FoutArg.areAllowedChannels(cArg))
            throw new WrongArgumentException("Unallowed channel(s) for selected output type.");
        //Check nombre de bits
        if (bArg < 1 || bArg > 8)
            throw new WrongArgumentException("Wrong parameter for -b argument.");
        //Check si show sans compress
        if (!compressArg && showArg)
            throw new WrongArgumentException("Can't have show without compress.");
        //Check si compressMore et compressEvenMore
        if (compressMoreArg && compressEvenMoreArg)
            throw new WrongArgumentException("more and even_more parameters are incompatible for -compress");
        //Check compression Huffman
        if (compressArg)
            msgArg = new HuffmanCompression(msgArg, compressMoreArg, compressEvenMoreArg, compressRecursiveArg, metricsArg, showArg);
    }

    public int getBits() {
        return bArg;
    }

    public ImageFormat getFin() {
        return FinArg;
    }

    public ImageFormat getFout() {
        return FoutArg;
    }

    public Channel[] getChannel() {
        return cArg;
    }

    public Pattern.PatternName getPattern() {
        return pArg;
    }

    public Path getIn() {
        return inArg;
    }

    public Path getOut() {
        return outArg;
    }

    public byte[] getMagic() {
        return magicArg;
    }

    public boolean getMetrics() {
        return metricsArg;
    }

    public boolean getCompress() {
        return compressArg;
    }

    public boolean getShow() {
        return showArg;
    }

    public Message getMsg(){
        return msgArg;
    }
}