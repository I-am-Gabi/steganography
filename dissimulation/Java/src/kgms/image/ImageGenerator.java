package kgms.image;

import kgms.ImageFormat;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Path;

public class ImageGenerator {
    protected Color[][] pixels;
    public ImageGenerator(Color[][] pixels){
        this.pixels = pixels;
    }
    public void saveImage (Path path, ImageFormat format) throws IOException {
        if (format.equals(ImageFormat.PNG) || format.equals(ImageFormat.BMP)){
            BufferedImage img = new BufferedImage(pixels.length, pixels[0].length,
                    format.equals(ImageFormat.BMP) ? BufferedImage.TYPE_3BYTE_BGR : BufferedImage.TYPE_4BYTE_ABGR);
            for (int x = 0; x < pixels.length; ++x)
                for (int y = 0; y < pixels[0].length; ++y)
                    img.setRGB(x, y, pixels[x][y].getRGB());
            ImageIO.write(img, format.toString().toLowerCase(), new File(path + "." + format.toString().toLowerCase()));
        }
        else if (format.equals(ImageFormat.PGM)){
            BufferedWriter writer = new BufferedWriter (new FileWriter(path + "." + format.toString().toLowerCase()));
            writer.write("P2\n" + pixels.length + " " + pixels[0].length + "\n255\n");
            for (int y = 0; y < pixels[0].length; ++y) {
                for (int x = 0; x < pixels.length; ++x)
                    writer.write(pixels[x][y].getRed() + " ");
                writer.write("\n");
            }
            writer.close();
        }
        else if (format.equals(ImageFormat.PPM)){
            BufferedWriter writer = new BufferedWriter (new FileWriter(path + "." + format.toString().toLowerCase()));
            writer.write("P3\n" + pixels.length + " " + pixels[0].length + "\n255\n");
            for (int y = 0; y < pixels[0].length; ++y) {
                for (int x = 0; x < pixels.length; ++x)
                    writer.write(pixels[x][y].getRed() + " " + pixels[x][y].getGreen()
                            + " " + pixels[x][y].getBlue() + " ");
                writer.write("\n");
            }
            writer.close();
        }
    }
}
