package Problem4;

import Problem1.LatitudeReader;
import Problem1.TimeComplexityAnalysis;

import java.util.*;

public class MainB {
    public static void main(String[] args) {
        try {
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            System.out.printf("\nNumber of unique latitude values:" + latitudes.size());

            List<Double> copy1 = new ArrayList<>(latitudes);
            List<Double> copy2 = new ArrayList<>(latitudes);
            List<Double> copy3 = new ArrayList<>(latitudes);

            // teller antall sammenligninger for hver strategi:
            int comparisonsFirst = QuickSort.sortFirst(copy1, 0, copy1.size() - 1);
            int comparisonsLast = QuickSort.sortLast(copy2, 0, copy2.size() - 1);
            int comparisonsRandom = QuickSort.sortRandom(copy3, 0, copy3.size() - 1);

            System.out.println("\n\n--- Pivot Strategy Comparisons (QuickSort) ---");
            System.out.println("Comparisons with first element as pivot:  " + comparisonsFirst);
            System.out.println("Comparisons with last element as pivot:  " + comparisonsLast);
            System.out.println("Comparisons with random element as pivot:  " + comparisonsRandom);

            // Analysis:
            System.out.println("\nAnalysis:");
            System.out.println("- Using the first or last element as pivot can result in poor performance if the list is already sorted or nearly sorted.");
            System.out.println("- A random pivot generally provides better performance because it avoids the worst-case split scenarios.");
            System.out.println("- The best pivot strategy for this dataset is: " + findBestStrategy(comparisonsFirst, comparisonsLast, comparisonsRandom));


        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static String findBestStrategy(int first, int last, int random) {
        if (random <= first && random <= last) return "RANDOM";
        if (first <= last && first <= random) return "FIRST";
        return "LAST";
    }
}
