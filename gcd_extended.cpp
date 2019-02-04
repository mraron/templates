int gcd(int a, int b, int* x, int* y) {
	if(a==0) {
		*x=0;
		*y=1;
		return b;
	}
	
	int xp, yp;
	int res=gcd(b%a, a, &xp, &yp);
	*x=yp-(b/a)*xp;
	*y=xp;
	
	return res;
}
