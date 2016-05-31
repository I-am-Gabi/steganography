package kgms.image;

import kgms.Stegano;
import org.junit.Test;

import java.awt.*;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import static org.junit.Assert.*;

public class PpmMatrixGeneratorTest {

    @Test
    public void testGetMatrix() throws Exception {
        File f = File.createTempFile("tmp", "");
        BufferedWriter bw = new BufferedWriter(new FileWriter(f));
        bw.write("P2\n2 2\n255\n10 20 30 40 50 60\n70 80 90 100 110 120");
        bw.close();
        PpmMatrixGenerator test = new PpmMatrixGenerator(f.getPath(), Stegano.imageType.RGBA);
        Color[][] pixels = test.getMatrix();
        assertEquals("Result", new Color(10, 20, 30), new Color(pixels[0][0].getRGB()));
        assertEquals("Result", new Color(40, 50, 60), new Color(pixels[1][0].getRGB()));
        assertEquals("Result", new Color(70, 80, 90), new Color(pixels[0][1].getRGB()));
        assertEquals("Result", new Color(100, 110, 120), new Color(pixels[1][1].getRGB()));
    }
}