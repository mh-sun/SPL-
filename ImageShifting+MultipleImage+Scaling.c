#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char charName[10][1000]={"0\\","1\\","2\\","3\\","4\\","5\\","6\\","7\\","8\\","9\\"};
char charNameDotTxt[10][1000]={"0.txt","1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt","9.txt"};
char fileLocation[]="D:\\SPL\\";
int w=28,h=28; //w=width,h=height of an image
int black=0,white=1;
int **imageArray;
int numOfImage=500;

void printArr(int arrayH_W[h][w]);
void ImageShifting(int imageArray[h][w]);
void ImageScaling(int arrayH_W[h][w],int setGrp);
int digitDetecting(int imageArray[h][w]);
void fillingForScaling(int tempArray[h][w],int xIndex,double XRatio,int Yindex,double YRatio,int ,int);
void splitArrayInXAxis(int startIndex,int endIndex);
void splitArrayInYAxis(int startIndex,int endIndex);

void printArr(int arrayH_W[h][w])
{
    printf("\n");
    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            printf("%d ",arrayH_W[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void ImageScaling(int arrayH_W[h][w],int setGrp)
{
    int StartingIndexInX=0,endingIndexInX=0;

    int breakFlag=0;
    for(int i=0;i<w;i++)
    {
        for(int j=0;j<h;j++)
        {
            if(arrayH_W[j][i]==1)
            {
                StartingIndexInX=i;
                breakFlag=1;
                break;
            }
        }
        if(breakFlag==1) break;
    }

    breakFlag=0;
    for(int i=w-1;i>=0;i--)
    {
        for(int j=0;j<h;j++)
        {
            if(arrayH_W[j][i]==1)
            {
                endingIndexInX=i;
                breakFlag=1;
                break;
            }
        }
        if(breakFlag==1) break;
    }

    int StartingIndexInY=0,endingIndexInY=0;

    breakFlag=0;
    for(int i=0;i<h;i++)
    {
        for(int j=0;j<w;j++)
        {
            if(arrayH_W[i][j]==1)
            {
                StartingIndexInY=i;
                breakFlag=1;
                break;
            }
        }
        if(breakFlag==1) break;
    }

    breakFlag=0;
    for(int i=h-1;i>=0;i--)
    {
        for(int j=0;j<w;j++)
        {
            if(arrayH_W[i][j]==1)
            {
                endingIndexInY=i;
                breakFlag=1;
                break;
            }
        }
        if(breakFlag==1) break;
    }

    //printf("X axis : (%d,%d)\nY axis : (%d,%d)\n",StartingIndexInX,endingIndexInX,StartingIndexInY,endingIndexInY);

    double differenceX=(endingIndexInX-StartingIndexInX+1.0);
    double differenceY=(endingIndexInY-StartingIndexInY+1.0);

    double ratioY=28.0/differenceY;
    double ratioX=28.0/differenceX;

    int tempArray[28][28]={0};

    if(differenceX>=differenceY)
    {
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                if(arrayH_W[i][j]==1)
                {
                    fillingForScaling(tempArray,j,ratioX,i,ratioY,StartingIndexInX,StartingIndexInY);                }
            }
        }
    }
    else{
        for(int i=0;i<h;i++)
        {
            for(int j=0;j<w;j++)
            {
                if(arrayH_W[i][j]==1)
                {
                    fillingForScaling(tempArray,j,ratioY,i,ratioY,StartingIndexInX,StartingIndexInY);                }
            }
        }
    }

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            arrayH_W[i][j]=tempArray[i][j];
        }
    }

    //printf("Xratio %llf\nYratio %llf\n",XRatio,YRatio);


}

void fillingForScaling(int tempArray[h][w],int xIndex,double XRatio,int Yindex,double YRatio,int startX,int startY)
{
    int start_x,end_x,start_y,end_y;
    int shiftX=round(startX*XRatio*1.0);
    int shiftY=round(startY*YRatio*1.0);

    start_x=round(xIndex*XRatio*1.0)-shiftX;
    end_x=round(xIndex*XRatio*1.0+XRatio)-shiftX;

    start_y=round(Yindex*YRatio*1.0)-shiftY;
    end_y=round(Yindex*YRatio*1.0+YRatio)-shiftY;


    double midX=(end_x+start_x)/2.0;
    double midY=(end_y+start_y)/2.0;

//    start_x=start_x-(midX-xIndex);
//    end_x=end_x-(midX-xIndex);
//
//    start_y-=((midY-Yindex));
//    end_y-=((midY-Yindex));


    for(int i=start_y;i<=end_y && i<28;i++)
    {
        for(int j=start_x;j<=end_x && j<28;j++)
        {
            tempArray[i][j]=1;
        }
    }
//
//    printArr(tempArray);

//    printf("%d,%d --- %llf,%llf ---\n",xIndex,Yindex,XRatio,YRatio);
//    getchar();

}

void splitArrayInXAxis(int startIndex,int endIndex)
{

    int array28_size[28][endIndex-startIndex+1];

    for(int i=startIndex;i<=endIndex;i++)
    {
        for(int j=0;j<28;j++)
        {
            array28_size[j][i-startIndex]=imageArray[j][i];
        }
    }

    int arrayH_W[28][28];

    for(int i=0;i<28;i++)
    {
        for(int j=0;j<28;j++)
        {
            arrayH_W[i][j]=0;
        }
    }

    for(int i=0;i<=(endIndex-startIndex);i++)
    {
        for(int j=0;j<28;j++)
        {
            arrayH_W[j][i]=array28_size[j][i];
        }
    }

    int finalDigit;

//    printArr(arrayH_W);
//    finalDigit=digitDetecting(arrayH_W);
//    printf("\n\nthe number is %d\n..........................\n",finalDigit);

    ImageScaling(arrayH_W,0);

//    printArr(arrayH_W);
//    finalDigit=digitDetecting(arrayH_W);
//    printf("\n\nthe number is %d\n..........................\n",finalDigit);

    ImageShifting(arrayH_W);

    printArr(arrayH_W);
    finalDigit=digitDetecting(arrayH_W);
    printf("\n\nthe number is %d\n..........................\n",finalDigit);

}

void splitArrayInYAxis(int startIndex,int endIndex)
{

    int arraysize_28[endIndex-startIndex+1][28];

    for(int i=startIndex;i<=endIndex;i++)
    {
        for(int j=0;j<28;j++)
        {
            arraysize_28[i-startIndex][j]=imageArray[i][j];
        }
    }

    int arrayH_W[28][28];

    for(int i=0;i<28;i++)
    {
        for(int j=0;j<28;j++)
        {
            arrayH_W[i][j]=0;
        }
    }

    for(int i=0;i<=(endIndex-startIndex);i++)
    {
        for(int j=0;j<28;j++)
        {
            arrayH_W[i][j]=arraysize_28[i][j];
        }
    }

    int finalDigit;

//    printArr(arrayH_W);
//    finalDigit=digitDetecting(arrayH_W);
//    printf("\n\nthe number is %d\n..........................\n",finalDigit);

    ImageScaling(arrayH_W,0);

//    printArr(arrayH_W);
//    finalDigit=digitDetecting(arrayH_W);
//    printf("\n\nthe number is %d\n..........................\n",finalDigit);

    ImageShifting(arrayH_W);

    printArr(arrayH_W);
    finalDigit=digitDetecting(arrayH_W);
    printf("\n\nthe number is %d\n..........................\n",finalDigit);

}

int digitDetecting(int imageArray[h][w])
{
        int decisionArray[10]={0};

        for(int i=0;i<10;i++)
        {
            char checkerFile[100];
            strcpy(checkerFile,fileLocation);
            strcat(checkerFile,"outputImage\\");
            strcat(checkerFile,charNameDotTxt[i]);

            //printf("checkerFile:%s\n",checkerFile);

            FILE* file=fopen(checkerFile,"r");

            int checkerArray[h][w];

            for(int j=0; j<h; j++)
            {
                for(int k=0; k<w; k++)
                {
                    //checkerArray[j][k]=getw(file);
                    fscanf(file,"%d",&checkerArray[j][k]);
                }
            }

            for(int j=0; j<h; j++)
            {
                for(int k=0; k<w; k++)
                {
                    if(imageArray[j][k]==1)
                    {
                        decisionArray[i]=decisionArray[i]+checkerArray[j][k];
                    }
                }
            }

        }
        printf("\nimage -> decisionArrayValue\n");
        int max=decisionArray[0];
        for(int i=0;i<10;i++)
        {
            if(decisionArray[i]>max) max=decisionArray[i];

            printf("%d     ->   %d %%\n",i,(decisionArray[i]*100)/(numOfImage*14*28));
        }

        for(int i=0;i<10;i++)
        {
            if(decisionArray[i]==max)
            {
                return i;
            }
        }
}

void ImageShifting(int imageArray[h][w])
{
    int w=28,h=28;
    int xLeft,xRight,yTop,yDown;
        for(int i=0;i<w;i++)
        {
            int tempHere=0;
            for(int j=0;j<h;j++)
            {
                if(imageArray[j][i]>=1)
                {
                    xLeft=i;
                    tempHere=1;
                    break;
                }
            }
            if(tempHere==1) break;
        }

        for(int i=w-1;i>=0;i--)
        {
            int tempHere=0;
            for(int j=0;j<h;j++)
            {
                if(imageArray[j][i]>=1)
                {
                    xRight=i;
                    tempHere=1;
                    break;
                }
            }
            if(tempHere==1) break;
        }

        for(int i=0;i<h;i++)
        {
            int tempHere=0;
            for(int j=0;j<w;j++)
            {
                if(imageArray[i][j]>=1)
                {
                    yTop=i;
                    tempHere=1;
                    break;
                }
            }
            if(tempHere==1) break;
        }

        for(int i=h-1;i>=0;i--)
        {
            int tempHere=0;
            for(int j=0;j<w;j++)
            {
                if(imageArray[i][j]>=1)
                {
                    yDown=i;
                    tempHere=1;
                    break;
                }
            }
            if(tempHere==1) break;
        }

        //printf("%d %d %d %d\n",xLeft,xRight,yTop,yDown);

        int middleOfX=xLeft+(xRight-xLeft)/2;
        int middleOfY=yTop+(yDown-yTop)/2;

        //printf("Middle of x:%d\tmiddle of Y:%d\nPlace to %d\tPlace to %d\n",middleOfX,middleOfY,w/2,h/2);

        if(middleOfX>w/2-1)
        {
            int Xshift=middleOfX-w/2+1;
            for(int i=0;i<h;i++)
            {
                for(int j=xLeft;j<=xRight;j++)
                {
                    imageArray[i][j-Xshift]=imageArray[i][j];
                    imageArray[i][j]=0;
                    //printf("(%d,%d),(%d,%d)\n",i,j,i,j-Xshift);
                }
            }
        }
        else if(middleOfX<w/2-1){
            int Xshift=w/2-1-middleOfX;
            for(int i=0;i<h;i++)
            {
                for(int j=xRight;j>=xLeft;j--)
                {
                    imageArray[i][j+Xshift]=imageArray[i][j];
                    imageArray[i][j]=0;
                    //printf("(%d,%d),(%d,%d)\n",i,j,i,j+Xshift);
                }
            }
        }


        if(middleOfY>h/2-1)
        {
            int yshift=middleOfY-h/2+1;
            for(int i=yTop;i<=yDown;i++)
            {
                for(int j=0;j<w;j++)
                {
                    imageArray[i-yshift][j]=imageArray[i][j];
                    imageArray[i][j]=0;
                    //printf("(%d,%d),(%d,%d)\n",i,j,i-yshift,j);
                }
            }
        }
        else if(middleOfY<h/2-1){
            int yshift=h/2-1-middleOfY;
            for(int i=yDown;i>=yTop;i--)
            {
                for(int j=0;j<w;j++)
                {
                    imageArray[i+yshift][j]=imageArray[i][j];
                    imageArray[i][j]=0;
                    //printf("(%d,%d),(%d,%d)\n",i,j,i+yshift,j);
                }
            }
        }

}

int main ()
{
    for(int num=0; num<10; num++)//num = number of digit
    {
        unsigned char header[54];
        FILE *bmp;

        int h=28,w=28,n=-2; //n=number of file in a directory
        char TrainingImageFileLocation[1000];
        strcpy(TrainingImageFileLocation,fileLocation);
        strcat(TrainingImageFileLocation,"trainingImage\\");
        strcat(TrainingImageFileLocation,charName[num]);

        printf("training image file location ::%s::\n",TrainingImageFileLocation);

        struct dirent *dirToRead;
        DIR *openEDDir=opendir(TrainingImageFileLocation);

        if(openEDDir==NULL)
        {
            printf("Directory not opened -> Part 1\n");
            return 0;
        }

        while((dirToRead=readdir(openEDDir))!=NULL)
        {
            n++;
        }

        closedir(openEDDir);

        openEDDir=opendir(TrainingImageFileLocation);

        char trainingImageName[n][100];
        for(int i=0; (dirToRead=readdir(openEDDir))!=NULL; i++)
        {
            if(i<2) continue; //first two file are "." and ".."
            strcpy(trainingImageName[i-2],dirToRead->d_name);
        }

        closedir(openEDDir);

        int arraYY[w*h]; //temporary array to read pixels in linear way
        for(int i=0; i<w*h; i++)
        {
            arraYY[i]=0;
        }

        int TrainingimageSumArray[h][w];
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                TrainingimageSumArray[i][j]=0;
            }
        }

        for(int c=0; c<n; c++) //c=counter
        {
            int imageArr[h][w];
            char trainingImageLocName[100]={0};
            strcpy(trainingImageLocName,TrainingImageFileLocation);
            strcat(trainingImageLocName,trainingImageName[c]);

            bmp=fopen(trainingImageLocName, "rb"); //bmp = BMP file opener
            if (!bmp) {
                printf("Error Part ->1\n");
                return 0;
            }

            fseek(bmp,0,SEEK_END);
            int len=ftell(bmp);
            fseek(bmp,0,SEEK_SET);

            fread(header,sizeof(char), 54,bmp);
            unsigned char temp[w*h*3];
            unsigned char temp1[len-w*h*3-54];

            fread(temp,sizeof(char), w*h*3,bmp);
            fread(temp1,sizeof(char), len-w*h*3-54,bmp);

            for(int i=0,j=0; i<w*h*3; i=i+3,j++)
            {
                if(temp[i]>=100 && temp[i]<=300 && temp[i+1]>=100 && temp[i+1]<=300&& temp[i+2]>=100 && temp[i+2]<=300) {
                    arraYY[j]=white;
                }
                else {
                    arraYY[j]=black;
                }
            }


            int k=0;
            for(int i=0; i<h; i++)
            {
                for(int j=0; j<w; j++)
                {
                    imageArr[i][j]=arraYY[k];
                    k++;
                }
            }

            if(num==1)
                ImageScaling(imageArr,3);
            else if(num==2||num==3||num==4)
                ImageScaling(imageArr,2);
            else
                ImageScaling(imageArr,1);
            ImageShifting(imageArr);

            for(int i=0; i<h; i++)
            {
                for(int j=0; j<w; j++)
                {

                    TrainingimageSumArray[i][j]+=imageArr[i][j];
                }
            }

            fclose(bmp);
        }

        int imageArr[h][w];

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                imageArr[i][j]=TrainingimageSumArray[h-1-i][j];
            }
        }

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                TrainingimageSumArray[i][j]=imageArr[i][j];
            }
        }

        char outputFileLocation[100]= {0};
        strcpy(outputFileLocation,fileLocation);
        strcat(outputFileLocation,"outputImage\\");

        //printf("\n\noutput file location : %s\n",outputFileLocation);
        //strcpy(OutputFileLocation2,outputFileLocation);

        char outputfileLocName[100]={0};
        //printf("char name : %s\n",charName[num]);
        strcpy(outputfileLocName,outputFileLocation);

        //printf("output name 1: %s\n",outputName);

        strcat(outputfileLocName,charNameDotTxt[num]);
        //printf("output name 2: %s\n",outputName);

        FILE *fileOutput=fopen(outputfileLocName,"w");
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                //putw(TrainingimageSumArray[i][j],fileOutput);

                fprintf(fileOutput," %d ",TrainingimageSumArray[i][j]);

//                printf("%d",TrainingimageSumArray[i][j]);
//                if(TrainingimageSumArray[i][j]<10) printf("   ");
//                else if(TrainingimageSumArray[i][j]<100) printf("  ");
//                else printf(" ");
            }
//            printf("\n");
            fprintf(fileOutput,"\n");
        }
        printf("\n");

        fclose(fileOutput);

        //getchar();

    }

    char inputFileLocation[100];
    strcpy(inputFileLocation,fileLocation);
    strcat(inputFileLocation,"inputImage\\");

    //printf("inputFileLocation : %s \n",inputFileLocation);

    struct dirent *dirToRead;
    DIR *openEDDir=opendir(inputFileLocation);

    if(openEDDir==NULL)
    {
        printf("Directory not opened Part 2\n");
        return 0;
    }

    int i=0;
    while((dirToRead=readdir(openEDDir))!=NULL)
    {
        i++;
        if(i<=2) continue;

        char inputImageName[100];
        char inputFileLocName[100];

        strcpy(inputImageName,dirToRead->d_name);
        strcpy(inputFileLocName,inputFileLocation);

        strcat(inputFileLocName,inputImageName);
        printf("input file : %s\n",inputFileLocName);

        FILE* inputimage=fopen(inputFileLocName,"rb");

        if (!inputimage) {
            printf("Error\n");
            return 0;
        }

        fseek(inputimage,0,SEEK_END);
        int len=ftell(inputimage);
        fseek(inputimage,0,SEEK_SET);

        char header[54];

        fread(header,sizeof(char), 54,inputimage);

        int w = *(int *)&header[18];
        int h = *(int *)&header[22];

        printf("W:[%d]\tH:[%d]\n",w,h);

        unsigned char temp[w*h*3];
        unsigned char temp1[len-w*h*3-54];

        fread(temp,sizeof(char), w*h*3,inputimage);
        fread(temp1,sizeof(char), len-w*h*3-54,inputimage);

        int arraYY[w*h];
        for(int i=0,j=0; i<w*h*3; i=i+3,j++)
        {
            if(temp[i]>=100 && temp[i]<=300 && temp[i+1]>=100 && temp[i+1]<=300&& temp[i+2]>=100 && temp[i+2]<=300)
            {
                arraYY[j]=white;
            }
            else
            {
                arraYY[j]=black;
            }
        }

        imageArray=malloc(h*sizeof(int));

        for(int i=0;i<h;i++)
            imageArray[i]=malloc(w*sizeof(int));

        int k=0;
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                imageArray[i][j]=arraYY[k];
                k++;
            }
        }

        int imageArr[h][w];

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                imageArr[i][j]=imageArray[h-1-i][j];
            }
        }

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                imageArray[i][j]=imageArr[i][j];
            }
        }

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                printf("%d ",imageArray[i][j]);
            }
            printf("\n");
        }

        int imageInX=0,imageInY=0;

        int flag1=1;
        for(int i=0;i<w;i++)
        {
            int flag2=1;
            for(int j=0;j<h;j++)
            {
                if(flag1==1 && imageArray[j][i]==1)
                {
                    flag1=0;
                    imageInX++;
                }
                if(imageArray[j][i]==1) flag2=0;

            }
            if(flag1==0 && flag2==1) flag1=1;
        }

        for(int i=0;i<h;i++)
        {
            int flag2=1;
            for(int j=0;j<w;j++)
            {
                if(flag1 && imageArray[i][j]==1)
                {
                    flag1=0;
                    imageInY++;
                }
                if(imageArray[i][j]==1) flag2=0;

            }
            if(!flag1 && flag2) flag1=1;
        }

        if(imageInX>=1 && imageInY==1)
        {
            int startIndex=0,endIndex=0;

            int flag1=0;
            for(int i=0;i<w;i++)
            {
                int flag2=0;
                for(int j=0;j<h;j++)
                {
                    if(imageArray[j][i]==1) flag2=1;
                    if(flag1==0 && imageArray[j][i]==1)
                    {
                        flag1=1;
                        startIndex=i;
                    }
                }

                if(flag1==1 && flag2==0)
                {
                        flag1=0;
                        endIndex=i-1;
                        //printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                        splitArrayInXAxis(startIndex,endIndex);
                }
                else if(i==w-1 && flag1==1)
                {
                    endIndex=w-1;
                    //printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                    splitArrayInXAxis(startIndex,endIndex);
                }
            }
        }

        else if(imageInX==1 && imageInY>1)
        {
            int startIndex=0,endIndex=0;

            int flag1=0;
            for(int i=0;i<h;i++)
            {
                int flag2=0;
                for(int j=0;j<w;j++)
                {
                    if(imageArray[i][j]==1) flag2=1;
                    if(flag1==0 && imageArray[i][j]==1)
                    {
                        flag1=1;
                        startIndex=i;
                    }
                }

                if(flag1==1 && flag2==0)
                {
                    flag1=0;
                    endIndex=i-1;
                    //printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                    splitArrayInYAxis(startIndex,endIndex);
                }
                else if(i==h-1 && flag1==1)
                {
                    endIndex=h-1;
                    //printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                    splitArrayInYAxis(startIndex,endIndex);
                }
            }
        }

    }
    closedir(openEDDir);

}
