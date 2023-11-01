import java.util.Arrays;
import java.util.Hashtable;

public class Fast {

   public static void main(String[] args) {
       // read in the input
       String filename = args[0];
       In in = new In(filename);
       int N = in.readInt();
       Point[] parr = new Point[N];
       Point[] ptmp = new Point[N];
       int i, j, k;
       double slopeold = 0.0, slopenew = 0.0;
       Hashtable<String, String> ht = new Hashtable<String, String>();
       boolean debug = args.length > 1 && args[1].equals("D");
       boolean draw = true;

        // rescale coordinates and turn on animation mode
       if (draw) StdDraw.setXscale(0, 32768);
       if (draw) StdDraw.setYscale(0, 32768);
       if (draw) StdDraw.show(0);

       for (i = 0; i < N; i++) {
           int x = in.readInt();
           int y = in.readInt();
           parr[i] = new Point(x, y);
           if (draw) parr[i].draw();
       }

       int NN = N;
       String ts = null;
       String ts1 = null;
       Point[] px = null;
       int ipx = 0, ipxs = 1;
       Arrays.sort(parr);
       for (j = 0; j < N; j++) {
            NN = N-j;
            for (i = 0; i < NN; i++)
                 ptmp[i] = parr[i+j];
            Arrays.sort(ptmp, 0, NN, parr[j].SLOPE_ORDER);
            if (debug) {
                StdOut.println("----------------------");
                StdOut.println(j+" PIVOT "+parr[j]);
                StdOut.println("----------------------");
                for (i = 0; i < NN; i++)
                    StdOut.println(i+" "+ptmp[i]+" "+parr[j].slopeTo(ptmp[i]));
                StdOut.println("----------------------");
            }
            for (i = 0; i < NN; i++) {
                if (i == 0) continue;
                slopenew = parr[j].slopeTo(ptmp[i]);
                if (i == 0) {
                    ipx = 0;
                    ipxs = 0;
                    slopeold = slopenew;
                }
                else {
                    if (i == NN-1 || slopenew != slopeold) {
                        if (i == NN-1 && NN > 3 && slopenew == slopeold)
                            ipx++;
                        if (ipx >= 3 && ipx < NN && ipxs < NN-ipx+1) {
                            px = new Point[ipx+1];
                            for (k = 0; k < ipx; k++)
                                 px[k] = ptmp[ipxs+k];
                            px[ipx++] = parr[j];
                            Arrays.sort(px);
                            ts = "";
                            ts1 = "";
                            for (k = 0; k < ipx-1; k++)
                                ts = ts + px[k].toString() + " -> ";
                            ts = ts + px[ipx-1].toString();
                            ts1 = px[ipx-2].toString() + " -> ";
                            ts1 = ts1 + px[ipx-1].toString();
                            if (!ht.containsKey(ts1)) {
                                StdOut.println(ts);
                                if (draw) px[0].drawTo(px[ipx-1]);
                                ht.put(ts1, " ");
                            }
                        }
                        ipx = 0;
                        ipxs = i;
                        slopeold = slopenew;
                    }
                }
                ipx++;
            }
        }
       // display to screen all at once
       if (draw) StdDraw.show(0);
    }
}
