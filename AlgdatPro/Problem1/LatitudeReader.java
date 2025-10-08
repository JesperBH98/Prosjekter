package Problem1;

import java.io.*;
import java.util.*;
import java.nio.file.*;

public class LatitudeReader {
    public static List<Double> getUniqueLatitudes(String filePath) throws IOException {
        Set<Double> uniqueLatitudes = new HashSet<>();
        File file = new File(filePath);

        if (!file.exists()) {
            throw new FileNotFoundException("Filen ble ikke funnet: " + file.getAbsolutePath());
        }

        List<String> lines = Files.readAllLines(file.toPath());

        for (String line : lines.subList(1, lines.size())) {
            String[] tokens = line.split(",");
            if (tokens.length > 2) {
                try{
                    String cleanedLat = tokens [2].replace("\"", "").trim();
                    double latitude = Double.parseDouble(cleanedLat);
                    uniqueLatitudes.add(latitude);
                } catch (NumberFormatException e) {
                    // hopper over linjer som ikke er gyldige
                }
            }
        }
        return new ArrayList<>(uniqueLatitudes);
    }
}
