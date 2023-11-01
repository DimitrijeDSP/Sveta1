public class Subset {
    public Subset() { }

    public static void main(String[] args) {
        if (args.length != 1) return;
        int i = Integer.parseInt(args[0]);
        String temp;
        RandomizedQueue<String> s = new RandomizedQueue<String>();
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            s.enqueue(item);
        }
        for (int j = 0; j < i; j++) {
            temp = s.dequeue();
            StdOut.println(temp);
        }
    }
}
