package Problem3;

import java.util.*;
import Problem1.LatitudeReader;

public class MainA {
    public static void main(String[] args) {
        try {
            // Reads unique latitudes:
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            System.out.println("Number of unique latitude values: " + latitudes.size());

            // Sorts list:
            List<Double> sorted = MergeSort.sort(latitudes);

            // Prints out the result:
            System.out.println("\n Sorted with merge Sort:\n");
            printLatitudes(sorted);

            System.out.println("\n Total number in sorted list: " + sorted.size());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void printLatitudes(List<Double> list) {
        for (Double lat : list) {
            System.out.printf("Latitude: %.4f\n", lat);
        }
        System.out.println();
    }

}
