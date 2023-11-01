/**
 * D-ary heap (min-heap)
 * @author Pavel Micka
 */
public class DAryHeap<ENTITY extends Comparable> {

    private final static int EXPAND_RATIO = 2; //how many times should be the underlying array expanded
    private final static double COLLAPSE_RATIO = 0.25; //how empty must the heap be, to be the underlying collaped
    private Object[] array;
    private int d; //parameter d
    private int size; //size of the heap
    private int initialSize;

    /**
     * Constructor
     * @param arraySize initial capacity of the heap
     */
    public DAryHeap(int initialSize, int d) {
        if (d < 2) {
            throw new IllegalArgumentException("D must be at least 2.");
        }
        this.d = d;
        this.array = new Object[initialSize];
        this.initialSize = initialSize;
        this.size = 0;
    }

    /**
     * Insert element into the heap
     * Complexity: O(log(n))
     * @param i element to be inserted
     */
    public void insert(ENTITY i) {
        if (array.length == size) {
            expand();
        }
        size++;
        int index = size - 1;
        int parentIndex = getParentIndex(index);
        while (index != 0 && i.compareTo(array[parentIndex]) < 0) { //while the element is less then its parent
            array[index] = array[parentIndex]; //place parent one level down
            index = parentIndex; //and repeat the procedure on the next level
            parentIndex = getParentIndex(index);
        }
        array[index] = i; //insert the element at the appropriate place
    }

    /**
     * Return the top element and remove it from the heap
     * Complexity: O(log(n))
     * @return top element
     */
    public ENTITY returnTop() {
        if (size == 0) {
            throw new IllegalStateException("Heap is empty");
        }
        ENTITY tmp = (ENTITY) array[0];
        array[0] = array[size - 1];
        size--;
        if (size < array.length * COLLAPSE_RATIO && array.length / EXPAND_RATIO > initialSize) {
            collapse();
        }
        repairTop(0);
        return tmp;
    }

    /**
     * Merge two heaps
     * Complexity: O(n)
     * @param heap heap to be merged with this heap
     */
    public void merge(DAryHeap<ENTITY> heap) {
        Object[] newArray = new Object[array.length + heap.array.length];
        System.arraycopy(array, 0, newArray, 0, size);
        System.arraycopy(heap.array, 0, newArray, size, heap.size);
        size = size + heap.size;
        array = newArray;
        //build heap
        for (int i = newArray.length / d; i >= 0; i--) {
            repairTop(i);
        }
    }

    /**
     * Return index of the parent element
     * @param index index of element, for which we want to return index of its parent
     * @return index of the parent element
     */
    private int getParentIndex(int index) {
        return (index - 1) / d;
    }

    /**
     * Place the top of the heap at a correct place withing the heap (repair the heap)
     * @param bottom last index of the array, which can be touched (is in the heap)
     * @param topIndex index of the top of the heap
     */
    private void repairTop(int topIndex) {
        Comparable tmp = (Comparable) array[topIndex];
        int succ = findSuccessor(topIndex * d + 1, topIndex * d + d);
        while (succ < size && tmp.compareTo(array[succ]) > 0) {
            array[topIndex] = array[succ];
            topIndex = succ;
            succ = findSuccessor(succ * d + 1, succ * d + d);
        }
        array[topIndex] = tmp;
    }

    /**
     * Return descendant with the least value
     * @param from index of the first descendant
     * @param to index of the last descendant
     * @return index of the descendant with least value
     */
    private int findSuccessor(int from, int to) {
        int succ = from;
        for (int i = from + 1; i <= to && i < size; i++) {
            if (((Comparable) array[succ]).compareTo((Comparable) array[i]) > 0) {
                succ = i;
            }
        }
        return succ;
    }

    /**
     * Expand the underlying array
     */
    private void expand() {
        array = Arrays.copyOf(array, array.length * EXPAND_RATIO);
    }

    /**
     * Collapse the underlying array
     */
    private void collapse() {
        array = Arrays.copyOf(array, array.length / EXPAND_RATIO);
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < size; i++) {
            builder.append(array[i]).append(" ");
        }
        return builder.toString();
    }
}
