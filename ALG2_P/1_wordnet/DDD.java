import java.util.Scanner;

public class DDD {

    public static void main(String[] args) {
        In in = new In(args[0]);
        Scanner s;
        String line;
        int v;
        while (!in.isEmpty()) {
            line = in.readLine();
            s = new Scanner(line).useDelimiter(",");
            while (s.hasNextInt()) {
                v = Integer.decode(s.next()).intValue();
                StdOut.print(v+" ");
            }
            StdOut.println(" ");
        }
    }

}