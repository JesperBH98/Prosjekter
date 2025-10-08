package Problem3;

import Problem1.LatitudeReader;
import java.util.*;


public class MainB {
    public static void main(String[] args) {
        try {
            // Reads unique latitude values:
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            System.out.println("\nNumber of unique latitude values: " + latitudes.size());

            // Sorted list:
            List<Double> sorted = new ArrayList<>(latitudes);
            Collections.sort(sorted);

            MergeCounter counterSorted = new MergeCounter();
            counterSorted.sort(sorted);
            int mergesSorted = counterSorted.getMergeCount();

            // Random shuffled list:
            List<Double> shuffled = new ArrayList<>(latitudes);
            Collections.shuffle(shuffled);

            MergeCounter counterShuffled = new MergeCounter();
            counterShuffled.sort(shuffled);
            int mergesShuffled = counterShuffled.getMergeCount();

            System.out.println("\n--- Merge Count Analysis ---\n");
            System.out.println("Sorted list:  " + mergesSorted + " merges");
            System.out.println("Shuffled list:  " + mergesShuffled + " merges");


            System.out.println("\n Analysis:\n");
            System.out.println("- Merge Sort always uses the same number of merges, regardless of order.");
            System.out.println("- This is because Merge Sort always splits the list into equal parts.");
            System.out.println("- Time complexity and number of merges are therefore O(n log n) in all cases.");

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
