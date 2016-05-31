package kgms.image;

import kgms.Stegano;
import org.junit.Test;

import java.awt.*;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

import static org.junit.Assert.*;

public class PgmMatrixGeneratorTest {

    @Test
    public void testGetMatrix() throws Exception {
        File f = File.createTempFile("tmp", "");
        BufferedWriter bw = new BufferedWriter(new FileWriter(f));
        bw.write("P2\n2 2\n255\n10 20\n30 40");
        bw.close();
        PgmMatrixGenerator test = new PgmMatrixGenerator(f.getPath(), Stegano.imageType.RGBA);
        Color[][] pixels = test.getMatrix();
        assertEquals("Result", 10, pixels[0][0].getRed());
        assertEquals("Result", 20, pixels[1][0].getRed());
        assertEquals("Result", 30, pixels[0][1].getRed());
        assertEquals("Result", 40, pixels[1][1].getRed());
    }
}