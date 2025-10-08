package Problem1;

import java.util.List;

public class OptimizedBubbleSort {
    public static void sort(List<Double> data) {
     int n = data.size();
     boolean swapped;
     for (int i = 0; i < n - 1; i++) {
         swapped = false;
         for (int j = 0; j < n - 1 - i; j++) {
             if (data.get(j) > data.get(j + 1)) {
                 double temp = data.get(j);
                 data.set(j, data.get(j + 1));
                 data.set(j + 1, temp);
                 swapped = true;
             }
         }
         if (!swapped) break; // It will finish early if it's already sorted
     }
    }
}
