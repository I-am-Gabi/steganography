package kgms.metrics;

import java.awt.Color;

public class MetricsGenerator{

	private int pixelImpacted;
	private	double correlation;
	private Color[][] initTab, steganoTab;
	private	int[] hist1, hist2;
	private long compressionTime;
	private long dissimulationTime;
	private long compressionStartTime;
	private long dissimulationStartTime;

	public MetricsGenerator(){
	}

	public void setInitTab(Color[][] colorTab){
		this.initTab = colorTab;
	}

	public void setSteganoTab(Color[][] colorTab){
		this.steganoTab = colorTab;
	}
	
	public void doHistogramCorrelation(){
		hist1 = new int[255];
		hist2 = new int[255];
		for(int i = 0; i < initTab.length; i++){
			for(int j = 0; j < initTab[0].length; j++){
				int initLuminanceCoeff = (int) (0.2126*initTab[i][j].getRed() + 0.7152*initTab[i][j].getGreen() + 0.0722*initTab[i][j].getBlue());
				int steganoLuminanceCoeff = (int) (0.2126*steganoTab[i][j].getRed() + 0.7152*steganoTab[i][j].getGreen() + 0.0722*steganoTab[i][j].getBlue());				
				hist1[initLuminanceCoeff]++;
				hist2[steganoLuminanceCoeff]++;
			}	
		}

		int sumHist1 = 0;
		int sumHist2 = 0;
		for(int i = 0; i < 255; i++){
			sumHist1 += hist1[i];
			sumHist2 += hist2[i];
		}
		sumHist1 = sumHist1/255;
		sumHist2 = sumHist2/255;

		int numerator = 0;
		int sum1 = 0;
		int sum2 = 0;
		for(int i=0; i<255; i++){
			numerator += (hist1[i] - sumHist1)*(hist2[i] - sumHist2);
			sum1 += Math.pow((hist1[i] - sumHist1), 2);
			sum2 += Math.pow((hist2[i] - sumHist2), 2);
		}
		correlation = (double) numerator/(Math.sqrt(sum1*sum2));
	}

	public void setStartTime(String phase){
		if(phase.equals("dissimulation"))
			dissimulationStartTime = System.nanoTime();
		else
			compressionStartTime = System.nanoTime();
	}

	public void setEndTime(String phase) {
		if (phase.equals("dissimulation"))
			dissimulationTime = (System.nanoTime() - dissimulationStartTime) / 1000000;
		else
			compressionTime = (System.nanoTime() - compressionStartTime) / 1000000;

	}

	public long getCompressionTime(){
		return compressionTime;
	}

	public void setPixelImpacted(int fileNbOfBits, int nbOfBitsToDissimulateOn, int imageSize){
		if(fileNbOfBits / nbOfBitsToDissimulateOn >= imageSize)
			this.pixelImpacted = imageSize;      
		else  
			this.pixelImpacted = (fileNbOfBits % nbOfBitsToDissimulateOn == 0)? fileNbOfBits/nbOfBitsToDissimulateOn : fileNbOfBits/nbOfBitsToDissimulateOn + 1;        
	}

	public void displayMetrics(){
		System.out.println("Dissimulation process time :\t" + dissimulationTime +"ms\nPixel impacted by the dissimulation :\t" + pixelImpacted + "\nCorrelation :\t" + correlation);
	}
}