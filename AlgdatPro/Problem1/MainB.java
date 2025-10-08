package Problem1;

import java.util.*;

public class MainB {
    public static void main(String[] args) {
        try {
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            TimeComplexityAnalysis.analyze(latitudes);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
