public class AnagramCheck {

    public static boolean areAnagrams(String str1, String str2) {
        // If lengths are not equal, they cannot be anagrams
        if (str1.length() != str2.length()) {
            return false;
        }

        // Create an array to count characters (assuming lowercase English letters)
        int[] count = new int[256]; // can handle all ASCII characters

        // Increase count for str1 and decrease for str2
        for (int i = 0; i < str1.length(); i++) {
            count[str1.charAt(i)]++;
            count[str2.charAt(i)]--;
        }

        // Check if all counts are zero
        for (int i = 0; i < 256; i++) {
            if (count[i] != 0) {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        String str1 = "abcd";
        String str2 = "dabc";

        if (areAnagrams(str1, str2)) {
            System.out.println("The strings are anagrams of each other.");
        } else {
            System.out.println("The strings are NOT anagrams of each other.");
        }
    }
}
