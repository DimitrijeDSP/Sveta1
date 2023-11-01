#include <stdio.h>
#include <conio.h>
#include <math.h> 

int fnBound(int iCp,int iCw,int iK,int iMax,int aiP[9],int iItem,int aiW[9]) 
{ 
float iUb; 
if(iK+1 iUb=iCp+(iMax - iCw)*(aiP[iK+1]/(float)aiW[iK+1]); 
else 
iUb=iCp; 
return iUb; 
} 

void fnBranch_bound(int iK,int iCp,int iCw,int iMax,int aiW[9],int aiPr[9],int iItem) 
{ 
static int sSol[9]; 
static int sFp,sFw; 
int iI,iJ; 
if(iCw+aiW[iK]<=iMax) 
{ 
sSol[iK]=1; 
if(iK fnBranch_bound(iK+1,iCp+aiPr[iK],iCw+aiW[iK],iMax,aiW,aiPr,iItem); 
if(iK==iItem && (iCp+aiPr[iK])>sFp) 
{ 
printf("\nSolution vectors are : "); 
for(iI=0;iI printf(" %d ",sSol[iI]); 
sFp=iCp+aiPr[iK]; 
sFw=iCw+aiW[iK-1]; 
printf("\nProfit is : %d",sFp); 
printf("\nWeight is : %d",sFw); 
} 
} 
if (fnBound(iCp,iCw,iK,iMax,aiPr,iItem,aiW)>sFp) 
{ 
sSol[iK]=0; 
if(iK fnBranch_bound(iK+1,iCp,iCw,iMax,aiW,aiPr,iItem); 
if(iK==iItem && iCp>sFp) 
{ 
sFp=iCp; 
sFw=iCw; 
for(iJ=0;iJ printf(" %d ",sSol[iJ]); 
printf("\nProfit is : %d",sFp); 
printf("\nWeight is : %d",iCw); 
} 
} 
} 



void main() 
{ 
int iItem,aiWeight[9],aiProfit[9],iI,iJ,iMax; 
void fnBranch_bound(int iK,int iCp,int iCw,int iMax,int aiW[9],int aiPr[9],int iItem); 
clrscr(); 
printf("Knap Sack Problem Solving using branch and bound method.\n"); 
printf("How many item do you want : "); 
scanf("%d",&iItem); 
printf("Enter the weight and profit for each item \n"); 
printf("Weight Profit\n"); 
for(iJ=0;iJ scanf("%d%d",&aiWeight[iJ],&aiProfit[iJ]); 
printf("Enter the maximum capacity of knapsack : "); 
scanf("%d",&iMax); 
fnBranch_bound(0,0,0,iMax,aiWeight,aiProfit,iItem); 
getch(); 
} 