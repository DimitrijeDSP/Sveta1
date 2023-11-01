public class PointSET {
   private RedBlackBST<Point2D, Integer> rbbst;

   // construct an empty set of points
   public PointSET()
   {
       rbbst = new RedBlackBST<Point2D, Integer>();
   }

   // is the set empty?
   public boolean isEmpty()
   {
       return rbbst.isEmpty();
   }

   // number of points in the set
   public int size()
   {
       return rbbst.size();
   }

   // add the point p to the set (if it is not already in the set)
   public void insert(Point2D p)
   {
       rbbst.put(p, 0);
   }

   // does the set contain the point p?
   public boolean contains(Point2D p)
   {
       return rbbst.contains(p);
   }

   // draw all of the points to standard draw
   public void draw()
   {
       for (Point2D p : rbbst.keys())
            p.draw();
   }

   // all points in the set that are inside the rectangle
   public Iterable<Point2D> range(RectHV rect)
   {
       Stack<Point2D> pr = new Stack<Point2D>();

       for (Point2D p : rbbst.keys())
            if (rect.contains(p))
                 pr.push(p);
       return pr;
   }

   // a nearest neighbor in the set to p; null if set is empty
   public Point2D nearest(Point2D p)
   {
       if (isEmpty()) return null;
       Point2D pmin = null;
       double temp, dmin = Double.POSITIVE_INFINITY;
       for (Point2D px : rbbst.keys()) {
           temp = px.distanceTo(p);
           if (temp < dmin) {
              dmin = temp;
              pmin = px;
           }
       }
       if (pmin == null || dmin == Double.POSITIVE_INFINITY) return null;
       return pmin;
   }
}