#include<stdio.h>
#include<conio.h>
#include<math.h>

#define MAXSIZE 1000

int fnBound(int iCp,int iCw,int iK,int iMax,int aiP[MAXSIZE],int iItem,int aiW[MAXSIZE])
{
   float iUb;
   if(iK+1<iItem)
      iUb=iCp+(iMax - iCw)*(aiP[iK+1]/(float)aiW[iK+1]);
   else
      iUb=iCp;
   return iUb;
}

void fnBranch_bound(int iK,int iCp,int iCw,int iMax,int aiW[MAXSIZE],int aiPr[MAXSIZE],int iItem)
{
   static int sSol[MAXSIZE];
   static int sFp,sFw;
   int iI,iJ;
   if(iCw+aiW[iK]<=iMax)
   {
      sSol[iK]=1;
      if(iK<iItem)
     fnBranch_bound(iK+1,iCp+aiPr[iK],iCw+aiW[iK],iMax,aiW,aiPr,iItem);
      if(iK==iItem && (iCp+aiPr[iK])>sFp)
      {
     printf("\nSolution vectors are : ");
     for(iI=0;iI<iK;iI++)
       printf(" %d ",sSol[iI]);
     sFp=iCp+aiPr[iK];
     sFw=iCw+aiW[iK-1];
     printf("\nProfit is : %d",sFp);
     printf("\nWeight is : %d",sFw);
      }
   }
   if (fnBound(iCp,iCw,iK,iMax,aiPr,iItem,aiW)>sFp)
   {
      sSol[iK]=0;
      if(iK<iItem)
    fnBranch_bound(iK+1,iCp,iCw,iMax,aiW,aiPr,iItem);
      if(iK==iItem && iCp>sFp)
      {
     sFp=iCp;
     sFw=iCw;
     for(iJ=0;iJ<iK;iJ++)
        printf(" %d ",sSol[iJ]);
     printf("\nProfit is : %d",sFp);
     printf("\nWeight is : %d",iCw);
      }
   }
}



void main()
{
   int iItem, aiWeight[MAXSIZE], aiProfit[MAXSIZE], iI, iJ, iMax;

   scanf("%d %d", &iMax, &iItem);
   printf("%d %d\n", iMax, iItem);

   for(iJ=0; iJ < iItem; iJ++) {
      scanf("%d %d", &aiProfit[iJ], &aiWeight[iJ]);
   }
   for(iJ=0; iJ < iItem; iJ++) {
      printf("%d %d\n", aiProfit[iJ], aiWeight[iJ]);
   }

   fnBranch_bound(0, 0, 0, iMax, aiWeight, aiProfit, iItem);
}
