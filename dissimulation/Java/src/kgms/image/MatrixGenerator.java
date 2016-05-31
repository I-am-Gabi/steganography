package kgms.image;

import kgms.ImageFormat;
import kgms.Stegano;

import java.awt.*;
import java.io.IOException;

public abstract class MatrixGenerator {
    private ImageFormat inputFormat; //Original image extension
    protected Stegano.imageType outputType;

    public MatrixGenerator(String path, ImageFormat inputFormat, Stegano.imageType outputType){
        this.inputFormat = inputFormat;
        this.outputType = outputType;
    }

    public abstract Color[][] getMatrix() throws IOException;

    public ImageFormat getFormat(){
        return inputFormat;
    }
}
