package model;

public class TypeConverter {

    public static String[][] convertTo2DArray(String string){
        string = string.replace("[", "");
        string = string.substring(0, string.length()-2);
        String[] array = string.split("],");
        String[][] tileArray = new String[array.length][array.length+1];

        for(int i = 0; i < array.length; i++){
            array[i] = array[i].trim();
            String[] number  = array[i].split(", ");

            System.arraycopy(number, 0, tileArray[i], 0, number.length);
        }
        return tileArray;
    }

    public static int convertToInt(String string){
        return Integer.parseInt(string);
    }

}
