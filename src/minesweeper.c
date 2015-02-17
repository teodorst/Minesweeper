#include <curses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "minesweeper.h"
#include <unistd.h>
#define MIN(a,b) ( (a) < (b) ? (a) : (b) )
#define MAX(a,b) ( (a) > (b) ? (a) : (b) )
#define KEY_ESCAPE 27
void table ( char skull[][1000], int nr_rows,int nr_cols);
void panel2( int row, int col,int lungime, int latime, int mines, time_t start,int flags,time_t hit);
void panel1( int row, int col,int lungime, int latime, int mines,int flags,time_t start);
void menudraw(char meniu[][1000],int row1, int col1, int row2, int col2, int row3, int col3, int lungime , int latime);

void multiplehit(int x,int y, int table_rows, int table_cols, char skull[][1000], char base[][1000], char lovire[][1000]);

void multiplehit(int x, int y , int table_rows, int table_cols, char skull[][1000], char base[][1000], char lovire[][1000] ){

    init_pair(11,COLOR_BLACK,COLOR_GREEN);
    if(x>0 && y-3>=0) {
        skull[x-1][y-3]=base[x-1][y-3];//stanga sus

        attron(COLOR_PAIR(11));
        if(base[x-1][y-3]!='0')
            mvaddch(x+1,y-2,base[x-1][y-3]);//
        else 
            mvaddch(x+1,y-2,' ');
        mvaddch(x+1,y-1,'|');
        mvaddch(x+1,y-3,'|');
        attroff(COLOR_PAIR(11));
        if( base[x-1][y-3]!='0')
            lovire[x-1][y-3]='L';
    }

    if(x>=0 && y-1 >0 ){
        skull[x][y-3]=base[x][y-3];//stanga
        attron(COLOR_PAIR(11));
        if(base[x][y-3]!='0')
            mvaddch(x+2,y-2,base[x][y-3]);
        else 
            mvaddch(x+2,y-2,' ');
        mvaddch(x+2,y-1,'|');
        mvaddch(x+2,y-3,'|');
        attroff(COLOR_PAIR(11));
        if( base[x][y-3]!='0')
            lovire[x][y-3]='L';
    }
    if(x-1 >=0 ){
        skull[x-1][y]=base[x-1][y];//sus

        attron(COLOR_PAIR(11));
        if( base[x-1][y]!='0')
            mvaddch(x+1,y+1,base[x-1][y]);
        else 
            mvaddch(x+1,y+1,' ');
        mvaddch(x+1,y,'|');
        mvaddch(x+1,y+2,'|');
        attroff(COLOR_PAIR(11));
        if( base[x-1][y]!='0')
            lovire[x-1][y]='L';
    }
    if(x-1>=0 && y+3< 3*table_cols ){ 
        skull[x-1][y+3]=base[x-1][y+3];//dreapta sus

        attron(COLOR_PAIR(11));
        if(base[x-1][y+3]!='0')
            mvaddch(x+1,y+4,base[x-1][y+3]);
        else 
            mvaddch(x+1,y+4,' ');
        mvaddch(x+1,y+5,'|');
        mvaddch(x+1,y+3,'|');
        attroff(COLOR_PAIR(11));
        if( base[x-1][y+3]!='0')
            lovire[x-1][y+3]='L';
    }

    if(x >=0 && y+4 <= 3* table_cols){
        skull[x][y+3]=base[x][y+3];//dreapta

        attron(COLOR_PAIR(11));
        if(base[x][y+3] != '0')
            mvaddch(x+2,y+4,base[x][y+3]);
        else
            mvaddch(x+2,y+4,' ');
        mvaddch(x+2,y+5,'|');
        mvaddch(x+2,y+3,'|');
        attroff(COLOR_PAIR(11));
        if( base[x][y+3]!= '0')
            lovire[x][y+3]='L';
    }
    if(x+1<table_rows && y-3 >= 1){
        skull[x+1][y-3]=base[x+1][y-3];//stangajos

        attron(COLOR_PAIR(11));
        if( base[x+1][y-3] != '0')
            mvaddch(x+3,y-2,base[x+1][y-3]);
        else 
            mvaddch(x+3,y-2,' ');
        mvaddch(x+3,y-1,'|');
        mvaddch(x+3,y-3,'|');
        attroff(COLOR_PAIR(11));
        if( base[x+1][y-3]!= '0')
            lovire[x+1][y-3]='L';
    }
    if(x+1 < table_rows){
        skull[x+1][y]=base[x+1][y];//jos

        attron(COLOR_PAIR(11));
        if(base[x+1][y] != '0' )
            mvaddch(x+3,y+1,base[x+1][y]);
        else 
            mvaddch(x+3,y+1,' ');
        mvaddch(x+3,y+2,'|');
        mvaddch(x+3,y,'|');
        attroff(COLOR_PAIR(11));
        if ( base[x+1][y] != '0' )
            lovire[x+1][y]='L';

    }

    if(x+1 < table_rows && y+3 < 3*table_cols ){
        skull[x+1][y+3]=base[x+1][y+3];//dreapta jos

        attron(COLOR_PAIR(11));
        if(base[x+1][y+3]!= '0')
            mvaddch(x+3,y+4,base[x+1][y+3]);
        else 
            mvaddch(x+3,y+4,' ');
        mvaddch(x+3,y+5,'|');
        mvaddch(x+3,y+3,'|');
        attroff(COLOR_PAIR(11));
        if(base[x+1][y+3]!='0') 
            lovire[x+1][y+3]='L';

    }
}



void menudraw(char meniu[][1000],int row1,int col1,int row2, int col2, int row3, int col3, int lungime, int latime)
{
    int i;
    for( i = col1+1; i < col1 + lungime; i ++){
        mvprintw(row1,i,"_");
        meniu[row1][i]='_';
    }
    for( i = col1+1; i < col1 + lungime; i ++){
        mvprintw(row1+latime,i,"_");
        meniu[row1+latime][i]='_';
    }
    for( i = row1 +1 ; i <= row1 + latime; i ++){
        mvprintw(i,col1,"|");
        meniu[i][col1]='|';
    }
    for( i = row1+1 ; i <= row1 + latime; i ++){
        mvprintw(i,col1+lungime,"|");
        meniu[i][col1+lungime]='|';
    }
    mvaddstr(row1+(latime/2)+1,col1+(lungime/2)-3,"NEW GAME");

    for( i = col2+1; i < col2 + lungime; i ++){
        mvprintw(row2,i,"_");
        meniu[row2][i]='_';
    }
    for( i = col2+1; i <= col2 + lungime; i ++){
        mvprintw(row2+latime,i,"_");
        meniu[row2+latime][i]='_';
    }
    for( i = row2 +1 ; i <= row2 + latime; i ++){
        mvprintw(i,col2,"|");
        meniu[i][col2]='|';
    }
    for( i = row2 +1 ; i <= row2 + latime; i ++){
        mvprintw(i,col2 +lungime,"|");
        meniu[i][col2+lungime]='|';
    }
    mvaddstr(row2+(latime/2)+1,col2+(lungime/2)-3,"SETTINGS");

    for( i = col3+1; i < col3 + lungime; i ++){
        mvprintw(row3,i,"_");
        meniu[row3][i]='_';
    }
    for( i = col3+1; i <= col3 + lungime; i ++){
        mvprintw(row3+latime,i,"_");
        meniu[row3+latime][i]='_';
    }
    for( i = row3+1 ; i <= row3 + latime; i ++){
        mvprintw(i,col3,"|");
        meniu[i][col3]='|';
    }
    for( i = row3+1 ; i <= row3 + latime; i ++){
        mvprintw(i,col3 +lungime,"|");
        meniu[i][col3+lungime]='|';
    }
    mvaddstr(row3+(latime/2) +1 ,col3+(lungime/2)-1,"QUIT");
}



void panel1( int row, int col, int lungime, int latime, int mines,int flags,time_t start)
{
    int i,seconds;

    time_t tim;
    time(&tim);
    seconds=difftime(tim,start);
    mvprintw(row+1,col+1,"Ora&data:%s", ctime(&tim));
    mvaddstr(row+2,col+1,"                    ");
    mvaddstr(row+3,col+1,"                    ");
    mvprintw(row+2,col+1,"Numarul de mine:%d",mines-flags);  
    mvprintw(row+3,col+1,"TIME: %d:%d:%d", seconds/3600,seconds/60,seconds%60);
    for( i = col; i < col + lungime; i ++)
        mvprintw(row,i,"_");
    for( i = col; i < col + lungime; i ++)
        mvprintw(row+latime,i,"_");
    for( i = row+1 ; i <= row + latime; i ++)
        mvprintw(i,col,"|");
    for( i = row+1 ; i <= row + latime; i ++)
        mvprintw(i,col+lungime,"|");


}


void panel2( int row, int col, int lungime, int latime, int mines, time_t start,int flags,time_t hit)
{
    int i,seconds=0;

    time_t tim;
    time(&tim);
    int secund=0;
    secund=difftime(tim,hit);
    seconds=difftime(tim,start);
    mvprintw(row+1,col+1,"Ora&data:%s", ctime(&tim));
    mvaddstr(row+2,col+1,"                    ");
    mvaddstr(row+3,col+1,"                    ");
    mvaddstr(row+4,col+1,"                    ");
    mvprintw(row+2,col+1,"Numarul de mine:%d",mines-flags);  

    mvprintw(row+3,col+1,"TIME: %d:%d:%d",seconds/3600,seconds/60,seconds%60);
    mvprintw(row+4,col+1,"FIRST HIT: %d",secund); 
    for( i = col; i < col + lungime; i ++)
        mvprintw(row,i,"_");
    for( i = col; i < col + lungime; i ++)
        mvprintw(row+latime,i,"_");
    for( i = row+1 ; i <= row + latime; i ++)
        mvprintw(i,col,"|");
    for( i = row+1 ; i <= row + latime; i ++)
        mvprintw(i,col+lungime,"|");


}






void table ( char skull[][1000],int nr_rows,int nr_cols)
{
    int i , j;
    init_pair(7,COLOR_BLACK,COLOR_GREEN) ;
    init_pair(10,COLOR_BLACK,COLOR_YELLOW);
    for(i = 0; i < nr_rows; i++)
        for( j=0; j < 3 * nr_cols; j++)
            skull[i][j] = '|';


    for(i=0; i < nr_rows; i++)
        for( j=1; j< 3 * nr_cols; j += 3)
            skull[i][j] = '_';

    for( i = 2; i < 2 + nr_rows; i ++ )
        for( j = 1; j < (1 + 3 * nr_cols)  ; j ++)
            if(skull[i-2][j-1]=='_'){
                attron(COLOR_PAIR(10));
                mvaddch(i,j,skull[i-2][j-1]);
                attroff(COLOR_PAIR(10));
            }
            else { 
                attron(COLOR_PAIR(10));
                mvaddch(i,j,skull[i-2][j-1]);
                attroff(COLOR_PAIR(10));
            }
}





int main()
{
    /* Initializarea ferestrei si determinarea dimensiunilor acesteia. */
    WINDOW* wnd = initscr();
    int nrows, ncols,p,m,gata=0,runda=0;
    /* TODO: Implementara jocului. */
    getmaxyx(wnd, nrows, ncols);
    curs_set(0);
    clear();
    noecho();
    cbreak();
    start_color();// DEFINIRE CULORI!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    init_pair(1,COLOR_BLACK,COLOR_MAGENTA);
    init_pair(2,COLOR_BLACK,COLOR_RED);
    init_pair(3,COLOR_BLUE,COLOR_MAGENTA);
    init_pair(4,COLOR_BLUE,COLOR_RED);
    init_pair(6,COLOR_BLACK,COLOR_YELLOW); 
    init_pair(5,COLOR_BLUE,COLOR_YELLOW);
    init_pair(7,COLOR_BLACK,COLOR_GREEN);
    init_pair(8,COLOR_BLUE,COLOR_GREEN);
    keypad(wnd, TRUE);
    nodelay(wnd, TRUE);
    wbkgd(wnd,COLOR_PAIR(1)); 
    /* Caracterul citit. */
    int i,table_cols,table_rows, ccol , crow, xccol, xcrow,j,returnare=0 ;
    char skull[1000][1000],flags[1000][1000], meniu[1000][1000],lovire[1000][1000];
    table_cols=9;
    table_rows=9;
    for(i=0;i<1000;i++)
        for(j=0;j<1000;j++)
            meniu[i][j]='.';
    move(0,0);

    int mcol,mrow,xmrow,xmcol,esc_pressed,nmines,returnare2;
    mcol=xmcol=15;
    mrow=xmrow=4;
    int scol,srow,xsrow,xscol,s,returnare3;
    time_t start;
    time_t firsthit;
    time(&start);
    table_rows=9;
    table_cols=9;
    nmines=10;
    int steaguri=0;

    menudraw(meniu,2,2,8,2,14,2,11,3);
    while (1) { // meniul si miscarea prin el 
        menudraw(meniu,2,2,8,2,14,2,11,3);

        m = getch();
        if(runda==0) {
            m=' ';
            runda=1;
        }
        else    
            time(&start);
        refresh();
        esc_pressed=0;

        switch (tolower(m)) {


            case 'w':
            case KEY_UP:
                mrow = MAX(mrow - 6 , 4);
                break;  

            case 's':
            case KEY_DOWN:
                mrow = MIN(mrow + 6,16 );
                break;

            case ' ':
                if( mrow==10) // SETTINGS
                {
                    returnare3=0;
                    werase(wnd);
                    refresh();
                    scol=srow=xsrow=xscol=0;

                    returnare2=0;
                    while(1){
                        if(returnare2) 
                        {
                            werase(wnd);
                            refresh();
                            returnare3=1;
                            break;
                        }
                        for(i=0;i<4;i++)
                        {
                            mvaddch(4,12+i,' ');
                            mvaddch(7,12+i,' ');
                            mvaddch(10,12+i,' ');
                        }
                        mvaddstr(3,7,"Numarul de mine");
                        mvprintw(4,13,"%d", nmines);
                        mvaddch(4,10,'-');
                        mvaddch(4,17,'+');

                        mvaddstr(6,7,"Numarul de coloane "); 
                        mvprintw(7,13,"%d", table_cols);
                        mvaddch(7,10,'-');
                        mvaddch(7,17,'+');


                        mvaddstr(9,7,"Numarul de linii "); 
                        mvprintw(10,13,"%d", table_rows);
                        mvaddch(10,10,'-');
                        mvaddch(10,17,'+');

                        for(i=8;i<20;i++)
                        {
                            mvaddch(13,i,'_');
                            mvaddch(16,i,'_');
                        }
                        for(i=14;i<17;i++){
                            mvaddch(i,7,'|');
                            mvaddch(i,20,'|');
                        }
                        mvaddstr(15,10," Menu");

                        s=getch();
                        xsrow=srow;
                        xscol=scol;
                        switch (tolower(s)) {

                            case 'a':
                            case KEY_LEFT:
                                scol = MAX(scol - 1, 0);
                                break;

                            case 'd':
                            case KEY_RIGHT:
                                scol = MIN(scol + 1, ncols - 1);
                                break;

                            case 'w':
                            case KEY_UP:
                                srow = MAX(srow - 1, 0);
                                break;  

                            case 's':
                            case KEY_DOWN:
                                srow = MIN(srow + 1, nrows - 1);
                                break;
                            case ' ':
                                if(scol==17 && srow==4 && nmines<(table_rows* table_cols-1) && nmines>=1 )
                                    nmines++;
                                if(scol==10 && srow==4 && nmines && nmines>=1 && nmines<table_rows*table_cols)
                                    nmines--;
                                if(scol == 17 && srow==7 && table_cols  >1 && table_cols <30)
                                    table_cols++;
                                if(scol == 10 && srow==7 && table_cols >1 && table_cols<30)
                                    table_cols--;
                                if(scol==17 && srow==10 && table_rows >1 && table_rows < 30)
                                    table_rows++;
                                if(scol==10 && srow==10 && table_rows > 1 && table_rows <30)
                                    table_rows--;
                                if( nmines > table_rows * table_cols )
                                    nmines=table_rows*table_cols-1;

                                if(scol>=8 && scol<20 && srow >=13 && srow<=17)
                                    returnare2=1;
                                break;



                        }
                        mvaddch(xsrow,xscol,' ');
                        attron(COLOR_PAIR(3));
                        mvaddch(srow,scol,ACS_DIAMOND);
                        attroff(COLOR_PAIR(3));
                    }
                    if(returnare3)
                        break;
                }

                if( mrow==4){ //NEW GAME
                    werase(wnd);
                    refresh();
                    int mines=0;     
                    wbkgd(wnd,COLOR_PAIR(2));

                    attron(COLOR_PAIR(6));
                    table(skull,table_rows,table_cols);
                    attroff(COLOR_PAIR(6));
                    int i,j,marcate=0,ok=0,final=0;;
                    for(i=0;i<table_rows;i++)
                        for(j=0;j<3*table_cols;j++)
                            lovire[i][j]=skull[i][j];

                    refresh();
                    move(table_rows,table_cols);
                    crow=table_rows/2+2;
                    ccol=3*table_cols/2+1;
                    xccol=0;
                    xcrow=0;
                    char base[1000][1000]={'.'};
                    move(table_rows/2+2,3*table_rows/2+1);
                    mvaddch(table_rows/2+2,3*table_cols/2+1,ACS_DIAMOND);

                    for(i=0; i<= table_rows; i++)
                        for(j=0;j < 3 * table_cols; j++)
                            base[i][j] = '.';

                    for(i=0; i <= table_rows; i++)
                        for(j=1;j < 3 * table_cols; j += 3) 
                            base[i][j]=48;

                    int c,l,k,g;
                    srand(time(NULL));

                    returnare=esc_pressed=0;
                    int cntx=0,cnty=0,cntflag=0;
                    cntx=0;
                    while(1) 
                    {
                        cnty=0;
                        cntflag=0;
                        if (cntx ) panel2(4,100,35,5,nmines,start,steaguri,firsthit);
                        else 
                        {
                            panel1(4,100,35,5,nmines,steaguri,start);
                            time(&firsthit);
                        }

                        p = getch();  



                        if(esc_pressed || returnare ){
                            werase(wnd);
                            wbkgd(wnd,COLOR_PAIR(1));
                            refresh();
                            break;
                        }
                        returnare=0;
                        esc_pressed=0; 
                        switch( tolower(p))
                        {
                            case 'a':
                            case KEY_LEFT:

                                ccol = MAX(ccol - 3,0);
                                if( ccol == 0) 
                                    ccol=2;
                                break;
                            case 'd':
                            case KEY_RIGHT:
                                ccol = MIN(ccol + 3, ncols-1);
                                if( ccol== ncols-1)
                                    ccol=ncols-3;
                                break;

                            case 'w':
                            case KEY_UP:
                                crow = MAX(crow - 1, 0);
                                break;

                            case 's':
                            case KEY_DOWN:
                                crow = MIN(crow+1, nrows -1);
                                break;

                            case ' ':
                                move(table_rows/2+2,3*table_cols/2-1);

                                if(cntx == 0 ){
                                    while (mines < nmines) // GENERARE MINE
                                    {
                                        move(table_rows/2+2,3*table_cols/2-1);
                                        l = rand() % (table_rows) ;
                                        c = rand() % ( 3 * table_cols );
                                        if(base[l][c] == 48 && ((l+2)!=crow && (c+2)!=ccol) )
                                        { 
                                            base[l][c] = 'M';
                                            mines++;
                                        }
                                    }

                                    for(i=-1;i<table_rows;i++){
                                        for(j=1;j< 3* table_cols; j += 3 )
                                        {
                                            if(i-1 >= 0 && base[i-1][j] == 'M' && base[i][j] != 'M') 
                                                base[i][j] += 1;
                                            if(i-1 >= 0 && j+3 < 3*table_cols && base[i-1][j+3] == 'M' && base[i][j] != 'M' ) 
                                                base[i][j] += 1;
                                            if(i-1 >= 0 && j-3 > 0  && base[i-1][j-3] == 'M' && base[i][j] != 'M' )
                                                base[i][j] +=1 ;
                                            if( j-3 > 0 && base[i][j-3]== 'M' && base[i][j] != 'M' )
                                                base[i][j] += 1;
                                            if( j +3 < 3 * table_cols && base[i][j+3] == 'M' && base[i][j] != 'M')
                                                base[i][j] += 1;

                                            if(i+1< table_rows && base[i+1][j] == 'M' && base[i][j] != 'M') 
                                                base[i][j] += 1;
                                            if(i+1< table_rows && j+3 < 3*table_cols && base[i+1][j+3] == 'M' && base[i][j] != 'M' ) 
                                                base[i][j] += 1;
                                            if(i+1< table_rows && j-3 > 0  && base[i+1][j-3] == 'M' && base[i][j] != 'M')
                                                base[i][j] += 1;
                                        }
                                    }

                                    lovire[crow-2][ccol-1]='L';

                                }
                                if( crow >=2 && crow < (2 + table_rows))
                                    if(ccol >1 && ccol < ( 1 + 3 * table_cols))
                                        if( (base[crow-2][ccol-1] >= 48 && base[crow-2][ccol-1] <= 57))
                                        {   
                                            attron(COLOR_PAIR(7));
                                            mvaddch(crow,ccol-1,'|');
                                            mvaddch(crow,ccol+1,'|');
                                            mvaddch(crow,ccol,base[crow-2][ccol-1]);
                                            if(base[crow-2][ccol-1] != '0') 
                                                skull[crow-2][ccol-1] = base[crow-2][ccol-1];
                                            lovire[crow-2][ccol-1] = 'L';
                                            if(base[crow-2][ccol-1] == '0') 
                                            {   
                                                gata=0; 
                                                multiplehit(crow-2,ccol-1,table_rows,table_cols,skull,base, lovire);
                                                while(!gata)
                                                { 
                                                    gata=1;
                                                    for(i=0;i<table_rows;i++)
                                                        for(j=1;j<3*table_rows;j += 3)
                                                            if(skull[i][j]== '0' && lovire[i][j]=='_')
                                                            {
                                                                multiplehit(i,j,table_rows,table_cols,skull,base,lovire);
                                                                lovire[i][j]='L';
                                                                refresh();
                                                                gata=0;
                                                            }

                                                }



                                            }

                                        } 

                                if( base[crow-2][ccol-1] == 'M' )
                                {
                                    for(i=0;i<table_rows;i++)
                                        for(j=0;j<3*table_cols;j++)
                                            if(base[i][j]=='M')
                                                mvaddch(i+2,j+1,'M');

                                    refresh();
                                    mvaddstr( 20,30 , "YOU LOST!");
                                    refresh();
                                    usleep(2000000);
                                    wbkgd(wnd,COLOR_PAIR(1));
                                    clear();
                                    werase(wnd);

                                    mvaddstr( 20,30 , "YOU LOST!");
                                    refresh();
                                    usleep(2000000);
                                    returnare=1;

                                }
                                cntx++;
                                break;
                            case 'm':
                                if( crow >=2 && crow <= (2 + table_rows))
                                    if(ccol >= 1 && ccol <= ( 1 + 3 * table_cols))
                                    {
                                        if( skull[crow-2][ccol-1] == '_'){ 
                                            skull[crow-2][ccol-1] = 97;
                                            cntflag++;
                                        }
                                        else if ( skull[crow-2][ccol-1] == 97){
                                            skull[crow-2][ccol-1] = '_';
                                            cntflag--;
                                        }
                                        if( base[crow-2][ccol-1] == 'M' && skull[crow-2][ccol-1] == 97) 
                                            mines--;
                                        if( base[crow-2][ccol-1] == 'M' && skull[crow-2][ccol-1] != 97)
                                            mines+=1;

                                    }

                                break;           

                            case KEY_ESCAPE:
                                esc_pressed = 1;
                                break;
                        }
                        move(xcrow,xccol);
                        if( (xcrow-2) >= 0 && xcrow-2 < table_rows && xccol-1 >= 0 && xccol-1< 3* table_cols )
                        {   
                            if(lovire[xcrow-2][xccol-1] == 'L' )
                                attron(COLOR_PAIR(7));
                            else 
                                attron(COLOR_PAIR(6));
                            if( skull[xcrow-2][xccol-1] == '|')
                                addch('|');
                            if( skull[xcrow-2][xccol-1] == '_')
                                addch('_');
                            if( skull[xcrow-2][xccol-1] > 48 && skull[xcrow-2][xccol-1] <= 57 )
                                addch(skull[xcrow-2][xccol-1]);
                            if( skull[xcrow-2][xccol-1] == 48 )
                                addch(' ');
                            if( skull[xcrow-2][xccol-1] == 'M')
                                addch('M');
                            if( skull[xcrow-2][xccol-1] == 97)
                                addch(ACS_CKBOARD);
                            if(lovire[xcrow-2][xccol-1] == 'L' )
                                attroff(COLOR_PAIR(7));
                            else 
                                attroff(COLOR_PAIR(6));

                        }
                        else
                            addch(' ');


                        move(crow,ccol);
                        if(crow-2>=0 && crow-2<table_rows && ccol-1>=0 && ccol<3*table_cols){
                            if( lovire[crow-2][ccol-1] != 'L')
                            {
                                attron(COLOR_PAIR(5));
                                addch(ACS_DIAMOND);
                                attroff(COLOR_PAIR(5));
                            }
                            else
                            { 
                                init_pair(12,COLOR_BLACK,COLOR_GREEN);
                                attron(COLOR_PAIR(8));
                                addch(ACS_DIAMOND);
                                attroff(COLOR_PAIR(8));
                            }
                        }
                        else {
                            attron(COLOR_PAIR(4));
                            addch(ACS_DIAMOND);
                            attroff(COLOR_PAIR(4));
                        }
                        xcrow = crow;
                        xccol = ccol;

                        for(i=0;i<table_rows;i++)
                            for(j=0;j<(3*table_cols);j++)
                                if(skull[i][j] == 97   && base[i][j] == 'M')
                                    cnty++;
                        marcate =0;
                        cntflag=0;
                        steaguri=0;
                        for(i=0;i<table_rows;i++)
                            for(j=0;j<3*table_cols;j++){
                                if(lovire[i][j]=='L')
                                    marcate++;
                                if( skull[i][j] == 97 && base[i][j]=='M' )
                                    cntflag++;
                                if( skull[i][j] == 97 ) 
                                    steaguri++;
                            }
                        final=0;
                        if( marcate==table_rows*table_cols-nmines && cntflag==nmines)
                            final=1;

                        if( final==1 )
                        {
                            clear();
                            refresh();
                            mvaddstr(20,30,"CONGRATULATIONS!!!");
                            refresh();
                            usleep(1000000);

                            returnare=1;
                            wbkgd(wnd,COLOR_PAIR(1));
                        }

                    }
                }


                if(mrow==16) //EXIT

                {
                    clear();
                    werase(wnd);
                    refresh();
                    mvaddstr(20,20,"GOODBYE");
                    refresh();
                    usleep(2000000);
                    endwin();
                    return 0;
                }
                break;


            case KEY_ESCAPE:
                esc_pressed = 1;
                break;
        }
        move(xmrow,xmcol);
        if(meniu[xmrow][xmcol] == '|')
            mvaddch(xmrow,xmcol,'|');
        if(meniu[xmrow][xmcol] == '_')
            mvaddch(xmrow,xmcol,'_');
        if(meniu[xmrow][xmcol] == '.')
            mvaddch(xmrow,xmcol,' ');
        xmcol=mcol;
        xmrow=mrow;
        move(mrow,mcol);
        attron(COLOR_PAIR(3));
        addch(ACS_LARROW);
        attroff(COLOR_PAIR(3));

    }


    endwin();
    return 0;
}
