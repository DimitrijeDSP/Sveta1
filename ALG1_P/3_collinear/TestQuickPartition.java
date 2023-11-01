class TestQuickPartition
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

//         Quick.sort(x);
         Quick.partition(x, 0, x.length -1);
		 for (i=0; i<args.length; i++)
		      StdOut.printf("%d ", x[i]);
		 StdOut.println(" ");
	 }
}
