#include <stdio.h>
#include <stdlib.h>
#include <tcutil.h>
#include <tchdb.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "bt1.h"

//gcc bt8.c -lm
//gcc -I/usr/local/include bt8.c -L/usr/local/lib -ltokyocabinet -lz -lbz2 -lrt -lpthread -lm -lc

struct node* insert(int data){
	int lower,upper,lower1,upper1,lower2,upper2,lower3,upper3,start=1,stop=5;
	if(data<15){lower1=16;upper1=30;lower2=16;upper2=30;lower3=16;upper3=30,lower=16,upper=30;
	}else{lower1=1;upper1=5;lower2=6;upper2=10;lower3=11;upper3=15;}
	struct node *node1 = (struct node*) malloc(sizeof(struct node));
	node1->name=data+1;
   
	node1->visionsubnodehead=(struct edge**) malloc(sizeof(struct edge));
    for(int i=start;i<=stop;i++){
		struct edge *edge1 = (struct edge*) malloc(sizeof(struct edge));
		edge1->name=(rand()%((upper1-lower1+1)) + lower1);
		edge1->weight=1;
		//printf("1 %d %d\n",data,i);
		if(i==start){
			edge1->next=NULL;
			*(node1->visionsubnodehead)=edge1;
			node1->visionsubnodetail=edge1;
			continue;
		}
		edge1->next=NULL;
		node1->visionsubnodetail->next=edge1;
		node1->visionsubnodetail=edge1;
    }
	node1->audiosubnodehead=(struct edge**) malloc(sizeof(struct edge));
    for(int i=start;i<=stop;i++){
		struct edge *edge1 = (struct edge*) malloc(sizeof(struct edge));
		edge1->name=(rand()%((upper2-lower2+1)) + lower2);
		edge1->weight=1;
		//printf("2 %d %d\n",data,i);
		if(i==start){
			edge1->next=NULL;
			*(node1->audiosubnodehead)=edge1;
			node1->audiosubnodetail=edge1;
			continue;
		}
		edge1->next=NULL;
		node1->audiosubnodetail->next=edge1;
		node1->audiosubnodetail=edge1;
    }
	node1->motionsubnodehead=(struct edge**) malloc(sizeof(struct edge));
    for(int i=start;i<=stop;i++){
		struct edge *edge1 = (struct edge*) malloc(sizeof(struct edge));
		edge1->name=(rand()%((upper3-lower3+1)) + lower3);
		edge1->weight=1;
		//printf("3%d %d\n",data,i);
		if(i==start){
			edge1->next=NULL;
			*(node1->motionsubnodehead)=edge1;
			node1->motionsubnodetail=edge1;
			continue;
		}
		edge1->next=NULL;
		node1->motionsubnodetail->next=edge1;
		node1->motionsubnodetail=edge1;
    }
    return node1;
}

int main(){/*
	TCHDB *hdb;
	int ecode;
	char *key, *value;
  /* create the object 
  hdb = tchdbnew();*/
  
  /* open the database
  if(!tchdbopen(hdb, "casket.tch", HDBOWRITER | HDBOCREAT)){
    ecode = tchdbecode(hdb);
    fprintf(stderr, "open error: %s\n", tchdberrmsg(ecode));
  }*/
   int lower=0,upper=30,initialcapacity=50,inputlen=15,count1=0,flag1=0;
   int outputcapacity=inputlen;
   struct node*** map=malloc(sizeof(*map) *2);
   struct node** ramlist=malloc(sizeof(*ramlist) * upper);
   for(int i=lower;i<upper;i++){ramlist[i]=insert(i);}//Create dummy ramlist of size 30
   
   
   struct Queue* Q=createQueue(initialcapacity);
   struct activations* input=(struct activations*)malloc(inputlen * sizeof(struct activations));
   while(count1<2){
		struct Queue* Qout=createQueue(outputcapacity);
		if(flag1==0){
			for(int i=0;i<inputlen;i++){
				input[i].name=i+1;
				input[i].activation=4;
				//enqueue(Q,i,4);
			}
			struct activations* temp1=signalprocess(ramlist,Q,Qout,input);
			for(int i=0;i<inputlen;i++){
				input[i].name=temp1[i].name;
				input[i].activation=temp1[i].activation;
			}
			free(Qout->array);
			free(Qout);
			flag1=1;
		}else{
			struct activations* temp1=signalprocess(ramlist,Q,Qout,input);
			for(int i=0;i<inputlen;i++){
				input[i].name=temp1[i].name;
				input[i].activation=temp1[i].activation;
			}
			free(Qout->array);
			free(Qout);
			flag1=0;
		}
		count1++;
	}
   
   struct node* signalnode2;
   for(int i=lower;i<upper;i++){
      signalnode2=ramlist[i];
      struct edge* visionsignaledge1=*(signalnode2->visionsubnodehead);
      struct edge* visionsignaledge2;
      while(visionsignaledge1!=NULL){
  			visionsignaledge2=visionsignaledge1;
  			visionsignaledge1=visionsignaledge1->next;
      }
      struct edge* audiosignaledge1=*(signalnode2->audiosubnodehead);
      struct edge* audiosignaledge2;
      while(audiosignaledge1!=NULL){
  			audiosignaledge2=audiosignaledge1;
  			audiosignaledge1->weight;
  			audiosignaledge1=audiosignaledge1->next;
      }
      struct edge* motionsignaledge1=*(signalnode2->motionsubnodehead);
      struct edge* motionsignaledge2;
      while(motionsignaledge1!=NULL){
  			motionsignaledge2=motionsignaledge1;
  			motionsignaledge1->weight;//* activation;
  			motionsignaledge1=motionsignaledge1->next;
      }
   }
   
   
   
   
   
   
   
   
   

   struct node* tempnode2;
   for(int i=lower;i<upper;i++){
      tempnode2=ramlist[i];
      struct edge* visiontempedge1=*(tempnode2->visionsubnodehead);
      struct edge* visiontempedge2;
      struct edge* audiotempedge1=*(tempnode2->audiosubnodehead);
      struct edge* audiotempedge2;
      struct edge* motiontempedge1=*(tempnode2->motionsubnodehead);
      struct edge* motiontempedge2;
      char **str=malloc(sizeof *str);
      (*str)=malloc(sizeof *(*str));
      int flag=0;
      while(visiontempedge1!=NULL){
  			visiontempedge2=visiontempedge1;
      		if(flag==0){
  				char curstr[(int)((ceil(log10(visiontempedge2->name))+1)*sizeof(char))];
  				sprintf(curstr, "%d", visiontempedge2->name);
  				//printf("_%d %d %s\n",tempnode2->name,visiontempedge2->name,curstr);
  				*str=concatenate(*str,curstr,flag);
  				flag=1;
  				char curstr1[(int)((ceil(log10(visiontempedge2->weight))+1)*sizeof(char))];
  				sprintf(curstr1, "%d", visiontempedge2->weight);
  				*str=concatenate(*str,curstr1,flag);
  				visiontempedge1=visiontempedge1->next;
      			continue;}
  			char curstr[(int)((ceil(log10(visiontempedge2->name))+1)*sizeof(char))];
  			sprintf(curstr, "%d", visiontempedge2->name);
  			//printf(" %d %d %s\n",tempnode2->name,visiontempedge2->name,curstr);
  			*str=concatenate(*str,curstr,flag);
  			char curstr1[(int)((ceil(log10(visiontempedge2->weight))+1)*sizeof(char))];
  			sprintf(curstr1, "%d", visiontempedge2->weight);
  			//printf(" %d %d %s\n",tempnode2->name,tempedge2->name,curstr);
  			*str=concatenate(*str,curstr1,flag);
  			visiontempedge1=visiontempedge1->next;
      }
      while(audiotempedge1!=NULL){
  			audiotempedge2=audiotempedge1;
      		if(flag==0){
  				char curstr[(int)((ceil(log10(audiotempedge2->name))+1)*sizeof(char))];
  				sprintf(curstr, "%d", audiotempedge2->name);
  				//printf("_%d %d %s\n",tempnode2->name,audiotempedge2->name,curstr);
  				*str=concatenate(*str,curstr,flag);
  				flag=1;
  				char curstr1[(int)((ceil(log10(audiotempedge2->weight))+1)*sizeof(char))];
  				sprintf(curstr1, "%d", audiotempedge2->weight);
  				*str=concatenate(*str,curstr1,flag);
  				audiotempedge1=audiotempedge1->next;
      			continue;}
  			char curstr[(int)((ceil(log10(audiotempedge2->name))+1)*sizeof(char))];
  			sprintf(curstr, "%d", audiotempedge2->name);
  			//printf(" %d %d %s\n",tempnode2->name,audiotempedge2->name,curstr);
  			*str=concatenate(*str,curstr,flag);
  			char curstr1[(int)((ceil(log10(audiotempedge2->weight))+1)*sizeof(char))];
  			sprintf(curstr1, "%d", audiotempedge2->weight);
  			//printf(" %d %d %s\n",tempnode2->name,tempedge2->name,curstr);
  			*str=concatenate(*str,curstr1,flag);
  			audiotempedge1=audiotempedge1->next;
      }
      while(motiontempedge1!=NULL){
  			motiontempedge2=motiontempedge1;
      		if(flag==0){
  				char curstr[(int)((ceil(log10(motiontempedge2->name))+1)*sizeof(char))];
  				sprintf(curstr, "%d", motiontempedge2->name);
  				//printf("_%d %d %s\n",tempnode2->name,motiontempedge2->name,curstr);
  				*str=concatenate(*str,curstr,flag);
  				flag=1;
  				char curstr1[(int)((ceil(log10(motiontempedge2->weight))+1)*sizeof(char))];
  				sprintf(curstr1, "%d", motiontempedge2->weight);
  				*str=concatenate(*str,curstr1,flag);
  				motiontempedge1=motiontempedge1->next;
      			continue;}
  			char curstr[(int)((ceil(log10(motiontempedge2->name))+1)*sizeof(char))];
  			sprintf(curstr, "%d", motiontempedge2->name);
  			//printf(" %d %d %s\n",tempnode2->name,motiontempedge2->name,curstr);
  			*str=concatenate(*str,curstr,flag);
  			char curstr1[(int)((ceil(log10(motiontempedge2->weight))+1)*sizeof(char))];
  			sprintf(curstr1, "%d", motiontempedge2->weight);
  			//printf(" %d %d %s\n",tempnode2->name,tempedge2->name,curstr);
  			*str=concatenate(*str,curstr1,flag);
  			motiontempedge1=motiontempedge1->next;
      }
      printf("\nVision key=%d, Value=%s",tempnode2->name,*str);/*
  	  char curstr[(int)((ceil(log10(tempnode2->name))+1)*sizeof(char))];
  	  sprintf(curstr, "%d", tempnode2->name);
      store records
      if(!tchdbput2(hdb, curstr, *str)){
         ecode = tchdbecode(hdb);
         fprintf(stderr, "put error: %s\n", tchdberrmsg(ecode));
      }*/
      free(*str);
      free(str);
   }
  /* close the database 
  if(!tchdbclose(hdb)){
    ecode = tchdbecode(hdb);
    fprintf(stderr, "close error: %s\n", tchdberrmsg(ecode));
  }*/

  /* delete the object 
  tchdbdel(hdb);*/

   //free data
   struct node* freenode2;
      for(int i=lower;i<upper;i++){
      freenode2=ramlist[i];
      struct edge* visionfreeedge1=*(freenode2->visionsubnodehead);
      struct edge* visionfreeedge2;
      while(visionfreeedge1!=NULL){
  			visionfreeedge2=visionfreeedge1;
  			visionfreeedge1=visionfreeedge1->next;
  			free(visionfreeedge2);
      }
      struct edge* audiofreeedge1=*(freenode2->audiosubnodehead);
      struct edge* audiofreeedge2;
      while(audiofreeedge1!=NULL){
  			audiofreeedge2=audiofreeedge1;
  			audiofreeedge1=audiofreeedge1->next;
  			free(audiofreeedge2);
      }
      struct edge* motionfreeedge1=*(freenode2->motionsubnodehead);
      struct edge* motionfreeedge2;
      while(motionfreeedge1!=NULL){
  			motionfreeedge2=motionfreeedge1;
  			motionfreeedge1=motionfreeedge1->next;
  			free(motionfreeedge2);
      }
      free(freenode2->visionsubnodehead);
      free(freenode2->audiosubnodehead);
      free(freenode2->motionsubnodehead);
      free(freenode2);
   }
   free(input);
   free(Q->array);
   free(Q);
   free(map);
   free(ramlist);
}
