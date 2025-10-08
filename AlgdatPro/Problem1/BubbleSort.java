package Problem1;

import java.util.List;

public class BubbleSort {
    public static void sort(List<Double> data) {
        int n = data.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - 1 - i; j++) {
                if (data.get(j) > data.get(j + 1)) {
                   double temp = data.get(j);
                   data.set(j, data.get(j + 1));
                   data.set(j + 1, temp);
                }
            }
        }
    }
}
