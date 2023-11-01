class TestRandomizedQueue {
	    public static void main(String[] args) {
			String temp;
	        RandomizedQueue<String> s = new RandomizedQueue<String>();
	        while (!StdIn.isEmpty()) {
	            String item = StdIn.readString();
	            if (item.equals("-")) { temp = s.dequeue();  StdOut.println(temp); continue; }
	            if (item.equals("+")) { temp = s.sample();  StdOut.println(temp); continue; }
	            s.enqueue(item);
	        }
	        StdOut.println("(" + s.size() + " left in queue)");

            for(String x : s ){
			   System.out.println(x);
            }
    }
}
