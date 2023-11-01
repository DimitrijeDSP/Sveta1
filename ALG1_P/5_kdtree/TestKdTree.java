import java.util.Iterator;
import java.util.Arrays;

public class TestKdTree {
    private KdTree k;

    public void set_up() {
        k = new KdTree();
    }

    public void tear_down() {}

    private Point2D[] get_points() {
        return new Point2D[]{
            new Point2D(0.3, 0.2),
            new Point2D(0.2, 0.2),
            new Point2D(0.1, 0.1),
            new Point2D(0.2, 0.1),
            new Point2D(0.3, 0.3)
        };
    }

    public void test_insert_first() {
        k.insert(new Point2D(0.1, 0.1));
    }

    public void test_insert_distinct() {
        Point2D[] points = get_points();
        for (Point2D point : points) k.insert(point);
    }

    public void test_insert_same() {
        for (int i = 0; i < 5; i++) k.insert(new Point2D(0.1, 0.1));
    }

    public void test_single_contains() {
        k.insert(new Point2D(0.1, 0.1));
    }

    public void test_multiple_contains() {
        Point2D[] points = get_points();
        for (Point2D point : points) k.insert(point);
    }

    public void test_not_empty_not_contains() {
        Point2D[] points = get_points();
        for (Point2D point : points) k.insert(point);
    }

    public void test_empty_range() {
        Iterator<Point2D> iter = k.range(new RectHV(0, 0, 1, 1)).iterator();
    }

    public void test_single_range() {
        Point2D p = new Point2D(1, 1);
        k.insert(p);

        Iterator<Point2D> iter = k.range(new RectHV(0, 0, 1, 1)).iterator();
    }

    public void test_multiple_range() {
        Point2D[] points = get_points();
        for (Point2D point : points) k.insert(point);

        Iterator<Point2D> iter = k.range(new RectHV(0, 0, 1, 1)).iterator();

        int cnt = 0;
        while (iter.hasNext()) {
            cnt++;
            Point2D p = iter.next();
            Arrays.asList(points).contains(p);
        }
    }

    public void test_selected_range() {
        Point2D[] points = new Point2D[]{
            new Point2D(.5, .5),
            new Point2D(.7, .8),
            new Point2D(.1, .1),
            new Point2D(1, 0),
            new Point2D(.3, .9),
        };
        for (Point2D point : points) k.insert(point);

        Iterator<Point2D> iter = k.range(new RectHV(.6, .6, .8, .8)).iterator();
        iter.next().equals(points[1]);

        iter = k.range(new RectHV(0, 0, .6, .6)).iterator();
        iter.next().equals(points[2]);
        iter.next().equals(points[0]);
    }

    public void test_not_empty_no_range() {
        Point2D[] points = get_points();
        for (Point2D point : points) k.insert(point);

        Iterator<Point2D> iter = k.range(new RectHV(.4, .4, 1, 1)).iterator();
    }

    public void test_nearest_single() {
        Point2D p = new Point2D(0, 0);
        k.insert(p);
    }

    public void test_nearest_multiple_exact() {
        Point2D[] points = get_points();
        for (Point2D point : points) k.insert(point);
    }

    public void test_nearest_multiple() {
        Point2D[] points = new Point2D[]{
            new Point2D(.5, .5),
            new Point2D(.7, .8),
            new Point2D(.1, .1),
            new Point2D(1, 0),
            new Point2D(.3, .9),
        };
        for (Point2D point : points) k.insert(point);

    }

    public static void main (String[] args)
    {
        TestKdTree x = new TestKdTree();
        x.set_up();
        x.test_insert_first();
    }
}