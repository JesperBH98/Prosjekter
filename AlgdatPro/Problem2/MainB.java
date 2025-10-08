package Problem2;

import Problem1.LatitudeReader;

import java.util.List;

public class MainB {
    public static void main(String[] args) {
        try {
            // Reads latitude values from CSV-fie:
            List<Double> latitudes = LatitudeReader.getUniqueLatitudes("src/worldcities.csv");
            System.out.println("Number of unique latitude values: " + latitudes.size());

            TimeComplexityInsertion.analyze(latitudes);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
