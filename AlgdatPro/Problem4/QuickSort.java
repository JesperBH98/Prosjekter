package Problem4;

import java.util.*;

public class QuickSort {
    public static int comparisonsFirst = 0;
    public static int comparisonsLast = 0;
    public static int comparisonsRandom = 0;

    // A. First element as pivot:
    public static int sortFirst(List<Double> list, int low, int high) {
        comparisonsFirst = 0;
        quickSortFirst(list, low, high);
        return comparisonsFirst;
    }

    private static void quickSortFirst(List<Double> list, int low, int high) {
        if (low < high) {
            int pivotIndex = partitionFirst(list, low, high);
            quickSortFirst(list, low, pivotIndex - 1);
            quickSortFirst(list, pivotIndex + 1, high);
        }
    }

    private static int partitionFirst(List<Double> list, int low, int high) {
        double pivot = list.get(low);
        int i = low + 1;
        for (int j = low + 1; j <= high; j++) {
            comparisonsFirst++;
            if (list.get(j) < pivot) {
                Collections.swap(list, i, j);
                i++;
            }
        }
        Collections.swap(list, low, i - 1);
        return i - 1;
    }

    // B. Last element as pivot:
    public static int sortLast(List<Double> list, int low, int high) {
        comparisonsLast = 0;
        quickSortLast(list, low, high);
        return comparisonsLast;
    }

    private static void quickSortLast(List<Double> list, int low, int high) {
        if (low < high) {
            int pivotIndex = partitionLast(list, low, high);
            quickSortLast(list, low, pivotIndex - 1);
            quickSortLast(list, pivotIndex + 1, high);
        }
    }

    private static int partitionLast(List<Double> list, int low, int high) {
        Collections.swap(list, low, high);
        double pivot = list.get(low);
        int i = low + 1;
        for (int j = low + 1; j <= high; j++) {
            comparisonsLast++;
            if (list.get(j) < pivot) {
                Collections.swap(list, i, j);
                i++;
            }
        }
        Collections.swap(list, low, i - 1);
        return i - 1;

    }

    // C. Random element as pivot:
    public static int sortRandom(List<Double> list, int low, int high) {
        comparisonsRandom = 0;
        quickSortRandom(list, low, high);
        return comparisonsRandom;
    }

    private static void quickSortRandom(List<Double> list, int low, int high) {
        if (low < high) {
            int pivotIndex = partitionRandom(list, low, high);
            quickSortRandom(list, low, pivotIndex - 1);
            quickSortRandom(list, pivotIndex + 1, high);
        }
    }

    private static int partitionRandom(List<Double> list, int low, int high) {
        int randomIndex = new Random().nextInt(high - low + 1) + low;
        Collections.swap(list, low, randomIndex);
        double pivot = list.get(low);
        int i = low + 1;
        for (int j = low + 1; j <= high; j++) {
            comparisonsRandom++;
            if (list.get(j) < pivot) {
                Collections.swap(list, i, j);
                i++;
            }
        }
        Collections.swap(list, low, i - 1);
        return i - 1;
    }
}
