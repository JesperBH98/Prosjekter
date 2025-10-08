package Problem1;

import java.util.Collections;
import java.util.*;

public class TimeComplexityAnalysis {
    public static long measureTime(List<Double> list, boolean optimized) {
        List<Double> copy = new ArrayList<>(list);
        long start = System.nanoTime();
        if (optimized) {
            OptimizedBubbleSort.sort(copy);
        } else {
            BubbleSort.sort(copy);
        }
        return System.nanoTime() - start;
    }

    public static void analyze(List<Double> latitudes) {
        List<Double> sortedList = new ArrayList<>(latitudes);
        Collections.sort(sortedList);

        List<Double> shuffledList = new ArrayList<>(latitudes);
        Collections.shuffle(shuffledList);

        System.out.println("--- Time Analysis (nanoseconds) ---");
        System.out.println("Not optimized (sorted): " + measureTime(sortedList, false));
        System.out.println("Not optimized (shuffled): " + measureTime(shuffledList, false));
        System.out.println("Optimized (sorted): " + measureTime(sortedList, true));
        System.out.println("Optimized (shuffled): " + measureTime(shuffledList, true));

        System.out.println("\nAnalysis:");
        System.out.println("- non-optimized bubble sort always has O(n^2) time complexity.");
        System.out.println("- Optimized bubble sort can have O(n) in the best case.");
        System.out.println("- Random order results in O(n^2) for both versions.");
    }
}
