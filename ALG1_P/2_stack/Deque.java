import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {
   private int N;          // size of the structure
   private Node first;     // top of structure
   private Node last;      // bottom of structure

    private class Node {
        private Item item;
        private Node next;
        private Node prev;
    }

   public Deque() {                    // construct an empty deque
       first = null;
       last = null;
       N = 0;
       assert check();
   }

   public boolean isEmpty() {          // is the deque empty?
       return (N == 0);
   }

   public int size() {                 // return the number of items on the deque
       return N;
   }

   public void addFirst(Item item) {  // insert the item at the front
       if (item == null) throw new java.lang.NullPointerException("Null element");
       if (isEmpty()) {
           first = new Node();
           last = first;
           first.item = item;
           first.prev = null;
           first.next = null;
       }
       else {
           Node oldfirst = first;
           first = new Node();
           first.item = item;
           first.next = oldfirst;
           first.prev = null;
           oldfirst.prev = first;
           oldfirst = null;       }
       N++;
       assert check();
   }

   public void addLast(Item item) {  // insert the item at the front
       if (item == null) throw new java.lang.NullPointerException("Null element");
       if (isEmpty()) {
           first = new Node();
           last = first;
           last.item = item;
           first.prev = null;
           first.next = null;
       }
       else {
           Node oldlast = last;
           last = new Node();
           last.item = item;
           last.prev = oldlast;
           last.next = null;
           oldlast.next = last;
           oldlast = null;
       }
       N++;
       assert check();
   }

   public Item removeFirst() {         // delete and return the item at the front
       Item result = null;
       if (isEmpty()) throw new NoSuchElementException("Stack underflow");
       if (N == 0) {
           result = null;
       }
       else if (N == 1) {
           result = first.item;
           first = null;
           last = null;
           N = 0;
       }
       else {
           result = first.item;
           first = first.next;
           first.prev = null;
           N--;
       }
       assert check();
       return result;
   }

   public Item removeLast() {         // delete and return the item at the front
       Item result = null;
       if (isEmpty()) throw new NoSuchElementException("Stack underflow");
       if (N == 0) {
           result = null;
       }
       else if (N == 1) {
          result = last.item;
           first = null;
           last = null;
           N = 0;
       }
       else {
           result = last.item;
           last = last.prev;
           last.next = null;
           N--;
       }
       assert check();
       return result;
   }

   public Iterator<Item> iterator() {   // return an iterator over items
       return new ListIterator();
   }


    // an iterator, doesn't implement remove() since it's optional
    private class ListIterator implements Iterator<Item> {
        private Node current = first;
        public boolean hasNext()  { return current != null;                     }
        public void remove()      { throw new UnsupportedOperationException();  }

        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    // check internal invariants
    private boolean check() {
        if (N == 0) {
            if (first != null && last != null) return false;
        }
        else if (N == 1) {
            if (first == null)      return false;
            if (first.next != null) return false;
            if (last == null)      return false;
        }
        else {
            if (first.next == null) return false;
            if (last.prev == null) return false;
        }

        // check internal consistency of instance variable N
        int numberOfNodes = 0;
        for (Node x = first; x != null; x = x.next) {
            numberOfNodes++;
        }
        if (numberOfNodes != N) return false;

        return true;
    }
}