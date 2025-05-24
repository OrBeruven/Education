public class ReverseOnlyLetters {
    private static boolean isLetter(char c) {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    }

    public static String reverseOnlyLetters(String s) {
        StringBuilder strToRet = new StringBuilder();
        int readIndex = s.length() - 1;

        for (int writeIndex = 0; writeIndex < s.length(); ++ writeIndex) {
            if (isLetter(s.charAt(writeIndex))) {
                while (readIndex > 0 && !isLetter(s.charAt(readIndex))) {
                    --readIndex;
                }

                if (readIndex < 0) {
                    break;
                }
                strToRet.append(s.charAt(readIndex));
                --readIndex; /*Correct?>*/
            } else {
                strToRet.append(s.charAt(writeIndex));
            }
        }

        return strToRet.toString();
    }
}