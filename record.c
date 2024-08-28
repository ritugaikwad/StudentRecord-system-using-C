#include<stdio.h>
#include<conio.h>

void addStudent();
void studentRecord();
void searchStudent();
void delete();

struct student{
	char first_name[20];
	char last_name[20];
	int roll_no;
	char Class[10];
	char vill[20];
	float per;
};

void main(){
	int choice;
	while(choice!=5){
		printf("\t\t\t-------Student Record-------");
		printf("\n\n\t\t\t 1. Add Student Record\n");
		printf("\n\n\t\t\t 2. Student Records\n");
		printf("\n\n\t\t\t 3. Search Student Record\n");
		printf("\n\n\t\t\t 4. Delete Student Record\n");
		printf("\n\n\n\t\t\t 5. Exit\n");
		printf("\n\n\t\t\t----------------------------");
		printf("\n\n\n\t\t\tEnter your choice[1-5]:  "); 
		scanf("%d",&choice);
		
		switch(choice){
			case 1:
				system("cls");
				addStudent();
				system("cls");
				break;
				
			case 2:
				system("cls");	
				studentRecord();
				printf("\t\t\tPress any key to exit\n");
				getch();
				system("cls");
				break;
			
			case 3:
				system("cls");
				searchStudent();
				printf("\n\t\t\tPress any key to exit\n");
				getch();
				system("cls");
				
			case 4:
				system("cls");
				delete();
				printf("\n\t\t\tPress any key to exit\n");
				getch();
				system("cls");
				break;
		}
	}
}

void addStudent(){
	char another;
	FILE *fp;
	struct student info;
	do{
		system("cls");
		printf("\t\t\t-------Add Student Record-------");
		fp=fopen("studeninfo.txt","a");
		printf("\n\n\t\tEnter student's first name   : ");
		scanf("%s",&info.first_name);
		printf("\n\n\t\tEnter student's last name    : ");
		scanf("%s",&info.last_name);
		printf("\n\n\t\tEnter student's roll no      : ");
		scanf("%d",&info.roll_no);
		printf("\n\n\t\tEnter student's class        : ");
		scanf("%s",&info.Class);
		printf("\n\n\t\tEnter student's address      : ");
		scanf("%s",&info.vill);
		printf("\n\n\t\tEnter student's percentage   : ");
		scanf("%f",&info.per);
		printf("\n\n\t\t\t----------------------------");
		
		if(fp==NULL){
			fprintf(stderr,"\n\n\t\t\tCan't open the file\n");
		}else{
			printf("\n\n\t\t\tRecord stored successfully\n");
		}
		
		fwrite(&info,sizeof(struct student),1,fp);
		fclose(fp);
		
		printf("\n\n\t\t\tDo you want to add another record?(Y/N): ");
		scanf("%s",&another);
	}while(another=='y'||another=='Y');
}

void studentRecord(){
	FILE *fp;
	struct student info;
	fp=fopen("studeninfo.txt","r");
	printf("\t\t\t-------Student Records-------");
	if(fp==NULL){
		fprintf(stderr,"\n\n\t\t\tCan't open the file");
	}else{
		printf("\n\n\t\t\t\t   Records\n");
		printf("\t\t\t-----------------------------\n\n");
	}
	while(fread(&info,sizeof(struct student),1,fp)){
		printf("\n\t\t\t Student name  : %s %s ",info.first_name,info.last_name);
		printf("\n\t\t\t Roll no.      : %d ",info.roll_no);
		printf("\n\t\t\t Class         : %s",info.Class);
		printf("\n\t\t\t Address       : %s",info.vill);
		printf("\n\t\t\t Percentage    : %f",info.per);
		printf("\n\n\t\t\t-----------------------------\n");
	}
	fclose(fp);
	getch();
}

void searchStudent(){
	FILE *fp;
	struct student info;
	int roll_no,found=0;
	fp=fopen("studeninfo.txt","r");
	printf("\t\t\t-------Search Student-------");
	printf("\n\n\t\t\tEnter roll no.: ");
	scanf("%d",&roll_no);
	while(fread(&info,sizeof(struct student),1,fp)){
		if(info.roll_no==roll_no){
			found=1;
			printf("\n\t\t\t Student name  : %s %s ",info.first_name,info.last_name);
			printf("\n\t\t\t Roll no.      : %d ",info.roll_no);
			printf("\n\t\t\t Class         : %s",info.Class);
			printf("\n\t\t\t Address       : %s",info.vill);
			printf("\n\t\t\t Percentage    : %f",info.per);
			printf("\n\n\t\t\t------------------------------\n");
		}
	}
if(!found){
	printf("\n\t\t\tRecord not found");
}
	fclose(fp);
	getch();
}

void delete(){
	FILE *fp,*fp1;
	struct student info;
	int roll_no,found=0;
	
	printf("\t\t\t-------Delete Student Record-------\n\n\n");
	fp=fopen("studeninfo.txt","r");
	fp1=fopen("temp.txt","w");
	printf("\t\t\tEnter roll no.: ");
	scanf("%d",&roll_no);
	if(fp==NULL){
		fprintf(stderr,"\n\n\t\t\tCan't open the file");
	}
	while(fread(&info,sizeof(struct student),1,fp)){
		if(info.roll_no==roll_no){
			found=1;
		}else{
			fwrite(&info,sizeof(struct student),1,fp1);
		}
	}
	fclose(fp);
	fclose(fp1);
	
	if(found){
		remove("studeninfo.txt");
		rename("temp.txt","studeninfo.txt");
		printf("\n\n\t\tRecord deleted successfully!!\n");
	}
	if(!found){
		printf("\n\n\t\tRecord not found.\n");
	}
	getch();

}
