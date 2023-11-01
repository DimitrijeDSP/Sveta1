public class KdTree {

   private Node root;
   private int cnt;

   private static class Node {
       private Point2D p;      // the point
       private RectHV rect;    // the axis-aligned rectangle
                               //corresponding to this node
       private Node lb;        // the left/bottom subtree
       private Node rt;        // the right/top subtree

       private Node(Point2D x, RectHV r)
       {
           p = x;
           rect = r;
           lb = null;
           rt = null;
       }

       private RectHV getRect()
       {
           return rect;
       }
   }

   // construct an empty set of points
   public KdTree()
   {
        root = null;
        cnt = 0;
   }

   // is the set empty?
   public boolean isEmpty()
   {
       return cnt == 0;
   }

   // number of points in the set
   public int size()
   {
       return cnt;
   }

   private boolean compareKd(boolean vertical, Point2D pold, Point2D pnew)
   {
       if (vertical)                       // compare x coordinates
           return pnew.x() < pold.x();
       else                                // compare y coordinates
           return pnew.y() < pold.y();
   }

   private RectHV splitRect(boolean vertical, Point2D pold,
                             RectHV rold, Point2D pnew)
   {
       if (vertical) {                       // compare x coordinates
           if (pnew.x() < pold.x())
               return new RectHV(rold.xmin(), rold.ymin(), pold.x(), rold.ymax());
           else
               return new RectHV(pold.x(), rold.ymin(), rold.xmax(), rold.ymax());
       }
       else {                                // compare y coordinates
           if (pnew.y() < pold.y())
               return new RectHV(rold.xmin(), rold.ymin(), rold.xmax(), pold.y());
           else
               return new RectHV(rold.xmin(), pold.y(), rold.xmax(), rold.ymax());
       }
   }

   // add the point p to the set (if it is not already in the set)
   public void insert(Point2D px)
   {
       if (root == null) {
           root = new Node(px, new RectHV(0.0, 0.0, 1.0, 1.0));
           cnt++;
       }
       else {
           boolean vertical = false, leftbottom = true;
           Node nold = root;
           while (true) {
               if (px.compareTo(nold.p) == 0) break;
               leftbottom = compareKd(vertical, nold.p, px);
               if (leftbottom) {
                   if (nold.lb == null) {
                       nold.lb = new Node(px, splitRect(vertical,
                                          nold.p, nold.rect, px));
                       cnt++;
                       break;
                   }
                   else {
                       nold = nold.lb;
                       vertical = !vertical;
                       continue;
                   }
               }
               else {
                   if (nold.rt == null) {
                       nold.rt = new Node(px, splitRect(vertical,
                                          nold.p, nold.rect, px));
                       cnt++;
                       break;
                   }
                   else {
                       nold = nold.rt;
                       vertical = !vertical;
                       continue;
                   }
               }
           }
       }
   }

   // add the point p to the set (if it is not already in the set)
   public boolean contains(Point2D px)
   {
       if (root == null) {
           return false;
       }
       else {
           boolean vertical = false, leftbottom = true;
           Node nold = root;
           while (true) {
               if (px.compareTo(nold.p) == 0) return true;
               leftbottom = compareKd(vertical, nold.p, px);
               if (leftbottom) {
                   if (nold.lb == null) {
                       return false;
                   }
                   else {
                       nold = nold.lb;
                       vertical = !vertical;
                       continue;
                   }
               }
               else {
                   if (nold.rt == null) {
                       return false;
                   }
                   else {
                       nold = nold.rt;
                       vertical = !vertical;
                       continue;
                   }
               }
           }
       }
   }

   // draw all of the points to standard draw
   public void draw()
   {
       StdOut.println("draw start");
   }

   // all points in the set that are inside the rectangle
   public Iterable<Point2D> range(RectHV rct)
   {
       Stack<Point2D> st = new Stack<Point2D>();
       if (root == null) return st;
       range(st, root, rct);
       return st;
   }

   private void range(Stack<Point2D> s, Node x, RectHV r)
   {
       if (x == null) return;
       if (!r.intersects(x.getRect())) return;
       Point2D pt = x.p;
       if (r.contains(pt)) s.push(pt);
       range(s, x.lb, r);
       range(s, x.rt, r);
   }

   // a nearest neighbor in the set to p; null if set is empty
   public Point2D nearest(Point2D p)
   {
       boolean vertical = false;
       Point2D res = null;
       if (cnt == 0) return null;
       res = nearest(vertical, root, p, Double.MAX_VALUE);
       return res;
   }

   private Point2D nearest(boolean vertical, Node x, Point2D p, double max)
   {
       Node n1, n2;
       Point2D pmin = null, px;
       double mx, m = max;
       boolean leftbottom = true;

       if (x == null) return null;
       if (p.compareTo(x.p) == 0) return p;
       if (x.getRect().distanceSquaredTo(p) > max) return null;
       leftbottom = compareKd(vertical, x.p, p);

       mx = p.distanceSquaredTo(x.p);
       if (mx < max) {
           pmin = x.p;
           m = mx;
       }

       if (leftbottom) {
           n1 = x.lb;
           n2 = x.rt;
       }
       else {
           n1 = x.rt;
           n2 = x.lb;
       }

       px = nearest(!vertical, n1, p, m);
       if (px != null) {
           mx = px.distanceSquaredTo(p);
           if (mx < m) {
               pmin = px;
               m = mx;
           }
       }

       px = nearest(!vertical, n2, p, m);
       if (px != null) {
           mx = px.distanceSquaredTo(p);
           if (mx < m) {
               pmin = px;
               m = mx;
           }
       }
       return pmin;
   }

   public static void main(String[] args)
   {
       KdTree x = new KdTree();

       x.insert(new Point2D(0.206107, 0.095492));
       x.insert(new Point2D(0.975528, 0.654508));
       x.insert(new Point2D(0.024472, 0.345492));
       x.insert(new Point2D(0.793893, 0.095492));
       x.insert(new Point2D(0.793893, 0.904508));
       x.insert(new Point2D(0.975528, 0.345492));
       x.insert(new Point2D(0.206107, 0.904508));
       x.insert(new Point2D(0.500000, 0.000000));
       x.insert(new Point2D(0.024472, 0.654508));
       x.insert(new Point2D(0.500000, 1.000000));
       Point2D r;
       r = x.nearest(new Point2D(0.81, 0.3));
       StdOut.println("r=" + r);
       r = x.nearest(new Point2D(0.206107, 0.095492));
       StdOut.println("r=" + r);
   }
}