import java.awt.Color;
import java.awt.image.*;
import java.io.*;

import javax.imageio.ImageIO;


public class Stegano {
		
	public BufferedImage hideoutImg; // Image où l'on va cacher le texte 
	public BufferedImage steganoImg; // Image avec texte caché
	public Color[][] pixels;
	public String textToHide;
	public String encryptText; // Texte à cacher en binaire
	
	public  Stegano(){
		textToHide = "You can't see me!";
		encryptText = encryptText(textToHide);
		initialize("C:\\Users\\Khadim GNING\\Pictures\\Test_projet\\polytech.png");
		
		if(steganoImg != null){
			getPixels(hideoutImg);
		} else{
			System.out.println("Error 404 !");
		}
		action("C:\\Users\\Khadim GNING\\Pictures\\testOutput.png");
	}
	
	public Stegano(String textFileName, String imgName, String steganoImgName) throws IOException{
		textToHide = readFile(textFileName);
		encryptText = encryptText(textToHide);
		initialize("C:\\Users\\Khadim GNING\\Pictures\\Test_projet\\" + imgName);
		
		if(steganoImg != null){
			getPixels(hideoutImg);
		} else{
			System.out.println("Error 404 !");
		}
		action("C:\\Users\\Khadim GNING\\Pictures\\" + steganoImgName);
	}
	
	public String readFile(String textFileName) throws IOException{
		try{
			FileReader fr = new FileReader("C:\\Users\\Khadim GNING\\Pictures\\Test_projet\\" + textFileName);
			BufferedReader bfr = new BufferedReader(fr);
			String str = "";
			String temp;
			while((temp=bfr.readLine()) != null) {
				str += temp + "\n";
			}
			bfr.close();
			return str;
		} catch(IOException ioe){
			throw new IOException();
		}
	}
	
	public void initialize(String hideoutImgName){ //initialise les objets hideoutImg & steganoImg  
		hideoutImg = null;
		try{
			hideoutImg = ImageIO.read(new File(hideoutImgName));			
		} catch(IOException ioe){
			ioe.printStackTrace();
		}
		if(hideoutImg != null) steganoImg = new BufferedImage(hideoutImg.getWidth(), hideoutImg.getHeight(), BufferedImage.TYPE_INT_ARGB);
		else System.out.println("Image loading irregularity !");
	}
	
	public void getPixels(BufferedImage buffImg){
		pixels = new Color[buffImg.getWidth()][buffImg.getHeight()];
		for(int i = 0; i < buffImg.getWidth(); i++){
			for(int j = 0; j < buffImg.getHeight(); j++){
				pixels[i][j] = new Color(buffImg.getRGB(i, j));
			}
		}
	}
	
	public String encryptText(String textToHide){ // EN COURS DE MODIFICATION
		String encryptT = new String();
		/* on prend le ième caractere qu'on cast en byte
		* on le réecrit sous forme de 0 et de 1
		* on remplace les ' ' que java met par default à la place des 0
		*/
		String stuffToHide = textToHide + " \0";
		for(int i = 0; i <= textToHide.length(); i++){
			encryptT += String.format("%8s", Integer.toBinaryString((byte) stuffToHide.charAt(i) & 0xFF)).replace(' ', '0');
		}
		return encryptT;
	}
	
	public void action(String steganoImgName){
		int indChar = 0; // parcours notre chaine de carctère à dissimuler
		for(int i = 0; i < pixels.length; i++){
			for(int j =0; j < pixels[i].length; j++){
				if(indChar < encryptText.length()){
					//System.out.println("Le pixel va etre encrypte et sa valeur Red = " + pixels[i][j].getRed());
					pixels[i][j] = steganoOnRed(encryptText.charAt(indChar), pixels[i][j]);
					//System.out.println("Le pixel a ete encrypte et sa valeur Red = " + pixels[i][j].getRed());
					indChar++;
				}
				if (indChar == encryptText.length()){
					pixels[i][j] = new Color(128, pixels[i][j].getGreen(), pixels[i][j].getBlue(), pixels[i][j].getAlpha());
					indChar++;
				}
				steganoImg.setRGB(i, j, pixels[i][j].getRGB());
			}
		}
		try{
			ImageIO.write(steganoImg, "png", new File(steganoImgName));
		} catch(IOException ioe){
			ioe.printStackTrace();
		}
	}
	
	public Color steganoOnRed(char bitToEncrypt, Color pixel){ // on travail sur le LSB ici pour MSB même principe mais on ajoute 128 si pixel.getRed() < 128  
		Color temp = pixel;
		if(bitToEncrypt%2 == 0){
			if(pixel.getRed()%2 == 1) temp = new Color(temp.getRed()-1, temp.getGreen(), temp.getBlue(), temp.getAlpha());
		} else{
			if(pixel.getRed()%2 == 0) temp = new Color(temp.getRed()+1, temp.getGreen(), temp.getBlue(), temp.getAlpha());
		} 
		return temp;
	}
	
	// Pour décrypter faire : unEncryptText(unEncrypt());
	
	public static char undoStegano(Color pixel){ // retourne le bit de poid faible du pixel passé en paramètre 
		//System.out.println(pixel.getRed() + " valeur entree");
		char bit = '0';
		if(pixel.getRed()%2 == 1) bit = '1';
		//System.out.println("Char retourne = " + bit);
		return bit;
	}
	
	public static String undoStegano2(Color pixel){ // retourne le bit de poid faible du pixel passé en paramètre pour ses coeffs R,G et B 
		//System.out.println(pixel.getRed() + " valeur entree");
		String bit = "0";
		if(pixel.getRed()%2 == 1) bit = "1";
		bit += (pixel.getGreen()%2 == 1)? "1" : "0";
		bit += (pixel.getBlue()%2 == 1)? "1" : "0";
		return bit;
	}
	
	public static String unEncryptText(String bitToUnencrypt){ // retourne le texte 'caché' en claire
		String resultat = "";
		System.out.println(bitToUnencrypt);
		String temp[] = bitToUnencrypt.split("(?<=\\G........)");
		System.out.println(temp[0]);
		for(int i = 0; i < temp.length; i++){
			//if (i == 2) return resultat;
			resultat += (char) Byte.parseByte(temp[i], 2);
		}
		return resultat;
	}
	
	public static String unEncrypt(BufferedImage buffImg){ // retourne le text cache en format "binaire"
		String unEncrypt = "";
		for(int i = 0; i < buffImg.getWidth(); i ++){
			for (int j = 0; j < buffImg.getHeight(); j++){
				Color c = new Color(buffImg.getRGB(i, j));
				if (c.getRed() == 128) {
					unEncrypt += undoStegano(c);
					return unEncrypt;
				}
				unEncrypt += undoStegano(c);
			}
		}
		return unEncrypt;
	}
	
	public static String unEncrypt2(BufferedImage buffImg){ // retourne le text cache en format "binaire"
		String unEncrypt = "";
		int cpt = 0;
		
			for(int i = 0; i < buffImg.getWidth(); i ++){
				for (int j = 0; j < 1; j++){
				Color c = new Color(buffImg.getRGB(i, j));
				cpt += 3;
				if (cpt == 24) {
					unEncrypt += undoStegano2(c);
					
					return unEncrypt;
				}
				unEncrypt += undoStegano2(c);
				//System.out.println(unEncrypt);
			}
		}
		return unEncrypt;
	}
	
}
