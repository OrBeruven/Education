import java.util.Arrays;
import java.util.List;

class Solution {
    public int minimumBucketsRegex(String hamsters) {
        if (hamsters.equals(".")) {
            return 0;
        } else if (hamsters.equals("H")) {
            return -1;
        } else if (hamsters.charAt(0) == 'H' && hamsters.charAt(1) == 'H') {
            return -1;
        } else if (hamsters.charAt(hamsters.length() - 1) == 'H' && hamsters.charAt(hamsters.length() - 2) == 'H') {
            return -1;
        } else if (hamsters.contains("HHH")) {
            return -1;
        }

        return hamsters.replace("H.H", "  ").length() - hamsters.replace("H", "").length();
    }

    public int minimumBuckets(String hamsters) {
        int numOfBuckets = 0;
        char[] chars = hamsters.toCharArray();

        for (int i = 0; i < hamsters.length(); ++i) {
            if (chars[i] == 'H') {
                if (i - 1 >= 0 && chars[i - 1] == 'B') {
                    continue;
                }

                if (i + 1 < hamsters.length() && chars[i + 1] == '.') {
                    chars[i + 1] = 'B';
                    ++numOfBuckets;
                } else if (i - 1 >= 0 && chars[i - 1] == '.') {
                    chars[i - 1] = 'B';
                    ++numOfBuckets;
                } else {
                    return -1;
                }
            }
        }

        return numOfBuckets;
    }


    private void permute(char[] str, int indx) {
        if (str.length - 1 == indx) {
            System.out.println(Arrays.toString(str));
            return;
        }

        char temp;
        for (int i = indx; i < str.length; ++i) {
            temp = str[i];
            str[i] = str[indx];
            str[indx] = temp;
            permute(str, indx + 1);
            //System.out.println(String.valueOf(str));
            temp = str[i];
            str[i] = str[indx];
            str[indx] = temp;
        }
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        System.out.println(solution.minimumBuckets("H..H"));

        solution.permute("abc".toCharArray(), 0);
    }
}