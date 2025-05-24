public class Main {
    public static void main(String[] args) {
        int[][] mat = {{2, 3, 4, 5},
                        {6, 7, 8, 9},
                        {2, 3, 4, 0},
                        {3, 3, 3, 1}};

        System.out.println("1 == " + identityMatrix(mat, 4));

        int[][] mat2 = {{2, 3, 4, 5},
                {3, 3, 3, 3},
                {6, 7, 1, 0},
                {2, 3, 0, 1}};

        System.out.println("2 == " + identityMatrix(mat2, 4));

        int[][] mat3 = {{4, 3, 9, 0, 2},
                {1, 2, 3, 4, 5},
                {6, 3, 1, 0, 0},
                {7, 6, 0, 1, 0},
                {3, 2, 0, 0, 1}};

        System.out.println("3 == " + identityMatrix(mat3, 5));

        int[][] mat4 = {{4, 3, 9, 0, 2},
                        {1, 2, 3, 4, 5},
                        {6, 3, 1, 0, 0},
                        {7, 6, 0, 1, 0},
                        {3, 2, 1, 0, 1}};

        System.out.println("2 == " + identityMatrix(mat4, 5));
    }

    public static int identityMatrix(int[][] mat, int size) {
        int result = 0;
        int currIndex = size - 1;

        while (currIndex >= 0 && mat[currIndex][currIndex] == 1) {
            for (int i = 0; i + currIndex < size - 1; ++i){
                if (mat[i + currIndex + 1][currIndex] != 0 || mat[currIndex][i + currIndex + 1] != 0) {
                    return result;
                }
            }

            ++result;
            --currIndex;
        }

        return result;
    }
}