package kgms;


import kgms.image.ImageGenerator;
import kgms.image.MatrixGenerator;
import kgms.image.MatrixGeneratorFactory;
import kgms.metrics.*;
import kgms.utils.*;
import kgms.pattern.*;
import kgms.exceptions.*;
import java.io.*;
import java.awt.Color;

public class Stegano{
    public enum imageType { GRAY, RGB, RGBA }

    FileByteStreamReader    fbsr = new FileByteStreamReader();
    MatrixGenerator         mgen;
    MetricsGenerator        metricsGen;
    private Color[][]       pixels;
    OptionManager           optManag;

    public void initialize(String[] args)
            throws IOException, UnauthorizedExtensionException, WrongArgumentException{
        initializeArgs(args);
        initializeImg(); //if wrong format go to ...
        initializeMsg();
    }
    
    public void initializeArgs(String[] args) throws WrongArgumentException, IOException {
        optManag = new OptionManager(args);
    }
    
    public void initializeImg() throws IOException, UnauthorizedExtensionException{
        mgen = MatrixGeneratorFactory.getMatrixGenerator(optManag.getIn().toString()
                , optManag.getFout(), optManag.getFin());
        pixels = mgen.getMatrix();
    }
    
    public void initializeMsg() throws IOException{
        fbsr.openMsg(optManag.getMsg());
        fbsr.setEndData(optManag.getMagic());
    }
    
    public void action() throws IOException{
        int nbBitsToHide        = optManag.getBits();
        Channel[] channelToAlter = optManag.getChannel();
        int nbChannelToAlter    = channelToAlter.length;
        Pattern pattern         = PatternFactory.getPattern(optManag.getPattern()
                , pixels.length, pixels[0].length);
        if (!pattern.isImgBigEnough(nbBitsToHide, nbChannelToAlter, (int) fbsr.getBitsLeft())){
            System.out.println("StandardMessage too big for the image and the desired pattern.");
            throw new IOException("StandardMessage too big");
        }

        if(optManag.getMetrics()){
            metricsGen = new MetricsGenerator();
            metricsGen.setInitTab(pixels);
            metricsGen.setPixelImpacted((int) fbsr.getBitsLeft(), nbBitsToHide, pixels.length*pixels[0].length);
            metricsGen.setStartTime("dissimulation");
        }

        int currentChannel = 0;
        Position p = pattern.getInitialPosition();
        while(fbsr.getBitsLeft() > 0){
            if(p.getX() == -1){
                ++currentChannel;
                p = pattern.getInitialPosition();
        	}
            pixels[p.getX()][p.getY()] = doStegano(pixels[p.getX()][p.getY()], nbBitsToHide, channelToAlter[currentChannel]);
            p = pattern.getNextPosition();
        }

        ImageGenerator imgen = new ImageGenerator(pixels);
        imgen.saveImage(optManag.getOut(), optManag.getFout());
        
        if(optManag.getMetrics()){
            metricsGen.setEndTime("dissimulation");
            metricsGen.setSteganoTab(pixels);
            metricsGen.doHistogramCorrelation();
            metricsGen.displayMetrics();
        }
    }
    
    public Color doStegano(Color pixel, int nbBitsToHide, Channel channel) throws IOException{ // Objectif : cacher de l'info sur les n derniers bits
        Color temp = pixel;

        byte bitsToHide;
        int bitsLeft = (int) fbsr.getBitsLeft();
        if (bitsLeft < nbBitsToHide){
            bitsToHide = (byte)(fbsr.getBits(bitsLeft) << (nbBitsToHide - bitsLeft));
        }else {
            byte b = fbsr.getBits(nbBitsToHide);
            //System.out.println(Bits.byteToString(b));
            bitsToHide = b;
        }

        int mask = Bits.getLessSignBits(bitsToHide, nbBitsToHide);
        int channelValue = getChannel(temp, channel);
        int newChannel = (channelValue & (0b11111111<<nbBitsToHide));
        channelValue = (newChannel|mask);
        temp = changeChannel(temp, channelValue, channel);
        return temp;
    }
    
    public int getChannel(Color pixel, Channel channel){
        if (channel == Channel.RED || channel == Channel.GRAY)
            return pixel.getRed();
        if (channel == Channel.GREEN)
            return pixel.getGreen();
        if (channel == Channel.BLUE)
            return pixel.getBlue();
        if (channel == Channel.ALPHA)
            return pixel.getAlpha();
        return 0;
    }
    
    public Color changeChannel(Color pixel, int newChannelValue, Channel channel){
        if (channel == Channel.RED || channel == Channel.GRAY)
            return new Color(newChannelValue, pixel.getGreen(), pixel.getBlue(), pixel.getAlpha());
        if (channel == Channel.GREEN)
            return new Color(pixel.getRed(), newChannelValue, pixel.getBlue(), pixel.getAlpha());
        if (channel == Channel.BLUE)
            return new Color(pixel.getRed(), pixel.getGreen(), newChannelValue, pixel.getAlpha());
        if (channel == Channel.ALPHA)
            return new Color(pixel.getRed(), pixel.getGreen(), pixel.getBlue(), newChannelValue);
        return new Color(pixel.getRed(), pixel.getGreen(), pixel.getBlue(), pixel.getAlpha());
    }
}