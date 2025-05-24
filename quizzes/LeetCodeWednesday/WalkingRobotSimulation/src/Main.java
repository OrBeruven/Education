import java.util.Arrays;
import java.util.Comparator;

class Solution {
    private static final int NORTH = 0;
    private static final int EAST = 1;
    private static final int SOUTH = 2;
    private static final int WEST = 3;

    private static int xDistance = 0;
    private static int yDistance = 0;
    private static int direction = NORTH;
    private static int numOfMoves = 0;

    private static int xFurthest = 0;
    private static int yFurthest = 0;
    public int robotSim(int[] commands, int[][] obstacles) {
        xDistance = 0;
        yDistance = 0;
        direction = NORTH;
        xFurthest = 0;
        yFurthest = 0;

        Arrays.sort(obstacles, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                return Integer.compare(o1[0], o2[0]);
            }
        });

        for (int i = 0; i < commands.length; ++i) {
            numOfMoves = getMovesOrChangeDirection(commands[i]);

            for (int j = 0; j < numOfMoves; ++j) {
                if (isBlocked(obstacles)) {
                    break;
                }

                moveInDirection();
            }
        }

        return (xFurthest * xFurthest) + (yFurthest * yFurthest);
    }

    public static void main(String[] args) {
        Solution solution = new Solution();
        int[] commands1 = {-2, 8, 3, 7, -1};
        int[][] obstacles1 = {{-4,-1} ,{1,-1}, {1,4}, {5,0}, {4,5}, {-2,-1}, {2,-5}, {5,1}, {-3,-1}, {5,-3}};
        System.out.println(solution.robotSim(commands1, obstacles1));
    }

    private static int getMovesOrChangeDirection(int command) {
        return switch (command) {
            case -1 -> {
                moveRight();
                yield 0;
            }
            case -2 -> {
                moveLeft();
                yield 0;
            }
            default -> command;
        };
    }

    private static void moveRight() {
        ++direction;
        if (direction > WEST) {
            direction = NORTH;
        }
    }

    private static void moveLeft() {
        --direction;
        if (direction < NORTH) {
            direction = WEST;
        }
    }

    private static void moveInDirection() {
        switch (direction) {
            case NORTH:
                ++yDistance;
                break;
            case EAST:
                ++xDistance;
                break;
            case SOUTH:
                --yDistance;
                break;
            case WEST:
                --xDistance;
                break;
        }

        if (Math.abs(xDistance) > Math.abs(xFurthest)) {
            xFurthest = xDistance;
        }

        if (Math.abs(yDistance) > Math.abs(yFurthest)) {
            yFurthest = yDistance;
        }
    }

    private static boolean isBlocked(int[][] obstacles) {
        for (int[] obstacle : obstacles) {
            switch (direction) {
                case NORTH:
                    if (obstacle[0] == xDistance && obstacle[1] == yDistance + 1) {
                        return true;
                    }
                    break;
                case EAST:
                    if (obstacle[0] == xDistance + 1 && obstacle[1] == yDistance) {
                        return true;
                    }
                    break;
                case SOUTH:
                    if (obstacle[0] == xDistance && obstacle[1] == yDistance - 1) {
                        return true;
                    }
                    break;
                case WEST:
                    if (obstacle[0] == xDistance - 1 && obstacle[1] == yDistance) {
                        break;
                    }
            }
        }
        return false;
    }
}

