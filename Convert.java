public class Convert{
   // A simple class that converts temperatures between Celsius, Fahrenheit and Kelvins.
    
   public static double convert(String temperature, char scale){
      // converts a temperature (value/scale) to a new scale
      // Finds out if the temperature string is a Celsius value or Fahrenheit value 
      String inputTemp = temperature.substring(temperature.length() - 1);
      System.out.println(inputTemp);
      // remove 'C' or 'F' character from temperature string
      String newTemp = temperature.substring(0,temperature.length() - 1);
      System.out.println("old temperature:" + temperature + "\nnew temperature:" + newTemp);
      // turn temperature into a float value
      Double TempFloat = Double.parseDouble(newTemp);
      // check if we convert to fahrenheit or celsius
      if (scale == 'F' && (inputTemp.compareTo("F") == 0)){
         System.out.println("Temperature is already in Fahrenheit.");
      }else if (scale == 'C' && (inputTemp.compareTo("C") == 0)){
         System.out.println("Temperature is already in Celsius.");
      }else if (scale == 'C' && (inputTemp.compareTo("F") == 0)){
         System.out.println("Converting to Celsius.");
         TempFloat = (TempFloat - 32) * 5/9;
      }else if (scale == 'F' && (inputTemp.compareTo("C") == 0)){
         System.out.println("Converting to Fahrenheit.");
         TempFloat = (TempFloat* 9/5) + 32;
      }
   return TempFloat;
   }
   public static void main(String[] args){
      System.out.println("Testing Convert.convert");
      String in = "10.0C";
      char scale = 'F';
      double expect = 50.0;
      double out = Convert.convert(in, scale);
      System.out.println("convert(\"" + in + "\",\'" + scale + "\')");
      System.out.println("...expect : " + expect);
      System.out.println("...actual : " + out);
      
      in = "10.0C";
      scale = 'C';
      expect = 10.0;
      out = Convert.convert(in, scale);
      System.out.println("convert(\"" + in + "\",\'" + scale + "\')");
      System.out.println("...expect : " + expect);
      System.out.println("...actual : " + out);
   }
}