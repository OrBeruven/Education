public enum EWeekDay {
    SUNDAY,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SHABAT;
    private int intValue;

    public int getValue() {
        return this.ordinal() + 1;
    }

    public static EWeekDay fromValue(int index) {
        EWeekDay[] arr = EWeekDay.values();
        return arr[index - 1];
    }

    public static void printValues() {
        for (EWeekDay day : EWeekDay.values()) {
            System.out.print(day.getValue());
        }
        System.out.println();
    }
}
