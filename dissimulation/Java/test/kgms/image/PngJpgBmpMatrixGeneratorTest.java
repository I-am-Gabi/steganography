package kgms.image;

import kgms.ImageFormat;
import kgms.Stegano;
import org.junit.Test;

import java.awt.*;
import java.nio.file.Path;
import java.nio.file.Paths;

import static org.junit.Assert.assertEquals;

public class PngJpgBmpMatrixGeneratorTest {

    @Test
    public void testGetMatrix() throws Exception {
        Path dir = Paths.get(".");
        PngJpgBmpMatrixGenerator test = new PngJpgBmpMatrixGenerator("resources/test.png", ImageFormat.PNG,
                Stegano.imageType.RGBA);
        Color[][] pixels = test.getMatrix();
        assertEquals("Result", new Color(255, 0, 0), new Color(pixels[0][0].getRGB()));
        assertEquals("Result", new Color(0, 0, 0), new Color(pixels[1][0].getRGB()));
        assertEquals("Result", new Color(0, 255, 0), new Color(pixels[0][1].getRGB()));
        assertEquals("Result", new Color(0, 0, 255), new Color(pixels[1][1].getRGB()));
    }
}