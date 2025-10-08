package Problem3;

import java.util.*;

public class MergeSort {

    public static List<Double> sort(List<Double> list) {
        if (list.size() <= 1) {
            return list;
        }

        int mid = list.size() / 2;
        List<Double> left = sort(new ArrayList<>(list.subList(0, mid)));
        List<Double> right = sort(new ArrayList<>(list.subList(mid, list.size())));

        return merge(left, right);
    }

    private static List<Double> merge(List<Double> left, List<Double> right) {
        List<Double> result = new ArrayList<>();
        int i = 0, j = 0;

        // merges two sorted lists:
        while (i < left.size() && j < right.size()) {
            if (left.get(i) <= right.get(j)) {
                result.add(left.get(i++));
            } else {
                result.add(right.get(j++));
            }
        }

        // adds remaining elements:
        while (i < left.size()) {
            result.add(left.get(i++));
        }
        while (j < right.size()) {
            result.add(right.get(j++));
        }

        return result;
    }
}
