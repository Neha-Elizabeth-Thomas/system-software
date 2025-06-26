#include<stdio.h>
#include<stdlib.h>
#include<string.h>

FILE *f1,*f2,*f3,*f4,*f5,*f6;


void getconstant(char str1[],char str2[]){
    char str[10];
    str1[0]='\0';
    for(int i=2 ; i<strlen(str2)-1 ;i++){
        int n=str2[i];
        sprintf(str,"%X",n);
        strcat(str1,str);
    }
}

void pass2(){
    char address[10],label[10],opcode[10],operand[20],length[10],text_record[70];
    char mach_inst[10],hex_str[10];
    int int_operand,start;
    int t_size=30,t_len=0,prev_start_addr;
    fscanf(f6,"%s",length);
    fscanf(f1,"%s\t%s\t%s",label,opcode,operand);
    if(strcasecmp(opcode,"START")==0){
        sscanf(operand,"%X",&start);
        fprintf(f3,"\t\t%s\t%s\t%s\n",label,opcode,operand);
        fprintf(f4,"H%-6s00%s0000%s\n",label,operand,length);
        fscanf(f1,"%s\t%s\t%s\t%s",address,label,opcode,operand);
    }

    sprintf(text_record,"T%06X00",start);
    prev_start_addr=start;
    while(strcasecmp(opcode,"end")!=0){
        if(strcasecmp(opcode,"resw")==0){
            mach_inst[0]='\0';
            int_operand=atoi(operand);
            t_size-=3*int_operand;
        }else if(strcasecmp(opcode,"resb")==0){
                    mach_inst[0]='\0';
                    int_operand=atoi(operand);
                    t_size-=int_operand;
            }else if(strcasecmp(opcode,"word")==0){
                    int_operand=atoi(operand);
                    sprintf(mach_inst,"%06X",int_operand);
                    t_size-=3;
                }else if(strcasecmp(opcode,"byte")==0){
                        char str[20];
                        if(operand[0]=='C'){
                            getconstant(mach_inst,operand);
                            t_size-=strlen(operand)-3;
                        }else if(operand[0]=='X'){
                                sprintf(mach_inst,"%s",&operand[2]);
                                mach_inst[strlen(mach_inst)-1]='\0';
                                t_size-=(strlen(operand)-3)/2;
                            }
                    }else{
                        char mnemonic[20],code[20];
                        int opfound=0;
                        fseek(f2,0,0);
                        while(fscanf(f2,"%s\t%s",mnemonic,code)!=EOF){
                            if(strcasecmp(opcode,mnemonic)==0){ 
                                sprintf(mach_inst,"%2s",code);
                                opfound=1;
                                break;
                            }
                        }
                        if(opfound){
                            char symb[10],addr[10];
                           int labfound=0;
                            fseek(f5,0,0);
                            while(fscanf(f5,"%s\t%s",symb,addr)!=EOF){
                                if(strcasecmp(symb,operand)==0){    
                                    strcat(mach_inst,addr);
                                    labfound=1;
                                    break;
                                }
                            }   
                            t_size-=3;
                    }else{
                        printf("ERROR: opcode not found\n");
                        strcpy(mach_inst,"00");
                    }
        }    
        fprintf(f3,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,mach_inst);
        if(t_size<0){
            sprintf(hex_str,"%02X",t_len);
            text_record[7]=hex_str[0];
            text_record[8]=hex_str[1];
            fprintf(f4,"%s\n",text_record);
            prev_start_addr+=t_len;
            sprintf(text_record,"T%06d00%s",prev_start_addr,mach_inst);
            t_len=strlen(mach_inst)/2;
            t_size=30-strlen(mach_inst)/2;
        }else{
            strcat(text_record,mach_inst);
            t_len+=strlen(mach_inst)/2;
        }
        fscanf(f1,"%s\t%s\t%s\t%s",address,label,opcode,operand);
    }
    sprintf(hex_str,"%02X",t_len);
    text_record[7]=hex_str[0];
    text_record[8]=hex_str[1];
    if(strlen(text_record)>9)
        fprintf(f4,"%s\n",text_record);

    fprintf(f3,"%s\t%s\t%s\t%s\t%s\n",address,label,opcode,operand,mach_inst);
    fprintf(f4,"E%06X",start);
}

void main(){
    f1=fopen("intermediate.txt","r");
    f2=fopen("optab.txt","r");
    f3=fopen("asmlist.txt","w");
    f4=fopen("output.txt","w");
    f5=fopen("symtab.txt","r");
    f6=fopen("length.txt","r");

    pass2();

    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);
    fclose(f5);
    fclose(f6);
}
