package Problem2;

import java.util.*;

public class TimeComplexityInsertion {

    public static void analyze(List<Double> latitudes) {
        List<Double> sortedList = new ArrayList<>(latitudes);
        Collections.sort(sortedList);

        List<Double> shuffledList = new ArrayList<>(latitudes);
        Collections.shuffle(shuffledList);

        System.out.println("\n--- Time Analysis: Inserion Sort (nanoseconds) ---");

        long timeSorted = timeExecution(sortedList);
        long timeShuffled = timeExecution(shuffledList);

        System.out.println("Sorted list:     " + timeSorted);
        System.out.println("Shuffled list:   " + timeShuffled);

        System.out.println("\nAnalysis:");
        System.out.println("- In the best case (already sorted) the time is O(n)");
        System.out.println("- In the average and worst case, the time is O(n^2)");
        System.out.println("- Random ordering usually leads to O(n^2)");
    }

    private static long timeExecution(List<Double> list) {
        List<Double> copy = new ArrayList<>(list);
        long start = System.nanoTime();
        InsertionSort.sort(copy);
        return System.nanoTime() - start;
    }
}
