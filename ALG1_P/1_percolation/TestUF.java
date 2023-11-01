class TestUF
{
     public static void main(String[] args)
     {
		 int N = StdIn.readInt();
         System.out.println("Elements N="+N);
		 String classtype = StdIn.readString();
         System.out.println("Class Type="+classtype);
		 UF uf = null;
		 if (classtype.equals("QuickFindUF")) uf = new QuickFindUF(N);
		 if (classtype.equals("QuickUnionUF")) uf = new QuickUnionUF(N);
		 if (classtype.equals("WeightedQuickUnionUF")) uf = new WeightedQuickUnionUF(N);
		 uf.printUF();
		 while (!StdIn.isEmpty()) {
			 int p = StdIn.readInt();
			 int q = StdIn.readInt();
			 if (!uf.connected(p,q)) {
				 uf.union(p,q);
				 StdOut.println(classtype+" UNION "+p + " " + q);
			 }
		 }
		 uf.printUF();
	 }
 }
