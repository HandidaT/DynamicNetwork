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
//gcc -I/usr/local/tokyocabinet/include dynamicNetwork_toy.c btutil.c -L/usr/local/tokyocabinet/lib -ltokyocabinet -lz -lbz2 -lrt -lpthread -lm -lc

node* insert(int data){
	int lower,upper,lower1,upper1,lower2,upper2,lower3,upper3,start=1,stop=5;
	if(data<15){lower1=16;upper1=30;lower2=16;upper2=30;lower3=16;upper3=30,lower=16,upper=30;
	}else{lower1=1;upper1=5;lower2=6;upper2=10;lower3=11;upper3=15;}
	node *node1 = malloc(sizeof(*node1));
	node1->name=data+1;
   
	node1->visionsubnodehead=malloc(sizeof(node1->visionsubnodehead));
    for(int i=start;i<=stop;i++){
		edge *edge1 = malloc(sizeof(*edge1));
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
	node1->audiosubnodehead=malloc(sizeof(node1->audiosubnodehead));
    for(int i=start;i<=stop;i++){
		edge *edge1 = malloc(sizeof(*edge1));
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
	node1->motionsubnodehead=malloc(sizeof(node1->motionsubnodehead));
    for(int i=start;i<=stop;i++){
		edge *edge1 = malloc(sizeof(*edge1));
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
   node*** map=malloc(sizeof(*map) *2);
   node** ramlist=malloc(sizeof(*ramlist) * upper);
   for(int i=lower;i<upper;i++){ramlist[i]=insert(i);}//Create dummy ramlist of size 30
   
   
   Queue* Q=createQueue(initialcapacity);
   activations *input=malloc(inputlen * sizeof(*input));
   while(count1<2){
		Queue* Qout=createQueue(outputcapacity);
		if(flag1==0){
			for(int i=0;i<inputlen;i++){
				input[i].name=i+1;
				input[i].activation=4;
				//enqueue(Q,i,4);
			}
			activations* temp1=signalprocess(ramlist,Q,Qout,input);
			for(int i=0;i<inputlen;i++){
				input[i].name=temp1[i].name;
				input[i].activation=temp1[i].activation;
			}
			free(Qout->array);
			free(Qout);
			flag1=1;
		}else{
			activations* temp1=signalprocess(ramlist,Q,Qout,input);
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
   
   node* signalnode2;//Here is code to just loop through all nodes. Can be used
   for(int i=lower;i<upper;i++){//for validation check or testing(whether any node link is broken,etc)
      signalnode2=ramlist[i];
      edge* visionsignaledge1=*(signalnode2->visionsubnodehead);
      edge* visionsignaledge2;
      edge* audiosignaledge1=*(signalnode2->audiosubnodehead);
      edge* audiosignaledge2;
      edge* motionsignaledge1=*(signalnode2->motionsubnodehead);
      edge* motionsignaledge2;
      while(visionsignaledge1!=NULL){
  			visionsignaledge2=visionsignaledge1;
  			visionsignaledge1=visionsignaledge1->next;
      }
      while(audiosignaledge1!=NULL){
  			audiosignaledge2=audiosignaledge1;
  			audiosignaledge1->weight;
  			audiosignaledge1=audiosignaledge1->next;
      }
      while(motionsignaledge1!=NULL){
  			motionsignaledge2=motionsignaledge1;
  			motionsignaledge1->weight;//* activation;
  			motionsignaledge1=motionsignaledge1->next;
      }
   }
   
   
   
   
   
   
   
   
   

   node* tempnode2;
   for(int i=lower;i<upper;i++){
      tempnode2=ramlist[i];
      edge* visiontempedge1=*(tempnode2->visionsubnodehead);
      edge* visiontempedge2;
      edge* audiotempedge1=*(tempnode2->audiosubnodehead);
      edge* audiotempedge2;
      edge* motiontempedge1=*(tempnode2->motionsubnodehead);
      edge* motiontempedge2;
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
   node* freenode2;
      for(int i=lower;i<upper;i++){
      freenode2=ramlist[i];
      edge* visionfreeedge1=*(freenode2->visionsubnodehead);
      edge* visionfreeedge2;
      while(visionfreeedge1!=NULL){
  			visionfreeedge2=visionfreeedge1;
  			visionfreeedge1=visionfreeedge1->next;
  			free(visionfreeedge2);
      }
      edge* audiofreeedge1=*(freenode2->audiosubnodehead);
      edge* audiofreeedge2;
      while(audiofreeedge1!=NULL){
  			audiofreeedge2=audiofreeedge1;
  			audiofreeedge1=audiofreeedge1->next;
  			free(audiofreeedge2);
      }
      edge* motionfreeedge1=*(freenode2->motionsubnodehead);
      edge* motionfreeedge2;
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
