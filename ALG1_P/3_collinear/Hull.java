Stack<Point2D> hull = new Stack<Point>();

Arrays.sort(p, Point2D.Y_ORDER);    p[0] is now point with lowest y-coordinate
Arrays.sort(p, p[0].BY_POLAR_ORDER);     sort by polar angle with respect to p[0]

hull.push(p[0]);        difinitely on hull
hull.push(p[0]);

for (int i = 2; i < N; i++) {
   Point2D top = hull.pop();
   while (Point2D.ccw(hull.peek(), top, p[i]) <= 0)
      top = hull.pop();
   hull.push(top);
   hull.push(p[i]);     add p[i] to putative hull
}