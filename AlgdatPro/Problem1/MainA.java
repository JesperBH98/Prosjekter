package Problem1;

import java.util.*;

public class MainA {
    public static void main(String[] args) {
        try {
            // reads latitude values from CSV-file
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");

            // non-optimized sorting:
            List<Double> copy1 = new ArrayList<>(latitudes);
            BubbleSort.sort(copy1);
            System.out.println("\n none-optimised Bubble sort:\n ");
            System.out.flush();
            printLatitudes(copy1);

            // Optimized sorting:
            List<Double> copy2 = new ArrayList<>(latitudes);
            OptimizedBubbleSort.sort(copy2);
            System.out.println("\n Optimised Bubble sort:\n");
            System.out.flush();
            printLatitudes(copy2);

            // Total number of values in each list:
            System.out.println("\nTotal number of values in each sorted list:");
            System.out.println("none-optimised: " + copy1.size());
            System.out.println("Optimised: " + copy2.size());

            System.out.println("\nNumber of unique latitude values: " + latitudes.size());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Prints list of latitudes:
    public static void printLatitudes(List<Double> list) {
        for (Double lat : list) {
            System.out.println("Latitude: " + lat);
        }
        System.out.println();
    }
}
