public enum EnumSingleton {
    INSTANCE;
    int value;
    public int getValue() {
        return this.value;
    }
    public void setValue(int value) {
        this.value = value;
    }
}