import java.util.Stack;

public class SeamCarver {
    private Picture pict;
    private int pwidth;
    private int pheight;
    private int pdim;
    private double[] ener;
    private int[] edgeTo;
    private double[] distTo;
    private Stack<Integer> tord;

    public SeamCarver(Picture picture) {
        pwidth = picture.width();
        pheight = picture.height();
        pdim = pwidth * pheight;
        ener = new double[pdim];
        edgeTo = new int[pdim];
        distTo = new double[pdim];
        tord = new Stack<Integer>();

        pict = new Picture(picture);
        for (int i = 0; i < pwidth; i++) {
            for (int j = 0; j < pheight; j++) {
                ener[j*pwidth + i] = energy(i, j);
            }
        }
//        printEner(true);
//        printAdj(true);
//        printEner(false);
//        printAdj(false);
    }

    private double ener(int index, boolean vertical)
    {
        if (index < 0 || index > pdim) return Double.POSITIVE_INFINITY;
        if (vertical) return ener[index];
        return ener[index / pheight + (index % pheight) * pwidth];
    }

    private double distTo(int index, boolean vertical)
    {
        if (index < 0 || index > pdim) return Double.POSITIVE_INFINITY;
        if (vertical) return distTo[index];
        return distTo[index / pheight + (index % pheight) * pwidth];
    }

    private int edgeTo(int index, boolean vertical)
    {
        if (index < 0 || index > pdim) return -1;
        if (vertical) return edgeTo[index];
        return edgeTo[index / pheight + (index % pheight) * pwidth];
    }

    private int pheight(boolean vertical) {
        if (vertical) return pheight;
        return pwidth;
    }

    private int pwidth(boolean vertical) {
        if (vertical) return pwidth;
        return pheight;
    }

    private void printEdge(boolean v)
    {
        if (v) 
            StdOut.println("edgeTo MATRIX VERTICAL");
        else
            StdOut.println("edgeTo MATRIX HORIZONTAL");
        int j = 0;
        for (int i = 0; i < pdim; i++) { 
            if (j == pwidth(v)) {
                StdOut.println(" ");
                j = 0;
            }
            StdOut.print(edgeTo(i, v) + " ");
            j++;
        } 
        StdOut.println(" ");
    }

    private void printDist(boolean v)
    {
        if (v) 
            StdOut.println("DISTANCE MATRIX VERTICAL");
        else
            StdOut.println("DISTANCE MATRIX HORIZONTAL");
        int j = 0;
        for (int i = 0; i < pdim; i++) { 
            if (j == pwidth(v)) {
                StdOut.println(" ");
                j = 0;
            }
            StdOut.print(distTo(i, v) + " ");
            j++;
        } 
        StdOut.println(" ");
    }

    private void printEner(boolean v)
    {
        if (v) 
            StdOut.println("ENERGY MATRIX VERTICAL");
        else
            StdOut.println("ENERGY MATRIX HORIZONTAL");
        int j = 0;
        for (int i = 0; i < pdim; i++) { 
            if (j == pwidth(v)) {
                StdOut.println(" ");
                j = 0;
            }
            StdOut.print(ener(i, v) + " ");
            j++;
        } 
        StdOut.println(" ");
    }

    private void printAdj(boolean v)
    {
        if (v) 
            StdOut.println("ADJANCENCY LIST VERTICAL");
        else
            StdOut.println("ADJANCENCY LIST HORIZONTAL");
        int[] x;
        for (int i = 0; i < pdim; i++) {
            x = adj(i, v);
            StdOut.println("-------- ADJ("+i+")={"+x[0]+","+x[1]+","+x[2]+"} "
                           +ener(i, v)+"-->{"+ener(x[0], v)
                           +","+ener(x[1], v)+","+ener(x[2], v)+"} ");  
        }
    }

    // current picture
    public Picture picture() {
        return pict;
    }                      

    // width  of current picture
    public     int width() {
        return pwidth;
    } 

    // height of current picture                       
    public     int height() {
        return pheight;
    }              

    // energy of pixel at column x and row y in current picture         
    public  double energy(int x, int y) {
        int ir1, ig1, ib1, ir2, ig2, ib2, rx, gx, bx;
        double dx2, dy2;

        if (x < 0 || x > pwidth - 1)  
            throw new java.lang.IndexOutOfBoundsException();

        if (y < 0 || y > pheight - 1)
            throw new java.lang.IndexOutOfBoundsException();

        if (x == 0 || x == pwidth - 1)  return 195075;
        if (y == 0 || y == pheight - 1)  return 195075;

        ir1 = pict.get(x-1, y).getRed();
        ig1 = pict.get(x-1, y).getGreen();
        ib1 = pict.get(x-1, y).getBlue();
        ir2 = pict.get(x+1, y).getRed();
        ig2 = pict.get(x+1, y).getGreen();
        ib2 = pict.get(x+1, y).getBlue();

        rx = ir1 - ir2; 
        gx = ig1 - ig2; 
        bx = ib1 - ib2;
        dx2 =  rx*rx + gx*gx + bx*bx;

        ir1 = pict.get(x, y-1).getRed();
        ig1 = pict.get(x, y-1).getGreen();
        ib1 = pict.get(x, y-1).getBlue();
        ir2 = pict.get(x, y+1).getRed();
        ig2 = pict.get(x, y+1).getGreen();
        ib2 = pict.get(x, y+1).getBlue();

        rx = ir1 - ir2; 
        gx = ig1 - ig2; 
        bx = ib1 - ib2;
        dy2 =  rx*rx + gx*gx + bx*bx;

        return dx2 + dy2;
    }           

    // sequence of indices for horizontal seam in current picture 
    public   int[] findHorizontalSeam()  {
        return findSeam(false);
    }          

    // sequence of indices for vertical   seam in current picture
    public   int[] findVerticalSeam() {
        return findSeam(true);
    }

    private int[] findSeam(boolean v)
    {
        double pmin1 = Double.POSITIVE_INFINITY;
        double pmin2 = Double.POSITIVE_INFINITY;
        int i, j, k, imin = -1;
        int[] bestseam = null;
        int[] result = new int[pheight(v)];

        for (i = 0; i < pwidth(v); i++) {
            seamSP(i, v);
            pmin1 = Double.POSITIVE_INFINITY;
            for (j = 0; j < pwidth(v); j++) {
                k = pdim - pwidth(v) + j;
                if (distTo[k] < pmin1) {
                    pmin1 = distTo[k];
                    imin = k;
                }
            }
            if (pmin1 < pmin2) {
                bestseam = pathTo(imin, v);
                pmin2 = pmin1;    
//                StdOut.printf("pmin1=%f pmin2=%f\n", pmin1, pmin2);
            } 
        }

        for (i = 0; i < pheight(v); i++)
            result[i] = bestseam[i] % pwidth(v);

//        printDist(v);
//        printEdge(v);
        return result;
    }             

    // remove horizontal seam from current picture
    public    void removeHorizontalSeam(int[] a) {
        removeSeam(a, false);
    }  

    // remove vertical   seam from current picture 
    public    void removeVerticalSeam(int[] a) {
        removeSeam(a, true);
    }

    private void removeSeam(int[] a, boolean v) {
        int x, y, pwnew, phnew;
        double temp;

        if (v) {
            pwnew = pwidth - 1;
            phnew = pheight;
            for (x = 0; x < pheight; x++)
                ener[x*pwidth + a[x]] = Double.NEGATIVE_INFINITY;
        }
        else {
            pwnew = pwidth;
            phnew = pheight - 1;
            for (x = 0; x < pwidth; x++)
                ener[a[x]*pwidth + x] = Double.NEGATIVE_INFINITY;            
        }

        Picture pnew = new Picture(pwnew, phnew);
        y = 0;
        for (x = 0; x < pdim; x++) {
            temp = ener[x];
            if (temp == Double.NEGATIVE_INFINITY) continue;
            ener[y] = temp;
            pnew.set(y%pwnew, y/pwnew, pict.get(x%pwidth, x/pwidth));
            y++;
        }
        pwidth = pwnew;
        pheight = phnew;
    }

    private int[] adj(int x, boolean v) {
        int[] a = {-1, -1, -1};
        int col = x % pwidth(v);
        int row = x / pwidth(v);
        int row1 = row + 1;
        int col1 = col - 1;
        int col2 = col;
        int col3 = col + 1;

        if (row < pheight(v) - 1) {
            if (col1 >= 0)             a[0] = row1 * pwidth(v) + col1;    
                                       a[1] = row1 * pwidth(v) + col2;    
            if (col3 <= pwidth(v) - 1) a[2] = row1 * pwidth(v) + col3;
        }  
        return a;
    }

    private void seamSP(int s, boolean v)
    {
        int i, j;
        int[] a;
         
        for (i = 0; i < pdim; i++) {
            distTo[i] = Double.POSITIVE_INFINITY;
            edgeTo[i] = -1;
        }

        int sx;
        //if (v) 
            sx = s;
        //else 
        //    sx = s / pheight + (s % pheight) * pwidth;

        distTo[sx] = 0.0;
        edgeTo[sx] = -1;

        // Topological order is same as natural order of pixels 
        // from upper left corner to bottom right corner
        tord.push(Integer.valueOf(sx));        
        while (!tord.empty()) {
            i = tord.pop().intValue();
            a = adj(i, v);
            for (j = 0; j < 3; j++) {
                if (a[j] == -1) continue;
                tord.push(Integer.valueOf(a[j]));
                relax(i, a[j], v);                
            }
        }
    }

    private void relax(int v, int w, boolean x)
    {
        if (distTo[w] > distTo[v] + ener(w, x)) {
            distTo[w] = distTo[v] + ener(w, x);
            edgeTo[w] = v;
        }
    }

    private int[] pathTo(int v, boolean x) {
        if (distTo[v] == Double.POSITIVE_INFINITY) return null;
        int[] path = new int[pheight(x)];
        int j = v;
        path[pheight(x) - 1] = v;
        for (int i = 0; i < pheight(x) - 1; i++) {
            path[pheight(x) - i - 2] = edgeTo[j];
            j = edgeTo[j];
        }
        return path;
    }

    public static void main(String[] args)
    {
        Picture inputImg = new Picture(args[0]);
        System.out.printf("image is %d columns by %d rows\n", 
            inputImg.width(), inputImg.height());
        //inputImg.show();        
        SeamCarver sc = new SeamCarver(inputImg);
        
        System.out.printf("Displaying vertical seam calculated.\n");

        int[] vs = sc.findVerticalSeam();
        for (int i = 0; i < vs.length; i++)
            StdOut.println("vs["+i+"]="+vs[i]);

        int[] hs = sc.findHorizontalSeam();
        for (int i = 0; i < hs.length; i++)
            StdOut.println("hs["+i+"]="+hs[i]);

    }

}