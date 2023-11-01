import java.util.Comparator;

public class Point implements Comparable<Point> {

    private static double PLUSZERO = ((double) 1.0 - (double) 1.0) / (double) 1.0;
                                     // positive zero ( 0.0)
    private static double MINUSZERO = ((double) 1.0 - (double) 1.0) / -(double) 1.0;
                                     // negative zero ( 0.0)

    // compare points by slope
    // YOUR DEFINITION HERE
//    public final Comparator<Point> SLOPE_ORDER = new BySlope(this);
    public final Comparator<Point> SLOPE_ORDER = new BySlope();

    private final int x;                              // x coordinate
    private final int y;                              // y coordinate


    // create the point (x, y)
    public Point(int x, int y)
    {
        /* DO NOT MODIFY */
        this.x = x;
        this.y = y;
    }

    private class BySlope implements Comparator<Point>
    {
        public int compare(Point xx, Point yy)
        {
            double s1 = slopeTo(xx);
            double s2 = slopeTo(yy);
            if (s1 == s2) return (0);
            if (s1 < s2) return (-1);
            if (s1 > s2) return (1);
            return (0);
        }
   }

    // plot this point to standard drawing
    public void draw() {
        /* DO NOT MODIFY */
        StdDraw.point(x, y);
    }

    // draw line between this point and that point to standard drawing
    public void drawTo(Point that) {
        /* DO NOT MODIFY */
        StdDraw.line(this.x, this.y, that.x, that.y);
    }

    // slope between this point and that point
    public double slopeTo(Point that) {
        /* YOUR CODE HERE */
        if (this.x == that.x && this.y == that.y)
             return (Double.NEGATIVE_INFINITY);
        if (this.y == that.y) return (PLUSZERO);
        if (this.x == that.x) return (Double.POSITIVE_INFINITY);
        return ((double) (that.y - this.y) / (double) (that.x - this.x));
    }

    // is this point lexicographically smaller than that one?
    // comparing y-coordinates and breaking ties by x-coordinates
    public int compareTo(Point that) {
        /* YOUR CODE HERE */
        if (this.y < that.y) return (-1);
        if (this.y > that.y) return (1);
        if (this.x < that.x)  return (-1);
        if (this.x > that.x)  return (1);
        return (0);
    }

    // return string representation of this point
    public String toString() {
        /* DO NOT MODIFY */
        return "(" + x + ", " + y + ")";
    }

    // unit test
    public static void main(String[] args) {
        /* YOUR CODE HERE */
        Point p = null;
        Point q = null;

        p = new Point(97, 98);
        q = new Point(339, 175);
        StdOut.println(p.slopeTo(q));
        p = new Point(7089, 16299);
        q = new Point(27106, 6539);
        StdOut.println(p.slopeTo(q));
        p = new Point(1, 1);
        q = new Point(9, 8);
        StdOut.println(p.slopeTo(q));
    }
}