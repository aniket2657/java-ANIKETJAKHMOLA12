package insertString;
package insertString;
public class insertString {

    public static String insertString(String original, String toInsert, int index) {
        String result = "";

        // Add characters from original before the index
        for (int i = 0; i < original.length(); i++) {
            if (i == index) {
                // Insert the new string at the correct index
                result += toInsert;
            }
            result += original.charAt(i);
        }

        // If index is beyond the length, add toInsert at the end
        if (index >= original.length()) {
            result += toInsert;
        }

        return result;
    }

    public static void main(String[] args) {
        String original = "ILoveMyIndia";
        String toInsert = "Also";
        int index = 1;

        String output = insertString(original, toInsert, index);
        System.out.println("Output: " + output);
    }
}
