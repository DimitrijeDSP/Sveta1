class TestDeque {

    public static void main(String[] args) {
		String temp;
        Deque<String> s = new Deque<String>();
        while (!StdIn.isEmpty()) {
            String item = StdIn.readString();
            if (item.equals("-")) { temp = s.removeLast();  StdOut.println(temp); continue; }
            if (item.equals("+")) { temp = s.removeFirst(); StdOut.println(temp); continue; }
            if (item.startsWith("+")) s.addFirst(item.substring(1));
            if (item.startsWith("-")) s.addLast(item.substring(1));
        }
        StdOut.println("(" + s.size() + " left on stack)");
    }
}
