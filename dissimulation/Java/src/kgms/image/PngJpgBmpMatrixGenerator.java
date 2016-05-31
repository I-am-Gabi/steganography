package kgms.image;

import kgms.ImageFormat;
import kgms.Stegano;
import kgms.utils.Utils;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class PngJpgBmpMatrixGenerator extends MatrixGenerator {
    private BufferedImage img;
    public PngJpgBmpMatrixGenerator(String path, ImageFormat format, Stegano.imageType outputType) throws IOException {
        super(path, format, outputType);
        img = ImageIO.read(new File(path));
        if (img == null)
            throw new IOException("Image not found or wrong format.");
    }

    public Color[][] getMatrix(){
        Color[][] pixels = new Color[img.getWidth()][img.getHeight()];
        for(int x = 0; x < img.getWidth(); x++){
            for(int y = 0; y < img.getHeight(); y++){
                if (outputType == Stegano.imageType.GRAY)
                    pixels[x][y] = new Color(Utils.luminosity(
                            new Color(img.getRGB(x, y)).getRed(),
                            new Color(img.getRGB(x, y)).getBlue(),
                            new Color(img.getRGB(x, y)).getGreen()
                    ), 0, 0);
                else
                    pixels[x][y] = new Color(img.getRGB(x, y), true);
            }
        }
        return pixels;
    }
}
