package Problem4;

import Problem1.LatitudeReader;
import java.util.*;

public class MainA {
    public static void main(String[] args) {
        try {
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            System.out.println("\nNumber of unique latitude values: " + latitudes.size());

            List<Double> copy1 = new ArrayList<>(latitudes);
            List<Double> copy2 = new ArrayList<>(latitudes);
            List<Double> copy3 = new ArrayList<>(latitudes);

            // Sortering med ulike pivot-strategier

            QuickSort.sortFirst(copy1, 0, copy1.size() - 1);
            System.out.println("\nFirst element as pivot:\n");
            printLatitudes(copy1);

            QuickSort.sortLast(copy2, 0, copy2.size() - 1);
            System.out.println("\nLast element as pivot:\n");
            printLatitudes(copy2);

            QuickSort.sortRandom(copy3, 0, copy3.size() - 1);
            System.out.println("\nRandom element as pivot:\n");
            printLatitudes(copy3);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void printLatitudes(List<Double> list) {
        for (Double lat : list) {
            System.out.printf("Latitude: %.4f\n", lat);
        }
    }
}
