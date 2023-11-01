public class RunLength {
    private final static int R = 256;
    private final static int lgR = 8;

    public static void compress() {

    }

    public static void expand() {
        boolean bit = false;
        while (!BinaryStdIn. isEmpty()) {
            int run = BinaryStdIn.readInt(lgR);
            for (int i = 0; i < run; i++)
                BinaryStdOut.write(bit);
            bit = !bit;
        }
        BinaryStdOut.close();
    }
}