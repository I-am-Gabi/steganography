package kgms.image;

import kgms.ImageFormat;
import kgms.Stegano;

import java.awt.*;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class PgmMatrixGenerator extends MatrixGenerator {
    Scanner scanner;
    public PgmMatrixGenerator(String path, Stegano.imageType outputType) throws IOException {
        super(path, ImageFormat.PGM, outputType);
        scanner = new Scanner(new FileReader(path));
    }
    @Override
    public Color[][] getMatrix() throws IOException {
        Color[][] pixels;
        //Premiers readline inutiles
        while (!scanner.hasNextInt())
            scanner.nextLine();
        pixels = new Color[scanner.nextInt()][scanner.nextInt()];
        scanner.nextInt();
        for(int y = 0; y < pixels[0].length; y++){
            for(int x = 0; x < pixels.length; x++){
                int color = scanner.nextInt();
                if (outputType == Stegano.imageType.GRAY)
                    pixels[x][y] = new Color(color, 0, 0);
                else
                    pixels[x][y] = new Color(color, color, color);
            }
        }
        return pixels;
    }
}
