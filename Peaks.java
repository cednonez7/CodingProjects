import java.util.Arrays;

public class Peaks{
    public static int numPeaks(int[] data){
        // returns the number of "peaks" in the input data
        int peak_count = 0;
        for (int i=0; i<data.length; i+= 1){
            if (i == 0){
                if (data[i] > data[i + 1]){
                    peak_count +=1;
                }
            }else if (i == data.length-1){
                if  (data[i] > data[i - 1]){
                    peak_count +=1;
                }
            }else if ((data[i] > data[i-1]) && (data[i] > data[i + 1])){
                peak_count +=1;
            }
        }
        return peak_count;
        // numPeaks method finished
    }

    public static int[] peaks(int[] data){
        // returns the locations of all peaks in the input data
        // make this method run numpeaks since we want to know how many peaks there are in the list
        int peak_count = numPeaks(data);
        // use the peak count in the peak_location list to know how many items we want to fit in our list

        int list_location = 0;
        int[] peak_location = new int[peak_count];

        for (int i=0; i<data.length; i+= 1){
            if (i == 0){
                if (data[i] > data[i + 1]){
                    peak_location[list_location] = i;
                    list_location += 1;
                }
            }else if (i == data.length-1){
                if (data[i] > data[i - 1]){
                    peak_location[list_location] = i;
                    list_location += 1;
                }
            }else if ((data[i] > data[i-1]) && (data[i] > data[i + 1])){
                peak_location[list_location] = i;
                list_location += 1;
            }
        }
        return peak_location;
    // we have now finished the peaks method
    }

    public static int[][] minmax(int[] data){
        int max = data[0];
        int min = data[0];
        int min_count = 1;
        int max_count = 1;
        for (int i=0; i<data.length; i+= 1){
            if (data[i] > max){
                max = data[i];
            }
            if (data[i] < min){
                min = data[i];
            }
        }    
        for (int i=0; i<data.length; i+= 1){
            if (data[i] == min){
                min_count +=1;
            }
            if (data[i] == max){
                max_count+=1;
            }
        }
        int count = 0;
        if (min_count >= max_count){
            count = min_count;
        }else{
            count = max_count;
        }
        min_count = 0;
        max_count = 0;
        int[][] minmax = new int[2][count];
        minmax[0][0] = min;
        minmax[1][0] = max;

        for (int i=0; i<data.length; i+= 1){
            if (data[i] == min){
                minmax[0][min_count] = i;
                min_count +=1;
            }
            if (data[i] == max){
                minmax[1][max_count] = i;
                max_count+=1;
            }
        }
        
        return minmax;   
    }

    public static void main(String[] args){
      // you can use this to help test your code
        int[] data1 = {1, 1, 4, 15, 3, 1};
        int numPeaks1 = Peaks.numPeaks(data1);
        int[] peaks1 = Peaks.peaks(data1);
        int[][] minmax1 = Peaks.minmax(data1);
        System.out.println("numPeak 1 return count: " + numPeaks1);
        System.out.println("peaks 1 return count: " + Arrays.toString(peaks1));
        System.out.println("minmax 1 return count: " + Arrays.deepToString(minmax1));
      //Peaks.numPeaks(data1) -> 1
      //Peaks.peaks(data1) -> [3]
      //Peaks.minmax(data1) -> [ [1,0,1,5], [15,3] ]

      int[] data2 = {3, 1, 4, -2, 13, -2, 5};
      int numPeaks2 = Peaks.numPeaks(data2);
      int[] peaks2 = Peaks.peaks(data2);
      int[][] minmax2 = Peaks.minmax(data2);
        System.out.println("numPeak 2 return count: " + numPeaks2);
        System.out.println("peaks 2 return count: " + Arrays.toString(peaks2));
        System.out.println("minmax 2 return count: " + Arrays.deepToString(minmax2));
      //Peaks.numPeaks(data2) -> 4
      //Peaks.peaks(data2) -> [0,2,4,6]
      //Peaks.minmax(data2) -> [ [-2,3,5] , [13,4] ]

      int[] data3 = {1, 4, 4, 1};
      int numPeaks3 = Peaks.numPeaks(data3);
      int[] peaks3 = Peaks.peaks(data3);
      int[][] minmax3 = Peaks.minmax(data3);
        System.out.println("numPeak 3 return count: " + numPeaks3);
        System.out.println("peaks 3 return count: " + Arrays.toString(peaks3));
        System.out.println("minmax 3 return count: " + Arrays.deepToString(minmax3));
      //Peaks.numPeaks(data2) -> 0
      //Peaks.peaks(data2) -> []
      //Peaks.minmax(data2) -> [ [1,0,3], [4,1,2] ]
    }
} 