package Problem2;

import Problem1.LatitudeReader;

import java.util.ArrayList;
import java.util.List;

public class MainA {
    public static void main(String[] args) {
        try {
            // Reads latitude values:
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            System.out.println("\nNumber of unique latitude values: " + latitudes.size());

            // Makes copies and sorts:
            List<Double> copy = new ArrayList<>(latitudes);
            InsertionSort.sort(copy);

            System.out.println("\nSorted with Insertion Sort:\n");
            printLatitudes(copy);

            System.out.println("\nTotal number in sorted list: " + copy.size());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Prints out latitudes:
    public static void printLatitudes(List<Double> list) {
        for (Double lat : list) {
            System.out.printf("Latitude: %.4f\n", lat);
        }
        System.out.println();
    }
}
