import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {
    private Item[] a;         // array of items
    private int N;            // number of elements on stack
    private int NMAX;         // number of max filled elements on stack

    public RandomizedQueue() {           // construct an empty randomized queue
        a = (Item[]) new Object[2];
//        long tcurr = System.currentTimeMillis();
//        StdRandom.setSeed(StdRandom.getSeed()+tcurr);
        N = 0;
        NMAX = 0;
    }

    public boolean isEmpty() {          // is the queue empty?
       return N == 0;
    }

    public int size() {                  // return the number of items on the queue
       return N;
    }

    public void enqueue(Item item) {               // add the item
        if (item == null) throw new java.lang.NullPointerException("Null element");
        if (N == a.length) resize(2*a.length);    // double size of array if nec
        a[N++] = item;                            // add item
        NMAX++;
    }

    public Item dequeue() {             // delete and return a random item
        Item item = null;
        Item temp = null;
        if (isEmpty()) throw new NoSuchElementException("Queue empty");
        if (N <= 0) {
            item = null;
        }
        else if (N == 1) {
            item = a[0];
            a[0] = null;
            N = 0;
            return item;
        }
        else if (N > 1 && N < 3) {
            item = a[N-1];
            a[N-1] = null;
            N--;
            return item;
        }
        else {
            int irand;
            irand = StdRandom.uniform(N);
            temp = a[irand];
            a[irand] = a[0];
            a[0] = temp;
            irand = StdRandom.uniform(N);
            temp = a[irand];
            a[irand] = a[N-1];
            a[N-1] = temp;
            irand = StdRandom.uniform(NMAX) % N;
            item = a[irand];
            if (irand < N-1) a[irand] = a[N-1];
            a[N-1] = null;    // to avoid loitering
            N--;
            // shrink size of array if necessary
            if (N > 0 && N == a.length/4) resize(a.length/2);
        }
        return item;
    }

    public Item sample() {            // return (but do not delete) a random item
        if (isEmpty()) throw new NoSuchElementException("Queue empty");
        int irand = StdRandom.uniform(N);
        Item item = a[irand];
        return item;
    }

    public Iterator<Item> iterator() {  // return an ind iterator in random order
        return new ReverseArrayIterator();
    }

    // an iterator, doesn't implement remove() since it's optional
    private class ReverseArrayIterator implements Iterator<Item> {
        private int i;
        private Item[] ia;        // array of items
        private int[] ix;         // array of random indices
        private boolean[] ib;     // statuses random indices

        public ReverseArrayIterator() {
 //           long tcurr = System.currentTimeMillis();
 //           StdRandom.setSeed(StdRandom.getSeed()+tcurr);
            i = N;
            ix = new int[N];
            ib = new boolean[N];
            for (int j = 0; j < N; j++) {
                ix[j] = j;
                ib[j] = false;
            }
            StdRandom.shuffle(ix);
        }

        public boolean hasNext() {
            return i > 0;
        }

        public void remove() {
            throw new UnsupportedOperationException();
        }

        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            return a[ix[--i]];
        }
    }

    // resize the underlying array holding the elements
    private void resize(int capacity) {
        assert capacity >= N;
        Item[] temp = (Item[]) new Object[capacity];
        for (int i = 0; i < N; i++) {
            temp[i] = a[i];
        }
        a = temp;
    }

}