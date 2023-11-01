class TestQuick
{
     public static void main(String[] args)
     {
		 Integer[] x = new Integer[args.length];
         int i;

		 for (i=0; i<args.length; i++)
		      x[i] = Integer.parseInt(args[i]);
		 for (i=0; i<args.length; i++)
		      StdOut.printf("%d ", x[i]);
		 StdOut.println(" ");

         Quick.sort(x);
		 for (i=0; i<args.length; i++)
		      StdOut.printf("%d ", x[i]);
		 StdOut.println(" ");
	 }
}
