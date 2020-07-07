#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "data.h"
#define BUF_SIZE 16

typedef struct s2{
char label[16];
char ad[8];
}NODE2;


    /* node array for label-strings **/
    NODE2 label[8] =
    {{"0","0"}, {"0","0"}, {"0","0"},
     {"0","0"}, {"0","0"}, {"0","0"},
      {"0","0"}, {"0","0"}};

    /* find command and return [i] of struct  **/
    int find(char *str , NODE *p, int clen)
    {
        for (int i = 0; i < clen; i++)
        {
            if( strcmp( str, (char *)(p[i].exp) ) ==0 ) {
                return i;
            }

        }
        return 99 ;
    }

    /* for label struct **/
     int find2(char *str , NODE2 *p, int clen)
    {
        for (int i = 0; i < clen; i++)
        {
            if( strcmp( str, (char *)(p[i].label) ) ==0 ) {
                return i;
            }

        }
        return 99 ;
    }

int main()
{
/*********************************************************************************/
/**  REQUIREMENTS                                                                */
/**  user-variables: lower-case only !!!                                         */
/*********************************************************************************/
/*         PART 1 OF PROGRAM                                                     */
/*         ASSEMBLY TO PURE ASSEMBLY                                             */
/*         in.txt      INPUT file with blanks, comments, labels, user-vars      **/
/*         nobl.txt    OUTPUT file with no blanks, no comments                  **/
/*         outas.txt   OUTPUT file with no pre-defined constants                **/
/*         outas2.txt  FULL CLEAR OUTPUT file with no loop-labels, no user-vars **/
/*********************************************************************************/

    int vari = 16; /* 1st start adress of user-variables, then increments  **/
    int nline = 0 ; /* count of file-lines **/
    char temp[32] ; /* buffers for string **/
    char out[32];                  /* out **/
    char buf[16] ;                /* atoi **/
    int num; /* var for return find function **/
    int  i_label=0; /* start num++ for record to label-node **/


    FILE *f , *outas; /* input-output files pointers, changed in 2-nd loop  **/

    /* zero-loop delete blanks and comments **/

      char temp0[128];
      FILE *f0 = fopen("in.txt", "r");
      FILE *nobl ;

       while (fgets(temp0 , 127 ,f0) != 0 ) {


           for(int i=0, j=0;  ; i++){

              if( temp0[i] == '\n' || temp0[i] == '\0' || temp0[i] =='/' || temp0[i] == -1  ) {
                temp0[j] = '\0';
                break;
            }

              if ( temp0[i] != ' ' && temp0[i] != '\t' ) temp0[j++] = temp0[i] ;
        }
    if( temp0[0] != '\0' ) {

     nobl = fopen("nobl.txt", "a+");
     fprintf(nobl, "%s", temp0 );
     fprintf(nobl, "%c", '\n');
     fclose(nobl);
    }

    }
         fclose(f0);

    /* end zero-loop create input for 1-st main-loop **/

  for( int mloop=0 ; mloop < 2 ; mloop++ ) { /*main loop **/

    if( mloop == 0 ) {
      f = fopen("nobl.txt", "r");
    } else {
    f = fopen("outas.txt", "r");
    }

     while (fgets(temp , 127 ,f) != 0 ) { /* read line from file **/

        if(temp[0] == '@' ) { /* check 1st symbol sobaka **/

        for(int i=1, j=0;  ; i++){

        if( temp[i] == '\n' || temp[i] == '\0' || temp[i] == -1  ) {
        temp[j] = '\0' ;
        break;
      }
        temp[j++] = temp[i] ;
    }

    printf("line-%d : %s\n", nline, temp);

        if(mloop==0) { /* 1-st main loop **/

           if ( (num = find(temp, pre_def ,23)) != 99 ) {
            strcpy(out , "@") ;
           // printf("num : %d\n", num);
            strcat( out , pre_def[ num ].code ) ;
           }else {
            strcpy(out , "@") ;
             strcat(out , temp ) ;

                  num =  find2( temp , label ,8 ) ;
                  if( (num == 99) && isalpha(temp[0]) && (temp[0] >= 97) && (temp[0] <= 122) ) {

                    strcpy( label[ i_label ].label ,temp )  ;
                     itoa(vari++ ,buf,10);
                    strcpy( label[ i_label ].ad , buf ) ;
                    i_label++;
                        }
                  }

        }else { /* 2-st main loop **/

        num = find2( temp , label ,8 )  ;
           if(  (num != 99) && ( strcmp( label[ num ].ad , "0" ) != 0) ) {
            strcpy(out , "@") ;
            strcat(out ,  label[ num ].ad ) ;

          }else {
                  strcpy(out , "@") ;
                  strcat(out , temp ) ;


          }
        }
      }

        else if(temp[0] == '(' ) { /* check 1st symbol open-brace **/

        for(int i=1, j=0;  ; i++){
        if( temp[i] == ')'  ) {
        temp[j] = '\0' ;
        break;
        }
        else {
        temp[j++] = temp[i] ;
            }
          }

           strcpy( label[ i_label ].label ,temp ) ;
           //nline++;
            itoa(nline, buf, 10) ;
           strcpy( label[ i_label ].ad , buf ) ;
           i_label++;

           continue;

           }
        else { /* default: copy input string to output buffer **/
        strcpy( out , temp ) ;

  if( mloop == 0 ) {
     outas = fopen("outas.txt", "a+");
  }else {
    outas = fopen("outas2.txt", "a+");
  }

     fprintf(outas, "%s", out );
     fclose(outas);

     nline++;

            continue;
  }

  if( mloop == 0 ) {
     outas = fopen("outas.txt", "a+");
  }else {
    outas = fopen("outas2.txt", "a+");
  }
     fprintf(outas, "%s", out );
     fprintf(outas, "%c", '\n');
     fclose(outas);


     nline++;

  }

  nline = 0;
  num = 0;
  i_label = 0;
}

/*********************************************************************************/
/**         PART 2 OF PROGRAM                                                    */
/**         ASSEMBLY TO MACHINE CODE                                             */
/**         outas2.txt           INPUT file                                      */
/**         out_bi.txt           OUTPUT file (new lines include for readability) */
/*********************************************************************************/

/* convert int to binary code of 16 cells  **/
char *int2bin(int a, char *buffer, int buf_size) {
    buffer += (buf_size - 1);

    for (int i = 15; i >= 0; i--) {
        *buffer-- = (a & 1) + '0';
        a >>= 1;
    }
    return buffer;
}

  char binbuf[BUF_SIZE];
  char dest[4] , compc[4] ,jump[5] ;
  jump[0 ] = '\0';
  char final[16];
  binbuf[16] = '\0';

  f = fopen("outas2.txt", "r");
  FILE *f2;
  int flag=0;

/* read line from outas2.txt without names,labels **/
  while (fgets(temp , 9 ,f) != 0 ) {

    if(temp[0] == '@' ) {

        for(int i=1, j=0;  ; i++){
              if( temp[i] == '\n' || temp[i] == '\0' || temp[i] == -1  ) {
                temp[j] = '\0';
                break;
            }
            temp[j++] = temp[i];
        }

    //printf("%s\n", temp);
    FILE *f2 = fopen("out_bi.txt", "a+");
    int2bin(atoi(temp), binbuf, BUF_SIZE);
    fprintf(f2, "%s", binbuf );
    fprintf(f2, "%c", '\n');
    fclose(f2);
    }else {
        int i=0;

        for(int ii=0; ;ii++){
          if(temp[ii] == '=') break;
          else if(temp[ii] == ';') {
                flag = 1;
                break;
        }
    }

        if(flag == 0)  {
       for(int j=0;  ; i++){
            if  (temp[i] == '=')  {
                dest[j] = '\0';
                break;
            }else {
             dest[j++] = temp[i];
            }
        }
    }else {

          for(int j=0;  ; i++){
             if ( temp[i] == ';')  {
                compc[j] = '\0';
               // printf("break temp: %s %d\n", temp, i);
                break;
             }
             compc[j++] = temp[i];

          }
    }

    if(temp[i] == '=') {
        i++;

        for(int j=0;  ; i++){

            if(temp[i] == '\0' || temp[i]=='\n') {
              compc[j] = '\0';
              break;
            }

             else compc[j++] = temp[i];
        }
    }

    /*else {
        compc[j] = '\0';
        goto jump;
    }
    **/
    //jump:

    if(temp[i] == ';'){
        i++;
        for(int j=0; ; i++){
                if(  temp[i] == '\0' || temp[i] == '\n'  ) {
                    jump[j] = '\0';
                     // printf("jump is: %s\n", jump);
                    break;
                }
             jump[j++] = temp[i];

      }
    }

           strcpy(final ,"111");

            int ti, a;
            char aa[2];
           if(  ti = find(compc, comp ,18) != 99 )a=0;
              else {ti = find(compc, comp_1 ,10); a=1;} ;
           printf("ti: %d\n", ti);
           itoa(a,aa,10) ;

            strcat(final, aa );

          if(flag==0) {
                if(a==0) {
                strcat(final ,comp[ti].code ) ;
                strcat(final , dest_code[ find(dest, dest_code, 8) ].code);
                }else {
                      strcat(final ,comp_1[ti].code ) ;
                      strcat(final , dest_code[ find(dest, dest_code, 8) ].code);
                }
          }else {

               if(  (ti = find(compc, comp ,18)) != 99 ) {
                   strcat(final ,comp[ ti ].code ) ;
                   strcat(final , "000");
               }
              else {
                    strcat(final ,comp_1[ find(compc, comp_1 ,10) ].code ) ;
                    strcat(final , "000");
              }

        }

          if(jump[0] != '\0') strcat(final , jump_code[ find(jump, jump_code,8)].code);
          else  strcat(final , "000");

    FILE *f2 = fopen("out_bi.txt", "a+");
    fprintf(f2, "%s", final);
    fprintf(f2, "%c", '\n');
    fclose(f2);

    }

         jump[0]='\0';
         dest[0] = '\0';
         flag =0 ;

  }



fclose(f);

/******************** END PROGRAM **************************************************/

    return 0;
}
