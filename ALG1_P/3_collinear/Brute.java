public class Brute {
   public static void main(String[] args) {
        // read in the input
        String filename = args[0];
        In in = new In(filename);
        int N = in.readInt();
        Point[] parr = new Point[N];

        // rescale coordinates and turn on animation mode
       StdDraw.setXscale(0, 32768);
       StdDraw.setYscale(0, 32768);
       StdDraw.show(0);

        for (int i = 0; i < N; i++) {
            int x = in.readInt();
            int y = in.readInt();
            parr[i] = new Point(x, y);
            parr[i].draw();
        }

       Point[] px = new Point[4];
       double slope1, slope2, slope3;
       for (int a = 0; a < N; a++) {
           for (int b = a + 1; b < N - 2; b++) {
               slope1 = parr[a].slopeTo(parr[b]);
               for (int c = b + 1; c < N - 1; c++) {
                   slope2 = parr[a].slopeTo(parr[c]);
                   if (slope1 != slope2) continue;
                   for (int d = c + 1; d < N; d++) {
                       slope3 = parr[a].slopeTo(parr[d]);
                       if (slope1 != slope3) continue;
                       px[0] = parr[a];
                       px[1] = parr[b];
                       px[2] = parr[c];
                       px[3] = parr[d];
                       Selection.sort(px);
                       StdOut.print(px[0].toString()+" -> ");
                       StdOut.print(px[1].toString()+" -> ");
                       StdOut.print(px[2].toString()+" -> ");
                       StdOut.println(px[3].toString());
                       px[0].drawTo(px[3]);
                   }
               }
           }
       }
       // display to screen all at once
       StdDraw.show(0);
    }
}
