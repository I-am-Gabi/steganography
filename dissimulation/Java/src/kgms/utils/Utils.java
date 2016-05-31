package kgms.utils;

public class Utils {
    public static String getImageExtension(String path){
        int i = path.length() - 1;
        while (i > 0){
            if (path.charAt(i) == '.' && i < (path.length() - 1))
                return path.substring(i + 1, path.length());
            if (path.charAt(i) == '\\' || path.charAt(i) == '/')
                break;
            --i;
        }
        return "unknown_format";
    }

    /**
     * Indicates if the item is contained (equivalence) in array. For further explanation, see {@link String#equals(java.lang.Object) String#equals}
     * @param item The item to look for in the array
     * @param array The array to explore
     * @return True is item is found in array, false otherwise
     */
    public static boolean foundInArray(String item, String[] array){
        for(String i : array){
            if(item.equalsIgnoreCase(i)){
                return true;
            }
        }
        return false;
    }
    public static int luminosity(int r, int g, int b){
        int i = (int)(0.21 * r + 0.72 * g + 0.07 * b);
        if (i > 255) return 255;
        return i;
    }
}
