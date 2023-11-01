
import java.awt.Font;

public class PercolationStatsTest
{
   private int np;
   private int tp;
   private double[] treshold;

   public PercolationStatsTest(int N, int T)    // perform T independent computational
                                            // experiments on an N-by-N grid
   {
        if (N < 0 || T <= 0)
            throw new java.lang.IllegalArgumentException("either N < 0 or T < 0");
        np = N;
        tp = T;
        treshold = new double[tp];
        for (int i = 0; i < tp; i++) {
            treshold[i] = runExperiment()/(np*np);
        }
   }

   private double runExperiment()
   {
       StdRandom.setSeed(System.currentTimeMillis());
       double count = 0.0;
       StdDraw.show(0);
	   Percolation px = new Percolation(np);
	   PercolationVisualizer.draw(px, np);
	   StdDraw.show(300);
       while (!px.percolates()) {
           int ix = StdRandom.uniform(np)+1;
           int jx = StdRandom.uniform(np)+1;
           if (!px.isOpen(ix, jx)) {
               count += 1.0;
               px.open(ix, jx);
               PercolationVisualizer.draw(px, np);
               StdDraw.show(300);
           }
       }
       return (count);
   }

   public double mean()    // sample mean of percolation threshold
   {
       double sum = 0.0;
       for (int i = 0; i < tp; i++) {
           sum += treshold[i];
       }
       if (tp > 0)
           return (sum/tp);
       else
           return (0.0);
   }

   public double stddev()    // sample standard deviation of percolation threshold
   {
       double sum = 0, x;
       double m = mean();
       for (int i = 0; i < tp; i++) {
           x = treshold[i] - m;
           sum += x*x;
      }
      if (tp > 1)
          return (Math.sqrt(sum/(tp -1)));
      else
          return (0.0);
   }

   public double confidenceLo()  // returns lower bound of the 95% confidence int
   {
       if (tp < 1) return (0.0);
       return (mean() - 1.96*stddev()/Math.sqrt(tp));
   }

   public double confidenceHi()  // returns upper bound of the 95% confidence int
   {
       if (tp < 1) return (0.0);
       return (mean() + 1.96*stddev()/Math.sqrt(tp));
   }

//   public void printTresholds()
//   {
//       for (int i=0; i<tp; i++) {
//           StdOut.printf("%18.16f", treshold[i]);
//           StdOut.println();
//      }
//   }

   public static void main(String[] args)   // test client, described below
   {
       int x = Integer.parseInt(args[0]);
       int y = Integer.parseInt(args[1]);
       PercolationStatsTest z = new PercolationStatsTest(x, y);

       StdOut.printf("mean =                    ");
       StdOut.printf("%18.16f", z.mean());
       StdOut.println();
       StdOut.printf("stddev =                  ");
       StdOut.printf("%18.16f", z.stddev());
       StdOut.println();
       StdOut.printf("95%% confidence interval = ");
       StdOut.printf("%18.16f", z.confidenceLo());
       StdOut.printf(", ");
       StdOut.printf("%18.16f", z.confidenceHi());
       StdOut.println();
//       z.printTresholds();
   }
}