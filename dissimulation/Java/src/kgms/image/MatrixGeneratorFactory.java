package kgms.image;

import kgms.ImageFormat;
import kgms.Stegano;
import kgms.utils.Utils;

import java.io.IOException;

public class MatrixGeneratorFactory {
    public static MatrixGenerator getMatrixGenerator(String path, ImageFormat outputFormat, ImageFormat inputFormat)
            throws IOException {
        Stegano.imageType opFormat;
        if (outputFormat.equals(ImageFormat.PNG))
            opFormat = Stegano.imageType.RGBA;
        else if (outputFormat.equals(ImageFormat.BMP) || outputFormat.equals(ImageFormat.PPM))
            opFormat = Stegano.imageType.RGB;
        else
            opFormat = Stegano.imageType.GRAY;
        if (inputFormat.equals(ImageFormat.PNG) || inputFormat.equals(ImageFormat.JPG)
                || inputFormat.equals(ImageFormat.JPEG)
                || inputFormat.equals(ImageFormat.BMP))
            return new PngJpgBmpMatrixGenerator(path, inputFormat, opFormat);
        if (inputFormat.equals(ImageFormat.PPM))
            return new PpmMatrixGenerator(path, opFormat);
        if (inputFormat.equals(ImageFormat.PGM))
            return new PgmMatrixGenerator(path, opFormat);
        return new PngJpgBmpMatrixGenerator(path, inputFormat, opFormat);
    }
}
