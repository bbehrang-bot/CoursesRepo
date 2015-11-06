double calc(int n,int m){
double x=0;
double i=1;
double j=1;
double nd = (double)n;
double md = (double)m;
double inner=0;
    for(i;i<=nd;i++){
        inner=0;
        for(j=1;j<=md;j++){

        inner= inner + (i/(j+2));

    }
     x= x+ cos(M_PI/i)*inner;
}
}