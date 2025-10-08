package Problem2;

import java.util.List;

public class InsertionSort {

    public static void sort(List<Double> list) {
        for (int i = 1; i < list.size(); i++) {
            double key = list.get(i);
            int j = i - 1;

            while (j >= 0 && list.get(j) > key) {
                list.set(j + 1, list.get(j));
                j--;
            }

            list.set(j + 1, key);
        }
    }
}
