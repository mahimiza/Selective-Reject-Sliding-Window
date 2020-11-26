#include <bits/stdc++.h>
#include<conio.h>
using namespace std;

int FrameSize,WindowSize;
char Reminder[500]= {};



char* CRC16(char *frame,char devi[])
{
    int i,j,devilen,framelen;
    char temp[500],quot[100],rem[500],devi1[500],xtra[500];
    char fin[500]= {};

    devilen=strlen(devi);
    framelen=strlen(frame);

    strcpy(devi1,devi);
    strcpy(xtra,frame);
    //cout<<"rk:"<<xtra<<endl;
    for (i=0; i<devilen-1; i++){
        xtra[framelen+i]='0';
    }


    for (i=0; i<devilen; i++){
        temp[i]=xtra[i];
    }


    for (i=0; i<framelen; i++)
    {
        quot[i]=temp[0];
        if(quot[i]=='0')
        {
            for (j=0; j<devilen; j++){
                devi[j]='0';
            }

        }
        else
        {
            for (j=0; j<devilen; j++){
                devi[j]=devi1[j];
            }

        }

        for (j=devilen-1; j>0; j--)
        {
            if(temp[j]==devi[j]){
                rem[j-1]='0';
            }

            else{
                rem[j-1]='1';
            }

        }

        rem[devilen-1]=xtra[i+devilen];
        strcpy(temp,rem);
    }

    strcpy(rem,temp);
    for (i=0; i<devilen-1; i++){
        Reminder[i]=rem[i];
    }


    for (i=0; i<framelen; i++){
        fin[i]=frame[i];
    }

    for (j=0; i<framelen+devilen-1; i++,j++){
        fin[i]=rem[j];
    }

    return fin;
}





bool ErrorFind(char* frame,char P[])
{
    int IsSafe,ranindex;
    char changed_frame[1000];
    strcpy(changed_frame,CRC16(frame,P));

    IsSafe=rand()%2; // if IsSafe is 0 then we will forcefully make an error

    ranindex=rand()%40; // randomely select an index to change if IsSafe is 0
    if(!IsSafe)
    {
        if(changed_frame[ranindex]=='1')
        {
            changed_frame[ranindex]='0';
        }

        else{
            changed_frame[ranindex]='1';
        }

    }
    strcpy(changed_frame,CRC16(changed_frame,P));

    //printf("\n\nReminder:%s\n",Reminder);
    cout<<right<<setw(55);

    cout<<"Reminder :"<<Reminder<<endl;
    for(int i=0; Reminder[i]; i++)
    {
        if(Reminder[i]=='1')
        {
            return true;
        }
    }

    return false;
}





void VisualOutput(int head,int start,int last, int check)
{
    cout<<endl;
    cout<<right<<setw(50)<<' ';
    cout<<left<<' ';
    for(int j=0; j<FrameSize; j++)
    {
        if(head==j&&j<=10){
            cout<<"|";
        }
        if(head==j&&j>10){
            cout<<"|";
        }

        if(j>=start&&j<=last)
        {
            if(j<10&&check==0)
            {
                cout<<"- ";
            }

            else if(j>=10&&check==0){
                cout<<" - ";
            }

            if(j<10&&check==1){
                cout<<"X ";
            }

            else if(j>=10&&check==1){
                cout<<" X ";
            }

        }
        else
        {
            if(j<10&&check==0){
                cout<<"  ";
            }

            else if(j>=10&&check==0){
                cout<<"   ";
            }

            if(j<10&&check==1){
                cout<<"  ";
            }

            else if(j>=10&&check==1)
            {
                cout<<"   ";
            }

        }
    }
    cout<<endl;


    cout<<' ';
    cout<<right<<setw(50)<<' ';
    cout<<left<<' ';
    for(int j=0; j<FrameSize; j++){
        cout<<j<<'.';
    }

    cout<<endl;



    cout<<right<<setw(50)<<' ';
    cout<<left<<' ';
    for(int j=0; j<FrameSize; j++)
    {
        if(head==j&&j<=10){
            cout<<"|";
        }
        if(head==j&&j>10){
            cout<<"|";
        }

        if(j>=start&&j<=last)
        {
            if(j<10&&check==0){
                cout<<"- ";
            }

            else if(j>=10&&check==0){
                cout<<" - ";
            }

            if(j<10&&check==1){
                cout<<"X ";
            }

            else if(j>=10&&check==1){
                cout<<" X ";
            }

        }
        else
        {
            if(j<10&&check==0){
                cout<<"  ";
            }

            else if(j>=10&&check==0){
                cout<<"   ";
            }

            if(j<10&&check==1){
                cout<<"  ";
            }

            else if(j>=10&&check==1){
                cout<<"   ";
            }

        }
    }
    cout<<endl;

}





int main()
{

    srand(time(NULL));
    char Frame[500][500];
    int i,start,last,chk=2;

    printf("Enter the total number of frames to be transmitted: ");
    cin>>FrameSize;

    printf("Enter the window size: ");
    cin>>WindowSize;

    for(i=0; i<FrameSize; i++)
    {
        for(int j=0; j<40; j++)
        {
            Frame[i][j]=((rand()%2)+48);   //Randomly Generate 40 bit for per frame

        }
    }

    i=0;
    for(i=0; i<FrameSize; )
    {

        start=i;
        last=min(i+WindowSize-1,FrameSize-1);




       // printf("\n\n!!!!!!!!!!! Sending Frame[%d] To Frame[%d] !!!!!!!!!!!\n\n",start,last);
        cout<<endl;
        cout<<right<<setw(60);
        cout<<"*Sending Frame["<<start<<"] To Frame["<<last<<"]*"<<endl;
        cout<<right<<setw(90);
        cout<<"[SENDER]--------->--------->-------->-------->------>[RECEIVER]"<<endl;


        VisualOutput(start,start,last,0);
        printf("Press Enter to continue...");
        getch();
        system("cls");



        for(int j=start; j<=last; j++)
        {
            chk=0;
            char P[]="11000000000000101";


            printf("Press Enter to continue...");
            getch();
            system("cls");
            cout<<right<<setw(40);
            cout<<"Frame["<<j<<"] : "<<Frame[j]<<endl;
            //printf("\n\nFrame[%d]: %s\n",j,Frame[j]);
            cout<<endl;
            cout<<right<<setw(55);
            cout<<"Divisor: "<<P<<endl;
            cout<<endl;
            //printf("\n\nDivisor:%s",P);

            if(!ErrorFind(Frame[j],P))
            {
                printf("\n\n!!!!!!!!!!! As all the bit of the remainder is '0' using CRC16 method, The Frame[%d] is Successfully Received !!!!!!!!\n\n\n",j);

                VisualOutput(start,j+1,last,0);
            }





            else
            {

                printf("\n\n!!!!!!!!!!! As all the bit of the remainder is not '0' using CRC16 method, The Frame[%d] is corrupted !!!!!!!!!\n\n",j);
                if(j==last)
                {
                    printf("\n!!!!!!!!!!! Need to Re-Send Frame[%d] !!!!!!!!!!!\n\n",j);
                }
                else
                {
                    printf("\n!!!!!!!!!!! Need to Re-Send Frame[%d] to Frame[%d] !!!!!!!!!!!\n\n",j,last);
                }

                VisualOutput(start,j,last,1);
                //printf("\n\n!!!!!!!!!!! Negative Acknowledgment (NAK-%d) sent for Re-sending !!!!!!!!!!!\n\n\n",j);
                cout<<endl;
                cout<<right<<setw(69);
                cout<<"*Negative Acknowledgment (NAK-"<<j<<") sent*"<<endl;
                cout<<right<<setw(90);
                cout<<"[SENDER]<---------<---------<--------<--------<------[RECEIVER]"<<endl;

                i=j;
                chk=1;

            }
            if(chk==1)
            {
                break;
            }
        }

        if(chk!=1)
        {
            //printf("Acknowledgment (ACK-%d) sent\n\n\n",last+1);
            cout<<endl;
            cout<<right<<setw(65);
            cout<<"*Acknowledgment (ACK-"<<last+1<<") sent*"<<endl;
            cout<<right<<setw(90);
            cout<<"[SENDER]<---------<---------<--------<--------<------[RECEIVER]"<<endl;

            i=last+1;
            chk=0;
        }

    }


cout<<endl<<endl<<endl<<right<<setw(50);
cout<<left<<' ';
    cout<<' ';
    for(int j=0; j<FrameSize; j++)
        cout<<j<<',';
    cout<<endl;
    cout<<"\n\n!!!!!!!!!!! All frames are received Successfully !!!!!!!!!!!\n\n\n\n";

    return 0;


}







