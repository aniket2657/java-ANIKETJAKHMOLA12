public class SimpleInsert {

    public static void main(String[] args) {
        String original = "ILoveMyIndia";
        String toInsert = "Also";
        int index = 1;

        String result = "";

        // Add characters before the index
        for (int i = 0; i < index && i < original.length(); i++) {
            result += original.charAt(i);
        }

        // Add the string to insert
        result += toInsert;

        // Add the rest of the original string
        for (int i = index; i < original.length(); i++) {
            result += original.charAt(i);
        }

        System.out.println("Output: " + result);
    }
}
