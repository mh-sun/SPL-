#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

char charName[10][1000]={"0\\","1\\","2\\","3\\","4\\","5\\","6\\","7\\","8\\","9\\"};
char charNameDotTxt[10][1000]={"0.txt","1.txt","2.txt","3.txt","4.txt","5.txt","6.txt","7.txt","8.txt","9.txt"};
char fileLocation[]="D:\\SPL\\";
int w=28,h=28;
int **imageArray;

void ImageShifting(int imageArray[h][w]);
int digitDetecting(int imageArray[h][w]);

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

    ImageShifting(arrayH_W);

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            printf("%d ",arrayH_W[i][j]);
        }
        printf("\n");
    }

    int finalDigit=digitDetecting(arrayH_W);

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

    ImageShifting(arrayH_W);

    for(int i=0; i<h; i++)
    {
        for(int j=0; j<w; j++)
        {
            printf("%d ",arrayH_W[i][j]);
        }
        printf("\n");
    }

    int finalDigit=digitDetecting(arrayH_W);

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
                    checkerArray[j][k]=getw(file);
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

            printf("%d     ->   %d\n",i,decisionArray[i]);
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
    //char OutputFileLocation2[100];

    for(int num=0; num<10; num++)
    {
        unsigned char header[54];
        FILE *bmp;

        int h=28,w=28,n=-2;
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

        int arraYY[w*h];
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

        for(int c=0; c<n; c++)
        {
            char trainingImageLocName[100]={0};
            strcpy(trainingImageLocName,TrainingImageFileLocation);
            strcat(trainingImageLocName,trainingImageName[c]);

            bmp=fopen(trainingImageLocName, "rb");
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
                    arraYY[j]=0;
                }
                else {
                    arraYY[j]=1;
                }
            }

            int Temp2dArrayCanBeUsedAgain[h][w];
            int k=0;
            for(int i=0; i<h; i++)
            {
                for(int j=0; j<w; j++)
                {
                    Temp2dArrayCanBeUsedAgain[i][j]=arraYY[k];
                    k++;
                }
            }

            ImageShifting(Temp2dArrayCanBeUsedAgain);

            for(int i=0; i<h; i++)
            {
                for(int j=0; j<w; j++)
                {
                    TrainingimageSumArray[i][j]+=Temp2dArrayCanBeUsedAgain[i][j];
                }
            }

            fclose(bmp);
        }

        int Temp2dArrayCanBeUsedAgain[h][w];

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                Temp2dArrayCanBeUsedAgain[i][j]=TrainingimageSumArray[h-1-i][j];
            }
        }

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                TrainingimageSumArray[i][j]=Temp2dArrayCanBeUsedAgain[i][j];
            }
        }

        printf("\n");
        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                printf("%d",TrainingimageSumArray[i][j]);
                if(TrainingimageSumArray[i][j]<10) printf("  ");
                else printf(" ");
            }
            printf("\n");
        }
        printf("\n");

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
                putw(TrainingimageSumArray[i][j],fileOutput);
            }
        }

        fclose(fileOutput);

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

        //int h=28,w=100;
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
                arraYY[j]=0;
            }
            else
            {
                arraYY[j]=1;
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

        int Temp2dArrayCanBeUsedAgain[h][w];

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                Temp2dArrayCanBeUsedAgain[i][j]=imageArray[h-1-i][j];
            }
        }

        for(int i=0; i<h; i++)
        {
            for(int j=0; j<w; j++)
            {
                imageArray[i][j]=Temp2dArrayCanBeUsedAgain[i][j];
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

        printf("%d %d\n",imageInX,imageInY);

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
                        printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                        splitArrayInXAxis(startIndex,endIndex);
                }
                else if(i==w-1 && flag1==1)
                {
                    endIndex=w-1;
                    printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
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
                    printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                    splitArrayInYAxis(startIndex,endIndex);
                }
                else if(i==h-1 && flag1==1)
                {
                    endIndex=h-1;
                    printf("start index:%d\nEnd Index :%d\n\n",startIndex,endIndex);
                    splitArrayInYAxis(startIndex,endIndex);
                }
            }
        }

    }
    closedir(openEDDir);

}
