enum operations{
   POP=-50,BREAK,CONTINUE,REPEAT
};

struct DO
{
    enum operations op;
    int stance;
};
int run(int moves[], int movesLen, int res[], int resLen)
{




struct DO m[4][4];
m[0][0].stance = 1;
m[0][0].op = POP;
m[0][1].stance = 1;
m[0][1].op = 1;
m[0][2].stance = 1;
m[0][2].op = BREAK;
m[0][3].stance = 0;
m[0][3].op = 6;
m[1][0].stance = 2;
m[1][0].op = POP;
m[1][1].stance = 0;
m[1][1].op = CONTINUE;
m[1][2].stance = 2;
m[1][2].op = 2;
m[1][3].stance = 3;
m[1][3].op = REPEAT;
m[2][0].stance = 1;
m[2][0].op = BREAK;
m[2][1].stance = 3;
m[2][1].op = 4;
m[2][2].stance = 1;
m[2][2].op = BREAK;
m[2][3].stance = 3;
m[2][3].op = 3;
m[3][0].stance = 1;
m[3][0].op = BREAK;
m[3][1].stance = 0;
m[3][1].op = 7;
m[3][2].stance = 2;
m[3][2].op = 5;
m[3][3].stance = 3;
m[3][3].op = CONTINUE;
int index=0;
int currentState=0;

int column=0;
int i=0;int j=0;
int inIndex=0;
int b[5]={-1,-1,-1,-1,-1};
    for(i=0;i<movesLen;i++)
    {

        if(whatToDo(moves[i],res,resLen,&currentState,m,&index)== 0)
        {
                res[index]=0;
                return index;
        }

       j=currentState;
    }
return index;
}
int whatToDo(int move,int res[], int resLen,int *stances,struct DO m[4][4],int *index)
{
    int k=index;
    int i=0;
    int mvmv = *stances;
    int b[5]={-5,-5,-5,-5,-5};

    struct DO infunc;
    struct DO testValues;
    testValues.op = m[3][1].op;
    switch(move)
    {
        case 18:
        {
            infunc.stance=m[*stances][0].stance;
            infunc.op = m[*stances][0].op;
            *stances = infunc.stance;
               break;

        }

        case 30:
        {
            infunc.stance=m[*stances][1].stance;
            infunc.op = m[*stances][1].op;
            *stances = infunc.stance;
  break;
        }

        case 45:
        {
            infunc.stance=m[*stances][2].stance;
            infunc.op = m[*stances][2].op;
            *stances = infunc.stance;
      break;
        }

        case 315:
        {
            infunc.stance=m[*stances][3].stance;
            infunc.op = m[*stances][3].op;
            *stances = infunc.stance;
  break;
        }
        default :
            return 0;
    }
    switch(infunc.op)
    {
        case POP:
            {
                if(*index>0 && *index<resLen)
                {
                    (*index)--;
                    res[*index]=0;
                    int c = *index;

                }
                 break;
            }

        case CONTINUE:
            {
                return 1;
                break;
            }
        case REPEAT:
            {
                whatToDo(move,res,resLen,stances,m,index);
                break;
            }
        case BREAK:
            {
                return 0;
                break;
            }
        default:
            {
                res[*index]=infunc.op;

                int u = res[*index];
                if(*index<resLen)
                {
                    (*index)++;

                }
                else
                    return 0;
            }


    }

}
